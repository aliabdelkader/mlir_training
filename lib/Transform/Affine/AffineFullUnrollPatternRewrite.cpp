#include "lib/Transform/Affine/AffineFullUnrollPatternRewrite.hpp"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/include/mlir/Pass/Pass.h"

namespace mlir {
namespace training {

#define GEN_PASS_DEF_AFFINEFULLUNROLLPATTENREWRITE
#include "lib/Transform/Affine/Passes.h.inc"

using mlir::affine::AffineForOp;
using mlir::affine::loopUnrollFull;

// pattern match on affine for op and unroll it
struct AffineFullUnrollPattern : public OpRewritePattern<AffineForOp>{
    AffineFullUnrollPattern(mlir::MLIRContext *context) : OpRewritePattern<AffineForOp>(context, /*benefit=*/1) {}

    LogicalResult matchAndRewrite(AffineForOp op, PatternRewriter &rewriter) const override {
        return loopUnrollFull(op);
    }
};

// define the pass invokes the pattern rewrite engine
struct AffineFullUnrollPatternRewrite : public impl::AffineFullUnrollPattenRewriteBase<AffineFullUnrollPatternRewrite> {

    using AffineFullUnrollPattenRewriteBase::AffineFullUnrollPattenRewriteBase;

    void runOnOperation() {
        mlir::RewritePatternSet patterns(&getContext());
        patterns.add<AffineFullUnrollPattern>(&getContext());
        (void)applyPatternsAndFoldGreedily(getOperation(), std::move(patterns));
    }
};

} // namespace training
} // namespace mlir