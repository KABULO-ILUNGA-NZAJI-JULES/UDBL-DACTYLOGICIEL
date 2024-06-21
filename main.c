#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MOTS 100
#define TAILLE_MAX_MOT 20


void ecranAccueil();
void menuAide();
void menuConfigurer();
void menuDemarrer();
void lireMots(char mots[][TAILLE_MAX_MOT]);
void afficherMots(char mots[][TAILLE_MAX_MOT], int nbMots);
int comparerTemps(clock_t debut1, clock_t fin1, clock_t debut2, clock_t fin2Y);


int main(){
    ecranAccueil();
    return 0;
}

// Fonctions pour chaque menu
void ecranAccueil(){

    int choix;
    printf("\n");
    printf("\t\t\t\t\tBienvenue dans le jeu de frappe rapide !\n");
    printf("\t\t\t\t======================================================\n");
    printf("\t\t\t\t\tMENBRES DE L'EQUIPE:\n");
    printf("\t\t\t\t======================================================\n");
    printf("\t\t\t\t\NINA \n");
    printf("\t\t\t\t\JULES \n");
    printf("\t\t\t\t\CONSOLATE\n");
    printf("\t\t\t\t======================================================\n");
    printf("\n");
    printf("\t\t\t\t\t1. DEMARRER\n");
    printf("\t\t\t\t\t2. CONGIGURER\n");
    printf("\t\t\t\t\t3. AIDE\n");
    printf("\t\t\t\t\t4. QUIER\n");
    printf("\t\t\t\t======================================================\n");
    printf("\n");
    printf("\t\t\t\t\tVeuillez choisir une option : ");
    scanf("%d", &choix);

    switch (choix){
        case 1:
            menuDemarrer();
            break;
        case 2:
            menuConfigurer();
            break;
        case 3:
            menuAide();
            break;
        case 4:
            printf("au revoir\n");
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n ");
            ecranAccueil();
    }
}

void menuAide(){
    printf("\n");
    printf("\t\t\t\t\tAide et informations sur l application:\n");
    printf("\t\t\t\t\t- Description : Jeu de frappe rapide en mode console.\n");
    printf("\t\t\t\t\t- Version : 1.0\n");
    printf("\t\t\t\t\t- Concepteurs : Jules Kabulo JOSKA\n");
    printf("\t\t\t\t\t- Date de conception : le 06-07-2024\n");
}

void menuConfigurer(){
    char mot[TAILLE_MAX_MOT];
    FILE *fichier = fopen("mots.txt", "w");
    if(fichier == NULL) {
        printf("Erreur lors de l’ouverture du fichier.\n");
        exit(1) ;
    }
    printf("\t\t\tEntrez les mots a utiliser dans le jeu (tapez \"fin\" pour terminer): ");
    while(1){
        scanf("%s", mot);
        if(strcmp(mot, "fin") == 0){
            break;
        }
        fprintf(fichier, "%s\n", mot);
    }
    fclose(fichier);
    printf("Configuration terminee.\n");
}

void menuDemarrer() {
    char mots[MAX_MOTS][TAILLE_MAX_MOT];
    int nbMots;
    char pseudo1[TAILLE_MAX_MOT], pseudo2[TAILLE_MAX_MOT] ;
    clock_t debut1, fin1, debut2, fin2;

    lireMots(mots);
    printf("\t\t\t\tEntrez le nombre de mots a utiliser : ");
    scanf("%d", &nbMots);
    printf("\t\t\t\tEntrez le nom du joueur 1 : ");
    scanf("%s", pseudo1);
    printf("\t\t\t\tEntrez le nom du joueur 2 : ");
    scanf("%s", pseudo2);

    afficherMots(mots, nbMots);

    printf("\t\t\t\t%s c est votre tour. Appuyez sur une touche pour commencer.\n ", pseudo1);
    getchar() ; // Pour consommer le ‘\n’ restant
    getchar() ; // Pour attendre que l’utilisateur appuie sur une touche

    debut1 = clock();
    // Logique de saisie des mots pour le joueur 1
    fin1 = clock();

    printf("\t\t\t\t%s c est votre tour. Appuyez sur une touche pour commencer.\n", pseudo2);
    getchar(); // Pour attendre que l’utilisateur appuie sur une touche
    debut2 = clock();
    // Logique de saisie des mots pour le joueur 2
    fin2 = clock();

    int resultat = comparerTemps(debut1, fin1, debut2, fin2);
    if(resultat < 0){
        printf("%s est le plus rapide !\n", pseudo1);
    } else if (resultat > 0) {
        printf("%s est le plus rapide !\n", pseudo2);
    } else {
        printf("\t\t\t\t\tEgalite parfaite !\n");
    }
}

void lireMots(char mots[][TAILLE_MAX_MOT]) {
    FILE *fichier = fopen("mots.txt", "r");
    if(fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    int i = 0;
    while(fscanf(fichier, "%s", mots[i]) != EOF && i < MAX_MOTS){
        i++;
    }
    fclose(fichier);
}

void afficherMots(char mots[][TAILLE_MAX_MOT], int nbMots) {
    printf("\t\t\t\t\tVoici les mots a taper : \n");
    for(int i = 0; i < nbMots; i++){
        printf("%s\n", mots[i]);
    }
}

int comparerTemps(clock_t debut1, clock_t fin1, clock_t debut2, clock_t fin2) {
    double tempsJoueur1 = (double)(fin1 - debut1) / CLOCKS_PER_SEC;
    double tempsJoueur2 = (double)(fin2 - debut2) / CLOCKS_PER_SEC;

    printf("\t\t\t\t\tTemps de saisie pour le joueur 1 : %.2f secondes\n", tempsJoueur1);
    printf("\t\t\t\t\tTemps de saisie pour le joueur 2 : %.2f secondes\n", tempsJoueur2);

    if (tempsJoueur1 < tempsJoueur2) {
        return -1;
    } else if (tempsJoueur1 > tempsJoueur2) {
        return 1;
    } else {
        return 0;
    }
}

