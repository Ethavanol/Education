using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Microsoft.AspNetCore.Mvc;
using WebmangaAspCore.Models.MesExceptions;
using WebmangaAspCore.Models.Metier;
using WebmangaAspCore.Models.Dao;
using Microsoft.AspNetCore.Http;

namespace WebmangaAspCore.Controllers
{
    public class MangaController : Controller
    {
        // GET: Manga
        // GET: Client
        public ActionResult Index()
        {
            System.Data.DataTable mesMangas = null;

            if (HttpContext.Session.GetInt32("id") != 0)
            {
                try
                {

                    mesMangas = ServiceManga.GetTousLesManga();
                }
                catch (MonException e)
                {
                    ModelState.AddModelError("Erreur", "Erreur lors de la récupération des clients : " + e.Message);
                }

                return View(mesMangas);
            }
            else

            return RedirectToAction("Index", "Home");
        }

        // GET: Commande/Edit/5
        public ActionResult Modifier(string id)
        {
            Manga unManga = null;
            try
            {
                unManga = ServiceManga.GetunManga(id);
                return View(unManga);
            }
            catch (MonException e)
            {
                return StatusCode(418);
            }
        }

        [HttpPost]
        public ActionResult Modifier(Manga unM)
        {
            try
            {
                ServiceManga.UpdateManga(unM);
                return View();
            }
            catch (MonException e)
            {
                return StatusCode(418);
            }
        }

        public ActionResult TitreManga()
        {
            System.Data.DataTable mesTitres = null;
            try
            {
                mesTitres = ServiceManga.GetTitreManga();
                return View(mesTitres);
            }
            catch (MonException e)
            {
                return StatusCode(418);
            }
        }

    }
}