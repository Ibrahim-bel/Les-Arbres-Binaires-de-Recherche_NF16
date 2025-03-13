#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"


 

int main(){
    T_Arbre abr= NULL;
    
    char* prenom = malloc(100*sizeof(char));
    char* nom = malloc(100*sizeof(char));
    char* code = malloc(5*sizeof(char));
    char* chemin = malloc(100*sizeof(char));
    char c;

    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    while (choix != '6') {
        printf("\n======================================");
        printf("\n1. Inscrire un etudiant a une UV");
        printf("\n2. Charger un fichier d'inscriptions");
        printf("\n3. Afficher tous les etudiants");
        printf("\n4. Afficher les inscrits a une UV");
        printf("\n5. Supprimer une inscription");
        printf("\n6. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");

        choix = getchar();

        switch (choix) {
            case '1' :
                printf("Entrez le nom : ");
                nom = Saisie(nom);
                printf("\nEntrez le prenom : ");
                prenom = Saisie(prenom);
                printf("\nEntrez le code UV : ");
                code = SaisieCode(code);
                /*nom = SaisieNom();
                prenom = SaisiePrenom();
                code = SaisieCode(); */
                abr=inscrire(abr,nom, prenom, code);
                printf("Appuyer sur entrer pour continuer\n");

                break;

            case '2' :

                printf("Saisir le chemin du fichier\n");
                scanf("%s", chemin);
                abr = chargerFichier(abr,chemin);
                printf("Appuyer sur entrer pour continuer\n");
                viderBuffer();

                break;

            case '3' :
                 if (abr == NULL) {
                    printf("Aucun etudiant inscrit.\n");
                } else {
                    printf("Liste de tous les etudiants :\n");
                    afficherInscriptions(abr);
                    }

                break;

            case '4' :
                  if (abr == NULL) {
                        printf("Aucun etudiant inscrit.\n");
                        }
                  else {
                        //code = SaisieCode();
                        printf("\nQuel UV voulez vous afficher la liste des eleves ? (pas de caracteres speciaux): ");
                        code = SaisieCode(code);
                        printf("Liste des etudiants inscrits a l'UV %s :\n", code);
                        afficherInscriptionsUV(abr, code);
                    }
                    printf("Appuyer sur entrer pour continuer\n");

                break;

            case '5':
                if(abr == NULL){
                    printf("Aucun etudiant inscrit.\n");
                }
                else{
                    printf("N'ulisez pas de carateres speciaux \n");
                    /*nom = SaisieNom();
                    prenom = SaisiePrenom();
                    code = SaisieCode();*/
                    nom = Saisie(nom);
                    printf("\nPrenom (pas de caracteres speciaux): ");
                    prenom = Saisie(prenom);
                    printf("\nCode UV (pas de caracteres speciaux): ");
                    code = SaisieCode(code);
                    abr = supprimerInscription(abr, nom, prenom, code);
                    printf("Appuyer sur entrer pour continuer\n");
                }
                    
                break;

            case '6' :
                libererArbre(&abr);
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
        }
        printf("\n\n\n");
        viderBuffer(); // supprimer de l'entr e standard le retour charriot et les  ventuels caract res suppl mentaires tap s par l'utilisateur
}

    return 0;
}
