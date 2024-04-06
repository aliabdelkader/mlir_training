#ifndef LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H
#define LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H

#include "mlir/include/mlir/Pass/Pass.h"

namespace mlir {
namespace training {

#define GEN_PASS_DECL_AFFINEFULLUNROLL
#include "lib/Transform/Affine/Passes.h.inc"

} // namespace training

} // namespace mlir

#endif // LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H