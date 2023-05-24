
function testNumerique(e){
    var tb_nb = document.getElementById("champTel");
    var string_tel = tb_nb.value;
    //var tb_message = document.getElementById("message");
    var caractere = carClavier(e); // Récupération du caractère associé à l'événement

    if (carEffacement(e))  //Teste s'il s'agit d'un caractère d'effacement
        return true;
    else {
        if (caractere < "0" || caractere > "9") {
            return false;
        }
        else {
            return true;
        }
    }
}

function testLettre(e){
    var tb_champ = document.getElementById("champPrenom");
    var string_tel = tb_champ.value;
    //var tb_message = document.getElementById("message");
    var caractere = carClavier(e); // Récupération du caractère associé à l'événement

    if (carEffacement(e))  //Teste s'il s'agit d'un caractère d'effacement
        return true;
    else {
        if ((caractere < "A" || caractere > "Z") && (caractere < "a" || caractere > "z")) {
            return false;
        }
        else {
            return true;
        }
    }
}

function testEspace(e){
    var tb_champ = document.getElementById("champPrenom");
    var string_tel = tb_champ.value;
    //var tb_message = document.getElementById("message");
    var caractere = carClavier(e); // Récupération du caractère associé à l'événement

    if (carEffacement(e))  //Teste s'il s'agit d'un caractère d'effacement
        return true;
    else {
        if (caractere < " " || caractere > " "){
            return true;
        }
        else {
            return false;
        }
    }
}

function carClavier(e){
    var unCaractere;
    if (window.event)
    // Pour Internet Explorer
        unCaractere = String.fromCharCode(window.event.keyCode);
    else
        unCaractere = String.fromCharCode(e.which); //on recupere le caractère tapé suivant le navigateur
    return unCaractere;
}

function carEffacement(e){
    var codeCaractere;
    if (window.event)
        codeCaractere = window.event.keyCode;
    else
        codeCaractere = e.which;

    if((codeCaractere == 0) || (codeCaractere == 8))
        return true;
    else
        return false;
}

function bloque_champ(champ){
    champ.blur();
}

function clic_moins(){
    var champ = document.getElementById("quantite");
    var qte = parseInt(champ.value);
    qte --;
    champ.value = qte;
}

function clic_plus(){
    var champ = document.getElementById("quantite");
    var qte = parseInt(champ.value);
    qte ++;
    champ.value = qte;
}

mail = /^[a-zA-Z0-9]+[a-zA-Z0-9\.-_]+@(([a-zA-Z0-9\-])+\.)+([a-zA-Z0-9])+$/;
function verifieMail(champmail){
    email = champmail.value;
    reponse = mail.test(email);

    if (reponse)
        alert("Adresse e-mail valide");
    else
        alert("Adresse e-mail invalide !");
}




