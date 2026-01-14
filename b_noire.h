#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// ====== CONSTANTES ======
#define CAPACITE_MAX 10
#define TEMP_SURCHAUFFE 110.0
#define TEMP_AMBIANTE 20.0
#define VITESSE_INIT 0.0
#define ACCELERATION 5.0
#define FREINAGE 7.0
#define K_CHAUFFE 0.5
#define K_COOL 0.1

// ====== STRUCTURES ======

// Structure Frame (Trame d'enregistrement)
typedef struct Frame {
    long timestamp;              // Timestamp en millisecondes depuis le début
    float vitesse;               // Vitesse en km/h
    float temperature_moteur;    // Température en °C
    struct Frame *suivant;       // Pointeur vers la frame suivante
} Frame;

// Structure BoiteNoire (Buffer circulaire)
typedef struct {
    Frame *debut;    // Pointeur vers la frame la plus ancienne
    Frame *fin;      // Pointeur vers la frame la plus récente
    int nb_frames;   // Nombre actuel de frames stockées
} BoiteNoire;

// ====== PROTOTYPES - blackbox.c ======
void initialiser_boite(BoiteNoire *b);
void enregistrer_cycle(BoiteNoire *b, float v, float t, long timestamp);
void liberer_boite(BoiteNoire *b);
void afficher_historique(BoiteNoire *b);

// ====== PROTOTYPES - simulation.c ======
void calculer_nouvelle_vitesse(float *vitesse, char action);
void calculer_nouvelle_temperature(float *temperature, float vitesse);
long obtenir_timestamp_ms(struct timeval debut_prog);

// ====== PROTOTYPES - fichier.c ======
void dump_memory(BoiteNoire *b);
void analyser_crash(void);

#endif
