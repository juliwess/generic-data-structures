# Projekt Alpha

## Projekt bauen
Um das Projekt zu bauen, soll einer der folgenden Befehlsketten im Projektverzeichnis ausgeführt werden.
In Linux Mint verwendet man
```
cmake -S . -B build && cmake --build build
```
Auf den Rechnern der CIP Pools ist der Aufruf leider ein wenig länger
```
export PROJ_PATH=`pwd` && cmake -S $PROJ_PATH -B $PROJ_PATH/build && cmake --build $PROJ_PATH/build
```
Falls das Projekt so nicht baut, liegen entweder Implementierungsfehler vor oder es fehlen externe Softwarepakete.


## Wo finde ich Was?
Die Interfaces für die Datenstrukturen findet man in include/Interfaces.hpp. Dort sind alle Interfaces nacheinander deklariert.

Alle konkreten Implementationen der Interfaces findet man ebenfalls in include/ und jeweils gefolgt vom Datenstrukturnamen.
