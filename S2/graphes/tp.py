
with open("cours-representation.gra", "r") as f:
    # Ignorer les premières lignes de commentaires
    for i in range(2):
        f.readline()

    oriented = f.readline().strip().split(": ")[1] == "true"
    nbSommets=int(f.readline().strip().split(": ")[1])
    nbValeursParSommets = int(f.readline().strip().split(": ")[1])
    nbArcs = int(f.readline().strip().split(": ")[1])
    nbValeursParArcs = int(f.readline().strip().split(": ")[1])

    #print(oriented,nbSommets,nbValeursParSommets,nbArcs,nbValeursParArcs)
    for i in range(2):
        f.readline()


    vertices = {}
    for i in range(nbSommets):
        vertex_info = f.readline().strip().split()
        vertex_id = int(vertex_info[0])
        vertex_name = vertex_info[1]
        vertex_values = list(map(int, vertex_info[2:]))
        vertices[vertex_id] = {"id": vertex_id, "name": vertex_name, "values": vertex_values, "outgoing_neighbors": [], "incoming_neighbors": []}

    for i in range(2):
        f.readline()
    # Parcourir chaque ligne du fichier correspondant à une arête
    for i in range(nbArcs):
        edge_info = f.readline().strip().split()
        initial_vertex_id = int(edge_info[0])
        final_vertex_id = int(edge_info[1])
        edge_values = list(map(float, edge_info[2:]))

        # Ajouter l'arête à la liste d'adjacence du sommet initial
        vertices[initial_vertex_id]["outgoing_neighbors"].append([final_vertex_id, edge_values])

        # Si le graphe est orienté, ajouter également l'arête à la liste d'adjacence du sommet final
        if oriented:
            vertices[final_vertex_id]["incoming_neighbors"].append([initial_vertex_id, edge_values])
        else:
            vertices[final_vertex_id]["outgoing_neighbors"].append([initial_vertex_id, edge_values])

    # Calculer les degrés de chaque sommet
    for vertex in vertices.values():
        degree = len(vertex["outgoing_neighbors"])
        if oriented:
            in_degree = len(vertex["incoming_neighbors"])
            out_degree = degree
            degree = in_degree + out_degree
            print("Sommet", vertex["id"], "(", vertex["name"], "): degré entrant =", in_degree, ", degré sortant =", out_degree)
        else:
            print("Sommet", vertex["id"], "(", vertex["name"], "): degré =", degree)

        vertex["degree"] = degree

    # Afficher la liste d'adjacence
    for vertex in vertices.values():
        print("Sommet", vertex["id"], "(", vertex["name"], "):")
        print("  Valeurs:", vertex["values"])
        print("  Degré:", vertex["degree"])
        if oriented:
            print("  Arcs sortants:", vertex["outgoing_neighbors"])
            print("  Arcs entrants:", vertex["incoming_neighbors"])
        else : 
            print("  Arcs :", vertex["outgoing_neighbors"])
