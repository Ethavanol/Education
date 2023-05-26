using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using dllLoto; // on fait référence au package dllLoto
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ProgressBar;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TextBox;

namespace Memory
{
    public partial class Memory : Form
    {
        // Déclaration des variables globales du jeu
        int nbCartesDansSabot; //nombre de cartes dans le sabot (nb images dans réservoir)
        int nbCartesSurTapis; //nombre de cartes sur le tapis (ici 12)
        int[] tImagesCartes; //le tableau qui contiendra les indices des 6 différentes images du jeu
        int maxValTirage; //l'indice maximum que l'on pourra tirer aléatoirement
        int premierTirage; //l'indice de la première carte retournée
        int[] tabAleat; // le tableau qui contiendra les valeurs aléatoires
        bool[] tCartesARetourner = new bool[] {true, true, true, true, true, true ,true, true, true, true, true, true};
        //un tableau de booléen dans lequel il y autant de cases que de cartes sur le tapis. Toutes initialisées
        //à True, les cartes seront retournées seulement si leur index correspondant vaut true dans ce tableau
        int nbCartesRetournees = 0; // nombre de cartes qui sont retournées à l'instant actuel
        bool Victoire = false, Defaite = false; //Victoire Vaut true, si le joueur a gagné
        //Defaite vaut true si le joueur a perdu
        bool resteCartes = true; //Booléen qui indique si oui ou non il reste des cartes à retourner
        //on se servira de se booléen pour déterminer Victoire ou Défaite

        //initialisation d'un entier secondes, pour le timer et d'un entier score, pour le score
        int secondes, score;
        //initialisation d'un booléen VictoireManche : si il est vrai on fait score+=10, sinon score-=2
        bool victoireManche;

        public Memory(Label label_Distrib = null)
        {
            InitializeComponent();
        }

        private void tlpTapisDeCartes_Paint(object sender, PaintEventArgs e)
        {

        }

        //Fonction appelée à chaque fois que l'on veut distribuer des cartes
        private void Distribution_Aleatoire()
        {

            // on récupère le nb de cartes dans le sabot (= nb images dans réservoir)
            nbCartesDansSabot = ilSabotDeCartes.Images.Count - 1;
            // on enlève 1 car l'image d'indice 0 ne compte pas, c'est celle du dos des cartes
            // On récupère également le nb d'images à disposer sur le tapis;
            // autrement dit, le nb de controles présents dans le conteneur
            nbCartesSurTapis = tlpTapisDeCartes.Controls.Count;
            //on utilise la LotoMachine pour générer une série aléat parmi le nb de Cartes qu'il y a à disposition
            LotoMachine hasard = new LotoMachine(nbCartesDansSabot);
            //On veut des couples de cartes. on veut donc tirer un nombre de cartes différentes correspondant
            //à la moitié du nombre de places "disponibles" pour les cartes, d'où le nbCartesSurTapis/2
            tImagesCartes = hasard.TirageAleatoire(nbCartesSurTapis/2, false);

            // On dit que toutes les cartes doivent être retournées pour qu'à chaque fois
            // que l'on distribue de nouvelles cartes, elles soient toutes retournées
            for(int j = 0; j< nbCartesSurTapis; j++)
            {
                tCartesARetourner[j] = true;
            }

            // Je sais que le contrôle est une PictureBox
            // donc je "caste" l'objet (le contrôle) en PictureBox...
            PictureBox carte;

            //on "active" toutes les PictureBox, pour que ces dernières "réagissent" lorsqu'on clique dessus.
            //On les met ici, car on veut que l'appel aux fonctions suite à un click sur une carte ne marche
            //que lorsqu'on a distribué des cartes
            foreach (Control ctrl in tlpTapisDeCartes.Controls)
            {
                carte = (PictureBox)ctrl;
                carte.Enabled = true;
            }

            //On initialise un tableau tabAleat de taille nbCartesSurTapis (=12) dans lequel on stockera
            //une liste aléatoires de 12 chiffres : 6 * 2 indices similaires (de 1 à 6). A l'aide de ces indices
            //il ne nous restera plus qu'à afficher les cartes stockées dans tImagesCartes d'indice correspondant
            tabAleat = new int[nbCartesSurTapis];
            // le tableau qui contient les 6 couples de même indice
            int[] tableauTuples = new int[] { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6};
            //la valeur maximale pour laquelle on tirera un nombre au hasard:
            maxValTirage = nbCartesSurTapis;


            Random rndSeeds = new Random();
            Random rnd = new Random(rndSeeds.Next());

            
            for(int i = 0; i<nbCartesSurTapis; i++)
            {
                // On tire un nouvelle valeur aléatoire entre 0 et maxValTirage-1 (la fonction est comme ça)
                // cette valeur sera passée en indice dans le tableau tableauTuples. On stockera ensuite dans
                // tabAleat, la valeur tableauTuples[valeur], puis on enlèvera tableauTuples[valeur] de tableauTuples
                // et on décalera toutes les valeurs après vers la gauche. On soustraira 1 de maxValTirage, puis
                // on recommencera l'opération jusqu'à que tableauTuples soit vide, et donc que tabAleat soit plein.
                // Et on aura un tableau aléatoire de 12 nombres comportant les 6 tuples
                int valAleat = rnd.Next(0, maxValTirage);
                // On stocke tableauTuples d'indice cette valeur dans notre tabAleat d'indice i
                tabAleat[i] = tableauTuples[valAleat];
                // On enlève la valeur de tableauTuples d'indice cette valeur et on décale
                //toutes les valeurs du tableau
                for(int j = valAleat; j<nbCartesSurTapis-1; j++)
                {
                    tableauTuples[j] = tableauTuples[j + 1];
                }
                //on décrémente maxValTirage, puisqu'on a enlevé une valeur de
                //notre tableau puis décalé les valeurs restantes
                maxValTirage--;
            }
           
            //affectation des images au picturebox
            //maintenant qu'on a une liste aléatoire de 6*2 indices de tImagesCartes (de 1 à 6),
            //on affecte les img à chaque controle du tapis (chaque PictureBox)
            //On a 6 nombres tirés aléatoirement et différents stockés dans tImagesCartes. En s'aidant
            //des 6 tuples d'indices allant de 1 à 6 tirés aléatoirement, de tabAleat, nous n'avons 
            // plus qu'à fare pour chaque PictureBox tImagesCartes[tabAleat[i]].
            int i_image;
            for (int i_carte = 0; i_carte < nbCartesSurTapis; i_carte++)
            {
                //on définit carte comme la première case du tapis (Controle 0)
                carte = (PictureBox)tlpTapisDeCartes.Controls[i_carte];
                //l'indice de l'image est égal à la valeur de tImagesCartes d'indice tabAleat[i_carte]
                i_image = tImagesCartes[tabAleat[i_carte]];
                //on met dans la variable Image de carte, l'image correspondante
                carte.Image = ilSabotDeCartes.Images[i_image];
            }
        }

        //Fonction qui sert à retourner les cartes
        private void Retourner_Les_Cartes()
        {
            PictureBox carte;
            nbCartesRetournees = 0;
            secondes = 0;

            foreach (Control ctrl in tlpTapisDeCartes.Controls)
            {
                if (tCartesARetourner[ctrl.TabIndex] == true)
                {
                    // Je sais que le contrôle est une PictureBox donc je "caste"
                    // l'objet (le contrôle) en PictureBox et je m'adresse à son contrôle
                    carte = (PictureBox)ctrl;
                
                    // Ensuite je peux accéder à la propriété Image
                    // je sais que l'indice de "DosCarte" est 0 dans ma liste d'images
                    // donc je mets toutes les Images des PictureBox de mon jeu à 0
                    carte.Image = ilSabotDeCartes.Images[0];
                }
            }
        }

        private void pb_YY_Click(object sender, EventArgs e)
        {
            // si le tirage aléatoire n'a pas encore effectué, on ne pourra afficher aucune carte
            if (tImagesCartes == null)
            {
                MessageBox.Show("Commencez par jouer ou distribuer des cartes", "Alerte");
            }
            else // sinon, on retourne une carte
            {
                PictureBox carte1, carte2;
                int i_carte1, i_carte2, i_image1, i_image2;
                resteCartes = false; // par défaut, on dit qu'il ne reste aucune Cartes
                nbCartesRetournees++; // on incrémente le nombre de cartes retournées
                victoireManche = false; //par défaut, on dit que la manche n'est pas gagnée
                
                if (nbCartesRetournees == 1)
                {
                    //si c'est la première carte retournée, on démarre le timer à 3 secondes
                    secondes = 3;
                    timer.Start();

                    //et on retourne la carte
                    carte1 = (PictureBox)sender;
                    i_carte1 = Convert.ToInt32(carte1.Tag) - 1;
                    i_image1 = tImagesCartes[tabAleat[i_carte1]];
                    // on stocke dans la variable globale (pour pouvoir garder sa valeur même
                    // quand on sortira de la boucle) premierTirage l'indice de l'image correspondante
                    premierTirage = i_carte1;
                    carte1.Image = ilSabotDeCartes.Images[i_image1];
                }
                //si il y a déjà une carte de retournée (donc qu'on retourne la deuxième carte)
                else if (nbCartesRetournees == 2)
                {
                    // On ne rédemmare pas le timer
                    //on retourne la carte
                    carte2 = (PictureBox)sender;
                    i_carte2 = Convert.ToInt32(carte2.Tag) - 1;
                    i_image2 = tImagesCartes[tabAleat[i_carte2]];
                    carte2.Image = ilSabotDeCartes.Images[i_image2];
                    //si les indices de leurs deux images correspondent
                    if (i_image2 == tImagesCartes[tabAleat[premierTirage]])
                    {
                        victoireManche = true;//on dit que le joueur a gagné cette manche
                        //on dit qu'il ne faut plus retourner ces deux cartes
                        tCartesARetourner[premierTirage] = false;
                        tCartesARetourner[i_carte2] = false; 
                        //On recatse l'objet carte1 en PictureBox (celle correspondant)
                        // à la première carte retournée
                        carte1 = (PictureBox)tlpTapisDeCartes.Controls[premierTirage];
                        //et on désactive les carte, pour qu'un click dessus n'appelle plus cette fonction
                        carte1.Enabled = false; 
                        carte2.Enabled = false;
                        // On regarde si il reste des cartes que l'on doit retourner
                        for (int i = 0; i < nbCartesSurTapis; i++)
                        {
                            if (tCartesARetourner[i] == true)
                            {
                        //si il reste au moins une carte à retourner, alors resteCartes est vrai et on quitte la boucle
                                resteCartes = true; break;
                            }
                        }
                        if (resteCartes == false)
                        {
                    // si il ne reste plus de cartes à retourner, alors Victoire est true
                            Victoire = true;
                        }
                    }
                }
                else// cas nbCartesRetournees == 0 et nbCartesRetournees > 2
                {

                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void btn_Distribuer_Click(object sender, EventArgs e)
        {
            PictureBox carte;
            Distribution_Aleatoire();
            //on rend visible les messages d'information et certains invisibles
            // on le fait sur ce bouton et non dans la fonction Distribuer(), car le click
            // sur le bouton Jouer  appelle la fonction et on ne veut pas afficher les mêmes choses.
            lb_chrono.Visible = true;
            label1.Visible = true;
            label2.Visible = true;
            lb_score1.Visible = false;
            lb_score_var.Visible = false;
            lb_info1.Visible = true;
            lb_info2.Visible = false;
        }

        private void btn_Retourner_Click(object sender, EventArgs e)
        {
            Retourner_Les_Cartes();
        }

        private void btn_Jouer_Click(object sender, EventArgs e)
        {
            PictureBox carte;
            //on remet letimer à 0
            secondes = 0;
            Distribution_Aleatoire();
            Retourner_Les_Cartes();
            // on initialise le score à 0
            score = 0;
            //on rend visible certains messages d'information et d'autres invisibles
            // on le fait sur ce bouton et non dans la fonction Distribuer(), car le click sur
            // le bouton Distribuer appelle la fonction et on ne veut pas afficher les mêmes choses.
            lb_score_var.Text = score.ToString();
            lb_chrono.Visible = true;
            label1.Visible = true;
            label2.Visible = true;
            lb_score1.Visible = true;
            lb_score_var.Visible = true;
            lb_info1.Visible = false;
            lb_info2.Visible = false;
        }

        //Pour tous les clicks sur les PictureBox, on fait appel à la fonction
        //pb_YY_Click(object sender, EventArgs e) en passant en paramètre
        //l'index de ce controle et l'événement e.
        private void pictureBox1_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_01.TabIndex], e);
        }

        private void pb_02_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_02.TabIndex], e);
        }

        private void pb_03_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_03.TabIndex], e);
        }

        private void pb_04_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_04.TabIndex], e);
        }

        private void pb_05_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_05.TabIndex], e);
        }

        private void pb_06_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_06.TabIndex], e);
        }

        private void pb_07_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_07.TabIndex], e);
        }

        private void pb_08_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_08.TabIndex], e);
        }

        private void pb_09_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_09.TabIndex], e);
        }

        private void pb_10_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_10.TabIndex], e);
        }

        private void pb_11_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_11.TabIndex], e);
        }

        private void pb_12_Click(object sender, EventArgs e)
        {
            pb_YY_Click(tlpTapisDeCartes.Controls[this.pb_12.TabIndex], e);
        }

        private void pb_Recherche_Click(object sender, EventArgs e)
        {

        }

        private void timer_Tick(object sender, EventArgs e)
        {
            lb_chrono.Text = secondes--.ToString();//on actualise l'affichage du nombre de secondes
            if (secondes < 0) //si secondes dépasse 0
            {
                timer.Stop(); //on arrête le timer
                Retourner_Les_Cartes(); // on retourne les cartes
                nbCartesRetournees = 0; //on met le nombre de Cartes Retournées à 0
                //si le joueur a retourné deux même cartes, il gagne 5 points, dans tous 
                // les autres cas, il en perd 2
                if (victoireManche == true)
                {
                    score += 5;
                }
                else { score -= 2; }
                // si le socre atteint -6 points, le joueur a perdu
                if (score <= -6)
                {
                    Defaite = true;
                }
                // on actualise l'affichage du score
                lb_score_var.Text = score.ToString();
                //si Victoire ou Défaite est true (un des deux), on affiche un message
                // puis on réinitialise tous les paramètres comme au début
                if(Victoire == true)
                {
                    MessageBox.Show("Bien joué Bossman. Score : " + score, "Victoire!!");
                }
                if(Defaite == true)
                {
                    MessageBox.Show("T'es nul. Score :" + score, "Défaite");
                }
                if(Victoire == true || Defaite == true)
                {
                    //On remet invisible, tous les labels qui l'étaient au début
                    lb_chrono.Visible = false;
                    label1.Visible = false;
                    label2.Visible = false;
                    lb_score1.Visible = false;
                    lb_score_var.Visible = false;
                    lb_info1.Visible = true;
                    lb_info2.Visible = true;
                    //on redéfinit toutes les cartes/PictureBox comme "doivent être retournées"
                    for (int j = 0; j < nbCartesSurTapis; j++)
                    {
                        tCartesARetourner[j] = true;
                    }
                    //finalement, on retourne les cartes
                    Retourner_Les_Cartes();
                    Victoire = false;
                    Defaite = false;
                    //ceci dans le but de redonner l'aspect initial à notre interface
                    //(par exemple pour pouvoir rejouer).
                }
            }
        }

    }
}
