using System;
using System.Data;
using WebmangaAspCore.Models.MesExceptions;
using WebmangaAspCore.Models.Persistance;
using WebmangaAspCore.Models.Metier;
using WebmangaAspCore.Models.Utilitaires;

namespace WebmangaAspCore.Models.Dao
{
    public class ServiceManga
    {
        /// <summary>
        /// Fonction qui retourne une collection de données n'appartenant
        /// pas à la même table
        /// </summary>
        /// <returns></returns>
        public static DataTable GetTousLesManga()
        {
            DataTable mesMangas;
            Serreurs er = new Serreurs("Erreur sur lecture des Mangas.", "Manga.getManags()");
            try
            {
                String mysql = "Select  id_manga,lib_genre,nom_dessinateur,nom_scenariste,dateParution,prix,couverture ";
                mysql += " from Manga join genre on   manga.id_genre  = genre.id_genre ";
                mysql += " join   dessinateur  on  manga.id_dessinateur  =  dessinateur.id_dessinateur";
                mysql += " join   scenariste   on  manga.id_scenariste   = scenariste.id_scenariste ";

                mesMangas = DBInterface.Lecture(mysql, er);

                return mesMangas;
            }
            catch (MonException e)
            {
                throw new MonException(er.MessageUtilisateur(), er.MessageApplication(), e.Message);
            }
        }

        /// <summary>
        /// Fonction qui retourne un manga
        /// </summary>
        /// <returns></returns>
        public static Manga GetunManga(String id)
        {
            DataTable dt;
            Manga unManga = null;
            Serreurs er = new Serreurs("Erreur sur lecture des Mangas", "ServiceManga.getunManag()");
            try
            {
                String mysql = "Select  id_manga,id_genre,id_dessinateur,id_scenariste,titre,dateParution,prix,couverture ";
                mysql += " from Manga ";
                mysql += " where id_manga = " + id;
                dt= DBInterface.Lecture(mysql, er);
                if (dt.IsInitialized && dt.Rows.Count > 0)
                {
                    unManga = new Manga();
                    DataRow dataRow = dt.Rows[0];
                    unManga.Id_manga = int.Parse(dataRow[0].ToString()); 
                    unManga.Id_genre = int.Parse(dataRow[1].ToString());
                    unManga.Id_dessinateur = int.Parse(dataRow[2].ToString());
                    unManga.Id_scenariste = int.Parse(dataRow[3].ToString());
                    unManga.Titre = dataRow[4].ToString();
                    unManga.DateParution = DateTime.Parse(dataRow[5].ToString());
                    unManga.Prix = Double.Parse(dataRow[6].ToString());
                    unManga.Couverture = dataRow[7].ToString();
                    return unManga;
                }
                else
                    return null;
            }
            catch (MonException e)
            {
                throw new MonException(er.MessageUtilisateur(), er.MessageApplication(), e.Message);
            }
        }
    

/// <summary>
/// Fonction qui met à jour un manga
/// </summary>
/// <param name="unM"></param>
    public static void UpdateManga(Manga unM)
    {
        Serreurs er = new Serreurs("Erreur sur l'écriture d'un manga.", "ServiceManga.update()");
        String requete = "UPDATE Manga SET " +
                              "id_scenariste = " + unM.Id_scenariste + 
                              ", id_dessinateur = " + unM.Id_dessinateur + "" +
                              ", id_genre = " +  + unM.Id_genre + 
                              ", titre = '" + unM.Titre + "'" +
                               ", Prix = " +unM.Prix + 
                                 ", dateParution = '" + FonctionsUtiles.DateToString(unM.DateParution )+ "'" +
                               ",couverture = '" + unM.Couverture + "'" +
                               " WHERE id_manga =" + unM.Id_manga;
        try
        {
            DBInterface.Execute_Transaction(requete);
        }
        catch (MonException erreur)
        {
            throw erreur;
        }
    }

        public static DataTable GetTitreManga()
        {
            DataTable dt;
            Manga unManga = null;
            Serreurs er = new Serreurs("Erreur sur lecture des Mangas", "ServiceManga.GetTitreManga()");
            try
            {
                String mysql = "Select id_manga, titre";
            }
        }  

    }
}