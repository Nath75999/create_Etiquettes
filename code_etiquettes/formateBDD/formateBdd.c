#include <stdio.h>
#include <stdlib.h>

void remplacer_pipe_et_ascii(const char* fichier_entree, const char* fichier_sortie) {
    FILE* fin = fopen(fichier_entree, "r");
    if (!fin) {
        perror("Erreur ouverture fichier entrée");
        exit(EXIT_FAILURE);
    }

    FILE* fout = fopen(fichier_sortie, "w");
    if (!fout) {
        perror("Erreur ouverture fichier sortie");
        fclose(fin);
        exit(EXIT_FAILURE);
    }

    int c;
    int pipe_en_cours = 0;  // 1 si on est dans une séquence de '|'

    while ((c = fgetc(fin)) != EOF) {
        if (c == '|') {
            if (!pipe_en_cours) {
                // Premier pipe => écrire une virgule
                fputc(',', fout);
                pipe_en_cours = 1;
            }
            // Sinon ignorer pipes suivants dans la séquence
        } else {
            pipe_en_cours = 0;
            if (c >= 0 && c <= 127) {
                // ASCII de base => on écrit tel quel
                fputc(c, fout);
            } else {
                // Hors ASCII de base => remplacer par un espace
                fputc('_', fout);
            }
        }
    }

    fclose(fin);
    fclose(fout);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s fichier_entree fichier_sortie\n", argv[0]);
        return EXIT_FAILURE;
    }

    remplacer_pipe_et_ascii(argv[1], argv[2]);
    printf("Fichier converti avec succès.\n");

    return EXIT_SUCCESS;
}
