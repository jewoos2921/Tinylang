//
// Created by jewoo on 2021-06-05.
//

#ifndef TINYLANG_PARSER_H
#define TINYLANG_PARSER_H

#include "tinylang/AST/AST.h"
#include "tinylang/Lexer/Lexer.h"
#include "llvm/Support/raw_ostream.h"

class Parser {
    Lexer &Lex;
    Token Tok;
    bool HasError;

    void error() {
        llvm::errs() << "Unexpected: " << Tok.getText() << "\n";
        HasError = true;
    }

    void advance() { Lex.next(Tok); }

    bool expect(Token::TokenKind Kind) {
        if (Tok.getKind() != Kind) {
            error();
            return true;
        }
        return false;
    }

    bool consume(Token::TokenKind Kind) {
        if (expect(Kind))
            return true;
        advance();
        return false;
    }

    AST *parseCalc();

    Expr *parseExpr();

    Expr *parseTerm();

    Expr *parseFactor();

public:
    Parser(Lexer &Lex) : Lex(Lex), HasError(false) { advance(); }

    bool hasError() { return HasError; }

    AST *parse();
};

#endif //TINYLANG_PARSER_H
