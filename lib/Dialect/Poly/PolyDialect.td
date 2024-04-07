#ifndef LIB_DIALECT_POLY_POLYDIALECT_TD_
#define LIB_DIALECT_POLY_POLYDIALECT_TD_

include "mlir/IR/DialectBase.td"

def Poly_Dialect : Dialect {
    let name = "poly";
    let summary = "a dialect for poly math";
    let description = [{
        poly dialect
    }];
    let cppNamespace = "::mlir::training::poly";

  let useDefaultTypePrinterParser = 1;
}

#endif // LIB_DIALECT_POLY_POLYDIALECT_TD_