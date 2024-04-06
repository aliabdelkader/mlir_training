#ifndef LIB_TRANSFORM_AFFINE_PASSES_H_
#define LIB_TRANSFORM_AFFINE_PASSES_H_

#include "lib/Transform/Affine/AffineFullUnroll.hpp"
#include "lib/Transform/Affine/AffineFullUnrollPatternRewrite.hpp"

namespace mlir {
namespace training {

#define  GEN_PASS_REGISTRATION
#include "lib/Transform/Affine/Passes.h.inc"

} // namespace training

} // namespace mlir

#endif