//
// Created by jewoo on 2021-06-05.
//

#ifndef TINYLANG_SEMA_H
#define TINYLANG_SEMA_H

#include "tinylang/AST/AST.h"
#include "tinylang/Lexer/Lexer.h"

class Sema {
public:
    bool semantic(AST *Tree);
};

#endif //TINYLANG_SEMA_H
