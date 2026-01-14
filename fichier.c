#include "b_noire.h"

// Sauvegarder d'urgence le contenu de la boîte noire dans crash.bin
void dump_memory(BoiteNoire *b) {
    FILE *fichier = fopen("crash.bin", "wb");
    if (fichier == NULL) {
        fprintf(stderr, "ERREUR: Impossible de créer crash.bin!\n");
        return;
    }
    
    printf("\n= Sauvegarde d'urgence dans crash.bin...\n");
    
    // Parcourir la liste et écrire chaque frame
    Frame *courant = b->debut;
    int nb_ecrites = 0;
    
    while (courant != NULL) {
        fwrite(&(courant->timestamp), sizeof(long), 1, fichier);
        fwrite(&(courant->vitesse), sizeof(float), 1, fichier);
        fwrite(&(courant->temperature_moteur), sizeof(float), 1, fichier);
        
        nb_ecrites++;
        courant = courant->suivant;
    }
    
    fclose(fichier);
    printf("= %d frames sauvegardées avec succès.\n\n", nb_ecrites);
}

// Analyser le fichier crash.bin (mode post-mortem)
void analyser_crash(void) {
    FILE *fichier = fopen("crash.bin", "rb");
    if (fichier == NULL) {
           printf("= Aucun fichier crash.bin trouvé. Aucun crash enregistré.\n");
        return;
    }
    
    printf("\n= ========== ANALYSE POST-MORTEM ==========\n\n");
    
    // Variables pour les calculs
    float somme_vitesses = 0;
    float temp_max = 0;
    int nb_frames = 0;
    
    // Lire toutes les frames
    long timestamp;
    float vitesse, temperature;
    
    printf("Frames enregistrées :\n");
    printf("-------------------------------------------------------\n");
    
    while (fread(&timestamp, sizeof(long), 1, fichier) == 1) {
        fread(&vitesse, sizeof(float), 1, fichier);
        fread(&temperature, sizeof(float), 1, fichier);
        
        printf("[Frame %d] Temps: %ld ms | V: %.2f km/h | T: %.2f °C\n",
               nb_frames + 1, timestamp, vitesse, temperature);
        
        somme_vitesses += vitesse;
        if (temperature > temp_max) {
            temp_max = temperature;
        }
        nb_frames++;
    }
    
    fclose(fichier);
    
    // Afficher les statistiques
    printf("-------------------------------------------------------\n");
    printf("\n= STATISTIQUES :\n");
    printf("   = Vitesse moyenne : %.2f km/h\n", somme_vitesses / nb_frames);
    printf("   = Température maximale : %.2f °C\n", temp_max);
    printf("\n===========================================\n\n");
}
