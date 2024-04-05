#ifndef LIB_TRANSFORM_ARITH_MULTOADD_H_
#define LIB_TRANSFORM_ARITH_MULTOADD_H_

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/include/mlir/Pass/Pass.h"

namespace mlir {
namespace training {

class MulToAddPass : public PassWrapper<MulToAddPass, OperationPass<mlir::func::FuncOp>> {

private:
    void runOnOperation() override;
    StringRef getArgument() const final {  return "mul-to-add"; }

    StringRef getDescription() const final {
        return "convert mul to repeated additions";
    }

}; // class MulToAddPass

} // namespace training

} // namespace mlir

#endif