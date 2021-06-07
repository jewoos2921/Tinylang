//
// Created by jewoo on 2021-06-05.
//

#include "tinylang/CodeGen/CodeGen.h"
#include "tinylang/Parser/Parser.h"
#include "tinylang/Sema/Sema.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

static llvm::cl::opt<std::string> Input(llvm::cl::Positional,
                                        llvm::cl::desc("<input expression>"),
                                        llvm::cl::init(""));

int main(int argc_, char **argv_) {
    llvm::InitLLVM X(argc_, argv_);
    llvm::cl::ParseCommandLineOptions(
            argc_, argv_, "calc - the expression compiler\n"
    );
    Lexer Lex(Input);
    Parser Parser(Lex);
    AST *Tree = Parser.parse();
    if (!Tree || Parser.hasError()) {
        llvm::errs() << "Syntax errors occurred\n";
        return 1;
    }
    Sema Semantic;
    if (Semantic.semantic(Tree)) {
        llvm::errs() << "Semantic errors occurred\n";
        return 1;
    }
    CodeGen CodeGenerator;
    CodeGenerator.compile(Tree);
    return 0;
}