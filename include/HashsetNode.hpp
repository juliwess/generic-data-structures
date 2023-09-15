#pragma once

#include <memory>
#include <string>


namespace ProjektAlpha
{


  template<class T>
  class HashsetNode
  {
  public:
    HashsetNode();
    HashsetNode(long hash);

    void set_next(std::shared_ptr<HashsetNode<T>> next);
    std::shared_ptr<HashsetNode<T>> get_next();

    //Der Hashwert wird normalerweise in hash gespeichert, deswegen kann es hier Sinn machen long als Datentyp zu wählen
    void set_hash(long hash);
    long get_hash() const;

    void set_key(T key);
    T get_key() const;
  private:
    std::shared_ptr<HashsetNode<T>> next;
    long hash;
    T key;
  };


    template<class T>
    HashsetNode<T>::HashsetNode()//Daten werden hash_ zugewiesen(ein integer Wert)
    {
		next = nullptr;
    }

    template<class T>
    HashsetNode<T>::HashsetNode(long hash)//Daten werden hash_ zugewiesen(ein integer Wert)
    {
        this->hash = hash;
		next = nullptr;
    }



    /*
     *
     * GETTER UND SETTER
     *
     */
    template<class T>
    void HashsetNode<T>::set_next(std::shared_ptr<HashsetNode<T>> next){
      this->next = next;
    }

    template<class T>
    std::shared_ptr<HashsetNode<T>> HashsetNode<T>::get_next(){
      return next;
    }

    template<class T>
    void HashsetNode<T>::set_hash(long hash){
      this->hash = hash;
    }

    template<class T>
    long HashsetNode<T>::get_hash() const{
      return hash;
    }

    template<class T>
    void HashsetNode<T>::set_key(T key)
    {
      this->key = key;
    }

    template<class T>
    T HashsetNode<T>::get_key() const
    {
      return key;
    }



}

