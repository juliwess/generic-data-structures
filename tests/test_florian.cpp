#include <gtest/gtest.h>

#include <string>

#include <Stack.hpp>
#include <Queue.hpp>



/** Teste den Stack */
class StackTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    //stack_string = ProjektAlpha::Stack<std::string>();
    //stack_int = ProjektAlpha::Stack<int>();
  }
  virtual void TearDown() {
  }
  static ProjektAlpha::Stack<std::string> stack_string;
  static ProjektAlpha::Stack<int> stack_int;
};

  ProjektAlpha::Stack<std::string> StackTest::stack_string;
  ProjektAlpha::Stack<int> StackTest::stack_int;


template<class T>
testing::AssertionResult stack_pop(ProjektAlpha::Stack<T>& stack) {
T t;
try {
  t = stack.pop();
  return testing::AssertionSuccess() << t << " wurde gepoppt";
}
catch (std::exception& e) {
  return testing::AssertionFailure() << t << " konnte nicht gepoppt werden wegen '" << e.what() << "'";
}
}


TEST_F(StackTest, Constructor) {
  ASSERT_NO_THROW(stack_string = ProjektAlpha::Stack<std::string>()) << "Konstruktor (String) nicht aufrufbar";
  ASSERT_NO_THROW(stack_int = ProjektAlpha::Stack<int>()) << "Konstruktor (Int) nicht aufrufbar";
}

TEST_F(StackTest, Enqueue) {
  EXPECT_EQ(stack_string.get_size(), 0) << "Stack-Größe (String) ist nicht 0";

  ASSERT_NO_THROW(stack_string.push("mogus"))  << "Erster Push bei leerem Stack (String) failed";
  ASSERT_NO_THROW(stack_string.push("Die Milbe namens Paul")) << "Zweiter Push failed (String)";
  ASSERT_NO_THROW(stack_string.push("Gruezi"));
  ASSERT_NO_THROW(stack_string.push("James"));
  ASSERT_NO_THROW(stack_string.push("Thomas"));
  ASSERT_NO_THROW(stack_string.push("Carl der Carlige"));

  EXPECT_EQ(stack_string.get_size(), 6) << "Stack-Größe (String) ist nicht 6";
  
  ASSERT_NO_THROW(stack_int.push(0))  << "Erster Push bei leerem Stack (Int) failed";
  ASSERT_NO_THROW(stack_int.push(4))  << "Zweiter Push failed (Int)";
  ASSERT_NO_THROW(stack_int.push(8));
  ASSERT_NO_THROW(stack_int.push(3));
  ASSERT_NO_THROW(stack_int.push(121));
  ASSERT_NO_THROW(stack_int.push(-4))  << "Push mit -1 (Int) failed";
}

TEST_F(StackTest, Pop) {
  ASSERT_TRUE(stack_pop(stack_string)) << "Erster Pop (String) failed";
  ASSERT_TRUE(stack_pop(stack_string)) << "Zweiter Pop (String) failed";
  ASSERT_TRUE(stack_pop(stack_string));
  ASSERT_TRUE(stack_pop(stack_string));
  EXPECT_EQ(stack_string.get_size(), 2) << "Stack-Größe (String) ist nicht 2";
  ASSERT_TRUE(stack_pop(stack_string));
  ASSERT_TRUE(stack_pop(stack_string));
  
  ASSERT_FALSE(stack_pop(stack_string)) << "Stack (String) ist noch nicht leer";

  ASSERT_TRUE(stack_pop(stack_int)) << "Erster Pop (Int) failed";
  ASSERT_TRUE(stack_pop(stack_int)) << "Zweiter Pop (Int) failed";
  ASSERT_TRUE(stack_pop(stack_int));
  ASSERT_TRUE(stack_pop(stack_int));
  ASSERT_TRUE(stack_pop(stack_int));
  ASSERT_TRUE(stack_pop(stack_int));
  
  ASSERT_FALSE(stack_pop(stack_int)) << "Stack (Int) ist noch nicht leer";
} 




/** Teste die Queue */
class QueueTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
  static ProjektAlpha::Queue<std::string> queue_string;
  static ProjektAlpha::Queue<int> queue_int;
};

  ProjektAlpha::Queue<std::string> QueueTest::queue_string;
  ProjektAlpha::Queue<int> QueueTest::queue_int;


template<class T>
testing::AssertionResult queue_dequeue(ProjektAlpha::Queue<T>& queue) {
T t;
try {
  t = queue.dequeue();
  return testing::AssertionSuccess() << "'" << t << "' wurde gedequeuet";
}
catch (std::exception& e) {
  return testing::AssertionFailure() << "'" << t << "' konnte nicht gedequeuet werden wegen '" << e.what() << "'";
}
}


TEST_F(QueueTest, Constructor) {
  ASSERT_NO_THROW(queue_string = ProjektAlpha::Queue<std::string>()) << "Konstruktor (String) nicht aufrufbar";
  ASSERT_NO_THROW(queue_int = ProjektAlpha::Queue<int>()) << "Konstruktor (Int) nicht aufrufbar";
}

TEST_F(QueueTest, Enqueue) {
  EXPECT_EQ(queue_string.get_size(), 0) << "Queue-Größe (String) ist nicht 0";

  ASSERT_NO_THROW(queue_string.enqueue("mogus"))  << "Erstes Enqueue bei leerer Queue (String) failed";
  ASSERT_NO_THROW(queue_string.enqueue("Die Milbe namens Paul")) << "Zweites Enqueue failed (String)";
  ASSERT_NO_THROW(queue_string.enqueue("Gruezi"));
  ASSERT_NO_THROW(queue_string.enqueue("James"));
  ASSERT_NO_THROW(queue_string.enqueue("Thomas"));
  ASSERT_NO_THROW(queue_string.enqueue("Carl der Carlige"));

  EXPECT_EQ(queue_string.get_size(), 6) << "Queue-Größe (String) ist nicht 6";
  
  ASSERT_NO_THROW(queue_int.enqueue(0))  << "Erstes Enqueue bei leerem Queue (Int) failed";
  ASSERT_NO_THROW(queue_int.enqueue(4))  << "Zweites Enqueue failed (Int)";
  ASSERT_NO_THROW(queue_int.enqueue(8));
  ASSERT_NO_THROW(queue_int.enqueue(3));
  ASSERT_NO_THROW(queue_int.enqueue(121));
  ASSERT_NO_THROW(queue_int.enqueue(-4))  << "Enqueue mit -1 (Int) failed";
}

TEST_F(QueueTest, Pop) {
  ASSERT_TRUE(queue_dequeue(queue_string)) << "Erstes Dequeue (String) failed";
  ASSERT_TRUE(queue_dequeue(queue_string)) << "Zweites Dequeue (String) failed";
  ASSERT_TRUE(queue_dequeue(queue_string));
  ASSERT_TRUE(queue_dequeue(queue_string));
  EXPECT_EQ(queue_string.get_size(), 2) << "Queue-Größe (String) ist nicht 2";
  ASSERT_TRUE(queue_dequeue(queue_string));
  ASSERT_TRUE(queue_dequeue(queue_string));
  
  ASSERT_FALSE(queue_dequeue(queue_string)) << "Queue (String) ist noch nicht leer";

  ASSERT_TRUE(queue_dequeue(queue_int)) << "Erstes Dequeue (Int) failed";
  ASSERT_TRUE(queue_dequeue(queue_int)) << "Zweites Dequeue (Int) failed";
  ASSERT_TRUE(queue_dequeue(queue_int));
  ASSERT_TRUE(queue_dequeue(queue_int));
  ASSERT_TRUE(queue_dequeue(queue_int));
  ASSERT_TRUE(queue_dequeue(queue_int));
  
  ASSERT_FALSE(queue_dequeue(queue_int)) << "Queue (Int) ist noch nicht leer";
} 