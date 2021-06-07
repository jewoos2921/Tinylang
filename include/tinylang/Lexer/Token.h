//
// Created by jewoo on 2021-06-06.
//

#ifndef TINYLANG_TOKEN_H
#define TINYLANG_TOKEN_H

#include "tinylang/Basic/LLVM.h"
#include "tinylang/Basic/TokenKinds.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

class Token {
    friend class Lexer;

    const char *Ptr;
    size_t length;
};

#endif //TINYLANG_TOKEN_H
