import pprint
import csv
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np


with open('build/messungen/messungen.csv','r') as data:
    inhalt = csv.reader(data,delimiter=';')
    messzahlen = next(inhalt)
    del messzahlen[0]
    del messzahlen[len(messzahlen)-1]
    print(f"Intervall: [{messzahlen[0]}; {messzahlen[len(messzahlen)-1]}]")
    werte = {row[0]: [row[i] for i in range(1, len(row)-1)] for row in inhalt}
    #pprint.pprint(werte)
    datenstrukturen = set([x.split()[1] for x in werte.keys()])
    #pprint.pprint(datenstrukturen)

    for datenstruktur in datenstrukturen:
        alpha = werte[f"Alpha {datenstruktur}"]
        cpp = werte[f"C++ {datenstruktur}"]
        #print(f"\n\n{datenstruktur}\n   Alpha")
        #pprint.pprint(alpha)
        #print("   CPP")
        #pprint.pprint(cpp)

        plt.clf()
        plt.plot(np.asarray(messzahlen, float), np.asarray(alpha, float)*1000, label="Projekt Alpha", color="blue")
        plt.plot(np.asarray(messzahlen, float), np.asarray(cpp, float)*1000, label="C++-Standard", color="lime")
        plt.legend(loc="upper left")
        plt.xlabel("Zahl der Elemente", loc="right")
        plt.ylabel("Zeit in ms", loc="top")
        # plt.show()
        plt.savefig(f'build/messungen/{datenstruktur}.jpg')

print("Diagramme erfolgreich erstellt.")


