<?php
session_start();                
ini_set('display_errors', 1);         
ini_set('display_startup_errors', 1); 
error_reporting(E_ALL); 
?>
<!DOCTYPE html>
<html>
<head>
    <link href="bootstrap4/css/bootstrap.css" rel="stylesheet">
    <link href="css/stylesheet.css" rel="stylesheet" media="all" type="text/css">
    <link rel="shortcut icon" type="image/x-icon" href="images/logoweb.jpg" />
</head>

<body>
    <?php
        var_dump($_SESSION);
       /* $authOK = false;
        if(isset($_SESSION['authOK'])){
            $authOK = $_SESSION['authOK'] == true;
        } 
        if(isset($_SESSION['auth2'])){
            $authOK = false;
        }*/?>

    <?php require('modele/modele.php');
    //require('inc/includes.php');  
//require('modele/modele.php');  
$controleur = 'accueil_controleur.php';
$vue = 'accueil_vue.php';

if(isset($_GET['page']))
{
    $pageName = $_GET['page'];

    $controleur = $pageName.'_controleur.php';
    $vue = $pageName.'_vue.php';
}

/* Header et menu */  
include('static/header.php');

include('static/menu.php');
//include('Controleurs/'.$controleur);
include('vues/'.$vue);
?>

</body>
</html>