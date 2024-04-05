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
        "//lib/Transform/Affine:AffineFullUnroll",
        "//lib/Transform/Arith:MulToAdd",
        "@llvm-project//mlir:AllPassesAndDialects",
        "@llvm-project//mlir:MlirOptLib",
        "@llvm-project//mlir:Pass"
    ],
)