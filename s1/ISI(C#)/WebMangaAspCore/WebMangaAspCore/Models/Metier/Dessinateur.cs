using System;

namespace WebmangaAspCore.Models.Metier
{
public   class Dessinateur
    {
        private int id_dessinateur;
        private String nom_dessinateur;
        private String prenom_dessinateur;

        public Dessinateur(int id_dessinateur, string nom_dessinateur, string prenom_dessinateur)
        {
            this.Id_dessinateur = id_dessinateur;
            this.Nom_dessinateur = nom_dessinateur;
            this.Prenom_dessinateur = prenom_dessinateur;
        }

        public string Prenom_dessinateur { get => prenom_dessinateur; set => prenom_dessinateur = value; }
        public int Id_dessinateur { get => id_dessinateur; set => id_dessinateur = value; }
        public string Nom_dessinateur { get => nom_dessinateur; set => nom_dessinateur = value; }
    }

}