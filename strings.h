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

// LastIndex returns the index of the last instance of substr in s, or -1 if substr is not present in s.
int LastIndex(const std::string &s, const std::string &substr) {
  size_t pos = s.rfind(substr);
  return (pos == std::string::npos) ? -1 : static_cast<int>(pos);
}

// Index returns the index of the first instance of substr in s, or -1 if substr is not present in s.
int Index(const std::string &s, const std::string &substr) {
  size_t pos = s.find(substr);
  return (pos == std::string::npos) ? -1 : static_cast<int>(pos);
}

// IndexAny returns the index of the first instance of any char
// from chars in s, or -1 if no char from chars is present in s.
int IndexAny(const std::string &s, const std::string &chars) {
  std::set<char> char_set(chars.begin(), chars.end());
  for (size_t i = 0; i < s.size(); ++i)
    if (char_set.find(s[i]) != char_set.end()) return static_cast<int>(i);

  return -1;
}

// LastIndexAny returns the index of the last instance of any char
// from chars in s, or -1 if no char from chars is present in s.
int LastIndexAny(const std::string &s, const std::string &chars) {
  std::set<char> char_set(chars.begin(), chars.end());
  for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
    if (char_set.find(s[i]) != char_set.end()) return i;

  return -1;
}

// LastIndexByte returns the index of the last instance of c in s, or -1 if c is not present in s.
int LastIndexByte(const std::string &s, char c) {
  for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
    if (s[i] == c) return i;

  return -1;
}

} // namespace strings