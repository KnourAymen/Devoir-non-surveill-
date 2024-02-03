#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include "fileBanner.h"
#include "fileProfile.h"
#include "texteCentre.h"
#include "texteColore.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------
struct DateNaissance
{
    int jour;
    int mois;
    int annee;
};

struct Employee
{
    int code;
    char nom[50];
    char prenom[50];
    struct DateNaissance date_naissance;
    char titre_poste[50];
    float salaire;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------
void printInfo()
{
    colorerTexte("\n===============================> Meri Beaucoup <========================================\n", FOREGROUND_RED );
    printf("Merci du fond du coeur professeur Mounadi pour les efforts et support");
    colorerTexte("\n===============================> .... <========================================\n", FOREGROUND_RED );
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void lireFichierEmployes(struct Employee **employes, int *nb_employes)
{
    FILE *fichier = fopen("employees.txt", "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    *employes = malloc(sizeof(struct Employee));
    int taille_employes = 1;

    while (!feof(fichier))
    {
        if (*nb_employes >= taille_employes)
        {
            taille_employes *= 2;
            *employes = realloc(*employes, taille_employes * sizeof(struct Employee));
        }

        int result = fscanf(fichier,"%d %s %s %d/%d/%d %s %f",
               &(*employes)[*nb_employes].code,
               (*employes)[*nb_employes].nom,
               (*employes)[*nb_employes].prenom,
               &(*employes)[*nb_employes].date_naissance.jour,
               &(*employes)[*nb_employes].date_naissance.mois,
               &(*employes)[*nb_employes].date_naissance.annee,
               (*employes)[*nb_employes].titre_poste,
               &(*employes)[*nb_employes].salaire);

        if (result == EOF)
        {
            break;
        }

        (*nb_employes)++;
    }
    fclose(fichier);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void afficherEmployes(struct Employee *employes, int nb_employes)
{
    colorerTexte("\n===============================> Liste des employes <========================================\n", FOREGROUND_RED );
    for (int i = 0; i < nb_employes; i++)
    {
        printf("Code : %d\n", employes[i].code);
        printf("Nom : %s\n", employes[i].nom);
        printf("Prenom : %s\n", employes[i].prenom);
        printf("Date de naissance : %d/%d/%d\n", employes[i].date_naissance.jour, employes[i].date_naissance.mois, employes[i].date_naissance.annee);
        printf("Titre du poste : %s\n", employes[i].titre_poste);
        printf("Salaire : %.2f", employes[i].salaire);
        printf("\n");
        colorerTexte("=======================================================================\n", FOREGROUND_RED );
    }
}
//----------------------------------------------------------------------------------------------------
bool estMemeCode(struct Employee *employes, int nb_employes, int code)
{
    for (int i = 0; i < nb_employes; i++)
    {
        if (employes[i].code == code)
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------------------------------
void ajouterNouveauxEmployes(struct Employee *employes, int *nb_employes)
{
    int nb_nouveaux_employes;
    printf("Combien de nouveaux employes souhaitez-vous ajouter ? ");
    scanf("%d", &nb_nouveaux_employes);

    for (int i = 0; i < nb_nouveaux_employes; i++)
    {
        ajouterEmploye(employes, nb_employes);
    }
}
//------------------------------------------------------------------------------------------------------
void ajouterEmploye(struct Employee *employes, int *nb_employes)
{
    struct Employee nouvel_employe;

    printf("Code : ");
    scanf("%d", &nouvel_employe.code);

    while (!estMemeCode(employes, *nb_employes, nouvel_employe.code))
    {
        printf("Ce code existe deja. Veuillez saisir un code unique : ");
        scanf("%d", &nouvel_employe.code);
    }

    printf("Nom : ");
    scanf("%s", nouvel_employe.nom);

    printf("Prenom : ");
    scanf("%s", nouvel_employe.prenom);

    printf("Date de naissance (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &nouvel_employe.date_naissance.jour, &nouvel_employe.date_naissance.mois, &nouvel_employe.date_naissance.annee);

    printf("Titre du poste : ");
    scanf("%s", nouvel_employe.titre_poste);

    printf("Salaire : ");
    scanf("%f", &nouvel_employe.salaire);

    employes[*nb_employes] = nouvel_employe;
    (*nb_employes)++;

    printf("L'employe a ete ajoute avec succes.\n");
}
//------------------------------------------------------------------------------------------------------
void supprimerEmploye(struct Employee *employes, int *nb_employes)
{
    int code;
    printf("Entrez le code de l'employe a supprimer : ");
    scanf("%d", &code);

    for (int i = 0; i < *nb_employes; i++)
    {
        if (employes[i].code == code)
        {
            colorerTexte("\n===============================> Employe trouve <========================================\n", BACKGROUND_GREEN);
            printf("\nCode : %d\n", employes[i].code);
            printf("Nom : %s\n", employes[i].nom);
            printf("Prenom : %s\n", employes[i].prenom);
            printf("Date de naissance : %d/%d/%d\n", employes[i].date_naissance.jour, employes[i].date_naissance.mois, employes[i].date_naissance.annee);
            printf("Titre du poste : %s\n", employes[i].titre_poste);
            printf("Salaire : %.2f\n", employes[i].salaire);
            printf("\n");

            char confirmation[3];
            colorerTexte("\n===============================> Confirmation <===========================================\n", BACKGROUND_BLUE);
            printf("\nEtes-vous sur de vouloir supprimer cet employe ? (o/n) : ");
            scanf("%s", confirmation);

            if (strcmp(confirmation, "o") == 0)
            {
                for (int j = i; j < *nb_employes - 1; j++)
                {
                    employes[j] = employes[j + 1];
                }
                (*nb_employes)--;
                printf("L'employe a ete supprime avec succes.\n");
            }
            else
            {
                printf("La suppression de l'employe a ete annulee.\n");
            }

            return;
        }
    }

    printf("Aucun employe trouve avec le code %d.\n", code);
}
//------------------------------------------------------------------------------------------------------
void rechercherEmploye(struct Employee *employes, int nb_employes)
{
    int choix;
    colorerTexte("\n======================================> Recherche <=================================================\n", BACKGROUND_BLUE);
    printf("\nRechercher un employe par :\n");
    printf("1. Code\n");
    printf("2. Nom\n");
    printf("3. Prenom\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
    {
        int code;
        printf("Entrez le code de l'employe : ");
        scanf("%d", &code);

        for (int i = 0; i < nb_employes; i++)
        {
            if (employes[i].code == code)
            {
                colorerTexte("\n======================================> Resultat trouve <=================================================\n", BACKGROUND_BLUE);
                printf("\nCode : %d\n", employes[i].code);
                printf("Nom : %s\n", employes[i].nom);
                printf("Prenom : %s\n", employes[i].prenom);
                printf("Date de naissance : %d/%d/%d\n", employes[i].date_naissance.jour, employes[i].date_naissance.mois, employes[i].date_naissance.annee);
                printf("Titre du poste : %s\n", employes[i].titre_poste);
                printf("Salaire : %.2f\n", employes[i].salaire);
                return;
            }
        }
        printf("Aucun employe trouve avec le code %d.\n", code);
        break;
    }
    case 2:
    {
        char nom[50];
        printf("Entrez le nom de l'employe : ");
        scanf("%s", nom);

        int nb_resultats = 0;
        for (int i = 0; i < nb_employes; i++)
        {
            if (strcmp(employes[i].nom, nom) == 0)
            {
                nb_resultats++;
                colorerTexte("\n======================================> Resultat trouve <=================================================\n", BACKGROUND_RED);
                printf("\nCode : %d\n", employes[i].code);
                printf("Nom : %s\n", employes[i].nom);
                printf("Prenom : %s\n", employes[i].prenom);
                printf("Date de naissance : %d/%d/%d\n", employes[i].date_naissance.jour, employes[i].date_naissance.mois, employes[i].date_naissance.annee);
                printf("Titre du poste : %s\n", employes[i].titre_poste);
                printf("Salaire : %.2f\n", employes[i].salaire);
                printf("\n");
            }
        }
        if (nb_resultats == 0)
        {
            printf("Aucun employe trouve avec le nom %s.\n", nom);
        }
        else
        {
            printf("Nombre total de resultats : %d\n", nb_resultats);
        }
        break;
    }
    case 3:
    {
        char prenom[50];
        printf("Entrez le prenom de l'employe : ");
        scanf("%s", prenom);

        int nb_resultats = 0;
        for (int i = 0; i < nb_employes; i++)
        {
            if (strcmp(employes[i].prenom, prenom) == 0)
            {
                nb_resultats++;
                colorerTexte("\n======================================> Resultat trouve <=================================================\n", BACKGROUND_GREEN);
                printf("\nCode : %d\n", employes[i].code);
                printf("Nom : %s\n", employes[i].nom);
                printf("Prenom : %s\n", employes[i].prenom);
                printf("Date de naissance : %d/%d/%d\n", employes[i].date_naissance.jour, employes[i].date_naissance.mois, employes[i].date_naissance.annee);
                printf("Titre du poste : %s\n", employes[i].titre_poste);
                printf("Salaire : %.2f\n", employes[i].salaire);
                printf("\n");
            }
        }
        if (nb_resultats == 0)
        {
            printf("Aucun employe trouve avec le prenom %s.\n", prenom);
        }
        else
        {
            printf("Nombre total de resultats : %d\n", nb_resultats);
        }
        break;
    }
    }
}
//------------------------------------------------------------------------------------------------------
void mettreAJourEmploye(struct Employee *employes, int nb_employes)
{
    int code;
    printf("Entrez le code de l'employe a mettre a jour : ");
    scanf("%d", &code);

    for (int i = 0; i < nb_employes; i++)
    {
        if (employes[i].code == code)
        {
            colorerTexte("\n======================================> Resultat trouve <=================================================\n", BACKGROUND_BLUE);
            printf("\nCode : %d\n", employes[i].code);
            printf("Nom : %s\n", employes[i].nom);
            printf("Prenom : %s\n", employes[i].prenom);
            printf("Date de naissance : %d/%d/%d\n", employes[i].date_naissance.jour, employes[i].date_naissance.mois, employes[i].date_naissance.annee);
            printf("Titre du poste : %s\n", employes[i].titre_poste);
            printf("Salaire : %.2f\n", employes[i].salaire);
            printf("\n");

            char nouveau_poste[50];
            printf("\nEntrez le nouveau titre du poste (President | VP-Sales | VP-Marketing | Sales-Manager | Sales-Rep) : ");
            scanf("%s", nouveau_poste);
            if (strcmp(nouveau_poste, "President") == 0 || strcmp(nouveau_poste, "VP-Sales") == 0 ||
                    strcmp(nouveau_poste, "VP-Marketing") == 0 || strcmp(nouveau_poste, "Sales-Manager") == 0 ||
                    strcmp(nouveau_poste, "Sales-Rep") == 0)
            {
                strcpy(employes[i].titre_poste, nouveau_poste);
                printf("Le titre du poste a ete mis a jour avec succes.\n");
            }
            else
            {
                printf("Titre du poste invalide. La mise a jour n'a pas ete effectuee.\n");
            }

            float nouveau_salaire;
            printf("Entrez le nouveau salaire : ");
            scanf("%f", &nouveau_salaire);
            employes[i].salaire = nouveau_salaire;
            printf("Le salaire a ete mis a jour avec succes.\n");

            return;
        }
    }
    printf("Aucun employe trouve avec le code %d.\n", code);
}
//------------------------------------------------------------------------------------------------------
void enregistrerDansFichier(struct Employee *employes, int nb_employes)
{
    FILE *fichier;
    fichier = fopen("employees.txt", "w");

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < nb_employes; i++)
    {
        fprintf(fichier, "%d %s %s %d/%d/%d %s %.2f\n",
                employes[i].code, employes[i].nom, employes[i].prenom,
                employes[i].date_naissance.jour, employes[i].date_naissance.mois, employes[i].date_naissance.annee,
                employes[i].titre_poste, employes[i].salaire);
    }

    fclose(fichier);
}
//------------------------------------------------------------------------------------------------------
void afficherMenu(struct Employee *employes, int nb_employes)
{
    int choix;
    do
    {
        sleep(3);
        colorerTexte("\n==============================================> Menu ==============================================> :\n", FOREGROUND_BLUE);
        printf("[1]=> Afficher les employes\n");
        printf("[2]=> Ajouter un nouvel employe\n");
        printf("[3]=> Supprimer un employe existant\n");
        printf("[4]=> Rechercher un employe\n");
        printf("[5]=> Mettre a jour les informations d'un employe\n");
        printf("[6]=> Info***\n");
        printf("[7]=> Quitter le programme\n");
        colorerTexte("\n==============================================> Option ==============================================> :\n", FOREGROUND_BLUE);
        printf("Veuillez choisir une option : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            afficherEmployes(employes, nb_employes);
            break;
        case 2:
            ajouterNouveauxEmployes(employes, &nb_employes);
            enregistrerDansFichier(employes, nb_employes);
            break;
        case 3:
            supprimerEmploye(employes, &nb_employes);
            enregistrerDansFichier(employes, nb_employes);
            break;
        case 4:
            rechercherEmploye(employes, nb_employes);
            break;
        case 5:
            mettreAJourEmploye(employes, nb_employes);
            enregistrerDansFichier(employes, nb_employes);
            break;

        case 6:
            printInfo();
            enregistrerDansFichier(employes, nb_employes);
            break;

        case 7:
            enregistrerDansFichier(employes, nb_employes);
            printf("Le programme a ete quitte. Les modifications ont ete enregistrees.\n");
            break;
        default:
            printf("Option invalide. Veuillez choisir une option valide.\n");
        }
    }
    while (choix != 7);
}
//-------------------------------------------------------------------------------------------------------------
void demanderModeUtilisateur(struct Employee *employes, int nb_employes)
{
    char mode;
    char continuer;

    colorerTexte("======================================> Mode Utilisateur <=================================================\n\n", BACKGROUND_RED);
    printf("Veuillez choisir le mode d'utilisation : (G pour graphique, C pour console) : ");
    scanf(" %c", &mode);

    if (mode == 'G' || mode == 'g')
    {
        colorerTexte("\n\n======================================> :( <=================================================\n\n", BACKGROUND_BLUE);
        printf("Malheureusement, le mode graphique est en cours de developpement, en utilise la bibliotheque graphique GTK\n");
        printf("Voulez-vous continuer dans l'application ? (O pour continuer, Q pour quitter) : ");
        scanf(" %c", &continuer);

        if (continuer == 'Q' || continuer == 'q')
        {
            exit(0);
        }
        else
        {
            printf("Vous avez choisi de continuer dans l'application.\n");
            afficherMenu(employes, nb_employes);
        }
    }
    else if (mode == 'C' || mode == 'c')
    {
        printf("Vous avez choisi le mode console.\n");
        afficherMenu(employes, nb_employes);
    }
    else
    {
        printf("Entree invalide. Veuillez choisir G pour graphique ou C pour console.\n");
    }
}
//-------------------------------------------------------------------------------------------------------------
int main()
{
    struct Employee *employes;
    int nb_employes = 0;


    sleep(3);
    readFileBanner();
    colorerTexte("\n#################################################################################################\n\n", BACKGROUND_BLUE);
    sleep(3);
    readFileProfile();
    colorerTexte("\n#################################################################################################\n\n", BACKGROUND_GREEN);
    sleep(3);
    printf("\nTapez entrer pour continuer : ");
    getch();
    system("cls");
    sleep(3);

    lireFichierEmployes(&employes, &nb_employes);
    demanderModeUtilisateur(employes, nb_employes);

    free(employes);
}
