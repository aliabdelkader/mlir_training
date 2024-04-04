#ifndef LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H
#define LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/include/mlir/Pass/Pass.h"

namespace mlir {
namespace training {

    class AffineFullUnrollPass : public PassWrapper<AffineFullUnrollPass, OperationPass<mlir::func::FuncOp>> {

        private:
            void runOnOperation() override;

            StringRef getArgument() const final { return "affine-full-unroll"; }

            StringRef getDescription() const final {
                return "fully unroll all affine loops";
            }
    };


    class AffineFullUnrollPassAsPatternRewrite : public PassWrapper<AffineFullUnrollPassAsPatternRewrite, OperationPass<mlir::func::FuncOp>> {

        private:
            void runOnOperation() override;

            StringRef getArgument() const final { return "affine-full-unroll-rewrite"; }

            StringRef getDescription() const final {
                return "Fully unroll all affine loops using pattern rewrite engine";
            }
    };

} // namespace training

} // namespace mlir

#endif // LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H