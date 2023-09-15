#include <string>
#include <chrono>
#include <functional>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include <stack>
#include <queue>
#include <forward_list>
#include <list>

#include <Stack.hpp>
#include <Queue.hpp>
#include <SinglyLinkedList.hpp>
#include <DoublyLinkedList.hpp>
#include <PriorityQueue.hpp>


/**
 *  Die Laufzeit verschiedener Datenstrukturen des Projektes Alpha wird mit der des entsprechenden C++-Standards verglichen. Die Ergebnisse werden in einer
 *  csv-Datei gespeichert. Aus dieser liest ein Python-Skript sie aus und erstellt individuelle jpg-Dateien, welche die Laufzeit als zweidimensionale Graphen
 *  darstellt.
 *
 *  Messungen für weitere Datenstrukturen können unproblematisch hinzugefügt werden: 
 *      1. messe_[Datenstruktur]()-Funktion erstellen und entsprechend implementieren (siehe Anforderungen dieser)
 *      2. messe_[Datenstruktur]_std()-Funktion erstellen und implementieren
 *      3. myfile << csv_parsable(messe_[Datenstruktur], "Alpha [Datenstruktur]"); der main-Funktion passend hinzufügen.
 *      4. myfile << csv_parsable(messe_[Datenstruktur]_std, "C++ [Datenstruktur]"); der main-Funktion passend hinzufügen.
 *  Wenn die Beschreibung, die csv_parsable() mitgegeben wird, das Format "[Alpha/C++] [Datenstruktur]" erfüllt, kann das Python-Skript automatisch die
 *  Graphen erstellen.
 *
 *  ANFORDERUNGEN:  Damit der Pyplot funktioniert, muss Matplotlib installiert sein!
*/

void messe_stack(int count);
void messe_queue(int count);
void messe_slist(int count);
void messe_dlist(int count);
void messe_pqueue(int count);
void messe_dlist_std(int count);
void messe_slist_std(int count);
void messe_stack_std(int count);
void messe_queue_std(int count);
void messe_pqueue_std(int count);


double get_duration(int count, std::function<void(int)> messfunktion);
std::string csv_parsable(std::function<void(int)> messfunktion, std::string beschreibung);

static const int MAX_COUNT = 5000;
static const int SCHRITTWEITE = 20;

int main() {
    mkdir("build/messungen", 0777);
    std::ofstream myfile;
        myfile.open("build/messungen/messungen.csv");
        myfile << "Datenstrukturen;";
        for (int i = 0; i <= MAX_COUNT; i += SCHRITTWEITE) { myfile << std::to_string(i) << ";"; }
        myfile << "\n";
        myfile << csv_parsable(messe_stack, "Alpha Stack");
        myfile << csv_parsable(messe_stack_std, "C++ Stack");
        myfile << csv_parsable(messe_queue, "Alpha Queue");
        myfile << csv_parsable(messe_queue_std, "C++ Queue");
        myfile << csv_parsable(messe_slist, "Alpha SinglyLinkedList");
        myfile << csv_parsable(messe_slist_std, "C++ SinglyLinkedList");
        myfile << csv_parsable(messe_dlist, "Alpha DoublyLinkedList");
        myfile << csv_parsable(messe_dlist_std, "C++ DoublyLinkedList");
        myfile << csv_parsable(messe_dlist, "Alpha PriorityQueue");
        myfile << csv_parsable(messe_dlist_std, "C++ PriorityQueue");
        myfile.close();

    std::string command = "python3 src/create_graphs.py";
    system(command.c_str());
    return 0;
}

/**
 *  Führt die Messungen durch und formatiert die Ergebnisse in einen String, der eine csv-Zeile darstellen kann.
 *  @param messfunktion Die Funktion, für die gestestet werden soll: Kein Rückgabewert, Zahl der Testungen als Parameter
 *  @param beschreibung Format: "[Alpha/C++] [datenstruktur]"; Wird im Python-Skript verwendet.
*/
std::string csv_parsable(std::function<void(int)> messfunktion, std::string beschreibung) {
    std::string res;
    res += beschreibung + ";";
    for (int i = 0; i <= MAX_COUNT; i += SCHRITTWEITE) {
        res += std::to_string(get_duration(i, messfunktion)) + ";";
    }
    res += "\n";
    //std::cout << res << std::endl;
    return res;
}


double get_duration(int count, std::function<void(int)> messfunktion) {
    auto start = std::chrono::steady_clock::now();
    messfunktion(count);
    auto ende = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = ende - start;
    return diff.count();
}

void messe_stack(int count) {
    ProjektAlpha::Stack<std::string> stack;
    
    for (int i = 0; i < count; i++) {
        stack.push(std::to_string(i));
    }
    
    while (stack.get_size() != 0) {
        stack.pop();
    }
}

void messe_queue(int count) {
    ProjektAlpha::Queue<std::string> queue;
    
    for (int i = 0; i < count; i++) {
        queue.enqueue(std::to_string(i));
    }
    
    while (queue.get_size() != 0) {
        queue.dequeue();
    }
}

void messe_pqueue(int count) {
    ProjektAlpha::PriorityQueue<std::string, std::string> queue;
    
    for (int i = 0; i < count; i++) {
        queue.enqueue(std::to_string(i), std::to_string(i));
    }
    
    while (queue.get_size() != 0) {
        queue.dequeue();
    }
}

void messe_slist(int count) {
    ProjektAlpha::SinglyLinkedList<std::string> list;
    
    for (int i = 0; i < count; i += 2) {
        list.insert_front(std::to_string(i));
        list.insert_after(list.get_last(), std::to_string(i));
    }
    
    while (list.get_size() >= 1) {
        list.remove_after(list.get_first());
        if (list.get_size() >= 1) list.remove_front();
    }
}

void messe_dlist(int count) {
    ProjektAlpha::DoublyLinkedList<std::string> list;
    
    for (int i = 0; i < count; i += 2) {
        list.insert_front(std::to_string(i));
    }

}

void messe_stack_std(int count) {
    std::stack<std::string> stack;
    
    for (int i = 0; i < count; i++) {
        stack.push(std::to_string(i));
    }
    
    while (stack.size() != 0) {
        stack.pop();
    }
}

void messe_queue_std(int count) {
    std::queue<std::string> queue;
    
    for (int i = 0; i < count; i++) {
        queue.push(std::to_string(i));
    }
    
    while (queue.size() != 0) {
        queue.pop();
    }
}

void messe_slist_std(int count) {
    std::forward_list<std::string> list;
    
    for (int i = 0; i < count; i += 2) {
        list.push_front(std::to_string(i));
        list.insert_after(list.begin(), std::to_string(i));
    }
    while (!list.empty()) {
        list.erase_after(list.begin());
        list.pop_front();
    }
}

void messe_dlist_std(int count) {
    std::list<std::string> list;
    
    for (int i = 0; i < count; i += 2) {
        list.push_front(std::to_string(i));
    }
}

void messe_pqueue_std(int count) {
    std::priority_queue<std::string> queue;

    for (int i = 0; i < count; i++) {
        queue.push(std::to_string(i));
    }
    
    while (queue.size() != 0) {
        queue.pop();
    }
}

