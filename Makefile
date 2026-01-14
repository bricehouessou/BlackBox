# Makefile pour BlackBox

CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = blackbox

# Fichiers sources et objets
SRCS = main.c b_noire.c simulation.c fichier.c
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "✓ Compilation réussie ! Lancez avec ./blackbox"

# Compilation des fichiers .o
%.o: %.c b_noire.h
	$(CC) $(CFLAGS) -c $<

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET) crash.bin
	@echo "✓ Nettoyage terminé"

# Nettoyage + recompilation
rebuild: clean all

.PHONY: all clean rebuild
