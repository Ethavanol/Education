
import numpy as np
import cv2
import os
import pickle
import sys
import math

import matplotlib.pyplot as plt

from torchvision.io import read_image
import torch.nn as nn
import torch.nn.functional as F
import torch
from torch.utils.data import Dataset
from torchvision import transforms
import torchvision.utils as vutils

from VideoSkeleton import VideoSkeleton
from VideoReader import VideoReader
from Skeleton import Skeleton
from GenVanillaNN import * 



class Discriminator(nn.Module):
    def __init__(self, ngpu=0):
        super(Discriminator, self).__init__()
        self.ngpu = ngpu
        self.model = nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=4, stride=2, padding=1, bias=False),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(64, 128, kernel_size=4, stride=2, padding=1, bias=False),
            nn.BatchNorm2d(128),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(128, 256, kernel_size=4, stride=2, padding=1, bias=False),
            nn.BatchNorm2d(256),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(256, 512, kernel_size=4, stride=2, padding=1, bias=False),
            nn.BatchNorm2d(512),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(512, 1, kernel_size=4, stride=1, padding=0, bias=False),
            nn.Sigmoid()
        )
        # print(self.model)

    def forward(self, input):
        return self.model(input)



class GenGAN():
    """ class that Generate a new image from videoSke from a new skeleton posture
       Fonc generator(Skeleton)->Image
    """
    def __init__(self, videoSke, loadFromFile=False):
        self.netG = GenNNSkeToImage()
        self.netD = Discriminator()
        self.device = torch.device("cuda:0" if (torch.cuda.is_available() and ngpu > 0) else "cpu")
        self.filenameGenerator = 'DanceGenGANGenerator.pth'
        self.filenameDiscriminator = 'DanceGenGANDiscriminator.pth'
        self.directory = 'data/weights/'
        tgt_transform = transforms.Compose(
                            [transforms.Resize((64, 64)),
                            transforms.CenterCrop(64),
                            transforms.ToTensor(),
                            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),
                            ])
        self.dataset = VideoSkeletonDataset(videoSke, ske_reduced=True, target_transform=tgt_transform)
        self.dataloader = torch.utils.data.DataLoader(dataset=self.dataset, batch_size=32, shuffle=True)
        pathGenerator = self.directory + self.filenameGenerator
        pathDiscriminator = self.directory + self.filenameDiscriminator
        if loadFromFile: 
            if os.path.isfile(pathGenerator):
                print("GenGAN Generator: Load=", pathGenerator, "   Current Working Directory=", os.getcwd())
                self.netG = torch.load(pathGenerator)
            if os.path.isfile(pathDiscriminator):
                print("GenGAN Discriminator: Load=", pathDiscriminator, "   Current Working Directory=", os.getcwd())
                self.netD = torch.load(pathDiscriminator)
        else :
            weights_init(self.netG)
            weights_init(self.netD)


    def train(self, n_epochs=20):
        criterion = nn.BCELoss()
        optimizerD = torch.optim.Adam(self.netD.parameters(), lr=0.0002, betas=(0.5, 0.999))
        optimizerG = torch.optim.Adam(self.netG.parameters(), lr=0.0002, betas=(0.5, 0.999))

        real_label = 1.
        fake_label = 0.

        G_losses = []
        D_losses = []
        iters = 0
        print("Starting Training Loop...")
        # For each epoch
        for epoch in range(n_epochs):
            # For each batch in the dataloader
            for i, data in enumerate(self.dataloader, 0): # i,(ske,img)

                real_img = data[1].to(self.device)# data[0] is for skeleton, here 1 is for image linked to the skeleton
                b_size = real_img.size(0)
                ############################
                # (1) Update D network: maximize log(D(x)) + log(1 - D(G(z)))
                ###########################
                ## Train with all-real batch
                self.netD.zero_grad()
                # Format batch
                label = torch.full((b_size,), real_label, dtype=torch.float, device=self.device)
                output = self.netD(real_img).view(-1)
                errD_real = criterion(output, label)
                errD_real.backward()
                D_x = output.mean().item()

                ## Train with all-fake batch
                # Generate batch of latent vectors : 100 is the size of the latent vector (i.e. size of generator input))
                #noise = torch.randn(b_size, 100, 1, 1, device=self.device)
                #c'est là la différence: nous on ne génère pas de fake avec du bruit, mais une image à partir d'un squelette
                # Generate fake image batch with Generator taking a skeleton as Generator input
                noise = torch.randn(b_size, 26, 1, 1, device=self.device)
                fake = self.netG(noise) #self.generate(ske.fromImage(data[1]))#self.generate(data[0]) #self.netG(noise) self.generate(ske.fromImage(data[1]))
                label.fill_(fake_label)
                output = self.netD(fake.detach()).view(-1)
                errD_fake = criterion(output, label)
                errD_fake.backward()
                D_G_z1 = output.mean().item()
                errD = errD_real + errD_fake
                optimizerD.step()

                ############################
                # (2) Update G network: maximize log(D(G(z)))
                ###########################
                #########################
                # And we gotta update the generators weights so we have ressemblant generated images
                #########################
                self.netG.zero_grad()
                image_generated = self.netG(data[0])
                loss_ressemblance = nn.MSELoss()(image_generated, real_img)

                label.fill_(real_label)  # fake labels are real for generator cost
                output = self.netD(fake).view(-1)
                errG_discrim = criterion(output, label)
                D_G_z2 = output.mean().item()

                errG = errG_discrim + 100 * loss_ressemblance
                errG.backward()
                optimizerG.step()

                # Output training stats
                if i % 50 == 0:
                    print('[%d/%d][%d/%d]\tLoss_D: %.4f\tLoss_G: %.4f\tD(x): %.4f\tD(G(z)): %.4f / %.4f'
                        % (epoch, n_epochs, i, len(self.dataloader),
                            errD.item(), errG.item(), D_x, D_G_z1, D_G_z2))

                # Save Losses for plotting later
                G_losses.append(errG.item())
                D_losses.append(errD.item())

                ############################
                # (3) Update G network: so it generates a ressembling image from a skeleton
                ###########################

        print("Training finish")

        if not os.path.exists(self.directory):
            print(f"Creating directory: {self.directory}")
            os.makedirs(self.directory)
        pathGenerator = self.directory + self.filenameGenerator
        pathDiscriminator = self.directory + self.filenameDiscriminator
        torch.save(self.netG, pathGenerator)
        torch.save(self.netG, pathDiscriminator)
        print(f"Modèle du Générateur sauvegardé à la fin de l'époque {epoch+1} dans : ", pathGenerator)
        print(f"Modèle du Discriminateur sauvegardé à la fin de l'époque {epoch+1} dans : ", pathDiscriminator)

        plt.figure(figsize=(10,5))
        plt.title("Generator and Discriminator Loss During Training")
        plt.plot(G_losses,label="G")
        plt.plot(D_losses,label="D")
        plt.xlabel("iterations")
        plt.ylabel("Loss")
        plt.legend()
        plt.show()
        

    def generate(self, ske): 
        """ generator of image from skeleton """
        ske_t = torch.from_numpy( ske.__array__(reduced=True).flatten() )
        ske_t = ske_t.to(torch.float32)
        ske_t = ske_t.reshape(1,Skeleton.reduced_dim,1,1) # ske.reshape(1,Skeleton.full_dim,1,1)
        normalized_output = self.netG(ske_t)
        res = self.dataset.tensor2image(normalized_output[0])
        return res


def weights_init(m):
    for layer in m.model.modules():
        if isinstance(layer, nn.Conv2d):
            print(m.__class__.__name__, "init conv")
            # Initialisation de He (Kaiming) pour les convolutions
            nn.init.kaiming_normal_(layer.weight, mode='fan_in', nonlinearity='leaky_relu')
            if layer.bias is not None:
                nn.init.constant_(layer.bias, 0)
        elif isinstance(layer, nn.BatchNorm2d):
            print(m.__class__.__name__, "init batchnorm")
            # Initialisation des poids de BatchNorm
            nn.init.normal_(layer.weight, mean=1.0, std=0.02)
            nn.init.constant_(layer.bias, 0)



if __name__ == '__main__':
    force = False
    n_epoch = 200 # 200
    train = 1 #False
    if len(sys.argv) > 1:
        filename = sys.argv[1]
        if len(sys.argv) > 2:
            force = sys.argv[2].lower() == "true"
    else:
        filename = "tp/dance/data/taichi1.mp4"
    print("GenGAN: Current Working Directory=", os.getcwd())
    print("GenGAN: Filename=", filename)

    targetVideoSke = VideoSkeleton(filename)

    #if False:
    if train:    # train or load
        # Train
        gen = GenGAN(targetVideoSke, loadFromFile=False)
        gen.train(n_epoch)
    else:
        gen = GenGAN(targetVideoSke, loadFromFile=True)    # load from file        


    for i in range(targetVideoSke.skeCount()):
        image = gen.generate(targetVideoSke.ske[i])
        #image = image*255
        nouvelle_taille = (256, 256) 
        image = cv2.resize(image, nouvelle_taille)
        cv2.imshow('Image', image)
        key = cv2.waitKey(-1)
