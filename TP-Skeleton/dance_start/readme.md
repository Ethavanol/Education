
# Objectif de ce code
(Ce code est indépendant de tout le reste du dépôt)

À partir d'une vidéo d'une personne source et d'une autre d'une personne, notre objectif est de générer une nouvelle vidéo de la cible effectuant les mêmes mouvements que la source. 

[Allez voir le sujet du TP ici](http://alexandre.meyer.pages.univ-lyon1.fr/m2-apprentissage-profond-image/am/tp_dance/)

# Utilisation du code

# 1 - Lancement

Comme ceci a été implémenté de base : changer le GEN_TYPE à 1, 2, 3 ou 4 suivant l'option de génération d'images que vous souhaitez.

# 2 - Entraînement Vanilla ou GAN

Il suffit de lancer les fichiers "GenVanillaNN.py" ou "GenGAN.py" pour lancer l'entraînement des modèles.

Les entraînements ont été réalisés sur 200 epochs dans les deux cas. 
N'ayant qu'une carte graphique intégrée sur mon PC, il m'aurait été compliqué de faire plus et pas spécialement bénéfique.
Les poids ont été sauvegardés dans "data/weights/" dans les deux cas.

Pour ce qui est du Vanilla, l'erreur utilisée a été la MSELoss. C'est celle qui me paraissait être la plus judicieuse.
Mes valeurs étant entre -1 et 1 à la sortie du modèle (à cause du Tanh à la fin du modèle), j'avais le choix entre la L1Loss
ou la MSELoss, j'ai opté pour cette dernière car elle semblait donner de meilleurs résultats.

Pour ce qui est du GAN, l'erreur utilisée est la BCELoss pour les loss liées au Discriminateur (possible de l'utiliser grâce à la dernière couche Sigmoid).
Puis, on utilise la MSELoss pour calculer la perte entre l'image générée par le générateur et l'image cible.
L'erreur du Générateur est égale à la somme de l'erreur entre le réalisme de la photo générée et 100 fois l'erreur entre l'image générée et l'image cible.
Le facteur 100 est mis dans le but de ne pas avoir tout le temps la même image (mode collapse, problème auquel j'ai été confronté au début) et que l'image générée ressemble bien à l'image source.

Voici un graphique représentant les courbes de pertes du Générateur et du Discriminateur du GAN durant l'entraînement subi.
(Si celui-ci ne s'affiche pas, vous pouvez le voir dans le dossier plots)

![alt text](plots/image.png)

