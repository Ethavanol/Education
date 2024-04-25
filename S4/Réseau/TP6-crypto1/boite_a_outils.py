import string

frequences_francais = {
    'A': 8.15,
    'B': 0.97,
    'C': 3.15,
    'D': 3.73,
    'E': 17.39,
    'F': 1.12,
    'G': 0.97,
    'H': 0.85,
    'I': 7.31,
    'J': 0.45,
    'K': 0.02,
    'L': 5.69,
    'M': 2.87,
    'N': 7.12,
    'O': 5.28,
    'P': 2.80,
    'Q': 1.21,
    'R': 6.64,
    'S': 8.14,
    'T': 7.22,
    'U': 6.38,
    'V': 1.64,
    'W': 0.03,
    'X': 0.41,
    'Y': 0.28,
    'Z': 0.15
}

def calcul_iterations_letter_message(message):
    iterationByLetter = {}
    message = message.upper()
    for lettre in string.ascii_uppercase:
        iterationByLetter[lettre] = 0

    for lettre in message:
        # Ignorer les caractères qui ne sont pas des lettres
        if lettre.isalpha():
            iterationByLetter[lettre] += 1

    return iterationByLetter


def calcul_frequence_letter_message(message):
    dictionnaire_iterations = calcul_iterations_letter_message(message)
    freqByLetter = {}
    saisiesTotal = sum(dictionnaire_iterations.values())

    for lettre, iterations in dictionnaire_iterations.items():
        freqByLetter[lettre] = (iterations / saisiesTotal) * 100

    return freqByLetter


def calcul_distance_frequences_francais(dictionnaire_freq):
    distance = 0
    for lettre in dictionnaire_freq:
        difference = dictionnaire_freq[lettre] - frequences_francais[lettre]
        distance += abs(difference)

    return distance


def calcul_indice_coincidence(dictionnaire_iterations):
    somme_freq = sum(iteration * (iteration - 1) for iteration in dictionnaire_iterations.values())
    total_iterations = sum(dictionnaire_iterations.values())
    indice_coincidence = somme_freq / (total_iterations * (total_iterations - 1))
    return indice_coincidence
