//
// Created by jewoo on 2021-06-06.
//

#include "tinylang/Basic/Diagnostic.h"

using namespace tinylang;
namespace {
    const char *DiagnosticText[] = {
#define  DIAG(ID, Level, Msg) Msg,

#include "tinylang/Basic/Diagnostic.def"
    };
    llvm::SourceMgr::DiagKind DiagnosticsKind[] = {
#define  DIAG(ID, Level, Msg) llvm::SourceMgr::DK_##Level,

#include "tinylang/Basic/Diagnostic.def"
    };
}

const char *DiagnosticsEngine::getDiagnosticText(unsigned int DiagID) {
    return DiagnosticText[DiagID];
}

llvm::SourceMgr::DiagKind DiagnosticsEngine::getDiagnosticKind(unsigned int DiagID) {
    return DiagnosticsKind[DiagID];
}
