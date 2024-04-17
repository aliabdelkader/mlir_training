#ifndef LIB_DIALECT_POLY_POLYOPS_TD_
#define LIB_DIALECT_POLY_POLYOPS_TD_

include "PolyDialect.td"
include "PolyTypes.td"
include "mlir/IR/BuiltinAttributes.td"
include "mlir/IR/OpBase.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
include "mlir/Interfaces/InferTypeOpInterface.td"

// Type constraint for binops arguments: polys, vectors of polys or tensors of polys
def PolyOrContainer : TypeOrContainer<PolynomialType, "poly-or-container">;

// Inject verification that all integer-like arguments are 32-bits
def Has32BitArguments : NativeOpTrait<"Has32BitArguments"> {
  let cppNamespace = "::mlir::training::poly";
}

class Poly_BinOp<string mnemmonic> : Op<Poly_Dialect, mnemmonic, [Pure, ElementwiseMappable, SameOperandsAndResultType]> {
    let arguments = (ins PolyOrContainer:$lhs, PolyOrContainer:$rhs);
    let results = (outs PolyOrContainer:$output);
    let assemblyFormat = "$lhs `,` $rhs attr-dict `:` qualified(type($output))";
    let hasFolder = 1;
    let hasCanonicalizer = 1;
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
    let assemblyFormat = "$input attr-dict `:` type($input) `->` qualified(type($output))";
    let hasFolder = 1;
}

def IntOrComplex : AnyTypeOf<[AnyInteger, AnyComplex]>;

def Poly_EvalOp : Op<Poly_Dialect, "eval", [AllTypesMatch<["point", "output"]>, Has32BitArguments]> {
    let summary = "eval a polynomial given input value";
    let arguments = (ins PolynomialType:$input, IntOrComplex:$point);
    let results = (outs IntOrComplex:$output);
    let assemblyFormat = "$input `,` $point attr-dict `:` `(` qualified(type($input)) `,` type($point) `)` `->` type($output)";
    let hasVerifier = 1;
    let hasCanonicalizer = 1;
}

def Poly_ConstantOp : Op<Poly_Dialect, "constant", [Pure, ConstantLike]> {
    let summary = "Define a constant poly via an attribute.";
    let arguments = (ins AnyIntElementsAttr:$coefficients);
    let results = (outs PolynomialType:$output);
    let assemblyFormat = "$coefficients attr-dict `:` qualified(type($output))";
    let hasFolder = 1;
}
#endif // LIB_DIALECT_POLY_POLYOPS_TD_