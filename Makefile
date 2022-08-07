# Options de compilation
# (infos debug, tous warnings, standard C99, dossier include)
CFLAGS=-g `pkg-config --cflags gtk+-3.0` -I ../include -Wall -Wextra -std=c99 -Iinclude
# Options d'édition des liens (pour utiliser math.h)
LDLIBS=-lm -lsndfile -lportaudio

# Règle par défaut : générer tous les exécutables

all: bin/test_beta
all: bin/test_complet
all: bin/test_seuillage
all: bin/test_lecture
all: bin/test_bord
all: bin/test_erosion
all: bin/test_last_erosion
all: bin/test_trous


# Règle générique pour générer les fichiers objets pour les sources (.c -> .o)
obj/%.o: src/%.c
	gcc $(CFLAGS) -c $^ -o $@

# Règle générique pour générer les fichiers objets pour les tests (.c -> .o)
obj/test_%.o: test/test_%.c
	gcc $(CFLAGS) -c $^ -o $@

# Règle générique pour générer les exécutables de test (.o -> executable)
bin/test_%: obj/%.o obj/test_%.o 
	gcc $^ $(LDLIBS) -o $@

# Règle spécifique pour générer l'exécutable 
bin/test_beta: obj/test_beta.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o
	gcc $^ $(LDLIBS) -o $@
bin/test_complet: obj/test_complet.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o
	gcc $^ $(LDLIBS) -o $@
bin/test_seuillage: obj/test_seuillage.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o
	gcc $^ $(LDLIBS) -o $@
bin/test_lecture: obj/test_lecture.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o
	gcc $^ $(LDLIBS) -o $@
bin/test_bord: obj/test_bord.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o
	gcc $^ $(LDLIBS) -o $@
bin/test_erosion: obj/test_erosion.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o
	gcc $^ $(LDLIBS) -o $@
bin/test_last_erosion: obj/test_last_erosion.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o
	gcc $^ $(LDLIBS) -o $@
bin/test_trous: obj/test_trous.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o obj/lecture_ecriture.o obj/op_booleennes.o obj/op_morphologiques.o obj/seuillage.o obj/application_cellules.o
	gcc $^ $(LDLIBS) -o $@

# Règle de nettoyage
clean:
	rm -rf bin obj
	mkdir bin obj
