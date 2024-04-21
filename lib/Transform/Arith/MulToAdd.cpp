#include "lib/Transform/Arith/MulToAdd.hpp"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/include/mlir/Pass/Pass.h"

namespace mlir {
namespace training {

#define GEN_PASS_DEF_MULTOADD
#include "lib/Transform/Arith/Passes.h.inc"

using arith::AddIOp;
using arith::ConstantOp;
using arith::MulIOp;

// Replace y = C*x 
// with y = (C/2)*x + (C/2)*x
// when C is a power of 2 otherwise do nothing.

struct PowerOfTwoExpand : public OpRewritePattern<MulIOp> {

    PowerOfTwoExpand(mlir::MLIRContext *context) : OpRewritePattern<MulIOp>(context, /*benefit*/2) {}

    LogicalResult matchAndRewrite(MulIOp op, PatternRewriter &rewriter) const override {
        
        Value lhs = op.getOperand(0) ;

        // canonicalization patterns ensure the constant is on the right, if there is a constant
        // see https://mlir.llvm.org/docs/Canonicalization/#globally-applied-rules
        Value rhs = op.getOperand(1);
        auto rhsDefiningOp = rhs.getDefiningOp<arith::ConstantIntOp>();
        if (!rhsDefiningOp) {
            return failure();
        }

        int64_t value = rhsDefiningOp.value(); // the constant value
        bool is_power_of_two = (value & (value - 1)) == 0;
        if (!is_power_of_two) {
            return failure();
        }

        ConstantOp newConstant = rewriter.create<arith::ConstantOp>(
            rhsDefiningOp.getLoc(), 
            rewriter.getIntegerAttr(rhs.getType(), (value / 2))
        );
        MulIOp newMul = rewriter.create<MulIOp>(op.getLoc(), lhs, newConstant);
        AddIOp newAdd = rewriter.create<AddIOp>(op.getLoc(), newMul, newMul);

        rewriter.replaceOp(op, newAdd);
        rewriter.eraseOp(rhsDefiningOp);
        return success();
    }

};


// Replace y = x*9 with y = x*9 + x
struct PeelFromMul : public OpRewritePattern<MulIOp> {
    PeelFromMul(mlir::MLIRContext *context) : OpRewritePattern<MulIOp>(context, /*benefit*/ 1) {}

    LogicalResult matchAndRewrite(MulIOp op, PatternRewriter &rewriter) const override {
        Value lhs = op.getOperand(0);
        Value rhs = op.getOperand(1);
        auto rhsDefiningOp = rhs.getDefiningOp<arith::ConstantIntOp>();
        if(!rhsDefiningOp){
            return failure();
        }
        int64_t rhsValue = rhsDefiningOp.value();        
        bool is_power_of_two = (rhsValue & (rhsValue - 1)) == 0;
        if (!is_power_of_two) {
            auto newConstant = rewriter.create<arith::ConstantOp>(
                rhsDefiningOp.getLoc(), 
                rewriter.getIntegerAttr(rhs.getType(), rhsValue - 1)
            );
            auto evenMulti = rewriter.create<arith::MulIOp>(op.getLoc(), lhs, newConstant);
            auto newAdd = rewriter.create<arith::AddIOp>(evenMulti->getLoc(), evenMulti, lhs);
            rewriter.replaceOp(op, newAdd);
            rewriter.eraseOp(rhsDefiningOp);
        }


        return success();
    }
};

struct MulToAdd : impl::MulToAddBase<MulToAdd> {

    using MulToAddBase::MulToAddBase;

    void runOnOperation() {
        mlir::RewritePatternSet patterns(&getContext());
        patterns.add<PowerOfTwoExpand>(&getContext());
        patterns.add<PeelFromMul>(&getContext());

        (void)applyPatternsAndFoldGreedily(getOperation(), std::move(patterns));
    }

};

} // namespace training

} // namespace mlir