from random import randint
from boite_a_outils import calcul_frequence_letter_message

class Cesar:
    def __init__(self, key=None):
        if key is None:
            key = randint(0, 26)
        self.key = key

    def encode(self, plain):
        cipher = ""
        for char in plain:
            if char.isalpha():  # Vérifiez si le caractère est une lettre
                shifted = ord(char) + self.key
                if char.islower():
                    if shifted > ord('z'):
                        shifted -= 26
                    elif shifted < ord('a'):
                        shifted += 26
                elif char.isupper():
                    if shifted > ord('Z'):
                        shifted -= 26
                    elif shifted < ord('A'):
                        shifted += 26
                cipher += chr(shifted)
            else:
                cipher += char  # Si ce n'est pas une lettre, conservez le caractère tel quel
        return cipher

    def decode(self, cipher):
        plain = ""
        for char in cipher:
            if char.isalpha():
                shifted = ord(char) - self.key
                if char.islower():
                    if shifted > ord('z'):
                        shifted -= 26
                    elif shifted < ord('a'):
                        shifted += 26
                elif char.isupper():
                    if shifted > ord('Z'):
                        shifted -= 26
                    elif shifted < ord('A'):
                        shifted += 26
                plain += chr(shifted)
            else:
                plain += char
        return plain




def bruteforce_decrypt(cesar, cipher):
    assert isinstance(cesar, Cesar)

    print("Les possibilités de déchiffrement de {} sont :".format(cipher))
    for i in range(26):
        cesar.key = i
        plain = cesar.decode(cipher)
        print("Clé : {}, Texte clair : {}".format(i, plain))


def chosen_cipher(cesar):
    assert isinstance(cesar, Cesar)
    #déduire la clé en utilisant cesar.decode()

    key = 26 - ord(cesar.decode('A'))%65

    print("la clé de chiffrement est : {}".format(key))
    return key

def chosen_plain(cesar):
    assert isinstance(cesar, Cesar)
    
    # Texte clair choisi
    known_plain = "A"
    
    # Chiffrer le texte clair choisi
    cipher = cesar.encode(known_plain)
    
    # Calculer la différence entre la première lettre du texte chiffré et la première lettre du texte clair choisi
    # pour trouver la clé
    key = (ord(cipher) - ord(known_plain)) % 26

    print("La clé de chiffrement est : {}".format(key))
    return key


def known_plain(plain, cipher):
    # Connaissant le texte clair et le texte chiffré,
    # vous pouvez calculer directement la clé utilisée
    key = (ord(cipher[0]) - ord(plain[0])) % 26
    print("la clé de chiffrement est : {}".format(key))
    return key


def cipher_text_only(cipher):
    frequences = calcul_frequence_letter_message(cipher)
    max_freq_letter = max(frequences, key=frequences.get)

    max_freq_position = ord(max_freq_letter.lower()) - ord('a')
    e_position = ord('e') - ord('a')
    distance_to_e = (max_freq_position - e_position) % 26

    return distance_to_e

def decode_cypher_text_only(cipher):
    key = cipher_text_only(cipher)
    print(Cesar(key).decode(cipher))

key = int(input("Veuillez saisir une clé de chiffrement ('-1' pour une clé aléatoire) :"))
cesar = Cesar() if key<0 else Cesar(key)

plain = input("Veuillez saisir un texte à chiffrer par la clé {}:".format(cesar.key))

print("Le chiffrement de {} par la clé {} est : {}".format(plain, cesar.key, cesar.encode(plain)))

cipher = input("Veuillez saisir un texte à déchiffrer par la clé {}:".format(cesar.key))

print("Le déchiffrement de {} par la clé {} est : {}".format(cipher, cesar.key, cesar.decode(cipher)))

# Ajoutez vos tests
bruteforce_decrypt(cesar, cipher)
chosen_cipher(Cesar(17))
chosen_plain(Cesar(17))
known_plain(plain, cipher)
print("Déchiffrons VK MSQKVO KIKXD MRKXDO DYED VODO CO DBYEFK PYBD NOZYEBFEO AEKXN VK LSCO PED FOXEO")
decode_cypher_text_only("VK MSQKVO KIKXD MRKXDO DYED VODO CO DBYEFK PYBD NOZYEBFEO AEKXN VK LSCO PED FOXEO")