""" macro to import LLVM """
load(
    "@bazel_tools//tools/build_defs/repo:git.bzl",
    "new_git_repository"
)

def import_llvm(name):
    """ import llvm """

    LLVM_COMMIT = "cd5fcea6d4c70a7328ca9538c9098d9f5af69682"

    new_git_repository(
        name = name,
        # this build file is empty, because LLVM project
        # internally contains a set of bazel BUILD files overlaying the project
        build_file_content = "# empty",
        commit = LLVM_COMMIT,
        init_submodules = False,
        remote = "https://github.com/llvm/llvm-project.git"
    )