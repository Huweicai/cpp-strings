#pragma once

#include <set>
#include <sstream>
#include <string>
#include <vector>

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

static std::vector<std::string> genSplit(const std::string &s, const std::string &sep, size_t sepSave, int n) {
  if (n == 0) return {};
  if (sep.empty()) return {};

  std::vector<std::string> result;
  if (n > 0) result.reserve(n);

  size_t start = 0, end;
  while ((n < 0 || static_cast<int>(result.size()) < n - 1) && (end = s.find(sep, start)) != std::string::npos) {
    result.emplace_back(s.substr(start, end - start + sepSave));
    start = end + sep.length();
  }

  result.emplace_back(s.substr(start));
  return result;
}

// SplitN slices s into substrings separated by sep and returns a vector of
// the substrings between those separators.
//
// The count determines the number of substrings to return:
// n > 0: at most n substrings; the last substring will be the unsplit remainder.
// n == 0: the result is an empty vector (zero substrings)
// n < 0: all substrings
std::vector<std::string> SplitN(const std::string &s, const std::string &sep, int n) { return genSplit(s, sep, 0, n); }

// SplitAfterN slices s into substrings after each instance of sep and
// returns a slice of those substrings.
//
// The count determines the number of substrings to return:
//
//	n > 0: at most n substrings; the last substring will be the unsplit remainder.
//	n == 0: the result is nil (zero substrings)
//	n < 0: all substrings
//
// Edge cases for s and sep (for example, empty strings) are handled
// as described in the documentation for SplitAfter.
std::vector<std::string> SplitAfterN(const std::string &s, const std::string &sep, int n) {
  return genSplit(s, sep, sep.size(), n);
}

// Split slices s into all substrings separated by sep and returns a slice of
// the substrings between those separators.
//
// If s does not contain sep and sep is not empty, Split returns a
// slice of length 1 whose only element is s.
//
// If sep is empty, Split returns an empty vector.
//
// It is equivalent to SplitN with a count of -1.
//
// To split around the first instance of a separator, see Cut.
std::vector<std::string> Split(const std::string &s, const std::string &sep) { return genSplit(s, sep, 0, -1); }

// SplitAfter slices s into all substrings after each instance of sep and
// returns a slice of those substrings.
//
// If s does not contain sep and sep is not empty, SplitAfter returns
// a slice of length 1 whose only element is s.
//
// If sep is empty, Split returns an empty vector.
//
// It is equivalent to SplitAfterN with a count of -1.
std::vector<std::string> SplitAfter(const std::string &s, const std::string &sep) {
  return genSplit(s, sep, sep.size(), -1);
}

// FieldsFunc splits the string s at each run of characters satisfying f(c)
// and returns an array of slices of s. If all characters in s satisfy f(c) or the
// string is empty, an empty vector is returned.
std::vector<std::string> FieldsFunc(const std::string &s, std::function<bool(char)> f) {
  std::vector<std::string> result{};
  std::string::size_type start = std::string::npos;

  for (std::string::size_type i = 0; i < s.length(); ++i) {
    if (f(s[i])) {
      if (start != std::string::npos) {
        result.push_back(s.substr(start, i - start));
        start = std::string::npos;
      }
    } else {
      if (start == std::string::npos) start = i;
    }
  }

  // Last field might end at EOF.
  if (start != std::string::npos) result.push_back(s.substr(start, s.length() - start));

  return result;
}

// Fields splits the string s around each instance of one or more consecutive white space
// characters, returning a vector of substrings of s or an empty vector if s contains only white space.
std::vector<std::string> Fields(const std::string &s) {
  return FieldsFunc(s, [](char c) { return std::isspace(c); });
}

// Join concatenates the elements of its first argument to create a single string.
// The separator string sep is placed between elements in the resulting string.
std::string Join(const std::vector<std::string> &elems, const std::string &sep) {
  if (elems.empty()) {
    return "";
  }

  std::ostringstream oss;
  for (size_t i = 0; i < elems.size(); ++i) {
    if (i != 0) oss << sep;

    oss << elems[i];
  }

  return oss.str();
}

} // namespace strings