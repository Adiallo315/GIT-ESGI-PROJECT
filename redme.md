
##Gestion des Adresses IP

Ce programme en langage C permet de gérer une liste d'adresses IP avec leurs masques associés. Les adresses IP et les masques sont stockés dans des tableaux et peuvent être ajoutés, affichés, filtrés par masque, ou supprimés.
Fonctionnalités
1. Ajouter une nouvelle adresse IP

L'utilisateur peut ajouter une nouvelle adresse IP avec son masque associé. Les adresses IP et les masques sont vérifiés pour leur validité avant d'être ajoutés à la liste.
2. Afficher les adresses IP

Cette option permet d'afficher la liste des adresses IP enregistrées, avec leur ID, adresse IP et masque.
3. Filtrage par masque

L'utilisateur peut entrer une adresse IP et un masque. Le programme vérifie si l'adresse IP appartient à un réseau connu en comparant avec les adresses IP enregistrées.
4. Supprimer

Permet de supprimer une adresse IP de la liste en utilisant son ID.
5. Quitter

Option pour quitter le programme.
Utilisation

    Compilation

    Compiler le programme en utilisant la commande suivante :

    bash


git clone https://github.com/Adiallo315/GIT-ESGI-PROJECT.git
git checkout feature/gestionAdressesIP
gcc Projet-Version-Final-avec-fonction.c
./a


Exécution

Exécuter le programme compilé avec la commande :

bash

    ./a

    Menu Principal

    Suivre les instructions du menu principal pour effectuer les différentes opérations.

Structure du Code

    Le code est organisé en fonctions pour améliorer la lisibilité et la maintenabilité.
    Les données (ID, adresses IP, masques) sont stockées dans des tableaux.
    Les adresses IP et masques sont vérifiés pour leur validité avant d'être ajoutés à la liste.
    Les données sont sauvegardées et chargées depuis un fichier CSV (adresses.csv).
