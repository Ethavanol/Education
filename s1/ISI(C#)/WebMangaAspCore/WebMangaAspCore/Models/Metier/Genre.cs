using System;

namespace WebmangaAspCore.Models.Metier
{
    public class Genre {

        private int id_genre;
        private String lib_genre;

        public Genre(int id_genre, string lib_genre)
        {
            this.id_genre = id_genre;
            this.lib_genre = lib_genre;
        }

        public int Id_genre { get => id_genre; set => id_genre = value; }
        public string Lib_genre { get => lib_genre; set => lib_genre = value; }
    }

}