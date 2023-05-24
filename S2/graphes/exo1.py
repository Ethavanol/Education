import math  # importation du module math pour la valeur infini dans djikstra

class Graphe:
    def __init__(self):
        self.oriented = False
        self.nbSommets = 0
        self.nbValeursParSommets = 0
        self.nbArcs = 0
        self.nbValeursParArcs = 0
        self.listeSommets = []
        self.listeAdjacence = []
        self.Vertices = {}

    def lectureFichier(self, nomFichier):
        with open(nomFichier, "r") as fichier:
            # Ignorer les premières lignes de commentaires
            for i in range(2):
                fichier.readline()
            self.oriented = fichier.readline().strip().split(": ")[1] == "true"
            self.nbSommets = int(fichier.readline().strip().split(": ")[1])
            self.nbValeursParSommets = int(fichier.readline().strip().split(": ")[1])
            self.nbArcs = int(fichier.readline().strip().split(": ")[1])
            self.nbValeursParArcs = int(fichier.readline().strip().split(": ")[1])
            #On ignore deux lignes
            for i in range(2):
                fichier.readline()
            
            self.Vertices = {}
            for i in range(self.nbSommets):
                vertex_info = fichier.readline().strip().split()
                vertex_id = int(vertex_info[0])
                vertex_name = vertex_info[1]
                vertex_values = list(map(int, vertex_info[2:]))
                self.Vertices[vertex_id] = {"id": vertex_id, "name": vertex_name, "values": vertex_values, "outgoing_neighbors": [], "incoming_neighbors": []}
                self.Vertices[vertex_id]["nbCheminsPossibles"] = 0

            for i in range(2):
                fichier.readline()

            for i in range(self.nbArcs):
                edge_info = fichier.readline().strip().split()
                initial_vertex_id = int(edge_info[0])
                final_vertex_id = int(edge_info[1])
                edge_values = list(map(float, edge_info[2:]))

            #Pour chaque sommet correspondant, on remplit avec les arêtes correspondantes
                self.Vertices[initial_vertex_id]["outgoing_neighbors"].append([final_vertex_id, edge_values])
            
            # Si le graphe est orienté, ajouter également l'arête à la liste d'adjacence du sommet final
                if self.oriented:
                    self.Vertices[final_vertex_id]["incoming_neighbors"].append([initial_vertex_id, edge_values])
                else:
                    self.Vertices[final_vertex_id]["outgoing_neighbors"].append([initial_vertex_id, edge_values])
                
        fichier.close()
    
    def calculDegresSommets(self):
        for vertex in self.Vertices.values():
            degree = len(vertex["outgoing_neighbors"])
            if self.oriented:
                in_degree = len(vertex["incoming_neighbors"])
                out_degree = degree
                degree = in_degree + out_degree
                print("Sommet", vertex["id"], "(", vertex["name"], "): degré entrant =", in_degree, ", degré sortant =", out_degree)
            else:
                print("Sommet", vertex["id"], "(", vertex["name"], "): degré =", degree)

            vertex["degree"] = degree

    def afficherListeAdjacence(self):
        for vertex in self.Vertices.values():
            print("Sommet", vertex["id"], "(", vertex["name"], "):")
            print("  Valeurs:", vertex["values"])
            print("  Degré:", vertex["degree"])
            if self.oriented:
                print("  Arcs sortants:", vertex["outgoing_neighbors"])
                print("  Arcs entrants:", vertex["incoming_neighbors"])
            else : 
                print("  Arcs :", vertex["outgoing_neighbors"])

    def calculChemin(self, idSommet, racineID):
        #Nous souhaitons faire une fonction récursive.
        #Cependant, il faut être vigileant pour ne pas incrémenter le 
        #compteur de chemins possibles à chaque fois.
        vertex = self.Vertices[idSommet]
        for id_arc_entrant in range(len(vertex["incoming_neighbors"])):
            #si le prédecesseur actuel est la racine du Graphe et que
            if (vertex["incoming_neighbors"][id_arc_entrant][0] == racineID):
                #ce sommet ne possède qu'un unique prédecesseur
                if(len(vertex["incoming_neighbors"]) == 1):
                    vertex["nbCheminsPossibles"] = 1
                #il a plusieurs prédecesseurs
                else:
                    vertex["nbCheminsPossibles"] += 1
            #si le prédecesseur actuel a déjà été calculé et que
            elif(self.Vertices[vertex["incoming_neighbors"][id_arc_entrant][0]]["nbCheminsPossibles"] != 0):
                #ce sommet ne possède qu'un unique prédecesseur
                if(len(vertex["incoming_neighbors"]) == 1):
                    vertex["nbCheminsPossibles"] = self.Vertices[vertex["incoming_neighbors"][id_arc_entrant][0]]["nbCheminsPossibles"]
                #il a plusieurs prédecesseurs
                else:
                    vertex["nbCheminsPossibles"] += self.Vertices[vertex["incoming_neighbors"][id_arc_entrant][0]]["nbCheminsPossibles"]
            #si le prédecesseur actuel n'a paxs été calculé  et que
            else:
                #ce sommet ne possède qu'un unique prédecesseur
                if(len(vertex["incoming_neighbors"]) == 1):
                    vertex["nbCheminsPossibles"] = self.calculChemin(vertex["incoming_neighbors"][id_arc_entrant][0], racineID)
                #il a plusieurs prédecesseurs
                else:
                    vertex["nbCheminsPossibles"] += self.calculChemin(vertex["incoming_neighbors"][id_arc_entrant][0], racineID)
        return vertex["nbCheminsPossibles"]

    def nbCheminsPossibles(self, idSommet):
        #on trouve la racine, dont on stocke l'id.
        #On l'affichera pour mieux comprendre
        #Et on définit pour tous les sommets, le nb de chemins à 0
        for vertex in self.Vertices.values():
            if (len(vertex["incoming_neighbors"]) == 0):
                racine = vertex["name"]
                racineID = vertex["id"]
            vertex["nbCheminsPossibles"] = 0
        print("racine : ", racine, ", id racine : ", racineID)
    #On affiche le nb de Chemins possibles pour aller au sommet 'idSommet'
        print("Nb de chemins possibles pour aller au sommet", idSommet," : ", self.calculChemin(idSommet, racineID))




####On garde
class Edge:
    def __init__(self, idSommetInitial, idSommetTerminal, valeurs):
        self.idSommetInitial = idSommetInitial
        self.idSommetTerminal = idSommetTerminal
        self.valeurs = valeurs

class Vertex:
    def __init__(self, id, nom, valeurs):
        self.id = id
        self.nom = nom
        self.valeurs = valeurs
####

graphe1 = Graphe()
graphe1.lectureFichier("graphe-tp-exo1.gra")
graphe1.calculDegresSommets()
#graphe1.afficherListeAdjacence()
graphe1.nbCheminsPossibles(8)