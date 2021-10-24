#include <iostream>
#include <unordered_set>
#include <iterator>

void taskOne(std::istream& in, std::ostream& out)
{
  std::unordered_set<std::string> wordsSet {std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()};
  std::copy(wordsSet.begin(), wordsSet.end(), std::ostream_iterator<std::string>(out, "\n"));
}
