#include "b_noire.h"

// Afficher le menu principal
void afficher_menu() {
    printf("=============     BLACKBOX - Boîte Noire     =============\n");
    printf("  [1] Lancer la simulation\n");
    printf("  [2] Analyser crash.bin\n");
    printf("  [3] Quitter\n\n");
    printf("Votre choix : ");
}


void lancer_simulation() {
    BoiteNoire boite;
    initialiser_boite(&boite);

    // Variables de simulation
    float vitesse = VITESSE_INIT;
    float temperature = TEMP_AMBIANTE;
    struct timeval debut_prog;
    gettimeofday(&debut_prog, NULL);
    int nb_acc = 0;
    int nb_frein = 0;

    printf("\n ========== DÉMARRAGE DE LA SIMULATION ==========\n");
    printf("Vitesse initiale : %.2f km/h\n", vitesse);
    printf("Température initiale : %.2f °C\n\n", temperature);
    printf("Tapez [A] pour accélérer ou [F] pour freiner à chaque seconde.\n\n");

    // Boucle infinie jusqu'à crash ou arrêt
    while (1) {
        // Affichage de l'état actuel et demander l'action
        printf("=======================================\n");
        printf("= Vitesse actuelle : %.2f km/h       \n", vitesse);
        printf("= Température moteur : %.2f °C       \n", temperature);
        printf("=======================================\n");
        printf("\n[A]ccélérer ou [F]reiner : ");

        char action;
        scanf(" %c", &action);

        printf("\n");

        // Calculer la nouvelle vitesse selon l'action
        calculer_nouvelle_vitesse(&vitesse, action);

        // Mettre à jour les compteurs A/F
        if (action == 'A' || action == 'a') {
            nb_acc++;
        } else if (action == 'F' || action == 'f') {
            nb_frein++;
        }

        // Calculer la nouvelle température
        calculer_nouvelle_temperature(&temperature, vitesse);

        // Obtenir le timestamp actuel
        long timestamp = obtenir_timestamp_ms(debut_prog);

        // Enregistrer l'état dans la boîte noire
        enregistrer_cycle(&boite, vitesse, temperature, timestamp);

        printf("\n");
        printf("Compteurs: Avancer = %d, Freiner  = %d\n", nb_acc, nb_frein);

        // Vérification des conditions de crash/arrêt
        if (temperature > TEMP_SURCHAUFFE) {
            printf("\n ========== SURCHAUFFE MOTEUR ! ==========\n");
            printf("   Température : %.2f °C (Limite : %.2f °C)\n",
                   temperature, TEMP_SURCHAUFFE);
            printf("    ARRÊT D'URGENCE DU VÉHICULE \n\n");
            break;
        }

        if (vitesse == 0) {
            printf("\n ========== VÉHICULE À L'ARRÊT ==========\n\n");
            break;
        }
    }

    // Afficher l'historique complet
    afficher_historique(&boite);

    // Sauvegarder dans crash.bin
    dump_memory(&boite);

    // Libérer la mémoire
    liberer_boite(&boite);
}

int main() {
    int choix;

    while (1) {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                lancer_simulation();
                break;
            case 2:
                analyser_crash();
                break;
            case 3:
                printf("\n Au revoir !\n\n");
                return 0;
            default:
                printf("\n Choix invalide. Réessayez.\n\n");
        }
    }

    return 0;
}
