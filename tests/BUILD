load("//bazel:lit.bzl", "glob_lit_tests")

filegroup(
    name = "test_utilities",
    testonly = True,
    data = [
        "//tests:lit.cfg.py",
        "@llvm-project//llvm:FileCheck",
        "@llvm-project//llvm:count",
        "@llvm-project//llvm:not",
        "@llvm-project//mlir:mlir-cpu-runner",
        "@llvm-project//mlir:mlir-opt",
        "@mlir_training_pip_deps_lit//:pkg",
        "//tools:mlir-training-opt"
    ],
)

glob_lit_tests()