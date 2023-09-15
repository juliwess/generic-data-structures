#pragma once

#include <memory>
#include <iostream>
#include <SinglyLinkedList.hpp>
#include <HashsetNode.hpp>


namespace ProjektAlpha {


/** @brief Die Klasse HashsetList wird nur genutzt um das Hashset mithilfe der Hashtable zu realisieren
und stellt im wesentlichen die selbe Klasse wie SinglyLinkedList dar*/
template<class T>
  class HashsetList{
  public:
    HashsetList();

    virtual std::shared_ptr<HashsetNode<T>> get_first() const;//Get the first and last element
    virtual std::shared_ptr<HashsetNode<T>> get_last() const;

    virtual std::shared_ptr<HashsetNode<T>> insert_front(long x, T h);//Insert and delete elements
    virtual std::shared_ptr<HashsetNode<T>> insert_after(const std::shared_ptr<HashsetNode<T>>&, long x, T h);
    virtual std::shared_ptr<HashsetNode<T>> remove_front();
    virtual std::shared_ptr<HashsetNode<T>> remove_after(const std::shared_ptr<HashsetNode<T>>& a);

    // Prüft, ob die Liste leer ist
    virtual bool is_empty() const;

    // Get the next Node of the current List
    std::shared_ptr<HashsetNode<T>> next(const std::shared_ptr<HashsetNode<T>>& a);

    // Print the current List
    void print() const;

  private:
    std::shared_ptr<HashsetNode<T>> head;
  };



   template<class T>
    HashsetList<T>::HashsetList()
    {
    }


    template<class T>
    bool HashsetList<T>::is_empty() const {
        return (head == nullptr);
    }

    template<class T>
    std::shared_ptr<HashsetNode<T>> HashsetList<T>::get_first() const
    {
        return head;
    }

    template<class T>
    std::shared_ptr<HashsetNode<T>> HashsetList<T>::get_last() const//Gibt das letzte Element zurück
    {
        std::shared_ptr<HashsetNode<T>> current = head;

        while(current->get_next() != NULL)
        {
                current = current->get_next();
        }
        return current;
    }


    template<class T>
    std::shared_ptr<HashsetNode<T>> HashsetList<T>::insert_front(long x, T h)//Fügt ein Element am Anfang ein
    {
        std::shared_ptr<HashsetNode<T>> n;//Neuer Shared Pointer, eines Elements der Klasse HashsetNode mit dem Parameter x
        n = std::make_shared<HashsetNode<T>>();
        n->set_hash(x);
        n->set_key(h);

        n->set_next(head);//Nachfolger von n wird auf Head gesetzt
        head = n;//Head wird auf n gesetzt

        return head;
    }

    template<class T>
    std::shared_ptr<HashsetNode<T>> HashsetList<T>::insert_after(const std::shared_ptr<HashsetNode<T>>& predec, long x, T h)//Fügt ein Element hinter einem gegebenen Vorgänger ein
    {
        // std::shared_ptr<HashsetNode<T>> predecessor;
        // predecessor = predec;
        std::shared_ptr<HashsetNode<T>> n;//Neuer Pointer mit dem Integer Wert x als Parameter
        n = std::make_shared<HashsetNode<T>>(x);
        n->set_key(h);

        n->set_next(predec->get_next());//Nachfolger von n wird auf den Nachfolger von dem Vorgänger gesetzt
        predec->set_next(n);//Nachfolger des Vorgängers wird auf n gesetzt

        return n;
    }

    template<class T>
    std::shared_ptr<HashsetNode<T>> HashsetList<T>::remove_front()//Vorderstes Element wird entfernt
    {
        if(not head)//Es kann nichts entfernt werden, wenn die Liste leer ist
        {
            return nullptr;
        }

        std::shared_ptr<HashsetNode<T>> removed = head;//Der Kopf wird entfernt
        head = head->get_next();//Der Nachfolger des Kopfes ist der neue Kopf

        return removed;
    }


    template<class T>
    std::shared_ptr<HashsetNode<T>> HashsetList<T>::remove_after(const std::shared_ptr<HashsetNode<T>>& predec)//Entfernt ein Element hinter einem gegebenen Vorgänger
    {
        //std::shared_ptr<HashsetNode<T>> successor = predecessor;
        std::shared_ptr<HashsetNode<T>> between = predec->get_next();//Knoten zwischen Vorgänger und dem nächsten neuen Nachfolger von dem Vorgänger(der Knoten, der entfernt wird)
        predec->set_next(between->get_next());//Nachfolger des Vorgängers wird zu dem nachfolger von between
        between->set_next(nullptr);//betweens nachfolger ist null

        return predec;
    }

//     // Get the next Node of the current List

    template<class T>
    std::shared_ptr<HashsetNode<T>> HashsetList<T>::next(const std::shared_ptr<HashsetNode<T>>& current)
    {
        return current->next;
    }
//
//     // Print the current List

    template<class T>
    void HashsetList<T>::print() const
    {
        std::shared_ptr<HashsetNode<T>> current = head;//Startet beim Head
        while(current)//Läuft sollange current nicht null ist
        {
            std::cout<<current->get_hash()<<", "<<current->get_key()<<"-> ";//Druckt den Wert auf den Current zeigt
            current = current->get_next();
        }
        std::cout<<"null"<<std::endl;
    }

}

