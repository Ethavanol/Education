<?php
session_start();    

    $_SESSION['quantite'] = $_GET['quantite'];

    header("Location: ../index.php?page=panier");
?>