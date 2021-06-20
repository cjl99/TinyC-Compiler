//
// Created by Jialiang Chen on 2021/6/8.
//
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/ADT/Optional.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/LegacyPassManager.h>

#include "../codeGen/CodeGen.h"
#include "ObjGen.h"

using namespace llvm;

void ObjGen(CodeGen & context, const string& filename){

    outs() << "[LLVM] Generate object file" << filename.c_str() << "\n";
    // Initialize the target registry etc.
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    auto targetTriple = sys::getDefaultTargetTriple();
    context.theModule->setTargetTriple(targetTriple);

    std::string error;
    auto Target = TargetRegistry::lookupTarget(targetTriple, error);

    if( !Target ){
        errs() << error;
        return;
    }

    auto CPU = "generic";
    auto features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto theTargetMachine = Target->createTargetMachine(targetTriple, CPU, features, opt, RM);

    context.theModule->setDataLayout(theTargetMachine->createDataLayout());
    context.theModule->setTargetTriple(targetTriple);

    std::error_code EC;
    raw_fd_ostream dest(filename.c_str(), EC, sys::fs::F_None);
    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return;
    }
//    formatted_raw_ostream formattedRawOstream(dest);

    legacy::PassManager pass;

    auto fileType = CGFT_ObjectFile;
//    dPassesToEmitFile(PassManagerBase &, raw_pwrite_stream &,
//                      raw_pwrite_stream *, CodeGenFileType,
    if( theTargetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType) ){
        errs() << "theTargetMachine can't emit a file of this type";
        return;
    }

    pass.run(*context.theModule.get());
    dest.flush();

    outs() << "[LLVM] Object code wrote to " << filename.c_str() << "\n";

    return;
}