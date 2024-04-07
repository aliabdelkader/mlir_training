#ifndef LIB_DIALECT_POLY_POLYTYPES_TD_
#define LIB_DIALECT_POLY_POLYTYPES_TD_

include "PolyDialect.td"
include "mlir/IR/AttrTypeBase.td"

class Poly_Type<string name, string typeMnemonic> : TypeDef<Poly_Dialect, name> {
    let mnemonic  = typeMnemonic;
}

def PolynomialType  : Poly_Type<"PolynomialType", "poly"> {
    let summary = "polynomial with u32 coefficients";
    let description = [{
        a type for polynomial with integer cofficients in a single var polynomial ring
    }];
    let parameters = (ins "int":$degreeBound);
    let assemblyFormat = "`<` $degreeBound `>`";
}
#endif  // LIB_DIALECT_POLY_POLYTYPES_TD_