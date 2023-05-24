<?php
session_start(); 
// on inclut la méthode de dialogue avec la BD
// code concernant l'appel de la requête SQL
require('../modele/modele.php');
try {
// on crée un objet référant la classe Modele
    $undlg = new Modele();
    $unUtilisateur = $undlg->getUtilisateur($_POST['login'],$_POST['mdp']);
    foreach ($unUtilisateur as $ligne) {
        $login = $ligne['username'];
        $id = $ligne['id'];
        $mdp = $ligne['password'];
    }
    // l'utilisateur existe dans la table
    // on ajoute ses infos en tant que variables de session
    if (isset($login) && isset($mdp))
    {
        $_SESSION['login'] = $login;
        $_SESSION['mdp'] = $mdp;
        // cette variable indique que l'authentification a réussi
        $authOK = true;
        $_SESSION['authOK'] = $authOK;
    }
    
    header("Location: ../index.php");

} catch (Exception $e) {
    $erreur = 
    $e->getMessage();
    header("Location: ../index.php?error=".$erreur);
}
?>