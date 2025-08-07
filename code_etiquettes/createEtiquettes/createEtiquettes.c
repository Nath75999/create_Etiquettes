#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // mkdir
#include <cairo.h>
#include <dirent.h>

#define WIDTH 600
#define HEIGHT 200
#define IMAGES_PAR_LIGNE 3  // 3 images par ligne (largeur)
#define IMAGES_PAR_COLONNE 7 // 7 images par colonne (hauteur)
#define MAX_IMAGES 21  // 21 étiquettes par image (3x7)

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#endif

// Crée le dossier s'il n'existe pas
void creer_dossier_si_necessaire(const char* chemin) {
    struct stat st = {0};
    if (stat(chemin, &st) == -1) {
        if (mkdir(chemin, 0700) != 0) {
            perror("Erreur création dossier");
            exit(EXIT_FAILURE);
        }
    }
}

// Fonction pour extraire une ligne spécifique du CSV
int lire_ligne_csv(const char* filename, int ligne_voulue, char* code_jeu, char* nom_jeu) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture CSV");
        return 0;
    }

    char buffer[1024];
    int ligne = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (ligne == 0) { // Ignorer en-tête
            ligne++;
            continue;
        }
        if (ligne == ligne_voulue) {
            // Séparer par virgules
            char* token = strtok(buffer, ",");
            if (token) strcpy(code_jeu, token);
            else code_jeu[0] = '\0';

            token = strtok(NULL, ",");
            if (token) {
                // Supprimer le saut de ligne final s'il existe
                size_t len = strlen(token);
                if(len > 0 && (token[len-1] == '\n' || token[len-1] == '\r')) token[len-1] = '\0';
                strcpy(nom_jeu, token);
            } else nom_jeu[0] = '\0';

            fclose(file);
            return 1;
        }
        ligne++;
    }

    fclose(file);
    return 0;
}

// Fonction pour dessiner l'étiquette PNG
void dessiner_etiquette(const char* code_jeu, const char* nom_jeu, const char* logo_path, const char* filename) {
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
    cairo_t* cr = cairo_create(surface);

    // Fond blanc
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Charger logo
    cairo_surface_t* logo = cairo_image_surface_create_from_png(logo_path);
    if (cairo_surface_status(logo) != CAIRO_STATUS_SUCCESS) {
        fprintf(stderr, "Erreur chargement logo\n");
    } else {
        cairo_save(cr);
        double scale = 0.5;
        cairo_translate(cr, 20, 20);
        cairo_scale(cr, scale, scale);
        cairo_set_source_surface(cr, logo, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
        cairo_surface_destroy(logo);
    }

    // Texte noir
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 24);

    // Afficher Code jeu
    cairo_move_to(cr, 200, 60);
    cairo_show_text(cr, code_jeu);

    // Afficher Nom du jeu
    cairo_move_to(cr, 200, 120);
    cairo_show_text(cr, nom_jeu);

    // Sauvegarder l'image
    cairo_surface_write_to_png(surface, filename);

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

// Fonction pour créer la grande image avec la grille 7x3
void creer_grille_etiquettes() {
    const char* filename = "bdd.csv";

    // Créer dossier result s'il n'existe pas
    creer_dossier_si_necessaire("result");

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture fichier CSV");
        return;
    }

    // Compter le nombre de lignes dans le fichier CSV (ignorer l'en-tête)
    char buffer[1024];
    int total_lignes = 0;
    int first_line = 1;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        total_lignes++;
    }
    fclose(file);

    if (total_lignes == 0) {
        fprintf(stderr, "Fichier CSV vide ou sans données.\n");
        return;
    }

    // Calcul du nombre d'images nécessaires (21 étiquettes par image max)
    int num_images = (total_lignes + MAX_IMAGES - 1) / MAX_IMAGES;

    char code_jeu[128];
    char nom_jeu[128];
    int ligne = 1; // Ligne du CSV (1 = première ligne après header)

    for (int i = 0; i < num_images; i++) {
        // Créer la nouvelle surface pour la grille
        cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, IMAGES_PAR_LIGNE * (WIDTH + 10), IMAGES_PAR_COLONNE * (HEIGHT + 10));
        cairo_t* cr = cairo_create(surface);

        // Fond blanc
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);

        for (int j = 0; j < MAX_IMAGES && ligne <= total_lignes; j++) {
            if (lire_ligne_csv(filename, ligne, code_jeu, nom_jeu)) {
                // Créer étiquette temporaire
                char temp_filename[256];
                snprintf(temp_filename, sizeof(temp_filename), "temp_etiquette_%d.png", j);
                dessiner_etiquette(code_jeu, nom_jeu, "logo.png", temp_filename);

                // Charger étiquette temporaire
                cairo_surface_t* temp_surface = cairo_image_surface_create_from_png(temp_filename);
                if (cairo_surface_status(temp_surface) != CAIRO_STATUS_SUCCESS) {
                    fprintf(stderr, "Erreur chargement image %s\n", temp_filename);
                    ligne++;
                    continue;
                }

                // Position dans la grille
                int x = (j % IMAGES_PAR_LIGNE) * (WIDTH + 10);
                int y = (j / IMAGES_PAR_LIGNE) * (HEIGHT + 10);

                cairo_set_source_surface(cr, temp_surface, x, y);
                cairo_paint(cr);

                cairo_surface_destroy(temp_surface);
            }
            ligne++;
        }

        // Enregistrer l'image complète dans result/
        char output_filename[256];
        snprintf(output_filename, sizeof(output_filename), "result/grille_etiquettes_%d.png", i + 1);
        cairo_surface_write_to_png(surface, output_filename);

        cairo_destroy(cr);
        cairo_surface_destroy(surface);

        printf("Image créée : %s\n", output_filename);
    }

    printf("Grilles d'étiquettes générées avec succès.\n");
}

void removeTempFile(){
    DIR *dir;
    struct dirent *entry;

    // Ouvre le dossier courant
    dir = opendir(".");
    if (!dir) {
        perror("Erreur lors de l'ouverture du dossier courant");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Vérifie si le nom correspond à temp_etiquette_X.png
        // Format attendu : "temp_etiquette_<nombre>.png"
        if (strncmp(entry->d_name, "temp_etiquette_", 15) == 0) {
            int num;
            if (sscanf(entry->d_name, "temp_etiquette_%d.png", &num) == 1) {
                if (num >= 0 && num <= 999) {
                    // Supprime le fichier
                    if (remove(entry->d_name) == 0) {
                        printf("Supprimé : %s\n", entry->d_name);
                    } else {
                        perror("Erreur lors de la suppression");
                    }
                }
            }
        }
    }

    closedir(dir);
}

int main() {
    creer_grille_etiquettes();
    removeTempFile();
    return 0;
}
