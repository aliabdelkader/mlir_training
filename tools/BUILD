# the tools directory contains binary targets that expose public api of
# the passes in the project

package(
    default_visibility = ["//visibility:public"],
)

# we name the tool `mlir-training-opt`
cc_binary(
    name = "mlir-training-opt",
    srcs = ["mlir-training-opt.cpp"],
    includes = ["include"],
    deps = [
        "//lib/Conversion/PolyToStandard",
        "//lib/Dialect/Poly",
        "//lib/Transform/Affine:Passes",
        "//lib/Transform/Arith:Passes",
        "@llvm-project//mlir:AllPassesAndDialects",
        "@llvm-project//mlir:ArithToLLVM",
        "@llvm-project//mlir:BufferizationPipelines",
        "@llvm-project//mlir:BufferizationTransforms",
        "@llvm-project//mlir:ControlFlowToLLVM",
        "@llvm-project//mlir:FuncToLLVM",
        "@llvm-project//mlir:LinalgTransforms",
        "@llvm-project//mlir:MemRefToLLVM",
        "@llvm-project//mlir:MemRefTransforms",
        "@llvm-project//mlir:MlirOptLib",
        "@llvm-project//mlir:Pass",
        "@llvm-project//mlir:SCFToControlFlow",
        "@llvm-project//mlir:TensorToLinalg",
    ],
)