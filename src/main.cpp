//
// Checks if sequence of braces is logically correct (and each brace has a pair)
//

#if defined(WIN32)
#include <tchar.h>
#endif

#include <cstdlib>
#include <exception>
#include <string>
#include <iostream>
#include <vector>

namespace {

bool is_open_brace(char c)
{
  return '(' == c
      || '[' == c
      || '{' == c;
} // is_open_brace

bool is_pair_braces(char open_brace, char close_brace)
{
  return ('(' == open_brace && ')' == close_brace)
      || ('[' == open_brace && ']' == close_brace)
      || ('{' == open_brace && '}' == close_brace);
} // is_pair_braces

bool is_valid_sequence_of_braces(const std::string& sequence_of_braces)
{
  const auto total_braces = sequence_of_braces.length();
  // Number of braces should be even because each brace should have a pair
  if (total_braces % 2)
  {
    return false;
  }
  std::vector<char> stack;
  stack.reserve(total_braces / 2);
  auto remaining_braces = total_braces;
  for (const auto current_brace: sequence_of_braces)
  {
    --remaining_braces;
    if (is_open_brace(current_brace))
    {
      if (stack.size() >= remaining_braces)
      {
        // Too many opening braces - we won't be able to find closing braces
        // for all of them
        return false;
      }
      // Remember this opening brace and go to the next one
      stack.push_back(current_brace);
      continue;
    }
    // Assuming this is a closing brace
    if (stack.empty())
    {
      // No opening braces for this closing brace
      return false;
    }
    const auto last_open_brace = stack.back();
    if (!is_pair_braces(last_open_brace, current_brace))
    {
      // Last opening brace has different kind comparing to
      // current closing brace
      return false;
    }
    // We found a pair for the last opening brace - let's forget about it now
    stack.pop_back();
  }
  // All braces should have a pair - there shouldn't be
  // any opening (pending) brace on the stack
  return stack.empty();
} // is_valid_sequence_of_braces

} // anonymous namespace

#if defined(WIN32)
int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
#else
int main(int /*argc*/, char* /*argv*/[])
#endif
{
  try
  {
    std::cout << "is_valid_sequence_of_braces(\"{((()))]\") = "
        << is_valid_sequence_of_braces("{((()))]") << std::endl;
    std::cout << "is_valid_sequence_of_braces(\"{((()))}\") = "
        << is_valid_sequence_of_braces("{((()))}") << std::endl;
    std::cout << "is_valid_sequence_of_braces(\"{()[()]}\") = "
        << is_valid_sequence_of_braces("{()[()]}") << std::endl;
    std::cout << "is_valid_sequence_of_braces(\"{([(])}]\") = "
        << is_valid_sequence_of_braces("{([(])}]") << std::endl;
    return EXIT_SUCCESS;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
  }
  return EXIT_FAILURE;
} // main
