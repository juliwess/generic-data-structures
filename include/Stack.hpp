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
 *  Konkrete Implementation der Datenstruktur Stack
 *  @author Florian Barth
 *  @tparam T Klasse, deren Objekte gespeichert werden sollen
 */
template<class T>
class Stack
        : public Abstract_Stack<T>
{

    /**
    *  Node auf dem Stack. Speichert ihren Inhalt sowie die naechstuntere Node.
    */
    template<class Node_T>
    struct StackNode {
    public:
        std::shared_ptr<StackNode<Node_T>> _next;
        Node_T _content;
    };

public:
    Stack();
    virtual integer get_size() const override;
    virtual void push(T content) override;
    virtual T pop() override;

private:
    std::shared_ptr<StackNode<T>> top;
    integer size;
};


}



// KOMMT EIGENTLICH IN DIE src/*.cpp
namespace ProjektAlpha{

template <typename T>
Stack<T>::Stack()
    : size(0)
{}

template<typename T>
integer Stack<T>::get_size() const {
    return size;
}

template<class T>
void Stack<T>::push(T content) {
    StackNode<T> node;
    node._content = content;
    if (top != nullptr) node._next = top;
    top = std::make_shared<StackNode<T>>(node);
    size++;
}

template<class T>
T Stack<T>::pop() {
    if (top == nullptr) throw std::out_of_range("Stack ist empty");
    std::shared_ptr<StackNode<T>> tmp = top;
    top = top -> _next;
    size--;
    return tmp -> _content;
}


}
