//===--- clang/Basic/CharInfo.h - Classifying ASCII Characters --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_BASIC_CHARINFO_H
#define LLVM_CLANG_BASIC_CHARINFO_H

#include "swift/Basic/LLVM.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/DataTypes.h"

namespace swift {
    namespace charinfo {
        extern const uint16_t InfoTable[256];

        enum {
            CHAR_HORZ_WS = 0x0001,  // '\t', '\f', '\v'.  Note, no '\0'
            CHAR_VERT_WS = 0x0002,  // '\r', '\n'
            CHAR_SPACE = 0x0004,  // ' '
            CHAR_DIGIT = 0x0008,  // 0-9
            CHAR_XLETTER = 0x0010,  // a-f,A-F
            CHAR_UPPER = 0x0020,  // A-Z
            CHAR_LOWER = 0x0040,  // a-z
            CHAR_UNDER = 0x0080,  // _
            CHAR_PERIOD = 0x0100,  // .
            CHAR_RAWDEL = 0x0200,  // {}[]#<>%:;?*+-/^&|~!=,"'
            CHAR_PUNCT = 0x0400   // `$@()
        };

        enum {
            CHAR_XUPPER = CHAR_XLETTER | CHAR_UPPER,
            CHAR_XLOWER = CHAR_XLETTER | CHAR_LOWER
        };
    } // end namespace charinfo

/// Return true if this character is an ASCII digit: [0-9]
    LLVM_READONLY inline bool isDigit(unsigned char c) {
        using namespace charinfo;
        return (InfoTable[c] & CHAR_DIGIT) != 0;
    }

/// Return true if this character is an ASCII letter: [a-zA-Z]
    LLVM_READONLY inline bool isLetter(unsigned char c) {
        using namespace charinfo;
        return (InfoTable[c] & (CHAR_UPPER | CHAR_LOWER)) != 0;
    }

/// Return true if this character is a lowercase ASCII letter: [a-z]
    LLVM_READONLY inline bool isLowercase(unsigned char c) {
        using namespace charinfo;
        return (InfoTable[c] & CHAR_LOWER) != 0;
    }

/// Return true if this character is an uppercase ASCII letter: [A-Z]
    LLVM_READONLY inline bool isUppercase(unsigned char c) {
        using namespace charinfo;
        return (InfoTable[c] & CHAR_UPPER) != 0;
    }

/// Converts the given ASCII character to its lowercase equivalent.
///
/// If the character is not an uppercase character, it is returned as is.
    LLVM_READONLY inline char toLowercase(char c) {
        if (isUppercase(c))
            return c + 'a' - 'A';
        return c;
    }

/// Converts the given ASCII character to its uppercase equivalent.
///
/// If the character is not a lowercase character, it is returned as is.
    LLVM_READONLY inline char toUppercase(char c) {
        if (isLowercase(c))
            return c + 'A' - 'a';
        return c;
    }


} // end namespace swift

#endif