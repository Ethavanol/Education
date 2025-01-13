import numpy as np
import cv2
import os
import pickle
import sys
import math

from PIL import Image
import matplotlib.pyplot as plt
from torchvision.io import read_image

import torch.nn as nn
import torch.nn.functional as F
import torch
from torch.utils.data import Dataset
from torchvision import transforms

#from tensorboardX import SummaryWriter

from VideoSkeleton import VideoSkeleton
from VideoReader import VideoReader
from Skeleton import Skeleton

torch.set_default_dtype(torch.float32)


class SkeToImageTransform:
    def __init__(self, image_size):
        self.imsize = image_size

    def __call__(self, ske):
        #image = Image.new('RGB', (self.imsize, self.imsize), (255, 255, 255))
        image = white_image = np.ones((self.imsize, self.imsize, 3), dtype=np.uint8) * 255
        ske.draw(image)
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        # cv2.imshow('Image', image)
        # key = cv2.waitKey(-1)
        return image



class VideoSkeletonDataset(Dataset):
    def __init__(self, videoSke, ske_reduced, source_transform=None, target_transform=None):
        """ videoSkeleton dataset: 
                videoske(VideoSkeleton): video skeleton that associate a video and a skeleton for each frame
                ske_reduced(bool): use reduced skeleton (13 joints x 2 dim=26) or not (33 joints x 3 dim = 99)
        """
        self.videoSke = videoSke
        self.source_transform = source_transform
        self.target_transform = target_transform
        self.ske_reduced = ske_reduced
        print("VideoSkeletonDataset: ",
              "ske_reduced=", ske_reduced, "=(", Skeleton.reduced_dim, " or ",Skeleton.full_dim,")" )


    def __len__(self):
        return self.videoSke.skeCount()


    def __getitem__(self, idx):
        # prepreocess skeleton (input)
        reduced = True
        ske = self.videoSke.ske[idx]
        ske = self.preprocessSkeleton(ske)
        # prepreocess image (output)
        image = Image.open(self.videoSke.imagePath(idx))
        if self.target_transform:
            image = self.target_transform(image)
        return ske, image

    
    def preprocessSkeleton(self, ske):
        if self.source_transform:
            ske = self.source_transform(ske)
        else:
            ske = torch.from_numpy( ske.__array__(reduced=self.ske_reduced).flatten() )
            ske = ske.to(torch.float32)
            ske = ske.reshape( ske.shape[0],1,1)
        return ske


    def tensor2image(self, normalized_image):
        numpy_image = normalized_image.detach().numpy()
        # Réorganiser les dimensions (C, H, W) en (H, W, C)
        numpy_image = np.transpose(numpy_image, (1, 2, 0))
        # passage a des images cv2 pour affichage
        numpy_image = cv2.cvtColor(np.array(numpy_image), cv2.COLOR_RGB2BGR)
        denormalized_image = numpy_image * np.array([0.5, 0.5, 0.5]) + np.array([0.5, 0.5, 0.5])
        denormalized_output = denormalized_image * 1
        return denormalized_output


class GenNNSkeToImage(nn.Module):
    """ class that Generate a new image from videoSke from a new skeleton posture
       Fonc generator(Skeleton)->Image
    """
    def __init__(self):
        super(GenNNSkeToImage, self).__init__()
        self.input_dim = Skeleton.reduced_dim #26
        self.model = nn.Sequential(
            nn.ConvTranspose2d(26, 128, kernel_size=4, stride=1, padding=0),
            nn.BatchNorm2d(128),
            nn.ReLU(True),            
            nn.ConvTranspose2d(128, 64, kernel_size=4, stride=2, padding=1),
            nn.BatchNorm2d(64),
            nn.ReLU(True),
            nn.ConvTranspose2d(64, 32, kernel_size=4, stride=2, padding=1),
            nn.BatchNorm2d(32),
            nn.ReLU(True),
            nn.ConvTranspose2d(32, 16, kernel_size=4, stride=2, padding=1),
            nn.BatchNorm2d(16),
            nn.ReLU(True),
            nn.ConvTranspose2d(16, 8, kernel_size=4, stride=2, padding=1),
            nn.BatchNorm2d(8),
            nn.ReLU(True),
            nn.ConvTranspose2d(8, 3, kernel_size=1, stride=1, padding=0),
            nn.Tanh()
        )
        # print(self.model)

    def forward(self, z):
        img = self.model(z)
        return img



class GenVanillaNN():
    """ class that Generate a new image from videoSke from a new skeleton posture
       Fonc generator(Skeleton)->Image
    """
    def __init__(self, videoSke, loadFromFile=False, optSkeOrImage=1):
        image_size = 64
        self.netG = GenNNSkeToImage()
        self.device = torch.device("cuda:0" if (torch.cuda.is_available() and ngpu > 0) else "cpu")
        src_transform = None
        self.filename = 'DanceGenVanillaFromSke.pth'
        self.directory = 'data/weights/'
        tgt_transform = transforms.Compose([
                            transforms.Resize(image_size),
                            transforms.CenterCrop(image_size),
                            transforms.ToTensor(),
                            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),
                            # [transforms.Resize((64, 64)),
                            # transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
                            ])
        self.dataset = VideoSkeletonDataset(videoSke, ske_reduced=True, target_transform=tgt_transform, source_transform=src_transform)
        self.dataloader = torch.utils.data.DataLoader(dataset=self.dataset, batch_size=16, shuffle=True)
        path = self.directory + self.filename
        if loadFromFile and os.path.isfile(path):
            print("GenVanillaNN: Load=", path)
            print("GenVanillaNN: Current Working Directory: ", os.getcwd())
            self.netG = torch.load(path)


    def train(self, n_epochs=200):
        # lr = 0.001
        # criterion = nn.L1Loss()        
        # optim = torch.optim.Adam(self.netG.parameters(), lr=lr)
        # for epoch in range(n_epochs):
        #     for i, (data, image) in enumerate(self.dataloader):
        #         ske = data
        #         img_label = image
        #         img = self.netG.forward(ske)
        #         # print(img.shape, ' img_label : ', img_label.shape)
        #         loss = criterion(img, img_label)
        #         loss.backward()
        #         optim.step()
        #         optim.zero_grad()
        #         if i == len(self.dataloader) - 1:
        #             print(loss)
        #     print(epoch)
        
        # if not os.path.exists(self.directory):
        #     print(f"Creating directory: {self.directory}")
        #     os.makedirs(self.directory)
        # path = self.directory + self.filename
        # print(path)
        # torch.save(self.netG, path)
        # print(f"Modèle sauvegardé à la fin de l'époque {epoch+1}")
        criterion = nn.MSELoss()
        optimizer = torch.optim.SGD(self.netG.parameters(), lr=0.001, momentum=0.9)

        for epoch in range(n_epochs):  # loop over the dataset multiple times
            running_loss = 0.0
            for i, data in enumerate(self.dataloader, 0):
                inputs, labels = data
                optimizer.zero_grad()
                outputs =self.netG(inputs)
                loss = criterion(outputs, labels)
                loss.backward()
                optimizer.step()
                running_loss += loss.item()
                if i % 50 == 0:
                    print('[%d/%d][%d/%d]\tloss: %.4f\t'
                        % (epoch, n_epochs, i, len(self.dataloader), running_loss))

        if not os.path.exists(self.directory):
            print(f"Creating directory: {self.directory}")
            os.makedirs(self.directory)
        path = self.directory + self.filename
        torch.save(self.netG, path)
        print(f"Modèle sauvegardé à la fin de l'époque {epoch+1} dans : ", path)


    def generate(self, ske):
        """ generator of image from skeleton """
        # TP-TODO
        ske_t = self.dataset.preprocessSkeleton(ske)
        ske_t_batch = ske_t.unsqueeze(0)        # make a batch
        normalized_output = self.netG(ske_t_batch)
        res = self.dataset.tensor2image(normalized_output[0])       # get image 0 from the batch
        return res



if __name__ == '__main__':
    force = False
    optSkeOrImage = 2           # use as input a skeleton (1) or an image with a skeleton drawed (2)
    n_epoch = 200 # 200
    train = 1 #False
    #train = True

    if len(sys.argv) > 1:
        filename = sys.argv[1]
        if len(sys.argv) > 2:
            force = sys.argv[2].lower() == "true"
    else:
        filename = "tp/dance/data/taichi1.mp4"
    print("GenVanillaNN: Current Working Directory=", os.getcwd())
    print("GenVanillaNN: Filename=", filename)
    print("GenVanillaNN: Filename=", filename)

    targetVideoSke = VideoSkeleton(filename)

    if train:
        # Train
        gen = GenVanillaNN(targetVideoSke, loadFromFile=True)
        gen.train(n_epoch)
    else:
        gen = GenVanillaNN(targetVideoSke, loadFromFile=True)    # load from file        


    # Test with a second video
    for i in range(targetVideoSke.skeCount()):
        image = gen.generate( targetVideoSke.ske[i] )
        #image = image*255
        nouvelle_taille = (256, 256) 
        image = cv2.resize(image, nouvelle_taille)
        cv2.imshow('Image', image)
        key = cv2.waitKey(-1)
