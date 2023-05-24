

    <a href="./static/afficheInfos.php">Affichage des adhérents</a>
    <!-- on appelle le script qui nous permettra de contrôler les saisies du formulaire-->
    <script type="text/javascript" src="./script/script.js"></script>

<?php
    if(isset($_SESSION['authOK']) && ($_SESSION['authOK'] == true)){
        echo 'Vous êtes déjà connectés';
    }
    else {
?>
<div class="row">
    <div class="col text-center">
    <h1>Connectez-vous</h1> 
    <form action="controleurs/authentification.php" method="post">
        <label for="champNom">&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp; Login:</label>
        <input type="text" name="login" id="champNom" required />
        <p> &nbsp &nbsp; </p>
        <label for="champMdp">Mot de passe :</label>
        <input type="password" name="mdp" id="champMdp" required /></br>
        <input type="submit" value="Connexion">
    </form>
    </div>
        <div class="col text-center">
            <h1>Créez-vous un compte</h1>

            <form action="controleurs/creation.php" method="post">
                <!-- pour le prenom et le nom, on veut seulement des lettres-->
                <label for="champPrenom">Prenom:</label>
                <input type="text" name="prenom" id="champPrenom" onKeyPress="return(testLettre(event));" required /></br>
                <label for="champNom">Nom:</label>
                <input type="text" name="nom" id="champNom" onKeyPress="return(testLettre(event));" required /></br>
                <!-- pour le numéro de tél, on veut seulement des nombres et on en veut 10 maximum -->
                <label for="champTel">N° téléphone:</label>
                <input type="text" name="telephone" id="champTel" size="10" maxlength="10" onKeyPress="return(testNumerique(event));" required /></br><!-- seulement des nb -->
                <!-- on veut que l'adresse mail ait le "look" d'une adresse mail-->
                <label for="champMail">Mail:</label>
                <input type="text" name="mail" id="champMail" size="30" onchange="verifieMail(this);" required /></br>
                <!-- onchange : se déclenche chaque fois que l'on perd le focus d'un champ après avoir modifié
                sa valeur (et non à chaque frappe de caractères) -->
                <label for="addresse">Adresse :</label>
                <input type="text" name="add1" id="addresse"/>
                <input type="text" name="add2" id="addresse"/>
                <!-- pour la ville,  on veut seulement des lettre-->
                <input type="text" name="add3" id="addresse" onKeyPress="return(testLettre(event));"/>
                (ex: 13 avenue Rodriguez) - (ex: indices d'appartement) - (ville)</br>
                <!-- pour le code postal, on veut seulement des nombres. On en veut 5 maximum-->
                <label for="champPostal">Code Postal:</label>
                <input type="text" name="postal" id="champPostal" size="5" maxlength="5" onKeyPress="return(testNumerique(event));" required /></br><!-- seulement des nb -->
                <label for="champPseudo">Pseudo:</label>
                <input type="text" name="pseudo" id="champPseudo" required /></br>
                <!-- pour le mdp, on ne veut pas qu'un espace puisse être "saisi"-->
                <label for="champMdp">Mot de passe :</label>
                <input type="password" name="mdpCreation" id="champMdp" onKeyPress="return(testEspace(event));" required /></br><!-- hasher le mdp-->
                <input type="submit" value="Créer un compte">
            </form>
        </div>
    </div>
<?php } 
?>