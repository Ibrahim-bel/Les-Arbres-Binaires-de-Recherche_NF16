#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

 

typedef struct Element{
    char* code_uv;
    struct Element* suivant;
}T_Element;

typedef struct Noeud{
    char* prenom;
    char* nom;
    T_Element* listeInscriptions;
    struct Noeud* filsGauche;
    struct Noeud* filsDroit;
}Noeud;

typedef struct Noeud* T_Arbre;

T_Element *creerElement(char* code);

Noeud *creerNoeud(char* nom, char* prenom, T_Element* listeInscriptions);

T_Element *ajouterInscription(T_Element *liste, char* code);

T_Arbre inscrire(T_Arbre abr, char *nom, char *prenom, char *code);
int rechercheEtu(T_Arbre abr, char *nom, char *prenom);

T_Arbre chargerFichier(T_Arbre abr, char *filename);

char *ToMajuscule(char* nom);

void afficherListe(T_Element* liste);

void afficherInscriptions(T_Arbre racine);

void afficherInscriptionsUV(T_Arbre abr, char *code);

T_Arbre supprimerInscription(T_Arbre abr, char *nom, char *prenom, char *code);
T_Element* supprimerUV(T_Element* liste, char* code);
Noeud* supprimerNoeud(Noeud* noeud, char *nom, char *prenom);
Noeud* minimum(T_Arbre abr);
void libererArbre(T_Arbre *abr);

char* SaisieNom();
char* SaisiePrenom();
char* SaisieCode();

void viderBuffer();


char* Saisie(char* chaine);
char* SaisieCode(char* code);

void libererListeInscriptions(T_Element *listeInscription);



#endif 