#pragma once

#include <functional>
#include <memory>
#include <cstddef>
#include <iterator>
#include <string>
#include <HashsetList.hpp>
#include <Interfaces.hpp>
#include <vector>

namespace ProjektAlpha {

  /**
  @author Julian Wessling
  @brief
  */
  template<class T>
  class Hashset: public Abstract_HashSet<T, typename std::shared_ptr<HashsetNode<T>>>{
  public:
    // Konstruktor
    Hashset(std::function<size_t(const T&)>);
    

    //Standard getter und setter
    virtual integer get_size() const override;
    virtual std::shared_ptr<HashsetNode<T>> get_first() const override;
    virtual std::shared_ptr<HashsetNode<T>> get_last() const override;
    
    

    // Element einfügen und entfernen
    virtual void insert(const T x) override;
    virtual void remove(const T& x)override;

    // Gibt genau dann true zurück,
    // wenn das Element in der Hashset enthalten ist
    virtual bool exists(const T& x) const override;

    // Druckt alle Elemente der Hashset
    virtual void print() const;
    virtual void adapt(int new_num_buckets);

    


    /*
    /*
    /*
    /*IMPLEMENTIERUNG DES ITERATORS*/
    class Iterator : public std::iterator<
        std::forward_iterator_tag,
        HashsetNode<T>,
        std::ptrdiff_t,
        std::shared_ptr<HashsetNode<T>>,
        HashsetNode<T>&
        >
        {
        private:
            std::shared_ptr<HashsetNode<T>> ptr_;
            std::vector<HashsetList<T>> buckets_;
            size_t bucket_index_;
        public:
            Iterator(std::vector<HashsetList<T>>& b, std::shared_ptr<HashsetNode<T>> p, size_t index) : buckets_(b), ptr_(p), bucket_index_(index) {}

            Iterator& operator++()
            {
                if (ptr_ != nullptr) {
                    ptr_ = ptr_->get_next();
                }
                if (ptr_ == nullptr) {

                    // Bucket um mindestens 1 erhöhen
                    bucket_index_++;

                    // Wir müssen zum nächsten nicht leeren Bucket springen
                    while (bucket_index_ < buckets_.size() && buckets_[bucket_index_].is_empty()) {
                        bucket_index_++;
                    }

                    // ptr neu setzen oder nullptr, falls es keine Elemente mehr gibt
                    if (bucket_index_ < buckets_.size())
                        ptr_ = buckets_[bucket_index_].get_first(); // Erstes Element im nächsten Bucket
                    else 
                        ptr_ = nullptr;
                }
                return *this;
            }

            Iterator operator++(int) {Iterator retval = *this; ++(*this); return retval;}
            bool operator==(Iterator other) const {return ptr_ == other.ptr_;}
            bool operator!=(Iterator other) const {return !(*this == other);}
            HashsetNode<T>& operator*() const {return *ptr_;}
        };

        Iterator begin() {     

            // Erstes, nicht leeres Bucket finden     
            size_t i = 0;
            while (i < buckets.size() && buckets[i].is_empty()) {
                ++i;
            }

            // Erstes Element des Buckets finden und in Iterator reingeben
            if (i < buckets.size()) {
                return Iterator(buckets, buckets[i].get_first(), i);
            }
            
            // Wenn Buckets alle leer sind
            return end();
        }
        
        Iterator end() { 
            return Iterator(buckets, nullptr, buckets.size());
        }


    /*   IMPLEMENTIERUNG DES ITERATORS
    *
    *
    *
    */

  private:
  /** Für ein Hashset wird genau eine Hashfunktion verwendet*/
    const std::function<size_t(const T&)> hashfkt;
 
    size_t num_buckets;
    double belegungsfaktor;

    std::vector<HashsetList<T>> buckets;

    virtual size_t get_num_buckets() const;
    virtual double get_belegungsfaktor();

  };


    template<class T>
    Hashset<T>::Hashset(std::function<size_t(const T&)> hashable) :
        hashfkt(hashable),
        num_buckets(32)
    {
        buckets.resize(32);
    }


    /**
    @brief Gibt die Anzahl an ELementen zurück
    */
    template<class T>
    integer Hashset<T>::get_size() const
    {
        size_t counter = 0;
        for(int i = 0; i < num_buckets; i++)
        {
            ProjektAlpha::HashsetList<T> l = buckets[i];
            std::shared_ptr<HashsetNode<T>> current = l.get_first();
            while(current)
            {
                current = current->get_next();
                counter ++;
            }
        }
        return counter;
    }

    /** @brief Hilfsfunktion, um Hashtable dynamisch zu machen */
    template<class T>
    double Hashset<T>::get_belegungsfaktor()
    {
        belegungsfaktor = ((double)get_size()/buckets.size());
        return belegungsfaktor;
    }

    /** @brief Zugriff auf das erste Element*/
    template<class T>
    std::shared_ptr<HashsetNode<T>> Hashset<T>::get_first() const
    {
        return buckets[0].get_first();
    }

    /** @brief Zugriff auf das letzte Element*/
     template<class T>
     std::shared_ptr<HashsetNode<T>> Hashset<T>::get_last() const
     {
        int size = buckets.size();
        return buckets[size-1].get_last();
     }

    /** @brief Anzahl der Listen, die als Buckets beschrieben werden wird zurückgegeben*/
    template<class T>
    size_t Hashset<T>::get_num_buckets() const
    {
        return num_buckets;
    }

    /** @brief Elemente aller Datentypen können in die Hashtable mit insert eingefügt werden*/
    template<class T>
    void Hashset<T>::insert(const T x)
    {

        //Überprüft, ob der Belegungsfaktor nach oben oder unten in einem kritischen Bereich ist
        if(get_belegungsfaktor() > 0.75)
        {
            adapt(num_buckets * 2);
        }else if(get_belegungsfaktor() < 0.25)
        {
            adapt(num_buckets / 2);
        }

        //Berechnet den Index für Buckets
        int i = hashfkt(x) % num_buckets;
        size_t a = hashfkt(x);

        //Überprüft, ob schon das erste Element frei sit
        if(buckets[i].get_first() == 0)
        {
            ProjektAlpha::HashsetList<T> l = buckets[i];
            l.insert_front(hashfkt(x), x);
            buckets[i] = l;
        }
        //Wenn es nicht frei ist wird hinten eingefügt
        else
        {
            buckets[i].insert_after(buckets[i].get_last(), hashfkt(x), x);
        }
    }

     /** @brief Überprüft, ob ein Element vorhanden ist */
    template<class T>
    bool Hashset<T>::exists(const T& x) const
    {

        /** Berechnet den Index für Buckets*/
        int i = hashfkt(x) % num_buckets;
        ProjektAlpha::HashsetList<T> l  = buckets[i];
        std::shared_ptr<HashsetNode<T>> current = l.get_first();

        /**Überprüft, ob schon das erste Element frei ist*/
        if(current != nullptr)
        {

            /**Ist current gleich dem Eingabestring?*/
            while(current->get_key() != x)
            {
                if(current->get_next() != nullptr)
                    current = current->get_next();
                else
                    return false;
            }
            return true;//Gibt false zurück, wenn das Eoement nicht vorhanden ist
        }else
        {
            return false;
        }

    }

    /** @brief Elemente aus dem Hashset entfernen*/
    template<class T>
    void Hashset<T>::remove(const T& x)
    {
        if(get_belegungsfaktor() > 0.75)
        {
            adapt(num_buckets * 2);
        }else if(get_belegungsfaktor() < 0.25)
        {
            adapt(num_buckets / 2);
        }

        //Berechnet den Index für buckets
        int i = hashfkt(x) % num_buckets;

        //Ist das Element schon vorhanden?
        if(Hashset<T>::exists(x) == true)
        {
            ProjektAlpha::HashsetList<T> l = buckets[i];

            //Ist schon der erste Wert der Wert der Hashfunktion?
            if((l.get_first())->get_hash() == hashfkt(x))
            {
                l.remove_front();
                buckets[i] = l;
            }
            else
            {
                //Knoten, nach dem entfernt werden soll
                std::shared_ptr<HashsetNode<T>> prev;
                ProjektAlpha::HashsetList<T> l = buckets[i];
                std::shared_ptr<HashsetNode<T>> current = l.get_first();

                while(current->get_key() != x)
                {
                    if(current->get_next()->get_key() == x)
                    {
                        prev = current;
                    }
                    current = current->get_next();
                }
                l.remove_after(prev);//Element wird entfernt
            }
        }
    }

    /** @brief Berücksichtigt den Belegungsfaktor und passt die größe der Buckets entsprechend an*/
    template<class T>
    void Hashset<T>::adapt(int new_num_buckets)
    {
        std::vector<HashsetList<T>> new_buckets;

        ProjektAlpha::HashsetList<T> l;
        new_buckets.resize(new_num_buckets);
        for(int i = 0; i < new_buckets.size(); i++)
        {//Listen werden in new_buckets an jeder Stelle eingefügt
            new_buckets[i] = l;
        }

        //Wird genutzt um den jeweils richtigen Index in buckets zu nutzen
        for(size_t i = 0; i < num_buckets; i++)
        {
            std::shared_ptr<HashsetNode<T>> current = buckets[i].get_first();

            //fügt Die Liste nach und nach korrekt in das neue Array ein
            while(current)
            {
                size_t new_bucket_index = hashfkt(current->get_key()) % new_num_buckets;
                new_buckets[new_bucket_index].insert_front(current->get_hash(), current->get_key());
                current = current->get_next();
            }
        }

        //Buckets wird auf new_buckets gesetzt
        buckets.clear();
        buckets = new_buckets;
        num_buckets = new_num_buckets;
    }


    /** @brief Druckt die Hashset<T> aus*/
    template<class T>
    void Hashset<T>::print() const
    {

        //Durchläuft alle Buckets
        for(int i = 0; i < num_buckets; i++)
        {

            //Kopie von Buckets
            ProjektAlpha::HashsetList<T> l = buckets[i];
            std::shared_ptr<HashsetNode<T>> current = l.get_first();
            std::cout<<"Bucket ["<<i<<"]";
            //Läuft solange current nicht null ist
            while(current)
            {
                std::cout<<"(Hash, Key): ("<<current->get_hash()<<", "<<current->get_key()<<")"<<"-> ";//Druckt den Wert auf den Current zeigt
                current = current->get_next();
            }
        std::cout<<"null"<<std::endl;
        }
         std::cout<<"A total of "<<num_buckets<<" buckets have been created and "<<get_size()<<" elements have been filled in"<<std::endl;

    }

 


};

