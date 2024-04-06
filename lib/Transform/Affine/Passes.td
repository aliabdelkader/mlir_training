#ifndef LIB_TRANSFORM_AFFINE_PASSES_ID_
#define LIB_TRANSFORM_AFFINE_PASSES_ID_

include "mlir/Pass/PassBase.td"

def AffineFullUnroll : Pass<"affine-full-unroll"> {
    let summary = "Fully unroll all affine loops";
    let description = [{
        Fully unroll all affine loops.
    }];
    let dependentDialects = ["mlir::affine::AffineDialect"];
}

def AffineFullUnrollPattenRewrite : Pass<"affine-full-unroll-rewrite"> {
    let summary = "fully unroll all affine loops with pattern rewrite";
    let description = [{
        fully unroll all affine loops using pattern rewrite engine.
    }];
    let dependentDialects = ["mlir::affine::AffineDialect"];
}

#endif // LIB_TRANSFORM_AFFINE_PASSES_ID_