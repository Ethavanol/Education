using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;
using WebmangaAspCore.Models.MesExceptions;


namespace WebmangaAspCore.Models.Persistance
{
    public class Connexion
    {
        private static MySql.Data.MySqlClient.MySqlConnection macnx;
        private static Connexion instance;
        /// <summary>
        /// Constructeur privé
        /// </summary>
        private Connexion() { }
        /// <summary>
        /// Connexion à MySql
        /// </summary>
        /// <returns>MysqlConnexion</returns>
        public MySqlConnection getConnexion()
        {
            string strConnexion;
            try
            {
                strConnexion = ConfigurationManager.ConnectionStrings["bddCourante"].ConnectionString;
        
                macnx = new MySqlConnection(strConnexion);
                macnx.Open();
               return macnx;
            }
            catch (MySqlException err)
            {
                throw new MonException("", "Erreur d'acces à la base.", err.Message);
            }
            catch (Exception e)
            {

                throw new MonException("", " Erreur d'accès", e.Message);
            }
        }

        /// <summary>
        /// Obtenir le singleton et le créer s'il n'existe pas
        /// </summary>
        public static Connexion getInstance()
        {
            if (Connexion.instance == null)
                Connexion.instance = new Connexion();
            return Connexion.instance;
        }

        /// <summary>
        /// Fermer la connexion si elle est ouverte
        /// </summary>
        public static void closeConnexion()
        {
            if (instance != null && macnx != null)
                macnx.Close();
        }

    }
}