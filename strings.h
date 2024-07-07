#pragma once

#include <set>
#include <string>

namespace strings {

// Count counts the number of non-overlapping instances of substr in s.
// If substr is an empty string, Count returns 0.
int Count(const std::string &s, const std::string &substr) {
  if (substr.empty()) return 0;

  int count = 0;
  auto pos = s.find(substr);
  while (pos != std::string::npos) {
    ++count;
    pos = s.find(substr, pos + substr.size());
  }

  return count;
}

bool Contains(const std::string &s, const std::string &substr) { return s.find(substr) != std::string::npos; }

// ContainsAny returns true if any of the characters in chars are in s.
bool ContainsAny(const std::string &s, const std::string &chars) {
  std::set<char> char_set(chars.begin(), chars.end());
  for (char c : s)
    if (char_set.find(c) != char_set.end()) return true;

  return false;
}

// Index returns the index of the first instance of substr in s, or -1 if substr is not present in s.
int Index(const std::string &s, const std::string &substr) {
  size_t pos = s.find(substr);
  return (pos == std::string::npos) ? -1 : static_cast<int>(pos);
}

} // namespace strings