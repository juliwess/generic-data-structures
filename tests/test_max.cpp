#include <gtest/gtest.h>
#include <DoublyLinkedList.hpp>


ProjektAlpha::DoublyLinkedList<std::string> l;

TEST(DoublyLinkedListTest, insert_front)
{
  ASSERT_NO_THROW(l.insert_front("Hallo"))<<"Fehler beim Einsetzen des 1. Strings";
  ASSERT_NO_THROW(l.insert_front("Ho"))<<"Fehler beim Einsetzen des 2. Strings";
  ASSERT_NO_THROW(l.insert_front("Max"))<<"Fehler beim Einsetzen des 3. Strings";
  ASSERT_NO_THROW(l.insert_front("Julian"))<<"Fehler beim Einsetzen des 4. Strings";
  ASSERT_NO_THROW(l.insert_front("Florian"))<<"Fehler beim Einsetzen des 5. Strings";
  ASSERT_NO_THROW(l.insert_front("ProjektAlpha"))<<"Fehler beim Einsetzen des 6. Strings";
  ASSERT_EQ(6,l.get_size())<<"Größe der Liste stimmt nicht mit Anzahl der eingesetzten Elemente überein";
}

TEST(DoublyLinkedListTest, remove_front)
{
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Entfernen des 1. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Entfernen des 2. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Entfernen des 3. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Entfernen des 4. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Entfernen des 5. Strings";
  ASSERT_NO_THROW(l.remove_front())<<"Fehler beim Entfernen des 6. Strings";
  ASSERT_EQ(0, l.get_size())<<"Größe der Table stimmt nicht mit Anzahl der entfernten Elemente überein";
}