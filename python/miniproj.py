nbColonnes = 10
nbLignes = 10
nbBateaux = 3
longBateau = 3
nbMines = 8
tab=[]

class Creationgrille:
    #création de la classe CréationGrille
    def __init__(self):
        self.grille = [[0 for _ in range(nbColonnes)] for _ in range(nbLignes)] #on définit un "tableau 2D"
        self.bateau = [[0 for _ in range(2)] for _ in range(3)]
        self.mineLigne = 0
        self.mineColonne = 0
        # remplis de 0, qui sera notre grille de jeu (en réalité, ce n'est pas exactement un tableau 2D,
        # il n'y en a pas vraiment en python
        def verifiersaisie(i):
            self.bateau[i][0] = int(input()) #on saisit l'indice de la ligne
            self.bateau[i][1] = int(input())#on saisit l'indice de la colonne
            if((self.bateau[i][0] < 1) | (self.bateau[i][0] > 10) | (self.bateau[i][1] < 1) | (self.bateau[i][1] > 10)):
                #tant qu'une des deux valeur n'est pas entre 1 et 10, on recommence
                print("Erreur, les valeurs saisies doivent être entre 1 et 10 compris. Veuillez resaisir")
                verifiersaisie(i)
            elif(self.grille[self.bateau[i][0] - 1][self.bateau[i][1] - 1] == 1):
                print("Erreur, il ya déjà un bateau ici. Veuillez resaisir des coordonnées svp")
                verifiersaisie(i)
            elif(i == 1):
                if( ( (self.bateau[i-1][0] == self.bateau[i][0]) & ( (self.bateau[i][1] == self.bateau[i-1][1] - 1) | (self.bateau[i][1] == (self.bateau[i-1][1] + 1)) ) ) |
                        ( (self.bateau[i-1][1] == self.bateau[i][1]) & ( (self.bateau[i][0] == self.bateau[i-1][0] - 1) | (self.bateau[i][0] == (self.bateau[i-1][0] + 1)) ) ) ):
                    self.grille[self.bateau[i][0] - 1][self.bateau[i][1] - 1] = 1
                else :
                    print("Les coordonnées d'un bateau doivent être à côtév2, veuillez resaisir la coordonnée")
                    verifiersaisie(i)
            elif(i == 2):
                for k in range(2): #0 ou 1
                    val1 = self.bateau[0][k]
                    val2 = self.bateau[1][k]
                    if ((val1 == val2) & (self.bateau[i][k] == val1)):
                    #si les deux cases "posées" avant sont sur la même ligne ou colonne que la case actuelle
                        if(k == 0):
                            if((self.bateau[i][0] == (self.bateau[i-2][0] - 1)) | (self.bateau[i][0] == (self.bateau[i-2][0] + 1)) |
                            (self.bateau[i][0] == (self.bateau[i-1][0] - 1)) | (self.bateau[i][0] == (self.bateau[i-1][0] + 1))):
                                #si le nouvel index est une case à coté des précédentes, on met 1 dans la case (le bateau)
                                self.grille[self.bateau[i][0] - 1][self.bateau[i][1] - 1] = 1
                            else: verifiersaisie(i)
                        #si k = 1
                        elif((self.bateau[i][1] == (self.bateau[i-2][1] - 1)) | (self.bateau[i][1] == (self.bateau[i-2][1] + 1)) |
                        (self.bateau[i][1] == (self.bateau[i-1][1] - 1)) | (self.bateau[i][1] == (self.bateau[i-1][1] + 1))):
                            #si le nouvel index est une case à coté des précédentes, on met 1 dans la case (le bateau)
                            self.grille[self.bateau[i][0] - 1][self.bateau[i][1] - 1] = 1
                        else:verifiersaisie(i)
                    else:
                        print("Erreur, il semblerait que les deux cases précédentes ne soient pas à côté, veuillez resaisir vos valeurs")
                        verifiersaisie(i)
                        break
            else :
                self.grille[self.bateau[i][0] - 1][self.bateau[i][1] - 1] = 1

        def saisirMines():
            mineLigne=int(input())
            mineColonne=int(input())
            if((mineLigne<1) | (mineLigne>10) | (mineColonne<1) | (mineColonne>10)):
                print("Les valeurs saisies doivent être entre 1 et 10 compris")
                saisirMines()
            elif((self.grille[mineLigne][mineColonne] == 1) | (self.grille[mineLigne][mineColonne] == 2)):
                print("Il y a déjà un élément sur cette case")
                saisirMines()
            else:
                self.grille[mineLigne][mineColonne] = 2
                print("Mine placée")

        for j in range(nbBateaux):
            print("Placez votre bateau :") #on va placer les bateaux sur la grille du joueur "Rouge"
            for i in range(longBateau): #on va saisir 3 fois des coordonnées puisque le bateau est de lg 3
                print("On saisira d'abord l'indice de la ligne puis celui de la colonne:")
                verifiersaisie(i)
        print("On va placer les mines :")
        for k in range(nbMines):#on place les mines
            print("Placez une mine")
            saisirMines()





grille = Creationgrille()

for j in range(nbLignes):
    print(grille.grille[j])

        