#ifndef LIB_DIALECT_POLY_POLYOPS_H_
#define LIB_DIALECT_POLY_POLYOPS_H_

#include "lib/Dialect/Poly/PolyDialect.hpp"
#include "lib/Dialect/Poly/PolyTypes.hpp"
#include "mlir/include/mlir/IR/BuiltinOps.h"
#include "mlir/include/mlir/IR/BuiltinTypes.h"
#include "mlir/include/mlir/IR/Dialect.h"

#define GET_OP_CLASSES
#include "lib/Dialect/Poly/PolyOps.h.inc"

#endif // LIB_DIALECT_POLY_POLYOPS_H_