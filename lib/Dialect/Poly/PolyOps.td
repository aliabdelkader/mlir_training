#ifndef LIB_DIALECT_POLY_POLYOPS_TD_
#define LIB_DIALECT_POLY_POLYOPS_TD_

include "PolyDialect.td"
include "PolyTypes.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

// Type constraint for binops arguments: polys, vectors of polys or tensors of polys
def PolyOrContainer : TypeOrContainer<PolynomialType, "poly-or-container">;

class Poly_BinOp<string mnemmonic> : Op<Poly_Dialect, mnemmonic, [Pure, ElementwiseMappable, SameOperandsAndResultElementType]> {
    let arguments = (ins PolyOrContainer:$lhs, PolyOrContainer:$rhs);
    let results = (outs PolyOrContainer:$output);
    let assemblyFormat = "$lhs `,` $rhs attr-dict `:` `(` type($lhs) `,` type($rhs) `)` `->` type($output)";
}

def Poly_AddOp : Poly_BinOp<"add"> {
    let summary = "addition operation between polynomials";
}

def Poly_SubOp : Poly_BinOp<"sub"> {
    let summary = "subtraction operation";
}

def Poly_MulOp : Poly_BinOp<"mul"> {
    let summary = "multiplication operation";
}

def Poly_FromTensorOp : Op<Poly_Dialect, "from_tensor", [Pure]> {
    let summary = "create a polynomial from int coefficents in a tensor";
    let arguments = (ins TensorOf<[AnyInteger]>:$input);
    let results = (outs PolynomialType:$output);
    let assemblyFormat = "$input attr-dict `:` type($input) `->` type($output)";
}

def Poly_EvalOp : Op<Poly_Dialect, "eval"> {
    let summary = "eval a polynomial given input value";
    let arguments = (ins PolynomialType:$input, AnyInteger:$point);
    let results = (outs AnyInteger:$output);
    let assemblyFormat = "$input `,` $point attr-dict `:` `(` type($input) `,` type($point) `)` `->` type($output)";
}
#endif // LIB_DIALECT_POLY_POLYOPS_TD_