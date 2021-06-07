//
// Created by jewoo on 2021-06-06.
//
#include "tinylang/Basic/TokenKinds.h"
#include "llvm/Support/ErrorHandling.h"

using namespace tinylang;
static const char *const TokNames[] = {
#define TOK(ID) #ID,
#define KEYWORD(ID, FLAG) #ID,

#include "tinylang/Basic/TokenKinds.def"

        nullptr
};

const char *tok::getTokenName(tok::TokenKind Kind) {
    return TokNames[Kind];
}

const char *tok::getPunctuatorSpelling(tok::TokenKind Kind) {
    switch (Kind) {
#define PUNCTUATOR(ID, SP) case ID: return SP;
#include "tinylang/Basic/TokenKinds.def"

        default:break;
    }
    return nullptr;
}

const char *tok::getKeywordSpelling(tok::TokenKind Kind) {
    switch (Kind) {
#define KEYWORD(ID, FLAG) case kw_ ## ID: return #ID;
#include "tinylang/Basic/TokenKinds.def"

        default:break;
    }
    return nullptr;
}

