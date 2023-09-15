#pragma once

#include <memory>
#include <string>
#include <Interfaces.hpp>

namespace ProjektAlpha {

/**
 * Implementation einer Node von DoublyLinkedList
 * @tparam T Klasse die in den Nodes gespeichert wird
 * @author Max Vtulkin
*/
  template<class T>
  class DoublyLinkedListNode : public std::enable_shared_from_this<DoublyLinkedListNode<T>> {

    public:

        // Konstruktor
        DoublyLinkedListNode(T data);

        // Shared this pointer zurückgeben
        std::shared_ptr<DoublyLinkedListNode<T>> get_ptr() {
            return this->shared_from_this();
        }

        // Sets und gets
        T get_data() const;
        std::shared_ptr<DoublyLinkedListNode<T>> get_next() const;
        std::shared_ptr<DoublyLinkedListNode<T>> get_pred() const;
        void set_data(const T& data);
        void set_next(std::shared_ptr<DoublyLinkedListNode<T>> next);
        void set_next_new(const T& data);

    private:

        std::shared_ptr<DoublyLinkedListNode> next_;
        std::weak_ptr<DoublyLinkedListNode> pred_;
        T data_;
    };

    // Konstruktor
    template<class T>
    DoublyLinkedListNode<T>::DoublyLinkedListNode(T data)//Daten werden data_ zugewiesen(ein integer Wert)
    {
        data_ = data;
    }

    // Get Data
    template<class T>
    T DoublyLinkedListNode<T>::get_data() const {
      return data_;
    }
  
    // Get Next
    template<class T>
    std::shared_ptr<DoublyLinkedListNode<T>> DoublyLinkedListNode<T>::get_next() const {
      return next_;
    }

    // Get Next
    template<class T>
    std::shared_ptr<DoublyLinkedListNode<T>> DoublyLinkedListNode<T>::get_pred() const {
      return pred_.lock();
    }

    // Set Data
    template<class T>
    void DoublyLinkedListNode<T>::set_data(const T& data) {
      data_ = data;
    }
  
    // Set Next (Direkt next angeben)
    template<class T>
    void DoublyLinkedListNode<T>::set_next(std::shared_ptr<DoublyLinkedListNode<T>> next) {
      if (next != nullptr) {
        next_ = next;
        next_->pred_ = this->get_ptr();
      } else {
        next_ = nullptr;
      }
    }

    // Set Next new (Nur T angeben). Erstellt neuen next und setzt die übergebenen Daten
    template<class T>
    void DoublyLinkedListNode<T>::set_next_new(const T& data) { 
        next_ = std::make_shared<DoublyLinkedListNode<T>>(data);
        next_->pred_ = this->get_ptr();
    }
}