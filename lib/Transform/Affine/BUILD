
package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "AffineFullUnroll",
    srcs = ["AffineFullUnroll.cpp"],
    hdrs = ["AffineFullUnroll.hpp"],
    deps = [
        "@llvm-project//mlir:AffineDialect",
        "@llvm-project//mlir:AffineUtils",
        "@llvm-project//mlir:FuncDialect",
        "@llvm-project//mlir:Pass",
        "@llvm-project//mlir:Transforms"
    ],
)