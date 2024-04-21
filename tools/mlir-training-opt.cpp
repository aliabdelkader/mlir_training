#include "lib/Conversion/PolyToStandard/PolyToStandard.hpp"
#include "lib/Dialect/Poly/PolyDialect.hpp"
#include "lib/Transform/Affine/Passes.h"
#include "lib/Transform/Arith/Passes.h"
#include "mlir/include/mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/include/mlir/Conversion/ControlFlowToLLVM/ControlFlowToLLVM.h"
#include "mlir/include/mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"
#include "mlir/include/mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/include/mlir/Conversion/TensorToLinalg/TensorToLinalgPass.h"
#include "mlir/include/mlir/Dialect/Bufferization/Pipelines/Passes.h"
#include "mlir/include/mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/include/mlir/Dialect/Linalg/Passes.h"
#include "mlir/include/mlir/InitAllDialects.h"
#include "mlir/include/mlir/InitAllPasses.h"
#include "mlir/include/mlir/Pass/PassManager.h"
#include "mlir/include/mlir/Pass/PassRegistry.h"
#include "mlir/include/mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/include/mlir/Transforms/Passes.h"

void polyToLLVMPipelineBuilder(mlir::OpPassManager &manager){
    // POLY
    manager.addPass(mlir::training::poly::createPolyToStandard());
    manager.addPass(mlir::createCanonicalizerPass());
    manager.addPass(mlir::createConvertElementwiseToLinalgPass());
    manager.addPass(mlir::createConvertTensorToLinalgPass());
    
    // One-shot bufferize, from
    // https://mlir.llvm.org/docs/Bufferization/#ownership-based-buffer-deallocation
    mlir::bufferization::OneShotBufferizationOptions bufferizationOptions;
    bufferizationOptions.bufferizeFunctionBoundaries = true;
    manager.addPass(
        mlir::bufferization::createOneShotBufferizePass(bufferizationOptions));
    mlir::bufferization::BufferDeallocationPipelineOptions deallocationOptions;
    mlir::bufferization::buildBufferDeallocationPipeline(manager, deallocationOptions);
    
    // // Does nothing yet!
    manager.addPass(mlir::createConvertLinalgToLoopsPass());
    manager.addPass(mlir::memref::createExpandStridedMetadataPass());
    manager.addPass(mlir::createConvertSCFToCFPass());
    manager.addPass(mlir::createConvertControlFlowToLLVMPass());
    manager.addPass(mlir::createArithToLLVMConversionPass());
    manager.addPass(mlir::createConvertFuncToLLVMPass());
    manager.addPass(mlir::createFinalizeMemRefToLLVMConversionPass());
    manager.addPass(mlir::createReconcileUnrealizedCastsPass());


    // Cleanup
    manager.addPass(mlir::createCanonicalizerPass());
    manager.addPass(mlir::createSCCPPass());
    manager.addPass(mlir::createCSEPass());
    manager.addPass(mlir::createSymbolDCEPass());
}

int main(int argc, char **argv) {
    mlir::DialectRegistry registry;
    registry.insert<mlir::training::poly::PolyDialect>();
    mlir::registerAllDialects(registry);
    mlir::training::registerAffinePasses();
    mlir::training::registerArithPasses();
    // mlir::PassRegistration<mlir::training::AffineFullUnroll>();
    // mlir::PassRegistration<mlir::training::AffineFullUnrollPassAsPatternRewrite>();
    // mlir::PassRegistration<mlir::training::MulToAddPass>();
    mlir::training::poly::registerPolyToStandardPasses();
    mlir::registerAllPasses();

    mlir::PassPipelineRegistration<>("poly-to-llvm", "Run passes to lower poly to llvm", polyToLLVMPipelineBuilder);
    return mlir::asMainReturnCode(
        mlir::MlirOptMain(argc, argv, "mlir training Pass Driver", registry)
    );
}