#pragma once

#include <memory>
#include <string>
#include <Interfaces.hpp>

/** @author Julian Wessling*/  
/** @brief Die SinglyLinkedList ist hier mit einer externen Node-Klasse realisiert , die den Inhalt der Liste verwaltet*/  
namespace ProjektAlpha {
  template<class T>
  class SinglyLinkedListNode
  {
  public:
    SinglyLinkedListNode(T data);
    T get_data() const;
    void set_data(T data);
    std::shared_ptr<SinglyLinkedListNode<T>> get_next();
    void set_next(std::shared_ptr<SinglyLinkedListNode<T>> next);

  private:
    std::shared_ptr<SinglyLinkedListNode<T>> next;

    T data;
  };


    /** @brief bei Instanziierung, wird in der Node ein wert gepseichert*/  
    template<class T>
    SinglyLinkedListNode<T>::SinglyLinkedListNode(T data)//Daten werden data_ zugewiesen(ein integer Wert)
    {
        this->data = data;
    }

    /*
     *
     * GETTER UND SETTER
     *
     */

  /** @brief gibt die Daten der node zurück*/  
    template<class T>
    T SinglyLinkedListNode<T>::get_data() const
    {
        return data;
    }

  /** @brief Ändere die Daten der Node*/  
    template<class T>
    void SinglyLinkedListNode<T>::set_data(T data)
    {
        this->data = data;
    }

  /** @brief Hole die Nachfolgenode*/  
    template<class T>
    std::shared_ptr<SinglyLinkedListNode<T>> SinglyLinkedListNode<T>::get_next()
    {
        return next;
    }

  /** @brief Setze die Nachfolgenode*/  
     template<class T>
    void SinglyLinkedListNode<T>::set_next(std::shared_ptr<SinglyLinkedListNode<T>> next)
    {
        this->next = next;
    }

  };
