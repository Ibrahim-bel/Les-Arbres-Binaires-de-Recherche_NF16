#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h" 
 


/* ********************************
 * Cr�ation et initialisation Element
 ******************************** */
T_Element *creerElement(char* code){
    T_Element* newElement = (T_Element*)malloc(sizeof(T_Element));
    if (newElement != NULL){ // l'allocation mémoire s'est bien passée
        newElement->code_uv = malloc(strlen(code) +1);
        strcpy(newElement->code_uv, code);
        newElement->suivant = NULL;
    }
    return newElement;
}


/* **************************************
 * Cr�ation et initialisation Noeud
 ************************************** */
Noeud *creerNoeud(char* nom, char* prenom, T_Element* listeInscriptions){
    Noeud* newNoeud = (Noeud*)malloc(sizeof(Noeud));
    if(newNoeud != NULL){ // l'allocation m�éoire s'est bien passée
        newNoeud->nom = malloc(strlen(nom) +1);
        newNoeud->prenom = malloc(strlen(prenom) +1);
        strcpy(newNoeud->nom, nom);
        strcpy(newNoeud->prenom, prenom);
        newNoeud->listeInscriptions = listeInscriptions;
        newNoeud->filsGauche = NULL;
        newNoeud->filsDroit = NULL;
    }
    return newNoeud;
}



/* ********************************
 * 1.	Ajout d'une inscription dans l'ordre alphabétique du code UV d'une liste de d'incription :
 ******************************** */
T_Element *ajouterInscription(T_Element *liste, char* code){
    T_Element* tmp = liste;
    T_Element* pred = NULL;
    T_Element* newUV = creerElement(code);
    if (liste==NULL){
        liste = newUV;
        return liste;
    }
    else{
        while(tmp != NULL){
            if(strcmp(tmp->code_uv, code) == 0){
                free(newUV); // Libérer la mémoire du nouvel élément pour eviter des fuites de memoire
                return liste;
            }
            if(strcmp(tmp->code_uv, newUV->code_uv)>0){
                if(pred == NULL){
                    newUV->suivant = tmp;
                    return newUV;
                }
                else{
                    pred->suivant = newUV;
                    newUV->suivant = tmp;
                    return liste;}
            }
            pred = tmp;
            tmp = tmp->suivant;
        }
        pred->suivant = newUV;
        return liste;
    }
}



/* **************************************
 * 2. Inscription d'un etudiant a une UV
 ************************************** */
T_Arbre inscrire(T_Arbre abr, char* nom, char* prenom, char* code) {
    T_Arbre racine = abr;
    char* Mcode = malloc(5*sizeof(char));
    char* Mprenom = malloc(100*sizeof(char));
    char* Mnom = malloc(100*sizeof(char));
    Mprenom = ToMajuscule(prenom);
    Mnom = ToMajuscule(nom);
    Mcode = ToMajuscule(code);
    if (racine == NULL) {
        racine = creerNoeud(Mnom, Mprenom, NULL);
        racine->listeInscriptions = ajouterInscription(racine->listeInscriptions, Mcode);
    }
    if (strcmp(racine->nom, Mnom) >0|| (strcmp(racine->nom, Mnom) == 0 &&strcmp(racine->prenom,Mprenom) > 0)) {  // Si le nom est inférieur, rechercher dans le sous-arbre gauche
        racine->filsGauche = inscrire(racine->filsGauche, Mnom, Mprenom, Mcode);
    }
    else if (strcmp(racine->nom, Mnom) <0 || (strcmp(racine->nom, Mnom) == 0 &&strcmp(racine->prenom, Mprenom) <0)) { // Si le nom est supérieur, rechercher dans le sous-arbre droit
        racine->filsDroit = inscrire(racine->filsDroit, Mnom, Mprenom, Mcode);
    }
    else {  // Si le nom est égal, l'étudiant existe déjà, ajouter l'UV à sa liste d'inscriptions
        racine->listeInscriptions = ajouterInscription(racine->listeInscriptions, Mcode);
    }
    free(Mprenom);
    free(Mnom);
    free(Mcode);
    return racine;
}



/* **************************************
 * 3. Charger dans l'ABR un fichier texte
 ************************************** */
T_Arbre chargerFichier(T_Arbre abr, char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");
        return abr;
    }

    char ligne[100];
    char nom[50], prenom[50], code[10];

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%[^;];%[^;];%s", nom, prenom, code) == 3) {
            abr = inscrire(abr, nom, prenom, code);
        }
    }

    fclose(file);
    return abr;
}

/*T_Arbre chargerFichier(T_Arbre abr, char *filename){
    FILE *fichier= fopen(filename, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return abr; 
    }
    else{ //Allocation des chaines de caracteres 
        char* code = malloc(5*sizeof(char));
        char* prenom = malloc(100*sizeof(char));
        char* nom = malloc(100*sizeof(char));
        char etudiant[200];
        while(
            fscanf(fichier," %[^;];%[^;];%s",nom,prenom,code) != EOF){
            nom = ToMajuscule(nom);
            prenom = ToMajuscule(prenom);
            code = ToMajuscule(code);
            abr = inscrire(abr,nom, prenom, code);
        }
        printf("Fichier chargé\n");
        //Liberer la memoire allouée
        free(code);
        free(prenom);
        free(nom);

    }
    fclose(fichier);
    return abr;
}*/

/* **************************************
 * 4. Afficher une liste d'étudiants avec leurs UVs
 ************************************** */
void afficherInscriptions(T_Arbre abr) {
    if (abr != NULL) {
        afficherInscriptions(abr->filsGauche); //Affiche le sous arbre gauche
        printf("%s %s :", abr->nom, abr->prenom);// Affiche le nom et le prenom de l'étudiant
        afficherListe(abr->listeInscriptions);// Affiche la liste des Uvs du de l'etudiant
        afficherInscriptions(abr->filsDroit);// Affiche le sous arbre droit
    }
}
/*Pour afficher la liste de tous les étudiants, classée par ordre alphabétique,
Il faut afficher le sous arbre gauche de chaque, ensuite le noeud et enfin le 
sous arbre droit du noeud*/



/* **************************************
 * 5. Affiche l’ensemble des étudiants inscrits à une UV 
 ************************************** */
void afficherInscriptionsUV(T_Arbre abr, char *code){
    Noeud *etu = abr;
    T_Element *listeEtudiant = malloc(sizeof(T_Element));
    if(etu != NULL){
        
        afficherInscriptionsUV(etu->filsGauche, code);// Afficher le sous arbre gauche
        listeEtudiant = etu->listeInscriptions;
        while(listeEtudiant != NULL){
           if(strcmp(listeEtudiant->code_uv,code) == 0 ){
                printf("%s %s\n", etu->nom, etu->prenom);
                break;
            }
            listeEtudiant = listeEtudiant->suivant;
        }
        afficherInscriptionsUV(etu->filsDroit, code);// Afficher le sous arbre droit
    }
}



/* **************************************
 * 6. supprimer l’inscription d’un étudiant à une UV
 ************************************** */
T_Arbre supprimerInscription(T_Arbre abr, char *nom, char *prenom, char *code){
    T_Arbre racine = abr;
    if(racine == NULL){
        printf("Arbre vide !\n");
        return racine;
    }
    if(rechercheEtu(abr, nom, prenom)){
        if(strcmp(racine->nom, nom) == 0 && strcmp(racine->prenom, prenom) == 0){
            racine->listeInscriptions = supprimerUV(racine->listeInscriptions, code);
            if(racine->listeInscriptions == NULL){
                racine = supprimerNoeud(racine, nom, prenom);
            }
        }
        else if(strcmp(racine->nom, nom) >0|| (strcmp(racine->nom, nom) == 0 &&strcmp(racine->prenom,prenom) > 0)) {  // Si le nom est inférieur, rechercher dans le sous-arbre gauche
            racine->filsGauche = supprimerInscription(racine->filsGauche, nom, prenom, code);
        }
        else {
            racine->filsDroit = supprimerInscription(racine->filsDroit, nom, prenom, code);
        }
    }
    else{
        printf("L'etudiant n'est pas inscrit\n");
    }
    return racine;
}


/* *********************
 * Fonctions utilitaires
 ********************* */

//Rercherche d'un etudiant dans l'arbre
int rechercheEtu(T_Arbre abr, char *nom, char *prenom){
    Noeud* pt= abr;
    while(pt!=NULL){
        if(!strcmp(pt->nom,nom) && !strcmp(pt->prenom,prenom)){
            return 1;
        }
        else if(strcmp(pt->nom,nom) >0|| (strcmp(pt->nom,nom) == 0 &&strcmp(pt->prenom,prenom) > 0)){
                pt=pt->filsGauche;
        }
        else{pt=pt->filsDroit;}
    }
return 0;
}


//pour convertir les minuscules en majuscules
char* ToMajuscule(char* nom) {
    char* Majnom = strdup(nom);  // Utilisation de strdup pour dupliquer nom dans Majnom
    if (Majnom == NULL) { // Gestion de l'échec de l'allocation
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (Majnom[i] != '\0') {
        if (Majnom[i] >= 'a' && Majnom[i] <= 'z') {
            Majnom[i] = Majnom[i] + 'A' - 'a';
        }
        i++;
    }
    return Majnom;
}


//Afficher la liste des UVs 
void afficherListe(T_Element* liste) {
    T_Element* ptListe = liste;
    while (ptListe != NULL) {
        printf(" %s", ptListe->code_uv);
        ptListe = ptListe->suivant;
    }
    printf("\n");
}


T_Element* supprimerUV(T_Element* liste, char* code){
    T_Element* pred = NULL; 
    T_Element* tmp = liste;
    while(tmp != NULL){
        if (strcmp(tmp->code_uv, code) == 0){
            if (pred==NULL){
                liste = tmp->suivant;
            }
            else{
                pred->suivant = tmp->suivant;
            }
            free(tmp);
            return liste;
        }
        pred = tmp;
        tmp = tmp->suivant;
    }
    printf("L'etudiant n'est pas inscrit a cette UV\n");
    return liste;
}


Noeud* supprimerNoeud(Noeud* racine, char *nom, char *prenom){
    if(racine == NULL){
        return racine;
    }
    else if(strcmp(racine->nom, nom) >0|| (strcmp(racine->nom, nom) == 0 &&strcmp(racine->prenom,prenom) > 0)) {
        racine->filsGauche = supprimerNoeud(racine->filsGauche, nom, prenom);
    }
    else if(strcmp(racine->nom, nom) <0|| (strcmp(racine->nom, nom) == 0 &&strcmp(racine->prenom,prenom) < 0)){
        racine->filsDroit = supprimerNoeud(racine->filsDroit, nom, prenom);
    }
    else{
        //Si c'est une feuille
        if(racine->filsGauche == NULL && racine->filsDroit == NULL){
            free(racine);
            racine = NULL;
        }
        //Si le noeud a un seul fils
        else if(racine->filsGauche == NULL){
            Noeud* tmp = racine;
            racine = racine->filsDroit;
            free(tmp);
        }
        else if(racine->filsDroit==NULL){
            Noeud* tmp = racine;
            racine = racine->filsGauche;
            free(tmp);
        }
        //Si le noeud a 2 fils
        else{
            Noeud* tmp = minimum(racine->filsDroit);
            racine->nom = strdup(tmp->nom);
            racine->prenom = strdup(tmp->prenom);
            racine->listeInscriptions = tmp->listeInscriptions;
            racine->filsDroit = supprimerNoeud(racine->filsDroit, tmp->nom, tmp->prenom);
        }
    }
    return racine;
}

Noeud* minimum(T_Arbre abr){
    if(abr == NULL){
        return NULL;
    }
    Noeud* min =  creerNoeud(abr->nom, abr->prenom, abr->listeInscriptions);
    while(abr->filsGauche != NULL){
        abr = abr->filsGauche; //Le noeud minimum se trouve le plus a gauche de l'arbre
        if(strcmp(min->nom, abr->nom) >0 || (strcmp(min->nom, abr->nom)==0 && strcmp(min->prenom, abr->prenom)>0)){
            min->nom = abr->nom;
            min->prenom = abr->prenom;
            min->listeInscriptions = abr->listeInscriptions;
        }
    }
    return min;
}

char* Saisie(char* chaine){
    int boolean = 0;
    while (boolean != 1){
        boolean = scanf("%s",chaine);
        if (boolean != 1) printf("La saisie n'est pas correcte, veuillez reessayer : \n");
        if (strlen(chaine) > 100) {
            printf("La saisie est trop grande\n ");
            boolean = 0;
        }
        viderBuffer();
    }
    chaine = ToMajuscule(chaine);
    return chaine;
}


char* SaisieCode(char* code){
    int boolean = 0;
    while (boolean != 1){
        boolean = scanf("%s",code);
        if (boolean != 1) printf("La saisie n'est pas correcte, veuillez reessayer : \n");
        if (strlen(code) != 4) {
            printf("Entrez un code UV de 4 caractères exactement. \n");
            boolean = 0;
        }
        viderBuffer();
    }
    code[5] = '\0';
    code = ToMajuscule(code);
    return code;
}


void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Liberer la memoire
void libererArbre(T_Arbre *abr){
    T_Arbre tmp = *abr;
    if (!tmp) return;
    if (tmp->filsGauche) {
        libererArbre(&tmp->filsGauche);
        }
    if (tmp->filsDroit) {
        libererArbre(&tmp->filsDroit);
        }
    free(tmp->nom);
    free(tmp->prenom);
    libererListeInscriptions(tmp->listeInscriptions);
    free(tmp);
    *abr = NULL;
}

void libererListeInscriptions(T_Element *listeInscription) {
    while (listeInscription != NULL) {
        T_Element *aux = listeInscription;
        listeInscription = listeInscription->suivant;
        free(aux->code_uv);
        free(aux);
    }
}