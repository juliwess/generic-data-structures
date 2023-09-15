// Konkrete Implementation des Datentyps "Priority Queue".
// Geerbt von den Interfaces in "interfaces.hpp".

#pragma once

#include <memory>
#include <queue>
#include <iostream>

#include <TreeNode.hpp>
#include <Interfaces.hpp>

namespace ProjektAlpha {

/**
 * Implementation einer Priority Queue
 * @brief Implementation in Form eines Binären Max Heap - Binärbaums
 * @tparam T Klasse für den gespeicherten Wert in jeder Node und U für die Priorität der Node
 * @author Max Vtulkin
 * */ 
template<class T, class U>
class PriorityQueue : public Abstract_PriorityQueue<T, U, typename std::shared_ptr<TreeNode<T,U>>> {

public:

    PriorityQueue();
    virtual integer get_size() const override;
    virtual std::shared_ptr<TreeNode<T,U>> get_first() const override;
    virtual std::shared_ptr<TreeNode<T,U>> get_last() const override;

    virtual T dequeue() override;
    virtual void enqueue(const T& value, const U& priority) override;
    void print() const;    // Gibt die Elemente der Queue in der entsprechenden Reihenfolge aus


    /* Iterator Implementation innerhalb des Containers
        *
        *
        */
       class iterator : public std::iterator<
            std::forward_iterator_tag,
            TreeNode<T,U>,
            std::ptrdiff_t,
            std::shared_ptr<TreeNode<T,U>>,
            TreeNode<T,U>&
            > 
        {
            private:

            std::shared_ptr<TreeNode<T,U>> ptr_;
            std::queue<std::shared_ptr<TreeNode<T,U>>> queue_;
            
            public: 

            iterator(std::shared_ptr<TreeNode<T,U>> p) : ptr_(p) {
                // Wurzel Kinder in Queue Pushen wenn möglich
                if (ptr_ != nullptr) {
                    if (ptr_->get_left_child() != nullptr) {
                        queue_.push(ptr_->get_left_child());
                    }

                    if (ptr_->get_right_child() != nullptr) {
                        queue_.push(ptr_->get_right_child());
                    }
                }
            }

            iterator& operator++() { 
                // Mit Level Order iterieren
                if (!queue_.empty())
                {
                    ptr_ = queue_.front();
                    queue_.pop();

                    if (ptr_->get_left_child() != nullptr) {
                        queue_.push(ptr_->get_left_child());
                    }

                    if (ptr_->get_right_child() != nullptr) {
                        queue_.push(ptr_->get_right_child());
                    }
                } else {
                    ptr_ = nullptr;
                }
                return *this; 
            }

            iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
            bool operator==(iterator other) const {return ptr_ == other.ptr_; }
            bool operator!=(iterator other) const {return !(*this == other); }
            TreeNode<T,U>& operator*() {return *ptr_;}
        };

        iterator begin() {return iterator(this->root_);}
        iterator end()   {return typename iterator::pointer(nullptr);}

        /*
        *
        *
        */

private:

    std::shared_ptr<TreeNode<T,U>> root_;
    integer size_;

protected:

    // Hilfsfunktionen
    std::shared_ptr<TreeNode<T,U>> add_to_empty_space(const T& value, const U& priority); // Fügt ein Node an den nächsen freien Platz ein
    std::shared_ptr<TreeNode<T,U>> find_last_node() const;                                // Gibt das letzte im Baum stehende Node zurück
    void swap_nodes(std::shared_ptr<TreeNode<T,U>> a, std::shared_ptr<TreeNode<T,U>> b);  // Tauscht die Attribute zweier Nodes

};


// Konstruktor
template<class T, class U>
PriorityQueue<T,U>::PriorityQueue() {
    size_ = 0;
}

// Get size
template<class T, class U>
integer PriorityQueue<T,U>::get_size() const {
    return size_;
}

// Get first
template<class T, class U>
std::shared_ptr<TreeNode<T,U>> PriorityQueue<T,U>::get_first() const {
    return root_;
}

// Get last
template<class T, class U>
std::shared_ptr<TreeNode<T,U>> PriorityQueue<T,U>::get_last() const {
    return find_last_node();
}


// Dequeue
template<class T, class U>
T PriorityQueue<T,U>::dequeue() {
    
    // Nur fortführen, falls es Objekte in der Queue gibt. Ansonsten Fehler.
    try {
        if (root_ != nullptr) {
        } else {
            throw (-10000);
        }
    } catch (T ret) {
        std::cout << "Queue is empty so unusable value will be returned." << std::endl;
        return ret;
    }

    // Root zwischenspeichern und am Ende zurückgeben
    T return_value = root_->get_value();

    // Wenn root einziges Element in der Queue ist, löschen
    if (root_->get_left_child() == nullptr && root_->get_right_child() == nullptr) {
        root_ = nullptr;
        size_--;
        return return_value;
    }

    // Node mit höchster Priorität (root) mit letztem Element tauschen
    std::shared_ptr<TreeNode<T,U>> last_node = find_last_node();
    swap_nodes(root_, last_node);

    // Ist das Node ein rechtes oder linkes Kind? Entsprechen löschen
    if (last_node == last_node->get_parent()->get_left_child())
        last_node->get_parent()->set_left_child(nullptr);
    else if (last_node == last_node->get_parent()->get_right_child())
        last_node->get_parent()->set_right_child(nullptr);

    // Root solange mit größtem Kind tauschen, bis größer als beide Kinder
    std::shared_ptr<TreeNode<T,U>> temp_node = root_;

    while (temp_node->get_left_child() != nullptr || temp_node->get_right_child() != nullptr) {

        std::shared_ptr<TreeNode<T, U>> largest_child = temp_node->get_left_child();

        if (temp_node->get_right_child() != nullptr) {
            if (temp_node->get_right_child()->get_priority() > largest_child->get_priority())
                largest_child = temp_node->get_right_child();
        }

        if (temp_node->get_priority() > largest_child->get_priority()) {
            break;
        }

        swap_nodes(temp_node, largest_child);
        temp_node = largest_child;

    }

    size_--;
    return return_value;
}

// Enqueue
template<class T, class U>
void PriorityQueue<T,U>::enqueue(const T& value, const U& priority) {
    
    // Einzufügendes Node
    std::shared_ptr<TreeNode<T,U>> new_node;

    // Ist die Queue leer?
    if (size_ == 0) {
        root_ = std::make_shared<TreeNode<T,U>>(value, priority);
    }
    // Ist die Queue nicht leer?
    else {
        
        // Finde die nächste freie Stelle in Level Order (Mit Hilfsfunktion durch Level-Order)
        new_node = add_to_empty_space(value, priority);

        // Neues Node solange mit Parent tauschen, bis Parent größer ist
        while (new_node->get_parent()->get_priority() < new_node->get_priority()) {
            
            swap_nodes(new_node, new_node->get_parent());

            new_node = new_node->get_parent();
            
            // Abbrechen, falls das Node bereits die Wurzel ist
            if (new_node->get_parent() == nullptr)
                break;
        }
    }

    size_++;
}

// Add to empty space
// Fügt ein neues Node an die nächst leere Stelle ein
template<class T, class U>
std::shared_ptr<TreeNode<T,U>> PriorityQueue<T,U>::add_to_empty_space(const T& value, const U& priority) {
    
    // Erstellen einer Queue für Durchlauf mit Levelorder
    std::queue<std::shared_ptr<TreeNode<T,U>>> q;
    q.push(root_);

    while (!q.empty()) {
        std::shared_ptr<TreeNode<T,U>> temp_node;
        temp_node = q.front();
        q.pop();

        if (temp_node->get_left_child() == nullptr) {
            temp_node->set_left_child(value, priority);
            return temp_node->get_left_child();
            
        } else if (temp_node->get_right_child() == nullptr) {
            temp_node->set_right_child(value, priority);
            return temp_node->get_right_child();
        } else {
            q.push(temp_node->get_left_child());
            q.push(temp_node->get_right_child());
        }
    }

    return nullptr; // Sollte diese Stelle nicht erreichen
}

// Swap nodes
template<class T, class U>
void PriorityQueue<T,U>::swap_nodes(std::shared_ptr<TreeNode<T,U>> a, std::shared_ptr<TreeNode<T,U>> b) {
    
    // Tausche die Attribute zweier Nodes
    T temp_value = a->get_value();
    U temp_priority = a->get_priority();

    a->set_value(b->get_value());
    a->set_priority(b->get_priority());

    b->set_value(temp_value);
    b->set_priority(temp_priority);
}

// Find last node
template<class T, class U>
std::shared_ptr<TreeNode<T,U>> PriorityQueue<T,U>::find_last_node() const {

    // Letztes Element mithilfe von Breitensuche finden
    std::queue<std::shared_ptr<TreeNode<T,U>>> q;
    q.push(root_);

    while (!q.empty()) {
        std::shared_ptr<TreeNode<T,U>> temp_node;
        temp_node = q.front();
        q.pop();

        if (temp_node->get_left_child() != nullptr)
            q.push(temp_node->get_left_child());
        if (temp_node->get_right_child() != nullptr)
            q.push(temp_node->get_right_child());

        if (q.empty())
            return temp_node;
    }

    return nullptr; // Sollte diese Stelle nicht erreichen
}

// Print
// Hilfsfunktion zum Visualisieren der Queue
template<class T, class U>
void PriorityQueue<T,U>::print() const {

    // Mit Breitensuche Queue ausgeben
    if (root_ == nullptr) return;

    std::queue<std::shared_ptr<TreeNode<T,U>>> q;
    q.push(root_);

    while (!q.empty()) {
        std::shared_ptr<TreeNode<T,U>> temp_node;
        temp_node = q.front();
        q.pop();
        std::cout << temp_node->get_priority() << " -> ";
        
        if (temp_node->get_left_child() != nullptr)
            q.push(temp_node->get_left_child());
        if (temp_node->get_right_child() != nullptr)
            q.push(temp_node->get_right_child());
    }
}

}

