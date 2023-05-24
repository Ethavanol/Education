<?php
session_start(); 
// on inclut la méthode de dialogue avec la BD
// code concernant l'appel de la requête SQL
require('../modele/modele.php');
try {
// on crée un objet référant la classe Modele
    $undlg = new Modele();
    $undlg->ajouterUtilisateurDonnees($_POST['prenom'], $_POST['nom'], $_POST['add1'], $_POST['add2'], $_POST['add3'], $_POST['postal'], $_POST['telephone'], $_POST['mail']);
    $customerId = $undlg->getMaxId();
    var_dump($customerId);
    foreach ($customerId as $ligne) {
        $id = $ligne['MAX(id)'];
    }
    echo $id;
    $undlg->ajouterUtilisateurLogins($id, $_POST['pseudo'], $_POST['mdpCreation']);
    
    header("Location: ../index.php?page=connexion");

} catch (Exception $e) {
    $erreur = 
    $e->getMessage();
    header("Location: ../index.php?error=".$erreur);
}
?>