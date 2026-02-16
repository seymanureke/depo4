#include <stdio.h>
#include "tensor.h"

int main() {
    printf("--- TinyML Dinamik Tensor Demo ---\n");

    // 1. 2x2'lik bir float tensör oluştur
    Tensor* my_tensor = create_tensor(2, 2);
    my_tensor->data.f32[0] = 1.5f;
    my_tensor->data.f32[1] = 2.7f;
    my_tensor->data.f32[2] = 0.0f;
    my_tensor->data.f32[3] = -1.2f;

    printf("Orijinal (Float32): ");
    print_tensor(my_tensor);

    // 2. Quantize et (Belleği daralt)
    quantize_tensor(my_tensor);

    printf("Quantized (Int8): ");
    print_tensor(my_tensor);

    return 0;
}