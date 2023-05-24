<?php
session_start();

    $_SESSION['produit'] = $_GET['produit'];

    header("Location: ../index.php?page=boutique");

?>