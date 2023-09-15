#pragma once

#include <memory>
#include <iostream>

#include <DoublyLinkedListNode.hpp>
#include <Interfaces.hpp>

namespace ProjektAlpha {

/**
 * Konkrete Implementierung einer Doppelt verketteten Liste
 * @tparam T Klasse der gespeicherten Werte in den Nodes
 * @author Max Vtulkin
*/
    template<class T>
    class DoublyLinkedList : public Abstract_DoublyLinkedList<T, typename std::shared_ptr<DoublyLinkedListNode<T>>> {

        public: 

        // Konstruktor
        DoublyLinkedList();

        // Gets und sets
        virtual integer get_size() const override;
        virtual std::shared_ptr<DoublyLinkedListNode<T>> get_first() const override;
        virtual std::shared_ptr<DoublyLinkedListNode<T>> get_last() const override;

        // Hauptfunktionen
        virtual void insert_front(const T& data) override;
        virtual void insert_after(const std::shared_ptr<DoublyLinkedListNode<T>>& pred, const T& data) override;
        virtual void remove(std::shared_ptr<DoublyLinkedListNode<T>> node) override;
        virtual void remove_front() override;

        // Hilfsfunktionen
        void print() const;


        /* Iterator Implementation innerhalb des Containers
        *
        *
        */
       class iterator : public std::iterator<
            std::bidirectional_iterator_tag,
            DoublyLinkedListNode<T>,
            std::ptrdiff_t,
            std::shared_ptr<DoublyLinkedListNode<T>>,
            DoublyLinkedListNode<T>&
            > 
        {
            private:

            std::shared_ptr<DoublyLinkedListNode<T>> _p;
            
            public: 

            iterator(std::shared_ptr<DoublyLinkedListNode<T>> p) : _p(p) {}
            iterator& operator++() { if(_p) { _p = _p->get_next(); } return *this; }
            iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
            iterator& operator--() { if(_p) { _p = _p->get_pred(); } return *this; }
            iterator operator--(int) { iterator retval = *this; --(*this); return retval; }
            bool operator==(iterator other) const {return _p == other._p; }
            bool operator!=(iterator other) const {return !(*this == other); }
            DoublyLinkedListNode<T>& operator*() {return *_p;}
        };

        iterator begin() {return this->head_;}
        iterator rbegin() {return this->tail_.lock();}
        iterator end()   {return typename iterator::pointer(nullptr);}

        /*
        *
        *
        */

        private:

        integer size_;
        std::shared_ptr<DoublyLinkedListNode<T>> head_;
        std::weak_ptr<DoublyLinkedListNode<T>> tail_;
    };

    // Konstruktor 
    template<class T>
    DoublyLinkedList<T>::DoublyLinkedList() {
    }

    // Get size
    template<class T>
    integer DoublyLinkedList<T>::get_size() const {
        return size_;
    }

    // Get First
    template<class T>
    std::shared_ptr<DoublyLinkedListNode<T>> DoublyLinkedList<T>::get_first() const {
        return head_;
    }

    // Get Last
    template<class T>
    std::shared_ptr<DoublyLinkedListNode<T>> DoublyLinkedList<T>::get_last() const {
        return tail_.lock();
    }

    // Insert Front
    // Fügt vorne in der Liste ein Element ein und speichert den übergebenen Wert
    template<class T>
    void DoublyLinkedList<T>::insert_front(const T& data) {
        std::shared_ptr<DoublyLinkedListNode<T>> new_node = std::make_shared<DoublyLinkedListNode<T>>(data);

        // Ist die Liste nicht leer?
        if (head_ != nullptr) {
            new_node->set_next(head_);
            head_ = new_node;
        } else {
            head_ = new_node;
            tail_ = new_node;
        }

        // Größe der Liste erhöht
        size_++;
    }


    // Insert After
    // Fügt Element nach angegebenen Vorgänger Element ein und speichert dort den übergebenen Wert
    template<class T>
    void DoublyLinkedList<T>::insert_after(const std::shared_ptr<DoublyLinkedListNode<T>>& pred, const T& data) {

        // Ist die Liste nicht leer?
        if (pred != nullptr) {
            std::shared_ptr<DoublyLinkedListNode<T>> temp_node = pred->get_next();
            pred->set_next_new(data);
            pred->get_next()->set_next(temp_node);

            // Tail neu setzen, falls das neue Element das letzte ist
            if (tail_.lock() == pred) {
                tail_ = pred->get_next();
            }

            // Größe der Liste erhöht
            size_++;
        }
    }

    // Remove
    // Entfernt das übergebene Node Element
    template<class T>
    void DoublyLinkedList<T>::remove(std::shared_ptr<DoublyLinkedListNode<T>> node) {

        // Ist die Liste nicht leer?
        if (node != nullptr) {
            // Ist nur ein Element in der Liste? 
            if (head_ == tail_.lock()) {
                head_ = nullptr;
                tail_.lock() = nullptr;
            } else {
                // Head oder Tail oder dazwischen entfernen?
                if (node == head_) {
                    head_= head_->get_next();
                } else if (node == tail_.lock()) {
                    tail_ = tail_.lock()->get_pred();
                    tail_.lock()->set_next(nullptr);
                } else {
                    node->get_pred()->set_next(node->get_next());
                }

                // Node auf null setzen
                node = nullptr;

                // Größe der Liste verringert
                size_--;
            }
        } else { throw std::out_of_range("List is empty"); }
    }

    // Remove Front
    // Entfernt das vorderste Element 
    template<class T>
    void DoublyLinkedList<T>::remove_front() {

        // Ist die Liste nicht leer?
        if (head_ != nullptr) {

            // Ist Head das einzige Element in der Liste?
            if (head_ == tail_.lock()) {
                head_ = nullptr;
                tail_.lock() = nullptr;
            } else {
                head_ = head_->get_next();
            }

            // Größte der Liste verringert
                size_--;
        }
    }

    // Hilfsfunktion: print
    // Visualisiert aktuelle Liste
    template<class T>
    void DoublyLinkedList<T>::print() const {
        std::shared_ptr<DoublyLinkedListNode<T>> temp_node = head_;

        // Liste ist leer
        if (temp_node == nullptr) {
            std::cout << "Empty List" << std::endl;
            return; 
        }

        // Liste hat mind. 1 Element
        while (temp_node != nullptr) {
            std::cout << temp_node->get_data() << " -> ";

            if (temp_node->get_next() != nullptr)
                temp_node = temp_node->get_next();
            else {
                std::cout << "nullptr" << std::endl;
                break;
            }
        }

        std::cout << std::endl;
    }
}
