#include <iostream>
#include <string>

#include <stack.hpp>
#include <queue.hpp>

void stack_test();
void queue_test();

int main() {
  queue_test();
  stack_test();
}

void stack_test() {
  std::cout << "-- Stack --" << std::endl;
  ProjektAlpha::Stack<int> sus;

  sus.push(60);
  sus.push(50);
  sus.push(40);
  sus.push(20);
  sus.push(20);
  sus.push(10);

  std::cout << std::to_string(sus.get_size()) << " | " << sus.pop() << std::endl;
  std::cout << std::to_string(sus.get_size()) << " | " << sus.pop() << std::endl;
  std::cout << std::to_string(sus.get_size()) << " | " << sus.pop() << std::endl;
  std::cout << std::to_string(sus.get_size()) << " | " << sus.pop() << std::endl;
  std::cout << std::to_string(sus.get_size()) << " | " << sus.pop() << std::endl;
  std::cout << std::to_string(sus.get_size()) << " | " << sus.pop() << std::endl << std::endl;
}

void queue_test() {
  std::cout << "-- Queue --" << std::endl;
  ProjektAlpha::Queue<std::string> sus;

  sus.enqueue("Zwergpinguin");
  sus.enqueue("Ziege");
  sus.enqueue("Schwertfisch");
  sus.enqueue("Toasthase");

  std::cout << std::to_string(sus.get_size()) << " | " << sus.dequeue() << std::endl;
  std::cout << std::to_string(sus.get_size()) << " | " << sus.dequeue() << std::endl;
  std::cout << std::to_string(sus.get_size()) << " | " << sus.dequeue() << std::endl;
  std::cout << std::to_string(sus.get_size()) << " | " << sus.dequeue() << std::endl << std::endl;
}
