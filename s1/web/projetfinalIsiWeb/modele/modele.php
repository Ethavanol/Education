<?php
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the templat
e in the editor.
*/
/**
* Description of Connexion
*
* @author christian.vial
*/
class Modele
{
//put your code here
    private $connexion=null;
    private $dbhost;
    private $dbbase;
    private $dbuser;
    private $dbpwd;


    public static function getConnexionBdd() {
        $dbhost = '127.0.0.1';
        $dbbase = 'nombase';
        $dbuser = 'nomuser';
        $dbpwd = 'motdepasse';
        try {
            $connexion = new PDO("mysql:host=$dbhost;dbname=$dbbase", $dbuser, $dbpwd);
            $connexion->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
            $connexion->exec('SET CHARACTER SET utf8');
        } catch (PDOException $e) {
            $erreur = $e->getMessage();
        }
        return $connexion;
    }

    public static function deConnexionBdd() {
    try {
        $connexion = null;
    } 
    catch (PDOException $e) {
        $erreur = $e->getMessage();
    }
    }


    public function getTousLesAdherents() {
        try {
        $connexion = $this->getConnexionBdd();
        $sql = "SELECT * FROM `logins`;";
        $sth = $connexion->prepare($sql);
        $sth->execute();
        $tabadherents =$sth->fetchAll(PDO::FETCH_ASSOC);
        return $tabadherents;
        } catch (PDOException $e) {
        $erreur = $e->getMessage();
        }
    }


    public function getUtilisateur($log, $mdp) {
        try {
            $connexion = $this->getConnexionBdd();
            $sql = "SELECT * FROM `logins` WHERE username='$log' AND password='$mdp';";
            $sth = $connexion->prepare($sql);
            $sth->execute();
            $tabadherents = $sth->fetchAll(PDO::FETCH_ASSOC);
            return $tabadherents;
        } catch (PDOException $e) {
            $erreur = $e->getMessage();
        }
    }


    public function ajouterUtilisateurDonnees($prenom, $nom, $add1, $add2, $add3, $postcode, $tel, $mail) {
        try{
            $connexion = $this->getConnexionBdd();
            $sql = "INSERT INTO customers(forname,surname,add1,add2,add3,postcode,phone,email,registered) 
            VALUES ('$prenom', '$nom', '$add1', '$add2', '$add3', $postcode, $tel, '$mail', 1);'";
            $sth = $connexion->prepare($sql);
            $sth->execute();
        } catch (PDOException $e) {
            $erreur = $e->getMessage();
        }
    }

    public function getMaxId(){
        try{
            $connexion = $this->getConnexionBdd();
            $sql = "SELECT MAX(id) FROM customers";
            $sth = $connexion->prepare($sql);
            $sth->execute();
            $tabMaxId = $sth->fetchAll(PDO::FETCH_ASSOC);
            return $tabMaxId;
        } catch (PDOException $e) {
            $erreur = $e->getMessage();
        }
    }

    public function ajouterUtilisateurLogins($id, $log, $mdp) {
        try{
            $connexion = $this->getConnexionBdd();
            $sql = "INSERT INTO logins(customer_id, username, password) VALUES ($id, '$log', '$mdp');'";
            $sth = $connexion->prepare($sql);
            $sth->execute();
        } catch (PDOException $e) {
            $erreur = $e->getMessage();
        }
    }

    
    public function deconnexion(){
        try{
            $_SESSION = [];
            /*$_SESSION['login'] = null;
            $_SESSION['mdp'] = null;
            $_SESSION['authOK'] = false;*/
        } catch (PDOException $e) {
            $erreur = $e->getMessage();
        }
    }

}