#include "b_noire.h"

// Initialiser la boîte noire (liste vide au départ)
void initialiser_boite(BoiteNoire *b) {
    b->debut = NULL;
    b->fin = NULL;
    b->nb_frames = 0;
}

// Enregistrer une nouvelle trame
void 
enregistrer_cycle(BoiteNoire *b, float v, float t, long timestamp) {

    // création dynamique
    Frame *nouvelle = (Frame*)malloc(sizeof(Frame));
    if (nouvelle == NULL) {
        fprintf(stderr, "ERREUR: Allocation mémoire échouée!\n");
        exit(1);
    }
    
    nouvelle->timestamp = timestamp;
    nouvelle->vitesse = v;
    nouvelle->temperature_moteur = t;
    nouvelle->suivant = NULL;
    
    // si la boite est vide, on n'initialise
    if (b->debut == NULL) {
        b->debut = nouvelle;
        b->fin = nouvelle;
        b->nb_frames = 1;
    } else {

        // supprimer l'ancienne frame si la capacité max est atteinte
        if (b->nb_frames >= CAPACITE_MAX) {
            Frame *ancienne = b->debut;
            b->debut = b->debut->suivant;  
            
            printf("= Rotation : Frame ancienne écrasée.\n");
            free(ancienne);
            b->nb_frames--;
        }
        
        // ajouter la nouvelle frame à la fin
        b->fin->suivant = nouvelle;
        b->fin = nouvelle;
        b->nb_frames++;
    }
    
    // ici on affiche
        printf("= Enregistrement Frame [%ld ms]... (Mémoire : %d/%d)\n", 
            timestamp, b->nb_frames, CAPACITE_MAX);
}

// liberer à la fin
void liberer_boite(BoiteNoire *b) {
    Frame *courant = b->debut;
    while (courant != NULL) {
        Frame *temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    b->debut = NULL;
    b->fin = NULL;
    b->nb_frames = 0;
}

// Afficher l'historique complète des 10 dernières secondes
void afficher_historique(BoiteNoire *b) {
    printf("\n========== HISTORIQUE DES 10 DERNIÈRES SECONDES ==========\n");
    Frame *courant = b->debut;
    int i = 1;
    
    while (courant != NULL) {
        printf("[Frame %d] Temps: %ld ms | Vitesse: %.2f km/h | Temp: %.2f °C\n",
               i++, courant->timestamp, courant->vitesse, courant->temperature_moteur);
        courant = courant->suivant;
    }
    printf("===========================================================\n\n");
}
