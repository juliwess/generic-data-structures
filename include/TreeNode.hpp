// Implementation von PriorityQueueNode

#pragma once

#include <memory>

namespace ProjektAlpha {

/**
 * Implementierung einer Node einer Priority Queue
 * @tparam T Klasse für Wert und U für Priorität
 * @author Max Vtulkin
*/
template<class T, class U>
class TreeNode : public std::enable_shared_from_this<TreeNode<T,U>> {

    public: 

        // Konstruktor
        TreeNode(const T& value, const U& priority);

        // Shared this pointer zurückgeben
        std::shared_ptr<TreeNode<T,U>> get_ptr() {
            return this->shared_from_this();
        }
        
        // Priority get
        virtual U get_priority() const;
        virtual void set_priority(const U& priority);

        // data get/set
        virtual T get_value() const;
        virtual void set_value(const T& value);
    
        // left/right child get/set
        virtual std::shared_ptr<TreeNode<T,U>> get_left_child() const;
        virtual std::shared_ptr<TreeNode<T,U>> get_right_child() const;
        virtual void set_right_child(const T& value, const U& priority);
        virtual void set_right_child(std::shared_ptr<TreeNode<T,U>> right);
        virtual void set_left_child(const T& value, const U& priority);
        virtual void set_left_child(std::shared_ptr<TreeNode<T,U>> left);
        
        // Parent get
        virtual std::shared_ptr<TreeNode<T,U>> get_parent() const;

    private:

        T value_;
        U priority_;
        
        std::shared_ptr<TreeNode<T,U>> left_;
        std::shared_ptr<TreeNode<T,U>> right_; 

        std::weak_ptr<TreeNode<T,U>> parent_;
};


// Konstrukor
template<class T, class U>
TreeNode<T,U>::TreeNode(const T& value, const U& priority) {
    value_ = value;
    priority_ = priority;  
}

// Get priority
template<class T, class U>
U TreeNode<T,U>::get_priority() const {
    return priority_;
}

// Set priority
template<class T, class U>
void TreeNode<T,U>::set_priority(const U& priority) {
    priority_ = priority;
}

// Get value
template<class T, class U>
T TreeNode<T,U>::get_value() const {
    return value_;
}

// Set value
template<class T, class U>
void TreeNode<T,U>::set_value(const T& value) {
    value_ = value;
}

// Get left child
template<class T, class U>
std::shared_ptr<TreeNode<T,U>> TreeNode<T,U>::get_left_child() const {
    return left_;
} 

// Get right child
template<class T, class U>
std::shared_ptr<TreeNode<T,U>> TreeNode<T,U>::get_right_child() const {
    return right_;
} 

// Set data of left child / create new one if null
template<class T, class U>
void TreeNode<T,U>::set_left_child(const T& value, const U& priority) {
    if (left_ == nullptr) {
        left_ = std::make_shared<TreeNode<T,U>>(value, priority);
        left_->parent_ = this->get_ptr();
    }
    else {
        left_->priority_ = priority;
        left_->value_ = value;
    }
}

// Überladung: Setzt das linke Kind gleich eines Nodes
template<class T, class U>
void TreeNode<T,U>::set_left_child(std::shared_ptr<TreeNode<T,U>> left) {
    left_ = left;
}

// Set data of right child / create new one if null
template<class T, class U>
void TreeNode<T,U>::set_right_child(const T& value, const U& priority) {
    if (right_ == nullptr) {
        right_ = std::make_shared<TreeNode<T,U>>(value, priority);
        right_->parent_ = this->get_ptr();
    }
    else {
        right_->priority_ = priority;
        right_->value_ = value;
    }
}

// Überladung: Setzt das rechte Kind gleich eines Nodes
template<class T, class U>
void TreeNode<T,U>::set_right_child(std::shared_ptr<TreeNode<T,U>> right) {
    right_ = right;
}

// Get Parent
template<class T, class U>
std::shared_ptr<TreeNode<T,U>> TreeNode<T,U>::get_parent() const {
    return parent_.lock();
}

}