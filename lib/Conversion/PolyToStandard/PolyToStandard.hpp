#ifndef LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_H_
#define LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_H_

#include "mlir/include/mlir/Pass/Pass.h" // from @llvm-project
#include "mlir/include/mlir/Dialect/Arith/IR/Arith.h" // from @llvm-project
#include "mlir/include/mlir/Dialect/Tensor/IR/Tensor.h" // from @llvm-project

namespace mlir {
namespace training {
namespace poly {

#define GEN_PASS_DECL
#define GEN_PASS_DECL_POLYTOSTANDARD
#include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"

#define GEN_PASS_REGISTRATION
#include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"

} // namespace poly

} // namespace training

} // namespace mlir

#endif // LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_H_