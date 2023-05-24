

<nav class="navbar navbar-expand-lg navbar-dark bg-dark">
<a class="navbar-brand" href="index.php">Accueil</a>
<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
</button>
<div class="collapse navbar-collapse" id="navbarNavAltMarkup">
    <div class="navbar-nav mr-auto mt-2 mt-lg-0">
        <a class="nav-item nav-link" href="index.php?page=boissons">Boissons</a>
        <a class="nav-item nav-link" href="index.php?page=biscuits">Biscuits</a>
        <a class="nav-item nav-link" href="index.php?page=fruits_secs">Fruits Secs</a>
    </div>

    <form action="controleurs/deconnexion.php" method="GET">
    <?php
        //echo 'oui'.($authOK ? 'true' : 'false') ;
        if(isset($_SESSION['authOK']) && ($_SESSION['authOK'] == true)){
        echo '<button class="btn btn-secondary mr-sm-2 btn-lg" name="deconnexion" type="submit">Se Déconnecter</button>';
        } 
        else {
        echo '<button class="btn btn-secondary mr-sm-2 btn-lg" name="connexion" value="connexion" type="submit">Se Connecter</button>';
        } ?>
        </form>
        <button class="btn btn-primary my-2 my-sm-0 btn-lg" type="submit">
            Panier
        <!-- <img src="bootstrap4/bootstrap-icons-1.10.2/bag-check.svg" alt="Bootstrap" width="25" height="25"> -->
        </button>
    </form>

</div>
</nav>
