import random

class Sommet:
    #Création de la classe Sommet
    def __init__(self, nom="Sommet", voisins=[], tresor=False, graphe=None, distance=-1, nourriture=False):
        self.nom = nom
        self.voisins = voisins
        self.tresor = tresor
        self.graphe = graphe
        self.distance = distance
        self.nourriture = nourriture
        ran = random.randint(1, 100)
        if ran <= 10:
            self.nourriture = True
        else:
            self.nourriture = False
    def __repr__(self):
        liste_vois = []
        for i in range(len(self.voisins)):
            liste_vois.append(self.voisins[i].nom)
        return str(self.nom) + " " + str(liste_vois)


class Graphe:
    #Création de la classe Graphe
    def __init__(self, sommets=[], nb_tresor=0):
        self.sommets = sommets
        self.nb_tresor = nb_tresor
        for i in range(len(sommets)):
            if self.sommets[i].tresor:
                self.nb_tresor += 1
            self.sommets[i].graphe = self
    def genere_tresor(self): #Génère un trésor aléatoirement parmi les sommets
        ran = random.randint(0, len(self.sommets) - 1)
        if not self.sommets[ran].tresor: #test si il n'y a pas déja un tresor sur le sommet
            self.sommets[ran].tresor = True
            self.sommets[ran].distance = 0
            self.nb_tresor += 1

class Explorateur:
    #Création de la classe Explorateur
    def __init__(self, position=None, butin=0, energie=10):
        self.position = position
        self.butin = butin
        self.energie = energie
    def deplacement(self): #Fonction de déplacement, chaque déplacement fait perde 1 energie
        graphe_exp = self.position.graphe
        liste_vois = []
        nouv_pos = None
        for i in range(len(self.position.voisins)):
            liste_vois.append(self.position.voisins[i].nom)
        print(liste_vois)
        choix = int(input("Choisir un voisin"))
        if choix in liste_vois:
            for i in range(len(graphe_exp.sommets)):
                if graphe_exp.sommets[i].nom == choix:
                    nouv_pos = graphe_exp.sommets[i]
                    self.energie -= 1
                    if nouv_pos.nourriture:
                        print("Nourriture trouvée ! +5 energie")
                        self.energie += 5
                        nouv_pos.nourriture = False
            self.position = nouv_pos
        else:
            print("le sommet visé est inaccessible")
            self.deplacement() #Rappel de la fonction si l'entrée de l'utilisateur est invalide


def recherche_tresor(explo): #Recherche trésor, la fonction s'arrête lorsqu'un trésor est trouvé
    if explo.position.graphe.nb_tresor == 0:
        explo.position.graphe.genere_tresor()
    if explo.position.tresor:           # Cas où l'explorateur commence sur un tresor
        print("Deja sur un tresor !")
        explo.butin += 1
        explo.position.tresor = False
    else:
        trouve = False
        while not trouve:
            explo.deplacement()
            if explo.position.tresor:
                print("butin trouvé !")
                explo.butin += 1
                explo.position.tresor = False
                trouve = True

def calcul_dist1(s, d):
    if (s.distance == -1 or d < s.distance):
        s.distance = d
        for i in range(len(s.voisins)):
            calcul_dist1(s.voisins[i], d + 1)


def calcul_dist(graphe):
    for i in range(len(graphe.sommets)):
        if (graphe.sommets[i].tresor):
            for j in range(len(graphe.sommets[i].voisins)):
                calcul_dist1(graphe.sommets[i].voisins[j], 1)


def recherche_distance(explo):  #Même fonction que recherche tresor mais indique la distance par rapport au tresor
    if explo.position.graphe.nb_tresor == 0:
        explo.position.graphe.genere_tresor()
    calcul_dist(explo.position.graphe)
    trouve = False
    while not trouve:
        print("Distance jusqu'au tresor :" + explo.position.distance)
        explo.deplacement()
        if explo.positions.tresor:
            explo.butin += 1
            explo.position.tresor = False
            trouve = True


def recherche_nourriture(explo):    #Même fonction que recherche_distance mais indique le nombre d'énergie restante
    if explo.position.graphe.nb_tresor == 0:
        explo.position.graphe.genere_tresor()
    calcul_dist(explo.position.graphe)
    trouve = False
    while not trouve:
        print("Distance jusqu'au tresor :" + explo.position.distance + " | Energie restante : " + explo.energie)
        if explo.energie > 0:
            explo.deplacement()
            if explo.positions.tresor:
                explo.butin += 1
                explo.position.tresor = False
                trouve = True
        else:
            print("Fin de partie ! Veuillez rejouer")
            trouve = True


n = 10
V = [Sommet(nom=i, voisins=[], distance=-1) for i in range(n)]

for i in range(n):
    V[i].voisins.append(V[(i+1)%n])
    V[i].voisins.append(V[(i-1)%n])

C10 = Graphe(sommets=V, nb_tresor=0)
C10.genere_tresor()
C10.genere_tresor()
calcul_dist(C10)

for i in range(n):
    print(str(C10.sommets[i].nom) + " " + str(C10.sommets[i].tresor) + " " + str(C10.sommets[i].distance))



ran=random.randint(0, 9)
while C10.sommets[ran].tresor:
    ran = random.randint(0, 9)
ashe = Explorateur(C10.sommets[ran], butin=0, energie=10)
recherche_tresor(ashe)
print(ashe.butin, ashe.energie)
