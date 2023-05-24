<?php
session_start();
    require('../modele/modele.php');

    try {
        // on crée un objet référant la classe Modele
            if(isset($_GET['connexion'])){
                header("Location: ../index.php?page=connexion");
            }
            else {
                $undlg = new Modele();
                $unUtilisateur = $undlg->deconnexion(); // met un tableau vide dans $_SESSION
                //var_dump($_SESSION);
                header("Location: ../index.php");
            }
    } catch (Exception $e) {
        $erreur = 
        $e->getMessage();
        header("Location: ../index.php?error=".$erreur);
    }
    //$_SESSION['authOK'] = false
?>