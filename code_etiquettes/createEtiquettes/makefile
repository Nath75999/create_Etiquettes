# Makefile Générique avec support de Cairo

EXT = c
CXX = gcc
EXEC = CREATE_ETIQUETTES

# Flags de compilation
CXXFLAGS = -Wall -W -pedantic $(shell pkg-config --cflags cairo)
LDFLAGS = $(shell pkg-config --libs cairo) -lm

# Organisation des fichiers
OBJDIR = dependencies
SRC = $(wildcard *.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

# Cible principale
all: $(OBJDIR) $(EXEC)

# Exécutable
$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(LDFLAGS)

# Compilation des .o dans dependencies/
$(OBJDIR)/%.o: %.$(EXT)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

# Création du dossier dependencies/ si nécessaire
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Nettoyage
clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -f $(EXEC)

# Exécution après compilation
run: all
	@./$(EXEC)
