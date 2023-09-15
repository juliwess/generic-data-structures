// Alle abstrakten Klassen (Interfaces) für die vorgesehenen Datentypen von Project Alpha
// werden hier deklariert.

#pragma once

#include <functional>


namespace ProjektAlpha {

//* Als Integer (Ganzzahl) wird der Datentyp int verwendet.
typedef int integer;

/**
 *  @brief Grundlegendste Datenstruktur. Die Größe kann ausgegeben werden.
 *  @author Florian Barth
 */
template<class T>
class Abstract_Container {
public:
    /**
    *  @return Die Größe des Containers
    */
    virtual integer get_size() const = 0;
};


/**
 *  @brief Datenstruktur Stack. Speichert Objekte in einem Stapel. Oberstes Objekt wird mit push() eingefügt und wird
 *  mit pop() entfernt und zurückgegeben.
 *  @author Florian Barth
 *  @tparam T Klasse, die die Datenstruktur speichern soll
 */
template<class T>
class Abstract_Stack
        : public Abstract_Container<T>
{
public:
    virtual integer get_size() const = 0;
    /**
    *  @brief Fügt ein Objekt vorne dem Stack hinzu.
    *  @param T Der hinzuzufügende Inhalt
    */
    virtual void push(const T content) = 0;
    /**
    *  Gibt das oberste Objekt zurück und entfernt dieses vom Stack
    *  @return Das oberste Objekt
    */
    virtual T pop() = 0;
};


/**
 *  @brief Datenstruktur Queue. Datenstruktur realiesiert eine Warteschlange. enqueue() fügt am Ende der Schlange ein,
 *  dequeue() gibt das vorderste Element zurück und entfernt dieses.
 *  @author Florian Barth
 */
template<class T>
class Abstract_Queue
        : public Abstract_Container<T>
{
public:
    virtual integer get_size() const = 0;
    /**
    *  Fügt ein Objekt am Ende der Queue hinzu.
    *  @param T Der hinzuzufügende Inhalt
    */
    virtual void enqueue(const T content) = 0;
    /**
    *  Gibt das vorderste Objekt zurück und entfernt dieses aus der Queue
    *  @return Das vorderste Objekt
    */
    virtual T dequeue() = 0;
};


/**
 *  @brief Grundlegende Datenstruktur. Die Größe sowie ein Iterator können ausgegeben werden. Iteratoren werden durch das Template Iter angegeben
 *  @author Florian Barth
 */
template<class T, class Iter>
class Abstract_IterableContainer
        : public Abstract_Container<T>
{
public:
    virtual integer get_size() const = 0;
    /**
     * @return Das vorderste Objekt
    */
    virtual Iter get_first() const = 0;
    /** 
     * @return Das hinterste Objekt
    */
    virtual Iter get_last() const = 0;
};

/**
 *  @brief Einfach verkettete Liste. Die Objekte können von vorne bis hinten durchlaufen werden.
 *  @author Florian Barth
 */
template<class T, class Iter>
class Abstract_SinglyLinkedList
        : public Abstract_IterableContainer<T, Iter>
{
public:
    virtual integer get_size() const = 0;
    virtual Iter get_first() const = 0;
    virtual Iter get_last() const = 0;
    /**
     * Fügt vorne ein neues Objekt ein
     * @param T Der einzufügende Inhalt
     * @return Das eingefügte Objekt
    */
    virtual Iter insert_front(const T content) = 0;
    /**
     * Fügt hinter dem angegebenen Objekt ein neues Objekt ein
     * @param Iter, T Der Vorgänger und der einzufügende Inhalt
     * @return Das eingefügte Objekt
    */
    virtual Iter insert_after(const Iter& pred, T content) = 0;
    /**
     * Entfernt das Objekt hinter dem angegeben Objekt
     * @param Iter Vorgänger-Objekt
     * @return Das entfernte Objekt
    */
    virtual Iter remove_after(const Iter& pred) = 0;
};


/**
 *  @brief Doppelt verkettete Liste. Die Objekte können von vorne bis hinten sowie von hinten nach vorne durchlaufen werden.
 *  @author Florian Barth
 */
template<class T, class Iter>
class Abstract_DoublyLinkedList
        : public Abstract_IterableContainer<T, Iter>
{
public:
    virtual integer get_size() const = 0;
    virtual Iter get_first() const = 0;
    virtual Iter get_last() const = 0;
    /**
     * Fügt vorne ein neues Objekt ein
     * @param T Der einzufügende Inhalt
    */
    virtual void insert_front(const T&) = 0;
    /**
     * Fügt hinter dem angegebenen Objekt ein neues Objekt ein
     * @param Iter, T Vorgänger und der einzufügende Inhalt
    */
    virtual void insert_after(const Iter& pred, const T&) = 0;
    /**
     * Entfernt des vorderste Objekt
    */
    virtual void remove_front() = 0;
    /**
     * Entfernt das angegebene Objekt
     * @param Iter Das zu entfernende Objekt
    */
    virtual void remove(Iter) = 0;
};


/**
 *  @brief Priority Queue. Funktioniert wie eine Queue, allerdings haben die Inhalte ein Gewicht, nach welchem
 *  ihr Platz in der Priority Queue festgelegt wird. (Höchstes Gewicht wird zuerst ausgegeben)
 *  @author Florian Barth
 */
template<class T, class U, class Iter>
class Abstract_PriorityQueue
        : public Abstract_IterableContainer<T, Iter>
{
public:
    virtual integer get_size() const = 0;
    virtual Iter get_first() const = 0;
    virtual Iter get_last() const = 0;
    /**
     * Entfernt das Objekt mit der höchsten Priorität aus der Queue
     * @return Den Wert des entfernten Elements
    */
    virtual T dequeue() = 0;
    /**
     * Fügt ein Objekt mit angegebener Priorität und Wert ein
     * @param T, U Wert und Priorität
    */
    virtual void enqueue(const T& value, const U& priority) = 0;
};


/**
 *  @brief Hashende Menge. Objekte ohne intrinsische Ordnung werden anhand eines Hashwertes gespeichert.
 *  Hashfunktion muss angegeben werden.
 *  @author Florian Barth
 */
template<class T, class Iter>
class Abstract_HashSet
        : public Abstract_IterableContainer<T, Iter>
{
public:
    virtual integer get_size() const = 0;
    virtual Iter get_first() const = 0;
    virtual Iter get_last() const = 0;
    virtual bool exists(const T&) const = 0;
    virtual void insert(const T) = 0;
    virtual void remove(const T&) = 0;
};


/**
 *  @brief Geordnete Menge. Objekte mit intrinsischer Ordnung werden anhand eines dieser Ordnung gespeichert.
 *  "<="-Operator muss implementiert sein.
 *  @author Florian Barth
 */
template<class T, class Iter>
class Abstract_OrderedSet
        : public Abstract_IterableContainer<T, Iter>
{
public:
    virtual integer get_size() = 0;
    virtual Iter& get_first() = 0;
    virtual Iter& get_last() = 0;
    virtual bool exists(const T& content) = 0;
    virtual T& search(const T& content) = 0;
    virtual void insert(const T content) = 0;
    virtual void remove(T& content) = 0;
};









}
