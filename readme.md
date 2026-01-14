# BLACKBOX - Enregistreur de Vol 

## Description du Projet

Ce projet simule une **boîte noire** embarquée dans un véhicule. Le système enregistre en permanence les paramètres vitaux (vitesse, température moteur) dans un **buffer circulaire** de capacité limitée. En cas de crash ou d'arrêt, les données sont sauvegardées pour analyse post-mortem.

---

##  Objectifs Pédagogiques

- **Gestion mémoire dynamique** : Utilisation de listes chaînées et malloc/free
- **Buffer circulaire (FIFO)** : Rotation automatique des données anciennes
- **Fichiers binaires** : Sauvegarde et lecture avec fread/fwrite
- **Simulation physique** : Cinématique (vitesse) et thermodynamique (température)

---

##  Structure du Projet

```
blackbox/
├── main.c           # Programme principal + Menu
├── b_noire_.h       # Structures et prototypes
├── b_noire_.c       # Gestion du buffer circulaire
├── simulation.c     # Calculs physiques (vitesse + température)
├── fichier.c        # Sauvegarde/Lecture crash.bin
├── config.c         # Chargement de config.txt
├── Makefile         # Compilation
└── README.md        # Ce fichier
```

---

##  Compilation et Exécution


### Compilation
```bash
make
```

### Exécution
```bash
./blackbox
```

### Nettoyage
```bash
make clean
```

---



