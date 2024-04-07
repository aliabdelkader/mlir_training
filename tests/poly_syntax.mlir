// RUN: mlir-training-opt %s

module {
    func.func @main(%arg0: !poly.poly<10>) -> !poly.poly<10> {
        return %arg0 : !poly.poly<10>
    }

    // CHECK-LABEL: test_op_syntax
    func.func @test_binop_syntax(%arg0 : !poly.poly<10>, %arg1 : !poly.poly<10>) -> !poly.poly<10> {
        // CHECK: poly.add
        %0 = poly.add %arg0, %arg1 : (!poly.poly<10>, !poly.poly<10>) -> !poly.poly<10>
        // CHECK: poly.sub
        %1 = poly.sub %arg0, %arg1 : (!poly.poly<10>, !poly.poly<10>) -> !poly.poly<10>
        // CHECK: poly.mul
        %2 = poly.mul %arg0, %arg1 : (!poly.poly<10>, !poly.poly<10>) -> !poly.poly<10>
        %3 = arith.constant dense<[1, 2, 3]> : tensor<3xi32>
        // check: poly.from_tensor
        %4 = poly.from_tensor %3 : tensor<3xi32> -> !poly.poly<10>
        %5 = arith.constant 7 : i32
        // CHECK: poly.eval
        %6 = poly.eval %4, %5 : (!poly.poly<10>, i32) -> i32

        return %4 : !poly.poly<10>
    }
}