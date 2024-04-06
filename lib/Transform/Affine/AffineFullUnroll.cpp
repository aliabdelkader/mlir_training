#include "lib/Transform/Affine/AffineFullUnroll.hpp"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/include/mlir/Pass/Pass.h"

namespace mlir {
namespace training {

#define  GEN_PASS_DEF_AFFINEFULLUNROLL
#include "lib/Transform/Affine/Passes.h.inc"

using mlir::affine::AffineForOp;
using mlir::affine::loopUnrollFull;

struct AffineFullUnroll : impl::AffineFullUnrollBase<AffineFullUnroll>{
    using AffineFullUnrollBase::AffineFullUnrollBase;
    
    // pass that manually walks the IR
    void runOnOperation() {
        getOperation()->walk([&](AffineForOp op){
            if (failed(loopUnrollFull(op))) {
                op.emitError("unrolling failed");
                signalPassFailure();
            }
        });
    }
};

} // namespace training

} // namespace mlir

