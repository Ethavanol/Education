using System;

namespace WebmangaAspCore.Models.Metier
{
    public class Manga
    {
        private int id_manga;
        private int id_dessinateur;
        private int id_scenariste;
        private Double prix;
        private String titre;
        private DateTime dateParution;
        private String couverture;
        private int id_genre;

        public int Id_manga { get => id_manga; set => id_manga = value; }
        public int Id_dessinateur { get => id_dessinateur; set => id_dessinateur = value; }
        public int Id_scenariste { get => id_scenariste; set => id_scenariste = value; }
        public double Prix { get => prix; set => prix = value; }
        public string Titre { get => titre; set => titre = value; }
        public string Couverture { get => couverture; set => couverture = value; }
        public int Id_genre { get => id_genre; set => id_genre = value; }
        public DateTime DateParution { get => dateParution; set => dateParution = value; }
    }
}
