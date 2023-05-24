nbColonnes = 7
nbLignes = 6

class CreationGrille:
    def __init__(self):
        self.grille = [['-' for i in range(nbColonnes)] for j in range(nbLignes)]

class Joueur:
    def __init__(self, grille, nomJoueur, signe):
        self.grille = grille
        self.nomJoueur = nomJoueur
        self.signe = signe

    def defAdversaire(self, joueurAdverse):
        self.joueurAdverse = joueurAdverse

    def tour(self):
        victoire = False
        grillePleine = True
        print("Tour de", self.nomJoueur,". Sur quelle rangée souhaitez-vous placer votre pion ?")
        indiceColonne = int(input())
        indiceColonne = indiceColonne-1
        if( (indiceColonne < 0) | (indiceColonne > 6) ):
            print("Le numéro de rangée doit être entre 1 et 7")
            self.tour()
        elif( (self.grille.grille[0][indiceColonne] != '-') ):
            print("Cettre rangée est pleine, saisissez-en une autre")
            self.tour()
        indiceLigne = 0
        while (indiceLigne < 5):
            if(self.grille.grille[indiceLigne+1][indiceColonne] == '-'):
                #tant que la case est vide, on descend d'une ligne
                indiceLigne = indiceLigne+1
            else:
                break #sinon, on reste sur cette ligne là
        self.grille.grille[indiceLigne][indiceColonne] = self.signe
        #test victoire, on initialise un compteur à 0
        cptcases = 0
        if(nbLignes - indiceLigne >= 4):
            for i in range(nbLignes):
                if(self.grille.grille[i][indiceColonne] == self.signe):
                    cptcases = cptcases+1
                else:
                    cptcases = 0
                if(cptcases == 4):
                    victoire = True
                    break
        for i in range(nbColonnes):
           # if(cptcases == 4):
             #   victoire = True
            #    break
            if(self.grille.grille[indiceLigne][i] == self.signe):
                cptcases = cptcases+1
            else:
                cptcases = 0
            if(cptcases == 4):
                victoire = True
                break

    #ici on sauvegarde les coordonnées que l'on va modifier
        indiceLigne2 = indiceLigne
        indiceColonne2 = indiceColonne
    #ici on va tester la diagonale qui descend vers la droite
        while((indiceLigne != 0) & (indiceColonne != 0)):
            indiceLigne = indiceLigne-1
            indiceColonne = indiceColonne-1

        print("L :", indiceLigne,", C:",indiceColonne)
        while((indiceLigne < nbLignes) & (indiceColonne < nbColonnes)):
            if(self.grille.grille[indiceLigne][indiceColonne] == self.signe):
                if(cptcases == 3):
                    victoire =True
                    break
                else:
                    cptcases = cptcases+1
                    indiceLigne = indiceLigne+1
                    indiceColonne = indiceColonne+1
            else:
                cptcases = 0
                indiceLigne = indiceLigne+1
                indiceColonne = indiceColonne+1

    #maintenant on va tester la diagonale qui descend vers la gauche
        while((indiceLigne2 != 0) & (indiceColonne2 != 6)):
            indiceLigne2 = indiceLigne2-1
            indiceColonne2 = indiceColonne2+1

        print("L2 :", indiceLigne2,", C2:",indiceColonne2)
        while((indiceLigne2 < nbLignes) & (indiceColonne2 >= 0)):
            if(self.grille.grille[indiceLigne2][indiceColonne2] == self.signe):
                if(cptcases == 3):
                    victoire =True
                    break
                else:
                    cptcases = cptcases+1
                    indiceLigne2 = indiceLigne2+1
                    indiceColonne2 = indiceColonne2-1
            else:
                cptcases = 0
                indiceLigne2 = indiceLigne2+1
                indiceColonne2 = indiceColonne2-1

        print(cptcases)
        for i in range(nbLignes):
            print(self.grille.grille[i])
        for i in range(nbColonnes):
            if(self.grille.grille[0][i] == '-'):
                grillePleine = False
                break
        if(grillePleine == True):
            print("Egalite")
        elif(victoire == True):
            print("Victoire de",self.nomJoueur,"!!!!!")
        else:
            self.joueurAdverse.tour()




print("Votre nom, J1 :")
nom1 = input()
print("Votre nom, J2 :")
nom2 = input()
print("Bien",nom1,"vous aurez les X et",nom2,"aura les O")

grille=CreationGrille()
joueur1 = Joueur(grille, nom1, 'X')
joueur2 = Joueur(grille, nom2, 'O')
joueur1.defAdversaire(joueur2)
joueur2.defAdversaire(joueur1)
for i in range(nbLignes):
    print(grille.grille[i])
joueur1.tour()

