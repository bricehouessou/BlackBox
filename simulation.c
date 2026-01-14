#include "b_noire.h"

// Calculer la nouvelle vitesse selon l'action utilisateur
void calculer_nouvelle_vitesse(float *vitesse, char action) {
    if (action == 'A' || action == 'a') {
        *vitesse += ACCELERATION;
        printf("\nAccélération : +%.1f km/h\n", ACCELERATION);
    } else if (action == 'F' || action == 'f') {
        *vitesse -= FREINAGE;
        printf(" Freinage : -%.1f km/h\n", FREINAGE);
        
        // La vitesse ne peut pas être négative
        if (*vitesse < 0) {
            *vitesse = 0;
        }
    }
}

// Calculer la nouvelle température selon la formule thermodynamique
// Tnew = Told + (Kchauffe * v) - (Kcool * (Told - Tamb))
void calculer_nouvelle_temperature(float *temperature, float vitesse) {
    //float delta_chauffe = K_CHAUFFE * vitesse;
    //float delta_refroidissement = K_COOL * (*temperature - TEMP_AMBIANTE);
    
    //*temperature = *temperature + delta_chauffe - delta_refroidissement;
    *temperature = *temperature + K_CHAUFFE * vitesse - (K_COOL * (*temperature - TEMP_AMBIANTE));

}

// Obtenir le timestamp en millisecondes depuis le début du programme
long obtenir_timestamp_ms(struct timeval debut_prog) {
    struct timeval maintenant;
    gettimeofday(&maintenant, NULL);
    
    // Calculer la différence en millisecondes
    long secondes = maintenant.tv_sec - debut_prog.tv_sec;
    long microsecondes = maintenant.tv_usec - debut_prog.tv_usec;
    
    return (secondes * 1000) + (microsecondes / 1000);
}
