#include "lib/Transform/Affine/Passes.h"
#include "lib/Transform/Arith/Passes.h"
#include "lib/Dialect/Poly/PolyDialect.hpp"
#include "mlir/include/mlir/InitAllDialects.h"
#include "mlir/include/mlir/Pass/PassRegistry.h"
#include "mlir/include/mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/include/mlir/InitAllPasses.h"

int main(int argc, char **argv) {
    mlir::DialectRegistry registry;
    registry.insert<mlir::training::poly::PolyDialect>();
    mlir::registerAllDialects(registry);
    mlir::training::registerAffinePasses();
    mlir::training::registerArithPasses();
    // mlir::PassRegistration<mlir::training::AffineFullUnroll>();
    // mlir::PassRegistration<mlir::training::AffineFullUnrollPassAsPatternRewrite>();
    // mlir::PassRegistration<mlir::training::MulToAddPass>();
    mlir::registerAllPasses();
    return mlir::asMainReturnCode(
        mlir::MlirOptMain(argc, argv, "mlir training Pass Driver", registry)
    );
}