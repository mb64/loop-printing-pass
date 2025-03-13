#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace {

struct LoopPrintingPass : public PassInfoMixin<LoopPrintingPass> {
  PreservedAnalyses run(Loop &L, LoopAnalysisManager &AM,
                      LoopStandardAnalysisResults &AR, LPMUpdater &U) {

    auto debug = 0;
    if (debug)
      errs() << "Running for a loop ...\n";

    auto bb = L.getHeader();
    LLVMContext &ctx = bb->getContext();
    auto func = bb->getModule()->getOrInsertFunction("hereWeGoAgain", Type::getVoidTy(ctx));
    IRBuilder<> builder(bb->getFirstNonPHI());
    builder.CreateCall(func);

    if (debug) {
      errs() << "Result:\n";
      errs() << *bb->getParent() << "\n";
    }

    return PreservedAnalyses::none();
  };
};

}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {
    .APIVersion = LLVM_PLUGIN_API_VERSION,
    .PluginName = "Loop printing pass",
    .PluginVersion = "v0.1",
    .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
      PB.registerPipelineStartEPCallback(
        [](ModulePassManager &MPM, OptimizationLevel Level) {
          MPM.addPass(createModuleToFunctionPassAdaptor(createFunctionToLoopPassAdaptor(LoopPrintingPass())));
        });
    }
  };
}
