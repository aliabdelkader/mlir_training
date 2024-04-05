// RUN: mlir-training-opt %s --mul-to-add > %t
// RUN FileCheck %s < %t
func.func @just_power_of_two(%arg: i32) -> i32 {
    %0 = arith.constant 8 : i32
    %1 = arith.muli %arg, %0 : i32
    func.return %1 : i32
}
// CHECK-LABEL: func.func @just_power_of_two(%[[ARG:.*]]: i32) -> i32 {
// CHECK:           %[[SUM_0:.*]] = arith.addi %[[ARG]], %[[ARG]]
// CHECK:           %[[SUM_1:.*]] = arith.addi %[[SUM_0]], %[[SUM_0]]
// CHECK:           %[[SUM_2:.*]] = arith.addi %[[SUM_1]], %[[SUM_1]]
// CHECK:           return %[[SUM_2]] : i32
// CHECK:       }

func.func @power_of_two_plus_one(%arg: i32) -> i32 {
    %0 = arith.constant 9 : i32
    %1 = arith.muli %arg, %0 : i32
    func.return %1 : i32
}

// CHECK-LABEL:  func.func @power_of_two_plus_one(%[[ARG:.*]] : i32) -> i32 {
// CHECK:           %[[SUM_0:.*]] = arith.addi %[[ARG]], %[[ARG]]
// CHECK:           %[[SUM_1:.*]] = arith.addi %[[SUM_0]], %[[SUM_0]]
// CHECK:           %[[SUM_2:.*]] = arith.addi %[[SUM_1]], %[[SUM_1]]
// CHECK:           %[[SUM_3:.*]] = arith.addi %[[SUM_2]], %[[SUM_2]]
// CHECK:           return %[[SUM_3]] : i32
// CHECK:       }


// RUN: mlir-training-opt %s -pass-pipeline="builtin.module(func.func(mul-to-add,convert-scf-to-cf, convert-arith-to-llvm), convert-func-to-llvm, convert-cf-to-llvm, reconcile-unrealized-casts)" \
// RUN: | mlir-cpu-runner -e test_power_of_two_plus_one -entry-point-result=i32 > %t
// RUN: FileCheck %s --check-prefix=CHECK_test_power_of_two_plus_one < %t
func.func @test_power_of_two_plus_one() -> i32 {
    %0 = arith.constant 12 : i32
    %1 = func.call @power_of_two_plus_one(%0) : (i32) -> i32
    func.return %1 : i32
}
// CHECK_test_power_of_two_plus_one: 108
