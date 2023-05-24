
<!-- on appelle le script qui nous permettra de contrôler la quantité des produits-->
<script type="text/javascript" src="./script/scriptBoutique.js"></script>

<h1>Boutique</h1>
<?php
    if(isset($_SESSION['produit'])){
        $produit =$_SESSION['produit'];
    }
?>
    <div class="row mt-2 mr-0">
        <div class="col text-center">
            <img src="images/<?php echo $produit; ?>.jpg" class="rounded" alt="Produit non defini" width="60%"/>
        </div>
        <div class="col text-center">
            <form action="controleurs/panier.php" method="GET">
            <h3><label for="quantite">Quantité :</label>
            <input type="text" name="quantite" id="quantite" value="1" size="2" onselect="bloque_champ(this);" onfocus="bloque_champ(this);"/>
                <!-- on peut utiliser onselect ou onclick mais il faut gérer pas seulement onfocus -->
            <input type="button" value="-" onclick="clic_moins();" />
            <input type="button" value="+" onclick="clic_plus();" /></h3>
            </br>
            <input type="submit" class="btn btn-primary my-2 my-sm-0 btn-lg" value="Ajouter au panier"/>
        </div>
        <div class="col text-center mr-0">
        </div>
    </div>
