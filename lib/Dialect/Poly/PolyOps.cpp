#include "lib/Dialect/Poly/PolyOps.hpp"
#include "mlir/Dialect/CommonFolders.h"
#include "llvm/Support/Debug.h"
#include "mlir/Dialect/Complex/IR/Complex.h"
#include "mlir/IR/PatternMatch.h"
// Required after PatternMatch.h
#include "lib/Dialect/Poly/PolyCanonicalize.cpp.inc"

namespace mlir {
namespace training {
namespace poly {

OpFoldResult ConstantOp::fold(ConstantOp::FoldAdaptor adaptor) {
    return adaptor.getCoefficients();
}

OpFoldResult AddOp::fold(AddOp::FoldAdaptor adaptor) {
    return constFoldBinaryOp<IntegerAttr, APInt>(
        adaptor.getOperands(),
        [&](APInt a, APInt b){ return a + b;}
    );
}

OpFoldResult SubOp::fold(SubOp::FoldAdaptor adaptor) {
    return constFoldBinaryOp<IntegerAttr, APInt>(
        adaptor.getOperands(),
        [&](APInt a, APInt b) { return a - b;}
    );
}

OpFoldResult MulOp::fold(MulOp::FoldAdaptor adaptor) {
    auto lhs = dyn_cast_or_null<DenseIntElementsAttr>(adaptor.getOperands()[0]);
    auto rhs = dyn_cast_or_null<DenseIntElementsAttr>(adaptor.getOperands()[1]);

    if (!lhs || !rhs) return nullptr;

    auto degree = getResult().getType().cast<PolynomialTypeType>().getDegreeBound();
    auto maxIndex = lhs.size() + rhs.size() - 1;

    SmallVector<APInt, 8> result;
    result.reserve(maxIndex);
    for (int i = 0; i < maxIndex; ++i ) {
        result.push_back(APInt((*lhs.begin()).getBitWidth(), 0));
    }

    int i = 0;
    for (auto lhsIt = lhs.value_begin<APInt>(); lhsIt != lhs.value_end<APInt>();
        ++lhsIt) {
        int j = 0;
        for (auto rhsIt = rhs.value_begin<APInt>(); rhsIt != rhs.value_end<APInt>();
            ++rhsIt) {
        // index is modulo degree because poly's semantics are defined modulo x^N = 1.
        result[(i + j) % degree] += *rhsIt * (*lhsIt);
        ++j;
        }
        ++i;
    }

    return DenseIntElementsAttr::get(
        RankedTensorType::get(
            static_cast<int64_t>(result.size()),
            IntegerType::get(getContext(), 32)),
        result);
}

OpFoldResult FromTensorOp::fold(FromTensorOp::FoldAdaptor adaptor) {
    return dyn_cast_or_null<DenseIntElementsAttr>(adaptor.getInput());
}

LogicalResult EvalOp::verify() {
    auto pointTy = getPoint().getType();
    bool isSignlessInteger = pointTy.isSignlessInteger(32);
    auto complexPt = llvm::dyn_cast<ComplexType>(pointTy);
    return isSignlessInteger || complexPt ? success() : emitOpError(
                                              "argument point must be a 32-bit "
                                              "integer, or a complex number");
}

void AddOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &result, ::mlir::MLIRContext *context) {}

void SubOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &result, ::mlir::MLIRContext *context) {
    result.add<DifferenceOfSquares>(context);
}

void MulOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &result, ::mlir::MLIRContext *context) {}

void EvalOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &result, ::mlir::MLIRContext *context) {
    result.add<LiftConjThroughEval>(context);
}

} // namespace poly
} // namespace training
} // namespace mlir