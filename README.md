# 🛠️ Fixed pcalc Calculator

[![License: BSD 3-Clause](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

This is a fixed version of the pcalc (Programmer's Calculator) that resolves critical compilation errors and grammar conflicts.

## 🔧 What Was Fixed

### 1. Bison/Yacc Grammar Conflicts

**Before:** 67 shift/reduce and 37 reduce/reduce conflicts  
**After:** 0 conflicts

**Fixes:**
- Rewritten list/element rule structure
- Removed duplicate IBUILTIN VAR and IBUILTIN expr rules
- Added correct operator precedence
- Fixed ambiguity in the empty list rule

### 2. C Type Errors

**Problem:** Mismatched function pointer signatures

**Fixes in symbol.h:**

```c
// Before:
long double (*ptr)();
int (*iptr)();

// After:
long double (*ptr)(long double);
int (*iptr)(void*);
```

### 3. Function Wrappers in symbol.c

Created wrapper functions for compatibility:
- `ddate_wrapper()`
- `print_wrapper()`
- `echo_wrapper()`
- `echo_nl_wrapper()`

### 4. Build System

- Fixed Makefile: `bison -ld` → `bison -d`
- Added header file generation
- Created symbolic link `pcalc.h` → `pcalc.tab.h`

## 🚀 Installation and Building

```bash
# Clone repository
git clone https://github.com/your-username/pcalc-fixed.git
cd pcalc-fixed

# Build project
make clean
make

# Run calculator
./pcalc "2 + 2"
```

## 📖 Usage

```bash
# Arithmetic operations
./pcalc "5 + 3 * 2"

# Bitwise operations (programmer's calculator!)
./pcalc "0xFF & 0x0F"
./pcalc "1 << 8"

# Mathematical functions
./pcalc "sin(3.14159/2)"
./pcalc "sqrt(256)"

# Variables
./pcalc "x = 42"
./pcalc "x / 2"

# Commands
./pcalc "help"
./pcalc "date"
```

## 📁 Project Structure

```
pcalc-fixed/
├── pcalc.y              # Fixed Bison grammar
├── pcalcl.l             # Flex lexer
├── symbol.h             # Fixed type declarations
├── symbol.c             # Function wrappers
├── Makefile             # Fixed build system
├── README.md            # This file
└── .gitignore           # Ignored files
```

## 🐛 Solved Issues

| Issue | Solution |
|-------|----------|
| Grammar conflicts | Rewritten rules, added precedence |
| Function pointer type errors | Fixed function signatures |
| Missing pcalc.h | Generation via `bison -d` |
| Compilation warnings | Added wrappers and explicit type casts |

## 👨‍💻 Authors

- **Original author:** Peter Glen, Mike Frysinger
- **Fixes:** Nana-sin

## 📄 License

Project distributed under BSD 3-Clause License. See [LICENSE](LICENSE) file for details.
