/*
 *  Definition der Datenstruktur Stack
 */

#pragma once

#include <memory>
#include <exception>

#include <Interfaces.hpp>

namespace ProjektAlpha {

typedef int integer;



/**
 *  Konkrete Implementation der Datenstruktur Queue
 *  @author Florian Barth
 *  @tparam T Klasse, deren Objekte gespeichert werden sollen
 */
template<class T>
class Queue
        : public Abstract_Queue<T>
{

    /*
    *  Node auf der Queue. Speichert ihren Inhalt sowie die naechstuntere und naechstobere Node.
    */
    template<class Node_T>
    struct QueueNode {
    public:
        std::shared_ptr<QueueNode<Node_T>> _next;
        std::shared_ptr<QueueNode<Node_T>> _prev;
        Node_T _content;
    };

public:
    Queue();
    virtual integer get_size() const override;
    virtual void enqueue(T content) override;
    virtual T dequeue() override;

private:
    std::shared_ptr<QueueNode<T>> head;
    std::shared_ptr<QueueNode<T>> tail;
    integer size;
};


}



// KOMMT EIGENTLICH IN DIE src/*.cpp
namespace ProjektAlpha {

template<class T>
Queue<T>::Queue()
    : size(0)
{}


template<class T>
integer Queue<T>::get_size() const {
    return size;
}

template<class T>
void Queue<T>::enqueue(T content) {
    QueueNode<T> node;
    node._content = content;
    std::shared_ptr<QueueNode<T>> tmp = std::make_shared<QueueNode<T>>(node);
    if (head != nullptr) {
        tmp -> _prev = tail;
        tail -> _next = tmp;
        tail = tmp;
    }
    else {
        tail = tmp;
        head = tmp;
    }
    size++;
}

template<class T>
T Queue<T>::dequeue() {
    if (head == nullptr) throw std::out_of_range("Queue ist empty");
    std::shared_ptr<QueueNode<T>> tmp = head;
    head = head -> _next;
    size--;
    return tmp -> _content;
}


}
