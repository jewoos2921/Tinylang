//
// Created by jewoo on 2021-06-05.
//

#ifndef TINYLANG_CODEGEN_H
#define TINYLANG_CODEGEN_H

#include "tinylang/AST/AST.h"

class CodeGen {
public:
    void compile(AST *Tree);
};

#endif //TINYLANG_CODEGEN_H
