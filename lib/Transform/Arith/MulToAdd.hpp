#ifndef LIB_TRANSFORM_ARITH_MULTOADD_H_
#define LIB_TRANSFORM_ARITH_MULTOADD_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace training {

#define GEN_PASS_DECL_MULTOADD
#include "lib/Transform/Arith/Passes.h.inc"


} // namespace training

} // namespace mlir

#endif