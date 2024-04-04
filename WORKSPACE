workspace(name = "mlir_training")

load(
    "@bazel_tools//tools/build_defs/repo:http.bzl",
    "http_archive"
)

load(
    "@bazel_tools//tools/build_defs/repo:utils.bzl",
    "maybe"
)

load(
    "@bazel_tools//tools/build_defs/repo:git.bzl", 
    "new_git_repository"
)

# setup skylib
http_archive(
    name = "bazel_skylib",
    sha256 = "74d544d96f4a5bb630d465ca8bbcfe231e3594e5aae57e1edbf17a6eb3ca2506",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()
# build llvm
# 1- download llvm code and add it to workspace as git repo
# 2- build file are overlaid using llvm_configure in the setup script
# 3- llvm-project bazel project is defined and can be built
load("//bazel:import_llvm.bzl", "import_llvm")

import_llvm("llvm-raw")

load("//bazel:setup_llvm.bzl", "setup_llvm")

setup_llvm("llvm-project")

maybe(
    http_archive,
    name = "llvm_zstd",
    build_file = "@llvm-raw//utils/bazel/third_party_build:zstd.BUILD",
    sha256 = "7c42d56fac126929a6a85dbc73ff1db2411d04f104fae9bdea51305663a83fd0",
    strip_prefix = "zstd-1.5.2",
    urls = [
        "https://github.com/facebook/zstd/releases/download/v1.5.2/zstd-1.5.2.tar.gz",
    ],
)

maybe(
    http_archive,
    name = "llvm_zlib",
    build_file = "@llvm-raw//utils/bazel/third_party_build:zlib-ng.BUILD",
    sha256 = "e36bb346c00472a1f9ff2a0a4643e590a254be6379da7cddd9daeb9a7f296731",
    strip_prefix = "zlib-ng-2.0.7",
    urls = [
        "https://github.com/zlib-ng/zlib-ng/archive/refs/tags/2.0.7.zip",
    ],
)

# Hedron's Compile Commands Extractor for Bazel ( COPIED )
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",

    # Replace the commit hash (0e990032f3c5a866e72615cf67e5ce22186dcb97) in both places (below) with the latest (https://github.com/hedronvision/bazel-compile-commands-extractor/commits/main), rather than using the stale one here.
    # Even better, set up Renovate and let it do the work for you (see "Suggestion: Updates" in the README).
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/0e990032f3c5a866e72615cf67e5ce22186dcb97.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-0e990032f3c5a866e72615cf67e5ce22186dcb97",
    # When you first run this tool, it'll recommend a sha256 hash to put here with a message like: "DEBUG: Rule 'hedron_compile_commands' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = ..."
)
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()
load("@hedron_compile_commands//:workspace_setup_transitive.bzl", "hedron_compile_commands_setup_transitive")
hedron_compile_commands_setup_transitive()
load("@hedron_compile_commands//:workspace_setup_transitive_transitive.bzl", "hedron_compile_commands_setup_transitive_transitive")
hedron_compile_commands_setup_transitive_transitive()
load("@hedron_compile_commands//:workspace_setup_transitive_transitive_transitive.bzl", "hedron_compile_commands_setup_transitive_transitive_transitive")
hedron_compile_commands_setup_transitive_transitive_transitive()

# setup python hermetic
new_git_repository(
    name = "rules_python",
    commit = "9ffb1ecd9b4e46d2a0bca838ac80d7128a352f9f", # v0.23.1
    remote = "https://github.com/bazelbuild/rules_python.git"
)

load(
    "@rules_python//python:repositories.bzl",
    "python_register_toolchains"
)

python_register_toolchains(
    name = "python3_10",
    # Available versions are listed at
    # https://github.com/bazelbuild/rules_python/blob/main/python/versions.bzl
    python_version = "3.10"
)

load(
    "@python3_10//:defs.bzl",
    "interpreter"
)

load(
    "@rules_python//python:pip.bzl",
    "pip_parse"
)

pip_parse(
    name = "mlir_training_pip_deps",
    python_interpreter_target = interpreter,
    requirements_lock = "//:requirements.txt"
)

load(
    "@mlir_training_pip_deps//:requirements.bzl",
    "install_deps"
)

install_deps()
