#ifndef LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_TD_
#define LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_TD_

include "mlir/Pass/PassBase.td"

def PolyToStandard : Pass<"poly-to-standard"> {
    let summary = "lower poly to standard mlir dialects";

    let description = [{
        lower poly to standard mlir, affine, tensor and arith dialects
    }];

    let dependentDialects = [
        "mlir::arith::ArithDialect",
        "mlir::training::poly::PolyDialect",
        "mlir::tensor::TensorDialect",
        "mlir::scf::SCFDialect",
    ];
}


#endif // LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_TD_