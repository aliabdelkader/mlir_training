#include "lib/Transform/Affine/AffineFullUnroll.hpp"
// #include "lib/Transform/Arith/MulToAdd.h"
#include "mlir/include/mlir/InitAllDialects.h"
#include "mlir/include/mlir/Pass/PassManager.h"
#include "mlir/include/mlir/Pass/PassRegistry.h"
#include "mlir/include/mlir/Tools/mlir-opt/MlirOptMain.h"


int main(int argc, char **argv) {
    mlir::DialectRegistry registry;
    mlir::registerAllDialects(registry);
    mlir::PassRegistration<mlir::training::AffineFullUnrollPass>();
    mlir::PassRegistration<mlir::training::AffineFullUnrollPassAsPatternRewrite>();
    // mlir::PassRegistration<mlir::training::MulToAddPass>();
    return mlir::asMainReturnCode(
        mlir::MlirOptMain(argc, argv, "mlir training Pass Driver", registry)
    );
}