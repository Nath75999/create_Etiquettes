# Nom du compilateur
CC = gcc

# Options de compilation : warnings activés, standard C11, optimisation légère
CFLAGS = -Wall -Wextra -std=c11 -O2

# Nom de l'exécutable
TARGET = FORMATE_BDD

# Fichier source
SRC = formateBdd.c

# Règle par défaut : compilation
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Nettoyage des fichiers générés
clean:
	rm -f $(TARGET)

# Pour forcer la recompilation (optionnel)
.PHONY: all clean
