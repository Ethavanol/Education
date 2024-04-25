from random import shuffle
from boite_a_outils import calcul_frequence_letter_message, frequences_francais

class Subs:
    def __init__(self, key=None):
        if key is None:
            # Si aucune clé n'est fournie, générer une clé aléatoire
            alphabet = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
            shuffled_alphabet = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
            shuffle(shuffled_alphabet)
            self.key = dict(zip(alphabet, shuffled_alphabet))
            self.key_inv = dict(zip(shuffled_alphabet, alphabet))
        else:
            # Utiliser la clé fournie
            self.key = key
            self.key_inv = {v: k for k, v in key.items()}  # Construire la clé inverse

    def encode(self, plain):
        cipher = ""
        for char in plain.upper():
            if char.isalpha():  # Vérifier si le caractère est une lettre
                cipher += self.key.get(char, char)  # Utiliser la substitution, sinon conserver le caractère tel quel
            else:
                cipher += char  # Si ce n'est pas une lettre, conserver le caractère tel quel
        return cipher

    def decode(self, cipher):
        plain = ""
        for char in cipher.upper():
            if char.isalpha():  # Vérifier si le caractère est une lettre
                plain += self.key_inv.get(char, char)  # Utiliser la substitution inverse, sinon conserver le caractère tel quel
            else:
                plain += char  # Si ce n'est pas une lettre, conserver le caractère tel quel
        return plain

def chosen_cipher(subs):
    assert isinstance(subs, Subs)

    # Déduire la clé en utilisant subs.decode()
    key = subs.decode('ABCDEFGHIJKLMNOPQRSTUVWXYZ')

    print("la clé de chiffrement est : {}".format(key))
    return key

def chosen_plain(subs):
    assert isinstance(subs, Subs)

    # Déduire la clé en utilisant subs.encode() mais sans utiliser subs.decode()
    key = subs.encode('ABCDEFGHIJKLMNOPQRSTUVWXYZ')

    print("la clé de chiffrement est : {}".format(key))
    return key

def known_plain(plain, cipher):
    # Déduire une clé possible à partir de plain et cipher
    key = {}
    for p, c in zip(plain, cipher):
        if p.isalpha() and c.isalpha():  # Vérifier si les caractères sont des lettres
            key[c] = p

    print("la clé de chiffrement est : {}".format(key))
    return key

def cipher_text_only(cipher):
    frequences = calcul_frequence_letter_message(cipher)
    sorted_freq = sorted(frequences.items(), key=lambda x: x[1], reverse=True)
    sorted_freq_francais = sorted(frequences_francais.items(), key=lambda x: x[1], reverse=True)

    key = {}
    for (letter, _), (letter_francais, _) in zip(sorted_freq, sorted_freq_francais):
        if letter.isalpha() and letter_francais.isalpha():  # Vérifier si les caractères sont des lettres
            key[letter_francais] = letter

    print("la clé de chiffrement est : {}".format(key))
    return key

def decode_cipher_text_only(cipher):
    key = cipher_text_only(cipher)
    return Subs(key).decode(cipher)


subs = Subs({'A': 'R', 'B': 'Y', 'C': 'B', 'D': 'Z', 'E': 'W', 'F': 'S', 'G': 'U', 'H': 'D', 'I': 'F', 'J': 'I', 'K': 'H', 'L': 'T', 'M': 'N', 'N': 'L', 'O': 'A', 'P': 'E', 'Q': 'K', 'R': 'G', 'S': 'C', 'T': 'P', 'U': 'Q', 'V': 'X', 'W': 'O', 'X': 'V', 'Y': 'M', 'Z': 'J'})
print(subs.key)
print(subs.key_inv)
cipher = subs.encode("LA CIGALE AYANT CHANTE TOUT LETE SE TROUVA FORT DEPOURVUE QUAND LA BISE FUT VENUE")
print(cipher)
print(subs.decode("TR BFURTW RMRLP BDRLPW PAQP TWPW CW PGAQXR SAGP ZWEAQGXQW KQRLZ TR YFCW SQP XWLQW"))
print(decode_cipher_text_only("TR BFURTW RMRLP BDRLPW PAQP TWPW CW PGAQXR SAGP ZWEAQGXQW KQRLZ TR YFCW SQP XWLQW"))
