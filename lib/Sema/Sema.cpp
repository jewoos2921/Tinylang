//
// Created by jewoo on 2021-06-05.
//

#include "tinylang/Sema/Sema.h"
#include "llvm/ADT/StringSet.h"

namespace {
    class DeclCheck : public ASTVisitor {
        llvm::StringSet<> scope;
        bool HasError;
        enum ErrorType {
            Twice, Not
        };

        void error(ErrorType ET, llvm::StringRef V) {
            llvm::errs() << "Variable " << V << " " << (ET == Twice ? "already" : "not") << " declared\n";
            HasError = true;
        }

    public:
        DeclCheck() : HasError(false) {}

        bool hasError() { return HasError; }

        void visit(Factor &Node) override {
            if (Node.getKind() == Factor::Ident) {
                if (scope.find(Node.getVal()) == scope.end()) {
                    error(Not, Node.getVal());
                }
            }
        }

        void visit(BinaryOp &Node) override {
            if (Node.getLeft())
                Node.getLeft()->accept(*this);
            else
                HasError = true;
            if (Node.getRight())
                Node.getRight()->accept(*this);
            else
                HasError = true;
        }

        void visit(WithDecl &Node) override {
            for (auto I = Node.begin(), E = Node.end(); I != E; ++I) {
                if (!scope.insert(*I).second)
                    error(Twice, *I);
                if (Node.getExpr())
                    Node.getExpr()->accept(*this);
                else
                    HasError = true;
            }
        }
    };
}

bool Sema::semantic(AST *Tree) {
    if (!Tree)
        return false;
    DeclCheck Check;
    Tree->accept(Check);
    return Check.hasError();
}
