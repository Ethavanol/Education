nbColonnes = 10
nbLignes = 10
nbBateaux = 3
nbMines = 6

class CreationGrille:
    #creation de la classe CreationGrille
    def __init__(self):
        self.grille = [[0 for _ in range(nbColonnes)] for _ in range(nbLignes)] #on définit un "tableau 2D"
        #de taille 10*10 rempli de 0, ça sera l grille de jeu de base
        self.longBateau = 3 #utile pour nos boucles for

        def saisirGrille():
            index1Ligne = int(input())
            index1Ligne = index1Ligne - 1 #on enlève 1 puisque les index dans un tableau vont de 0 à 9
            index1Colonne = int(input())
            index1Colonne = index1Colonne - 1 #on enlève 1 puisque les index dans un tableau vont de 0 à 9
            if( (index1Ligne<0) | (index1Ligne>7) | (index1Colonne<0) | (index1Colonne>7) ):
                #si les index de la case saisie ne sont pas dans la grille
                print("Une des valeurs saisies n'est pas entre 1 et 8, veuillez resaisir les valeurs")
                saisirGrille() #on rappelle la fonction(on recommence)
            else:
                print("Vous souhaitez positionner votre bateau à horizontal(tapez h) ou à la vertical (tapez v)")
                sensBateau = input()
                if(sensBateau == "h"):
                    #si le joueur veut placer son bateau à l'horizontal, on vérifie que les
                    # deux cases suivantes sur la même ligne sont inoccupées
                    if( (self.grille[index1Ligne][index1Colonne] == 0) & (self.grille[index1Ligne][index1Colonne+1] == 0)
                        & (self.grille[index1Ligne][index1Colonne+2] == 0) ):
                        for i in range(self.longBateau):
                            #on met des 1 dans les trois cases sur la même ligne
                            self.grille[index1Ligne][index1Colonne+i] = 1
                    else:
                        print("Il y a déjà un élément sur une des cases. Veuillez resaisir")
                        saisirGrille() #sinon, on met qu'il y a déjà un élément
                        # sur une des trois cases et on recommence
                elif(sensBateau =="v"):
                    #si le joueur veut placer son bateau à la verticale, on vérifie que les
                    # deux cases suivantes sur la même colonne sont inoccupées
                    if( (self.grille[index1Ligne][index1Colonne] == 0) & (self.grille[index1Ligne+1][index1Colonne] == 0)
                        & (self.grille[index1Ligne+2][index1Colonne] == 0) ):
                        for i in range(self.longBateau):
                            #on met des 1 dans les trois cases sur la même colonne
                            self.grille[index1Ligne+i][index1Colonne] = 1
                    else : #sinon, on met qu'il y a déjà un élément sur une des trois cases et on recommence
                        print("Il y a déjà un élément sur une des cases. Veuillez resaisir")
                        saisirGrille()
                else: #si le joueur saisi quelque chose d'autre que 'h' ou 'v', on lui dit et on recommence
                    print("Erreur, vous devez saisir h ou v, veuillez resaisir")
                    saisirGrille()

        def saisirMines():
            indexMineLigne = int(input())
            indexMineLigne = indexMineLigne - 1
            indexMineColonne = int(input())
            indexMineColonne = indexMineColonne - 1
            #on vérifier que les coordonées saisies ne sont pas hors de la grille
            if( (indexMineLigne<0) | (indexMineLigne>9) | (indexMineColonne<0) | (indexMineColonne>9) ):
                print("Une des valeurs saisies n'est pas entre 1 et 10, veuillez resaisir")
                #sinon on recommence en affichant un message de prévention
                saisirMines()
                #si les coordonnées appartiennent à la grille, on vérifie que la case
                # correspondante est inocuppée
            elif(self.grille[indexMineLigne][indexMineColonne] != 0):
                print("Il ya déjà un élément sur cette case, veuillez resaisir")
                #sinon on recommence en affichant un message de prévention
                saisirMines()
            else:
                #si tout est bon, on met un 2 sur la case correspondante
                self.grille[indexMineLigne][indexMineColonne] = 2

        for i in range(nbBateaux): #on place nbBateaux(=3) bateaux sur la grille
            print("Placez votre", (i+1), "e bateau.")
            saisirGrille()
        for j in range(nbMines): #on place nbMines(=8) mines sur la grille
            print("Placez votre", (j+1), "e mine;")
            saisirMines()


class Joueur:
    #creation de la classe Jouer
    def __init__(self, grilleJoueur, grilleAdverse, nom=""):
        self.grilleJoueur = grilleJoueur
        self.grilleAdverse = grilleAdverse
        self.nom = nom
        self.nbVies = 3

    def adversaire(self, joueurAdverse): #on définit cette fonction, car lorque l'on instancie
    #joueur1 de type Joueur, on veut luui attribuer joueur2 en joueurAdverse, cependant comme celui-ci
    #n'est pas encore instancié, il est impossible de le passer en paramètres. On créé donc pour commencer
    #les deux joueurs, puis on fait appelle à cette fonction pour définir leur adversaire respectif
        self.joueurAdverse = joueurAdverse

    def tour(self, joueurAdverse):
        # on affiche à qui est le tour
        print("Lieutenant :", self.nom, "à vous de jouer")
        print("Saisissez une case sur laquelle vous souhaitez envoyer un missile")
        LigneVisee = int(input())
        LigneVisee = LigneVisee-1
        ColonneVisee = int(input())
        ColonneVisee = ColonneVisee-1
        #si les coordonnées saisies sont hors de la grille, on demande au joueur de les resaisir
        if( (LigneVisee<0) | (LigneVisee>9) | (ColonneVisee<0) | (ColonneVisee>9) ):
            print("Veuillez  resaisir les bonnes coordonnes svp")
            LigneVisee = int(input())
            LigneVisee = LigneVisee-1
            ColonneVisee = int(input())
            ColonneVisee = ColonneVisee-1
        #si les coordonnées saisies par le joueur correspondent à une case contenant la partie d'un bateau
        #(c-à-d un 1), on affiche un message, met la case à 0 et vérifie qu'il reste d'autres bateaux sur la
        #grille
        if(self.grilleAdverse.grille[LigneVisee][ColonneVisee] == 1):
            print("Bien joué ! Vous avez touché un bateau adverse")
            self.grilleAdverse.grille[LigneVisee][ColonneVisee] = 0
            #on initialise un booléen à faux dans le but de vérifier à chaque tour si il reste des bateaux
            ResteBateaux = False
            #si il reste au moins un 1 sur la grille, on place le booléen à True
            for i in range(nbLignes):
                for j in range(nbColonnes):
                    if (self.grilleJoueur.grille[i][j] == 1):
                        ResteBateaux = True
            #si le booléen est True, on fait jouer l'adversaire, sinon, on dit au joueur qu'il a gagné
            # et on arrête la partie
            if(ResteBateaux == True):
                self.joueurAdverse.tour(self)
            else:
                print("Mais OMG c'est win pour le Lieutenant ", self.nom, ", vous avez explosé tous les bateaux adverses")
        #si la case visée contient une mine (c-à-d un 2), on regarde le nombre de vies du joueur.
        #si celui-ci a 1 vie ou moins, on signale la victoire de l'autre joueur et on arrête la partie
        #sinon, on enlève une vie au joueur, on lui signale son nombre de vies restant et on fait
        # jouer l'adversaire
        elif(self.grilleAdverse.grille[LigneVisee][ColonneVisee] == 2):
            if(self.nbVies <= 1):
                print("Aïe... Vous êtes tombés sur une mine, vous n'avez plus de vies ! Vous avez perdu Commandant")
                print("Victoire du joueur : ", self.joueurAdverse.nom)
            else:
                self.nbVies = self.nbVies - 1
                print("Aïe... Vous êtes tombés sur une mine, vous perdez une vie, il vous reste ", self.nbVies," vies.")
                self.grilleAdverse.grille[LigneVisee][ColonneVisee] = 0
                self.joueurAdverse.tour(self)
        # si la case contient un 0, on indique que la case était vide, et on fait jouer l'adversaire
        else:
            print("Plouf ! La case était vide, vous ferez mieux la prochaine fois")
            self.joueurAdverse.tour(self)


print("Bienvenue sur notre super Jeu de touché coulé remix sauce pili-pili :")
print("Pour les coordonnées, on saisira d'abord l'indice de la ligne, puis celui de la colonne")
print("Quel est le nom du premier lieutenant : ")
nom1 = input()
print("Quel est le nom du second lieutenant : ")
nom2 = input()

#ici on affiche les deux grilles par souci de simplicité, pour tester le jeu
#évidemment elles ne seraient pas affiché pour que les grilles soient saisies de manière anonyme
print("Lieutenant", nom1, ", veuillez saisir votre grille à l'abri des regards du Lieutenant", nom2)
grille1 = CreationGrille()
for j in range(nbLignes):
    print(grille1.grille[j])

print("Lieutenant", nom2, ", veuillez saisir votre grille à l'abri des regards du Lieutenant", nom1)
grille2 = CreationGrille()
for j in range(nbLignes):
     print(grille2.grille[j])

joueur1 = Joueur(grille1, grille2, nom1)
joueur2 = Joueur(grille2, grille1, nom2)
joueur1.adversaire(joueur2)
joueur2.adversaire(joueur1)
joueur1.tour(joueur2)
                        