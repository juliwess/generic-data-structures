#include <gtest/gtest.h>
#include <Hashset.hpp>
#include <SinglyLinkedList.hpp>


std::function<size_t(const std::string&)> func = std::hash<std::string>();

ProjektAlpha::Hashset<std::string> h(func);

TEST(HashsetTest, insert)
{
  ASSERT_NO_THROW(h.insert("Hallo"))<<"Fehler beim Einsetzen des 1. Strings";
  ASSERT_NO_THROW(h.insert("Ho"))<<"Fehler beim Einsetzen des 2. Strings";
  ASSERT_NO_THROW(h.insert("Max"))<<"Fehler beim Einsetzen des 3. Strings";
  ASSERT_NO_THROW(h.insert("Julian"))<<"Fehler beim Einsetzen des 4. Strings";
  ASSERT_NO_THROW(h.insert("Florian"))<<"Fehler beim Einsetzen des 5. Strings";
  ASSERT_NO_THROW(h.insert("ProjektAlpha"))<<"Fehler beim Einsetzen des 6. Strings";
  ASSERT_EQ(6,h.get_size())<<"Größe der Table stimmt nicht mit Anzahl der eingesetzten Elemente überein";
}

TEST(HashsetTest, exists)
{
  ASSERT_EQ(h.exists("Julian"), 1);
  ASSERT_EQ(h.exists("FLorian"),0);
}

TEST(HashsetTest, remove)
{
  ASSERT_NO_THROW(h.remove("Hallo"))<<"Fehler beim Einsetzen des 1. Strings";
  ASSERT_NO_THROW(h.remove("Ho"))<<"Fehler beim Einsetzen des 2. Strings";
  ASSERT_NO_THROW(h.remove("Max"))<<"Fehler beim Einsetzen des 3. Strings";
  ASSERT_NO_THROW(h.remove("Julian"))<<"Fehler beim Einsetzen des 4. Strings";
  ASSERT_NO_THROW(h.remove("Florian"))<<"Fehler beim Einsetzen des 5. Strings";
  ASSERT_NO_THROW(h.remove("ProjektAlpha"))<<"Fehler beim Einsetzen des 6. Strings";
  ASSERT_EQ(0, h.get_size())<<"Größe der Table stimmt nicht mit Anzahl der entfernten Elemente überein";
}


ProjektAlpha::SinglyLinkedList<std::string> l;


TEST(SinglyLinkedListTest, insert)
{
  ASSERT_NO_THROW(l.insert_front("Hallo"))<<"Fehler beim Einsetzen des 1. Strings";
  ASSERT_NO_THROW(l.insert_front("Ho"))<<"Fehler beim Einsetzen des 2. Strings";
  ASSERT_NO_THROW(l.insert_front("Max"))<<"Fehler beim Einsetzen des 3. Strings";
  ASSERT_NO_THROW(l.insert_front("Julian"))<<"Fehler beim Einsetzen des 4. Strings";
  ASSERT_NO_THROW(l.insert_front("Florian"))<<"Fehler beim Einsetzen des 5. Strings";
  ASSERT_NO_THROW(l.insert_front("ProjektAlpha"))<<"Fehler beim Einsetzen des 6. Strings";
  ASSERT_EQ(6,l.get_size())<<"Größe der Table stimmt nicht mit Anzahl der eingesetzten Elemente überein";
}

TEST(SinglyLinkedListTest, remove)
{
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Einsetzen des 1. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Einsetzen des 2. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Einsetzen des 3. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Einsetzen des 4. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Einsetzen des 5. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Einsetzen des 6. Strings";
  ASSERT_EQ(0,l.get_size())<<"Größe der Table stimmt nicht mit Anzahl der eingesetzten Elemente überein";
}

