#ifndef LIB_TRANSFORM_ARITH_PASSES_H_
#define LIB_TRANSFORM_ARITH_PASSES_H_

#include "lib/Transform/Arith/MulToAdd.hpp"

namespace mlir {
namespace training {

    #define GEN_PASS_REGISTRATION
    #include "lib/Transform/Arith/Passes.h.inc"
    
} // namespace training
} // namespace mlir


#endif