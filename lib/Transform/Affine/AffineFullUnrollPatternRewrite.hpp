#ifndef LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLLPATTERNREWRITE_H_
#define LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLLPATTERNREWRITE_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace training {


#define GEN_PASS_DECL_AFFINEFULLUNROLLPATTENREWRITE
#include "lib/Transform/Affine/Passes.h.inc"

} // namespace training
} // namespace mlir

#endif