""" configure llvm bazel overlays from a raw import llvm repo """ 

load(
    "@llvm-raw//utils/bazel:configure.bzl",
    "llvm_configure"
)

_LLVM_TARGETS = [
    "X86",
    # The bazel dependency graph for mlir-opt fails to load (at the analysis
    # step) without the NVPTX target in this list
    "NVPTX",
]

def setup_llvm(name):
    """ build @llvm-project from @llvm-raw using the upstream bazel overlays"""
    llvm_configure(
        name = name,
        targets = _LLVM_TARGETS
    )