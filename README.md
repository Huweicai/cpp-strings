# CPP-STRINGS

A c++ header only library that provides string manipulation functions similar to Go's strings package.

e.g.

```c++

#include <cpp-strings/strings.h>

int main() {
  std::string s = "Hello, World!";
  std::string sub = strings::TrimPrefix(s, "Hello, ");
  std::cout << sub << std::endl;
  return 0;
}

> World !
```

# Implementation Details

Since there are some differences between the Go and C++ strings design, so some of the functions are not implemented.

| Function Name  | Implemented |
|----------------|-------------|
| Count          | ✔           |
| Contains       | ✔           |
| ContainsAny    | ✔           |
| ContainsRune   |             |
| ContainsFunc   |             |
| LastIndex      |             |
| IndexByte      |             |
| IndexRune      |             |
| IndexAny       |             |
| LastIndexAny   |             |
| LastIndexByte  |             |
| SplitN         |             |
| SplitAfterN    |             |
| Split          |             |
| SplitAfter     |             |
| Fields         |             |
| FieldsFunc     |             |
| Join           |             |
| HasPrefix      |             |
| HasSuffix      |             |
| Map            |             |
| Repeat         |             |
| ToUpper        |             |
| ToLower        |             |
| ToTitle        |             |
| ToUpperSpecial |             |
| ToLowerSpecial |             |
| ToTitleSpecial |             |
| ToValidUTF8    |             |
| Title          |             |
| TrimLeftFunc   |             |
| TrimRightFunc  |             |
| TrimFunc       |             |
| IndexFunc      |             |
| LastIndexFunc  |             |
| Trim           |             |
| TrimLeft       |             |
| TrimRight      |             |
| TrimSpace      |             |
| TrimPrefix     |             |
| TrimSuffix     |             |
| Replace        |             |
| ReplaceAll     |             |
| EqualFold      |             |
| Index          | ✔           |
| Cut            |             |
| CutPrefix      |             |
| CutSuffix      |             |