/*
Instructions :

1 - Compléter le code ci-dessous pour avoir une implémentation
d'un arbre de type AVL.

2 - Faire des tests d'insertion, de suppression et de recherche (penser à faire une fonction d’affichage).
Faire en sorte d’avoir toutes les possibilités dans vos tests.

3 – Considérer le fichier "avl_bench.cpp". Il génère des ensembles de benchmarking avec des tailles d’arbre différentes :
de 2^5 éléments dans l’arbre à 2^25 éléments. Pour chaque taille, il donne 3 fichiers :
Values, Search et Delete, contenant respectivement les valeurs à insérer dans l’arbre,
les valeurs à rechercher, et celles à supprimer. Ajouter dans ce fichier (avl.cpp) les codes nécessaire pour lire
les fichiers de benchmark et effectuer les opérations correspondantes.

4 – Ajouter du code pour chronométrer les opérations. Réaliser des courbes comparatives
des temps d’exécutions des différentes opération en fonction de la taille de l’arbre.
Retrouvons-nous bien les complexité logarithmiques promises ?

*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>
#include <typeinfo>
using namespace std;

// Définition du type noeud de l'arbre ...
typedef struct node {
    struct node *left;
    uint64_t data;
    int height;
    struct node *right;

} node;


int getHeight(node* n) {
    if (n == NULL) {
        return 0;
    }
    else {
        return n->height;
    }
}


void updateHeight(node* n) {
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
}


int getBalanceFactor(node* n) {
    if (n == NULL) {
        return 0;
    }
    else {
        return getHeight(n->left) - getHeight(n->right);
    }
}


node* llrotation(node *n){ // Rotation LL
    node *p;
    node *tp;
    p = n;
    tp = p->left;

    p->left = tp->right;
    tp->right = p;

    updateHeight(p);
    updateHeight(tp);

    return tp;
}


node* rrrotation(node *n){ // Rotation RR
    node *p;
    node *tp;
    p = n;
    tp = p->right;

    p->right = tp->left;
    tp->left = p;

    updateHeight(p);
    updateHeight(tp);

    return tp;
}

node * rlrotation(node *n){
    node* tp = n;
    tp->right = llrotation(tp->right);
    tp = rrrotation(tp);
    return tp;
}


node* lrrotation(node *n){
    node* tp = n;
    tp->left = rrrotation(tp->left);
    tp = llrotation(tp);
    return tp;
}


node* insert(node *root, uint64_t data){
    if (root == NULL) {
        root = new node;
        root->data = data;
        root->right = NULL;
        root->left = NULL;
        root->height = 1;
    }
    else if (root->data > data) {
        root->left = insert(root->left, data);
    }
    else if (root->data < data) {
        root->right = insert(root->right, data);
    }
    else {
        return root;
    }

    updateHeight(root);
    int balance_factor = getBalanceFactor(root);

    if (balance_factor > 1 && getBalanceFactor(root->left) < 0) {
        return lrrotation(root);
    }
    else if (balance_factor > 1) {
        return llrotation(root);
    }
    else if (balance_factor < -1 && getBalanceFactor(root->right) > 0) {
        return rlrotation(root);
    }
    else if (balance_factor < -1) {
        return rrrotation(root);
    }

    return root;
}


node* search(node* root, uint64_t data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    else if (root->data > data) {
        return search(root->left, data);
    }
    else {
        return search(root->right, data);
    }
}


node* deleteNode(node* root, uint64_t data) {
    if (root == NULL) {
        return root;
    }
    else if (root->data > data) {
        root->left = deleteNode(root->left, data);
    }
    else if (root->data < data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }

        node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }

    if (root == NULL) {
        return root;
    }

    updateHeight(root);
    int balance_factor = getBalanceFactor(root);

    if (balance_factor > 1 && getBalanceFactor(root->left) >= 0) {
        return llrotation(root);
    }
    else if (balance_factor > 1 && getBalanceFactor(root->left) < 0) {
        return lrrotation(root);
    }
    else if (balance_factor < -1 && getBalanceFactor(root->right) <= 0) {
        return rrrotation(root);
    }
    else if (balance_factor < -1 && getBalanceFactor(root->right) > 0) {
        return rlrotation(root);
    }

    return root;
}


void afficherArbre(node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " (h=" << root->height << ") : ";
    if (root->left != NULL) {
        cout << root->left->data << " ";
    }
    else {
        cout << "- ";
    }
    if (root->right != NULL) {
        cout << root->right->data << " ";
    }
    else {
        cout << "- ";
    }
    cout << endl;
    afficherArbre(root->left);
    afficherArbre(root->right);
}


void afficherNode(node* n) {
    cout << n->data << " (h=" << n->height << ")"<<endl;
}


int main(){

    node * root = NULL;
    ifstream valuesToInsert("Values_5.txt");
    ifstream valuesToSearch("Search_5.txt");
    ifstream valuesToDelete("Delete_5.txt");

    if(valuesToInsert){
        string line;

        while(getline(valuesToInsert, line))
        {
          //  cout << typeid(line).name() << endl;
            uint64_t valueInsert;
            istringstream iss(line);
            iss >> valueInsert;
            root=insert(root, valueInsert);
        }
    }
    else{
        cout<<"Erreur de l'ouverture du fichier Insert"<<endl;
    }

    afficherArbre(root);

    cout << "------------------"<< endl;

    if(valuesToSearch){
        string line;

        while(getline(valuesToSearch, line))
        {
          //  cout << typeid(line).name() << endl;
            uint64_t valueSearch;
            istringstream iss(line);
            iss >> valueSearch;
            afficherNode(search(root, valueSearch));
        }
    }
    else{
        cout<<"Erreur de l'ouverture du fichier Search"<<endl;
    }

    cout << "------------------"<< endl;

    if(valuesToDelete){
        string line;

        while(getline(valuesToDelete, line))
        {
          //  cout << typeid(line).name() << endl;
            uint64_t valueDelete;
            istringstream iss(line);
            iss >> valueDelete;
            root=deleteNode(root, valueDelete);
        }
    }
    else{
        cout<<"Erreur de l'ouverture du fichier Delete"<<endl;
    }

    afficherArbre(root);

    cout << "------------------"<< endl;



   /* root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 5);
    root = insert(root, 45);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 75);
    root = insert(root, 80);
    root = insert(root, 85);
    root = insert(root, 30);
    root = insert(root, 35);
    root = insert(root, 83);
    root = insert(root, 40);
    root = insert(root, 45);
    root = insert(root, 50);
    root = insert(root, 55);
    root = insert(root, 60);
    root = insert(root, 65);
    root = insert(root, 70);
    root = insert(root, 75);
    root = insert(root, 80);
    root = insert(root, 85);
    root = insert(root, 90);
    root = insert(root, 100);
    root = insert(root, 110);
    root = insert(root, 190);
    root = insert(root, 150);
    root = insert(root, 170);
    root = insert(root, 120);
    root = insert(root, 130);*/

    return 0;

}
