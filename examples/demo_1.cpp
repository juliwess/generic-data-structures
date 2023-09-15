// Compiler with
//   clang++ -std=c++17 demo1.cpp -o demo1
// or
//   g++ -std=c++17 demo1.cpp -o demo1
// or (Windows with MSVC compiler)
//   cl /std:c++17 demo1.cpp /link /out:demo1.exe


#include <iostream>
#include <string>
#include<PriorityQueue.hpp>

#if defined __clang__
  #define current_compiler current_compiler_helper("Clang++ version ", __clang_major__, __clang_minor__, __clang_patchlevel__)
  #define cppversion "C++ version " + std::to_string(__cplusplus)
#elif defined(__GNUC__)
  #define current_compiler current_compiler_helper("GCC version ", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
  #define cppversion "C++ version " + std::to_string(__cplusplus)
#elif defined _MSC_VER
  #define current_compiler current_compiler_helper("Microsoft Visual C++ version ", _MSC_FULL_VER)
  #define cppversion "C++ version " + std::to_string(_MSVC_LANG)
#endif

/**
* @brief Creates a string that describes the current compiler in use.
*
* @param name  the name of the compiler.
* @param    A  the version of the compiler.
* @return a string that describes the current compiler in use.
*/
template<typename A>
std::string current_compiler_helper(const std::string& name, const A& a) {
  return name + std::to_string(a);
}


template<typename A, typename B, typename C>
std::string current_compiler_helper(const std::string& name, const A& a, const B& b, const C& c) {
  return name + std::to_string(a) + "." + std::to_string(b) + "." + std::to_string(c);
}


int main () {
  std::cout << "Compiler:  " << current_compiler << std::endl;
  std::cout << "Language:  " << cppversion << std::endl;
}
