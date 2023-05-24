function bloque_champ(champ){
    champ.blur();
}


function test(){
    document.write("penis");
}

function clic_moins(){
    var champ = document.getElementById("quantite");
    var qte = parseInt(champ.value);
    if(qte <= 1){
        champ.value = qte;
        alert("Vous ne pouvez pas commander une quantité nulle ou négative")
    }
    else {
        qte --;
        champ.value = qte;
    }
}

function clic_plus(){
    var champ = document.getElementById("quantite");
    var qte = parseInt(champ.value);
    qte ++;
    champ.value = qte;
}