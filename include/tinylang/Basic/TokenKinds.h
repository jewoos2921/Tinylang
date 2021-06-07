//
// Created by jewoo on 2021-06-06.
//

#ifndef TINYLANG_TOKENKINDS_H
#define TINYLANG_TOKENKINDS_H

namespace tinylang::tok {
    enum TokenKind : unsigned short {
#define TOK(ID) ID,

#include "TokenKinds.def"

        NUM_TOKENS
    };

    const char *getTokenName(TokenKind Kind);

    const char *getPunctuatorSpelling(TokenKind Kind);

    const char *getKeywordSpelling(TokenKind Kind);
}
#endif //TINYLANG_TOKENKINDS_H
