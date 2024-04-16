#include "lib/Dialect/Poly/PolyDialect.hpp"
#include "lib/Dialect/Poly/PolyTypes.hpp"
#include "lib/Dialect/Poly/PolyOps.hpp"
#include "mlir/include/mlir/IR/Builders.h"
#include "llvm/include/llvm/ADT/TypeSwitch.h"

#include "lib/Dialect/Poly/PolyDialect.cpp.inc"
#define GET_TYPEDEF_CLASSES
#include "lib/Dialect/Poly/PolyTypes.cpp.inc"
#define GET_OP_CLASSES
#include "lib/Dialect/Poly/PolyOps.cpp.inc"

namespace mlir {
namespace training {
namespace poly {

void PolyDialect::initialize() {
addTypes<
#define GET_TYPEDEF_LIST
#include "lib/Dialect/Poly/PolyTypes.cpp.inc"
>();

addOperations<
#define GET_OP_LIST
#include "lib/Dialect/Poly/PolyOps.cpp.inc"
>();
}

Operation *PolyDialect::materializeConstant(OpBuilder &builder, Attribute value, Type type, Location loc) {
    auto coeffs = dyn_cast<DenseIntElementsAttr>(value);
    if(!coeffs) return nullptr;
    return builder.create<ConstantOp>(loc, type, coeffs);
}

} // namespace poly
} // namespace training
} // namespace mlir