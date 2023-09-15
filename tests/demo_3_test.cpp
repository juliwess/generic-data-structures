#include <gtest/gtest.h>
#include <iostream>
#include <memory>

class DestructionTester {
public:
  DestructionTester()  { std::cerr << "DestructionTester init" << std::endl; }
  ~DestructionTester() { std::cerr << "DestructionTester fini" << std::endl; }
};

TEST(MeineTestSuite, Speicher) {
  std::shared_ptr<DestructionTester> x = std::make_shared<DestructionTester>();
  ASSERT_EQ(1, 2);
  // Beim Ausführen des Tests wird der Smartpointer aufgeräumt, falls der Text
  // "DestructionTester fini" auf der Standardausgabe zu sehen ist.
}

