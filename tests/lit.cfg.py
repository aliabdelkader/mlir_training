import os
from pathlib import Path
from lit.formats import ShTest

config.name = "mlir_training"
config.test_format = ShTest()
config.suffixes = [".mlir"]


import subprocess

# print(subprocess.run(["pwd",]).stdout)
# print(subprocess.run(["echo", os.environ["RUNFILES_DIR"]]).stdout)
# print(subprocess.run(["ls", "-l", os.environ["RUNFILES_DIR"]]).stdout)
# print(subprocess.run([ "env", ]).stdout)

runfiles_dir = Path(os.environ["RUNFILES_DIR"])
tool_relpaths = [
    "llvm-project/mlir",
    "llvm-project/llvm",
    "llvm-project/clang",
    "mlir_training/tools",
]

config.environment["PATH"] = (
    ":".join(
        str(runfiles_dir.joinpath(Path(path))) for path in tool_relpaths
    )
    + ":"
    + os.environ["PATH"]
)


substitutions = {
    "%project_source_dir": runfiles_dir.joinpath(Path('mlir_training')),
}
config.substitutions.extend(substitutions.items())