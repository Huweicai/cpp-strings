#include "strings.h"

#include "catch2/catch_amalgamated.hpp"

TEST_CASE("Count") {
  struct TestCase {
    std::string s;
    std::string sep;
    int expected;
  };

  TestCase cases[] = {
      {"", "", 0},
      {"", "notempty", 0},
      {"notempty", "", 0},
      {"smaller", "not smaller", 0},
      {"12345678987654321", "6", 2},
      {"611161116", "6", 3},
      {"notequal", "NotEqual", 0},
      {"equal", "equal", 1},
      {"abc1231231123q", "123", 3},
      {"11111", "11", 2},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.s << ", " << test_case.sep << " Want: " << test_case.expected);
    REQUIRE(strings::Count(test_case.s, test_case.sep) == test_case.expected);
  }
}

TEST_CASE("Contains", "[Contains]") {
  struct TestCase {
    std::string str;
    std::string substr;
    bool expected;
  };

  std::vector<TestCase> cases = {
      {"abc", "bc", true},
      {"abc", "bcd", false},
      {"abc", "", true},
      {"", "a", false},
      // 2-byte needle
      {"xxxxxx", "01", false},
      {"01xxxx", "01", true},
      {"xx01xx", "01", true},
      {"xxxx01", "01", true},
      // 3-byte needle
      {"xxxxxxx", "012", false},
      {"012xxxx", "012", true},
      {"xx012xx", "012", true},
      {"xxxx012", "012", true},
      // 4-byte needle
      {"xxxxxxxx", "0123", false},
      {"0123xxxx", "0123", true},
      {"xx0123xx", "0123", true},
      {"xxxx0123", "0123", true},
      // 5-7-byte needle
      {"xxxxxxxxx", "01234", false},
      {"01234xxxx", "01234", true},
      {"xx01234xx", "01234", true},
      {"xxxx01234", "01234", true},
      // 8-byte needle
      {"xxxxxxxxxxxx", "01234567", false},
      {"01234567xxxx", "01234567", true},
      {"xx01234567xx", "01234567", true},
      {"xxxx01234567", "01234567", true},
      // 9-15-byte needle
      {"xxxxxxxxxxxxx", "012345678", false},
      {"012345678xxxx", "012345678", true},
      {"xx012345678xx", "012345678", true},
      {"xxxx012345678", "012345678", true},
      // 16-byte needle
      {"xxxxxxxxxxxxxxxxxxxx", "0123456789ABCDEF", false},
      {"0123456789ABCDEFxxxx", "0123456789ABCDEF", true},
      {"xx0123456789ABCDEFxx", "0123456789ABCDEF", true},
      {"xxxx0123456789ABCDEF", "0123456789ABCDEF", true},
      // 17-31-byte needle
      {"xxxxxxxxxxxxxxxxxxxxx", "0123456789ABCDEFG", false},
      {"0123456789ABCDEFGxxxx", "0123456789ABCDEFG", true},
      {"xx0123456789ABCDEFGxx", "0123456789ABCDEFG", true},
      {"xxxx0123456789ABCDEFG", "0123456789ABCDEFG", true},
      // partial match cases
      {"xx01x", "012", false},
      {"xx0123x", "01234", false},
      {"xx01234567x", "012345678", false},
      {"xx0123456789ABCDEFx", "0123456789ABCDEFG", false},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.str << ", " << test_case.substr << " Want: " << test_case.expected);
    REQUIRE(strings::Contains(test_case.str, test_case.substr) == test_case.expected);
  }
}

TEST_CASE("Index") {
  struct TestCase {
    std::string str;
    std::string substr;
    int expected;
  };

  TestCase cases[] = {
      {"", "", 0},
      {"", "a", -1},
      {"", "foo", -1},
      {"fo", "foo", -1},
      {"foo", "foo", 0},
      {"oofofoofooo", "f", 2},
      {"oofofoofooo", "foo", 4},
      {"barfoobarfoo", "foo", 3},
      {"foo", "", 0},
      {"foo", "o", 1},
      {"abcABCabc", "A", 3},
      {"jrzm6jjhorimglljrea4w3rlgosts0w2gia17hno2td4qd1jz", "jz", 47},
      {"ekkuk5oft4eq0ocpacknhwouic1uua46unx12l37nioq9wbpnocqks6", "ks6", 52},
      {"999f2xmimunbuyew5vrkla9cpwhmxan8o98ec", "98ec", 33},
      {"9lpt9r98i04k8bz6c6dsrthb96bhi", "96bhi", 24},
      {"55u558eqfaod2r2gu42xxsu631xf0zobs5840vl", "5840vl", 33},
      // cases with one byte strings - test special case in Index()
      {"x", "a", -1},
      {"x", "x", 0},
      {"abc", "a", 0},
      {"abc", "b", 1},
      {"abc", "c", 2},
      {"abc", "x", -1},
      // test special cases in Index() for short strings
      {"", "ab", -1},
      {"bc", "ab", -1},
      {"ab", "ab", 0},
      {"xab", "ab", 1},
      {"", "abc", -1},
      {"xbc", "abc", -1},
      {"abc", "abc", 0},
      {"xabc", "abc", 1},
      {"xabxc", "abc", -1},
      {"", "abcd", -1},
      {"xbcd", "abcd", -1},
      {"abcd", "abcd", 0},
      {"xabcd", "abcd", 1},
      {"xbcqq", "abcqq", -1},
      {"abcqq", "abcqq", 0},
      {"xabcqq", "abcqq", 1},
      {"xabxcqq", "abcqq", -1},
      {"xabcqxq", "abcqq", -1},
      {"", "01234567", -1},
      {"32145678", "01234567", -1},
      {"01234567", "01234567", 0},
      {"x01234567", "01234567", 1},
      {"x0123456x01234567", "01234567", 9},
      {"", "0123456789", -1},
      {"3214567844", "0123456789", -1},
      {"0123456789", "0123456789", 0},
      {"x0123456789", "0123456789", 1},
      {"x012345678x0123456789", "0123456789", 11},
      {"x01234567x89", "0123456789", -1},
      {"", "0123456789012345", -1},
      {"3214567889012345", "0123456789012345", -1},
      {"0123456789012345", "0123456789012345", 0},
      {"x0123456789012345", "0123456789012345", 1},
      {"x012345678901234x0123456789012345", "0123456789012345", 17},
      {"", "01234567890123456789", -1},
      {"32145678890123456789", "01234567890123456789", -1},
      {"01234567890123456789", "01234567890123456789", 0},
      {"x01234567890123456789", "01234567890123456789", 1},
      {"x0123456789012345678x01234567890123456789", "01234567890123456789", 21},
      {"", "0123456789012345678901234567890", -1},
      {"321456788901234567890123456789012345678911", "0123456789012345678901234567890", -1},
      {"0123456789012345678901234567890", "0123456789012345678901234567890", 0},
      {"x0123456789012345678901234567890", "0123456789012345678901234567890", 1},
      {"x012345678901234567890123456789x0123456789012345678901234567890", "0123456789012345678901234567890", 32},
      {"", "01234567890123456789012345678901", -1},
      {"32145678890123456789012345678901234567890211", "01234567890123456789012345678901", -1},
      {"01234567890123456789012345678901", "01234567890123456789012345678901", 0},
      {"x01234567890123456789012345678901", "01234567890123456789012345678901", 1},
      {"x0123456789012345678901234567890x01234567890123456789012345678901", "01234567890123456789012345678901", 33},
      {"oxoxoxoxoxoxoxoxoxoxoxoy", "oy", 22},
      {"oxoxoxoxoxoxoxoxoxoxoxox", "oy", -1},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.str << ", " << test_case.substr << " Want: " << test_case.expected);
    REQUIRE(strings::Index(test_case.str, test_case.substr) == test_case.expected);
  }
}

TEST_CASE("ContainsAny") {
  struct TestCase {
    std::string str;
    std::string substr;
    bool expected;
  };

  TestCase cases[] = {
      {"", "", false},
      {"", "a", false},
      {"", "abc", false},
      {"a", "", false},
      {"a", "a", true},
      {"aaa", "a", true},
      {"abc", "xyz", false},
      {"abc", "xcz", true},
      {"a☺b☻c☹d", "uvw☻xyz", true},
      {"aRegExp*", ".(|)*+?^$[]", true},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.str << ", " << test_case.substr << " Want: " << test_case.expected);
    REQUIRE(strings::ContainsAny(test_case.str, test_case.substr) == test_case.expected);
  }
}

TEST_CASE("LastIndex") {
  struct TestCase {
    std::string str;
    std::string substr;
    int expected;
  };

  TestCase cases[] = {
      {"", "", 0},
      {"", "a", -1},
      {"", "foo", -1},
      {"fo", "foo", -1},
      {"foo", "foo", 0},
      {"foo", "f", 0},
      {"oofofoofooo", "f", 7},
      {"oofofoofooo", "foo", 7},
      {"barfoobarfoo", "foo", 9},
      {"foo", "", 3},
      {"foo", "o", 2},
      {"abcABCabc", "A", 3},
      {"abcABCabc", "a", 6},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.str << ", " << test_case.substr << " Want: " << test_case.expected);
    REQUIRE(strings::LastIndex(test_case.str, test_case.substr) == test_case.expected);
  }
}

TEST_CASE("IndexAny") {
  struct TestCase {
    std::string str;
    std::string chars;
    int expected;
  };

  TestCase cases[] = {
      {"", "", -1},       {"", "a", -1},     {"", "abc", -1},
      {"a", "", -1},      {"a", "a", 0},     {"aaa", "a", 0},
      {"abc", "xyz", -1}, {"abc", "xcz", 2}, {"aRegExp*", ".(|)*+?^$[]", 7},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.str << ", " << test_case.chars << " Want: " << test_case.expected);
    REQUIRE(strings::IndexAny(test_case.str, test_case.chars) == test_case.expected);
  }
}

TEST_CASE("LastIndexAny") {
  struct TestCase {
    std::string str;
    std::string chars;
    int expected;
  };

  TestCase cases[] = {
      {"", "", -1},       {"", "a", -1},     {"", "abc", -1},
      {"a", "", -1},      {"a", "a", 0},     {"aaa", "a", 2},
      {"abc", "xyz", -1}, {"abc", "xcz", 2}, {"aRegExp*", ".(|)*+?^$[]", 7},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.str << ", " << test_case.chars << " Want: " << test_case.expected);
    REQUIRE(strings::LastIndexAny(test_case.str, test_case.chars) == test_case.expected);
  }
}

TEST_CASE("LastIndexByte") {
  struct TestCase {
    std::string str;
    char sep;
    int expected;
  };

  TestCase cases[] = {
      {"", 'q', -1},
      {"abcdef", 'q', -1},
      {"abcdefabcdef", 'a', static_cast<int>(std::string("abcdef").size())},      // something in the middle
      {"abcdefabcdef", 'f', static_cast<int>(std::string("abcdefabcde").size())}, // last byte
      {"zabcdefabcdef", 'z', 0},                                                  // first byte
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.str << ", " << test_case.sep << " Want: " << test_case.expected);
    REQUIRE(strings::LastIndexByte(test_case.str, test_case.sep) == test_case.expected);
  }
}

TEST_CASE("SplitN") {
  struct TestCase {
    std::string s;
    std::string sep;
    int n;
    std::vector<std::string> expected;
  };

  std::vector<TestCase> cases = {
      {"", "", -1, {}},
      {"abcd", "", 0, {}},
      {"abcd", "a", 0, {}},
      {"abcd", "a", -1, {"", "bcd"}},
      {"abcd", "z", -1, {"abcd"}},
      {"1,2,3,4", ",", -1, {"1", "2", "3", "4"}},
      {"1....2....3....4", "...", -1, {"1", ".2", ".3", ".4"}},
      {"☺☻☹", "☹", -1, {"☺☻", ""}},
      {"☺☻☹", "~", -1, {"☺☻☹"}},
      {"1 2 3 4", " ", 3, {"1", "2", "3 4"}},
      {"1 2", " ", 3, {"1", "2"}},
      {"", "T", INT_MAX / 4, {""}},
      {"\xff-\xff", "-", -1, {"\xff", "\xff"}},
  };

  for (const auto &test_case : cases) {
    auto a = strings::SplitN(test_case.s, test_case.sep, test_case.n);
    INFO("Input: " << test_case.s << ", sep: " << test_case.sep << ", n: " << test_case.n);
    REQUIRE(a == test_case.expected);

    if (test_case.n == 0) {
      continue;
    }

    auto s = strings::Join(a, test_case.sep);
    REQUIRE(s == test_case.s);

    if (test_case.n < 0) {
      auto b = strings::SplitN(test_case.s, test_case.sep, -1);
      REQUIRE(a == b);
    }
  }
}

TEST_CASE("SplitAfterN") {
  struct TestCase {
    std::string s;
    std::string sep;
    int n;
    std::vector<std::string> expected;
  };

  std::vector<TestCase> cases = {
      {"abcd", "a", -1, {"a", "bcd"}},
      {"abcd", "z", -1, {"abcd"}},
      {"1,2,3,4", ",", -1, {"1,", "2,", "3,", "4"}},
      {"1....2....3....4", "...", -1, {"1...", ".2...", ".3...", ".4"}},
      {"1 2 3 4", " ", 3, {"1 ", "2 ", "3 4"}},
      {"1 2 3", " ", 3, {"1 ", "2 ", "3"}},
      {"1 2", " ", 3, {"1 ", "2"}},
  };

  for (const auto &test_case : cases) {
    auto a = strings::SplitAfterN(test_case.s, test_case.sep, test_case.n);
    INFO("Input: " << test_case.s << ", sep: " << test_case.sep << ", n: " << test_case.n);
    REQUIRE(a == test_case.expected);

    auto s = strings::Join(a, "");
    REQUIRE(s == test_case.s);

    if (test_case.n < 0) {
      auto b = strings::SplitAfterN(test_case.s, test_case.sep, -1);
      REQUIRE(a == b);
    }
  }
}

TEST_CASE("Fields") {
  struct FieldsTest {
    std::string s;
    std::vector<std::string> want;
  };

  FieldsTest cases[] = {
      {"", {}},
      {" ", {}},
      {" \t ", {}},
      {"  abc  ", {"abc"}},
      {"1 2 3 4", {"1", "2", "3", "4"}},
      {"1  2  3  4", {"1", "2", "3", "4"}},
      {"1\t\t2\t\t3\t4", {"1", "2", "3", "4"}},
      {"\n™\t™\n", {"™", "™"}},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.s);
    REQUIRE(strings::Fields(test_case.s) == test_case.want);
  }
}

TEST_CASE("FieldsFunc") {
  struct FieldsTest {
    std::string s;
    std::vector<std::string> a;
  };

  FieldsTest cases[] = {
      {"", {}},
      {" ", {}},
      {" \t ", {}},
      {"  abc  ", {"abc"}},
      {"1 2 3 4", {"1", "2", "3", "4"}},
      {"1  2  3  4", {"1", "2", "3", "4"}},
      {"1\t\t2\t\t3\t4", {"1", "2", "3", "4"}},
      {"\n™\t™\n", {"™", "™"}},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.s);
    REQUIRE(strings::FieldsFunc(test_case.s, [](char c) { return std::isspace(c); }) == test_case.a);
  }

  auto pred = [](char c) { return c == 'X'; };
  FieldsTest funcCases[] = {
      {"", {}},
      {"XX", {}},
      {"XXhiXXX", {"hi"}},
      {"aXXbXXXcX", {"a", "b", "c"}},
  };

  for (const auto &test_case : funcCases) {
    INFO("Input: " << test_case.s);
    REQUIRE(strings::FieldsFunc(test_case.s, pred) == test_case.a);
  }
}

TEST_CASE("HasPrefix") {
  struct TestCase {
    std::string s;
    std::string prefix;
    bool expected;
  };

  TestCase cases[] = {
      {"", "", true},      {"", "a", false},     {"a", "", true},         {"a", "a", true},
      {"abc", "ab", true}, {"abc", "bc", false}, {"abcdef", "abc", true}, {"abcdef", "def", false},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.s << ", Prefix: " << test_case.prefix << " Want: " << test_case.expected);
    REQUIRE(strings::HasPrefix(test_case.s, test_case.prefix) == test_case.expected);
  }
}

TEST_CASE("HasSuffix") {
  struct TestCase {
    std::string s;
    std::string suffix;
    bool expected;
  };

  TestCase cases[] = {
      {"", "", true},       {"", "a", false},    {"a", "", true},          {"a", "a", true},
      {"abc", "ab", false}, {"abc", "bc", true}, {"abcdef", "abc", false}, {"abcdef", "def", true},
  };

  for (const auto &test_case : cases) {
    INFO("Input: " << test_case.s << ", Suffix: " << test_case.suffix << " Want: " << test_case.expected);
    REQUIRE(strings::HasSuffix(test_case.s, test_case.suffix) == test_case.expected);
  }
}