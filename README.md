# Comptage de cellules

Auteur : Florent Tachenne et Marie Barbeau

Ce programme compte le nombre de cellules présentes dans une image en niveau de gris.

## Compilation

`make`

## Utilisation

`./bin/test_complet NOM_IMAGE` pour une image de microscope

`./bin/test_beta NOM_IMAGE` pour une image de artificielle

- `NOM_IMAGE` : le nom du fichier image .pgm à analyser.

## Tests

    $ ./bin/test_complet cellules.pgm
    Nombre de cellules: 17

    $ ./bin/test_beta disques.pgm
    Nombre de cellules: 9

    $ valgrind --leak-check=full          --show-leak-kinds=all          --track-origins=yes          --verbose          --log-file=valgrind-out.txt          ./bin/test_complet cellules.pgm
    Nombre de cellules: 17

