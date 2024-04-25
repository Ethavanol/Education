import re

LETTRES = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
NONLETTRES_PATTERN = re.compile('[^A-Z]')
MAX_LEN_CLE = 16

def liste_sous_mots2(message, p):
    message = NONLETTRES_PATTERN.sub('', message.upper())
    maxLenRepetitions = 15

    liste_sous_mots = {}
    for sous_mot_len in range(p, maxLenRepetitions):
        for sous_mot_start in range(len(message) - sous_mot_len):
            seq = message[sous_mot_start:sous_mot_start + sous_mot_len]
            for i in range(sous_mot_start + sous_mot_len, len(message) - sous_mot_len):
                if message[i:i + sous_mot_len] == seq:
                    if seq not in liste_sous_mots:
                        liste_sous_mots[seq] = []
                    liste_sous_mots[seq].append(i - sous_mot_start)
    return liste_sous_mots


def diviseurs(num):
    if num < 2:
        return []

    l_diviseurs = []

    for i in range(2, MAX_LEN_CLE + 1):
        if num % i == 0:
            l_diviseurs.append(i)
            l_diviseurs.append(int(num / i))

    if 1 in l_diviseurs:
        l_diviseurs.remove(1)

    return list(set(l_diviseurs))


def calcul_iterations_diviseurs(liste_diviseurs):
    nb_iterations_sous_mot = {}

    for div in liste_diviseurs:
        iterations_diviseurs = liste_diviseurs[div]
        for cle in iterations_diviseurs:
            if cle not in nb_iterations_sous_mot:
                nb_iterations_sous_mot[cle] = 0
            nb_iterations_sous_mot[cle] += 1

    diviseur_avec_iterations = []
    for diviseur in nb_iterations_sous_mot:
        if diviseur <= MAX_LEN_CLE:
            diviseur_avec_iterations.append((diviseur, nb_iterations_sous_mot[diviseur]))

    diviseur_avec_iterations.sort(key= lambda x: x[1], reverse=True)
    return diviseur_avec_iterations


def decode_babbage_kasiski(message, p):
    liste_sous_mots = liste_sous_mots2(message, p)
    print(liste_sous_mots)

    liste_diviseurs = {}

    for sous_mot in liste_sous_mots:
        liste_diviseurs[sous_mot] = []
        for div in liste_sous_mots[sous_mot]:
            liste_diviseurs[sous_mot].extend(diviseurs(div))

    iterations_diviseurs = calcul_iterations_diviseurs(liste_diviseurs)
    
    cles_probables = []

    for tuple_diviseurs in iterations_diviseurs:
        cles_probables.append(tuple_diviseurs[0])

    print("Les solutions probables sont : ", cles_probables)

    return cles_probables[0]

### Texte clair :
### Le soleil brille dans un ciel bleu azur, éclairant doucement la terre endormie.
### Les oiseaux chantent joyeusement, annonçant l'arrivée d'une nouvelle journée.
### Au loin, les montagnes se dressent majestueusement, témoins silencieux du passage du temps.
### Chiffré avec la clé "test"
message = """
wefl vi exlwszx umx ci nhnw wvkmk, cx xaxgw s ohyk xvpsbkij. Vx qwlleyx t tgnk fmm wi nhnw wgosqxk yf fxwktzi, inx n'sb xgjbl, md r t pggzxwfiw. Bx mmwgl e nhnw vbki inx gw fxwktzi vtmi v'be c s ehrymxqhl. Vi exlwszx umb welx w'yf ixxam fsexgx (dhgklxftk) t xxw xvvam iej fhm-exfi. U'xlx mg fikltkw jnm vtmi v'be c s ehrymxqhl jyw cx zgnl iukbw dt.
"""
p = 3
cle = decode_babbage_kasiski(message, p)
print("la clé la plus probable est : ", cle)

