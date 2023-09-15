#pragma once

#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <SinglyLinkedListNode.hpp>
#include <Interfaces.hpp>

namespace ProjektAlpha {

/** @author Julian Wessling*/
/** @brief eine einfach verkettete Liste wird hier realisiert*/
template<class T>
class SinglyLinkedList : public Abstract_SinglyLinkedList<T, typename std::shared_ptr<SinglyLinkedListNode<T>>>
{
    public:
    SinglyLinkedList();

    virtual integer get_size() const override;
    virtual std::shared_ptr<SinglyLinkedListNode<T>> get_first() const override;
    virtual std::shared_ptr<SinglyLinkedListNode<T>> get_last() const override;

    // Einfügen und entfernen
    virtual std::shared_ptr<SinglyLinkedListNode<T>> insert_front(T x) override;
    virtual std::shared_ptr<SinglyLinkedListNode<T>> insert_after(const std::shared_ptr<SinglyLinkedListNode<T>>& predec, T x) override;
    virtual std::shared_ptr<SinglyLinkedListNode<T>> remove_front();
    virtual std::shared_ptr<SinglyLinkedListNode<T>> remove_after(const std::shared_ptr<SinglyLinkedListNode<T>>& predec) override;

    // Nächste Node zurückgeben
    virtual std::shared_ptr<SinglyLinkedListNode<T>> next(const std::shared_ptr<SinglyLinkedListNode<T>>& a);

    // Die SinglyLinkedList drucken
    void print() const;

    //Implementierung des iterators
    /*
     *
     *
     */
     /** @brief Ein simpler Forwarditerator, der durch die einzelnen Knotern der Liste geht*/
        class iterator: public std::iterator<
        std::forward_iterator_tag,
        SinglyLinkedListNode<T>,
        std::ptrdiff_t,
        std::shared_ptr<SinglyLinkedListNode<T>>,
        SinglyLinkedListNode<T>&
        >
        {
        private:
            std::shared_ptr<SinglyLinkedListNode<T>> ptr;
        public:
            iterator(std::shared_ptr<SinglyLinkedListNode<T>> p) : ptr(p){}
            iterator& operator++() { if(ptr) { ptr = ptr->get_next(); } return *this;}
            iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
            bool operator==(iterator other) const {return ptr == other.ptr;}
            bool operator!=(iterator other) const {return !(*this == other);}
            SinglyLinkedListNode<T> operator*() const {return *ptr;}
        };

        iterator begin() {return this->head;}
        iterator end() {return typename iterator::pointer(nullptr);}
        /*
         *
         *
         */

    private:
    std::shared_ptr<SinglyLinkedListNode<T>> head;
    integer size = 0;
    };






    //Wegen der Nutzung von Templates wird der Quellcode in der hpp abgelegt

   /** @brief Konstrkutor kann leer bleiben*/      
   template<class T>
   SinglyLinkedList<T>::SinglyLinkedList()
    {
    }

    /** @brief gibt die Größe zurück*/  
    template<class T>
    integer SinglyLinkedList<T>::get_size() const
    {
        return size;
    }

    /** @brief gibt das erste Element zurück*/  
    template<class T>
    std::shared_ptr<SinglyLinkedListNode<T>> SinglyLinkedList<T>::get_first() const
    {
        return head;
    }

    /** @brief Iteriert durch die Liste, um dann das erste Element zurück zu geben*/  
    template<class T>
    std::shared_ptr<SinglyLinkedListNode<T>> SinglyLinkedList<T>::get_last() const
    {
        std::shared_ptr<SinglyLinkedListNode<T>> current = head;
        while(current->get_next() != nullptr)
        {
            current = current->get_next();
        }
        return current;
    }

    /** @brief Fügt ein Element am Anfang der Liste ein*/  
    template<class T>
    std::shared_ptr<SinglyLinkedListNode<T>> SinglyLinkedList<T>::insert_front(T x)
    {
        std::shared_ptr<SinglyLinkedListNode<T>> n;//Neuer Shared Pointer, eines Elements der Klasse SinglyLinkedListNode mit dem Parameter x
        n = std::make_shared<SinglyLinkedListNode<T>>(x);

        n->set_next(head);//Nachfolger von n wird auf Head gesetzt
        head = n;//Head wird auf n gesetzt
        size++;
        return head;
    }



    /** @brief Man hat auch die Möglichkeit nach einem gegebenen Vorgänger einzufügen*/  
    template<class T>
    std::shared_ptr<SinglyLinkedListNode<T>> SinglyLinkedList<T>::insert_after(const std::shared_ptr<SinglyLinkedListNode<T>>& predec, T x)//Fügt ein Element hinter einem gegebenen Vorgänger ein
    {
        std::shared_ptr<SinglyLinkedListNode<T>> n;//Neuer Pointer mit dem Integer Wert x als Parameter
        n = std::make_shared<SinglyLinkedListNode<T>>(x);

        n->set_next(predec->get_next());//Nachfolger von n wird auf den Nachfolger von dem Vorgänger gesetzt
        predec->set_next(n);//Nachfolger des Vorgängers wird auf n gesetzt
        size++;
        return n;
    }





    /** @brief das erste Element der Liste wird entfernt*/  
    template<class T>
    std::shared_ptr<SinglyLinkedListNode<T>> SinglyLinkedList<T>::remove_front()
    {
        try
        {
            if(head == nullptr)
            {
                throw std::logic_error("There is no first element to remove");
            }
        }
            
        catch(std::logic_error& e)
        {
            std::cout<<"Nullptr will be returned"<<std::endl;
            std::cout<<e.what();
            return nullptr;
        }
        

        size--;
        std::shared_ptr<SinglyLinkedListNode<T>> removed = head;//Der Kopf wird entfernt
        head = head->get_next();//Der Nachfolger des Kopfes ist der neue Kopf

        return removed;
    }




    /** @brief man hat auch die Möglichkeit nach einem gegebenen Vorgänger zu entfernen*/  
    template<class T>
    std::shared_ptr<SinglyLinkedListNode<T>> SinglyLinkedList<T>::remove_after(const std::shared_ptr<SinglyLinkedListNode<T>>& predec)//Entfernt ein Element hinter einem gegebenen Vorgänger
    {
        size--;
        std::shared_ptr<SinglyLinkedListNode<T>> between = predec->get_next();//Knoten zwischen Vorgänger und dem nächsten neuen Nachfolger von dem Vorgänger(der Knoten, der entfernt wird)
        predec->set_next(between->get_next());//Nachfolger des Vorgängers wird zu dem nachfolger von between
        between->set_next(nullptr);//betweens nachfolger ist null

        return predec;
    }








    /** @brief gibt den Nachfolger einer ListNode zurück*/  
    template<class T>
    std::shared_ptr<SinglyLinkedListNode<T>> SinglyLinkedList<T>::next(const std::shared_ptr<SinglyLinkedListNode<T>>& current)
    {
        return current->get_next();
    }



    /** @brief druckt die SinglyLinkedList aus*/  
    template<class T>
    void SinglyLinkedList<T>::print() const
    {
        std::shared_ptr<SinglyLinkedListNode<T>> current = head;//Startet beim Head
        while(current)//Läuft sollange current nicht null ist
        {
            std::cout<< current->get_data() <<"-> ";//Druckt den Wert auf den Current zeigt
            current = current->get_next();
        }
        std::cout<<"null"<<std::endl;
    }



};
