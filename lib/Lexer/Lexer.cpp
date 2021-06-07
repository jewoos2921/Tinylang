//
// Created by jewoo on 2021-06-03.
//

#include "tinylang/Lexer/Lexer.h"

namespace charinfo {
    LLVM_READNONE inline bool isWhitespace(char c) {
        return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r' || c == '\n';
    }

    LLVM_READNONE inline bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    LLVM_READNONE inline bool isLetter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
}

void Lexer::next(Token &token) {
    while (*BufferPtr && charinfo::isWhitespace(*BufferPtr)) {
        ++BufferPtr;
    }
    if (!*BufferPtr) {
        token.Kind = Token::eoi;
        return;
    }
    if (charinfo::isLetter(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isLetter(*end))
            ++end;
        llvm::StringRef Name(BufferPtr, end - BufferPtr);
        Token::TokenKind kind = Name == "with" ? Token::KW_with : Token::ident;
        formToken(token, end, kind);
        return;
    } else if (charinfo::isDigit(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isDigit(*end))
            ++end;
        formToken(token, end, Token::number);
        return;
    } else {
        switch (*BufferPtr) {

            case '+':
                formToken(token, BufferPtr + 1, Token::plus);
                break;
            case '-':
                formToken(token, BufferPtr + 1, Token::minus);
                break;
            case '*':
                formToken(token, BufferPtr + 1, Token::star);
                break;
            case '/':
                formToken(token, BufferPtr + 1, Token::slash);
                break;
            case '(':
                formToken(token, BufferPtr + 1, Token::Token::l_paren);
                break;
            case ')':
                formToken(token, BufferPtr + 1, Token::Token::r_paren);
                break;
            case ':':
                formToken(token, BufferPtr + 1, Token::Token::colon);
                break;
            case ',':
                formToken(token, BufferPtr + 1, Token::Token::comma);
                break;
            default:
                formToken(token, BufferPtr + 1, Token::unknown);
        }
        return;
    }
}

void Lexer::formToken(Token &Result, const char *TokEnd, Token::TokenKind Kind) {
    Result.Kind = Kind;
    Result.Text = llvm::StringRef(BufferPtr, TokEnd - BufferPtr);
    BufferPtr = TokEnd;
}
