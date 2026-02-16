//
// Created by Şeymanur Eke on 16.02.2026.

#include "tensor.h"
#include <stdio.h>
#include <math.h>

// Tensör oluşturma
Tensor* create_tensor(uint16_t rows, uint16_t cols) {
    Tensor* t = (Tensor*)malloc(sizeof(Tensor));
    t->type = TENSOR_FLOAT32;
    t->rows = rows;
    t->cols = cols;
    t->data.f32 = (float*)malloc(rows * cols * sizeof(float));
    return t;
}

// Float32 -> Int8 Dönüşümü (Quantization)
void quantize_tensor(Tensor* t) {
    if (t->type != TENSOR_FLOAT32) return;

    size_t size = t->rows * t->cols;
    float* old_data = t->data.f32;

    // Basit bir scale hesabı (Örnek amaçlı sabit değerler)
    t->scale = 0.1f;
    t->zero_point = 0;

    // Yeni bellek alanı (Int8 için)
    int8_t* new_data = (int8_t*)malloc(size * sizeof(int8_t));

    for (size_t i = 0; i < size; i++) {
        // Formül: Q = (V / S) + Z
        new_data[i] = (int8_t)(old_data[i] / t->scale + t->zero_point);
    }

    // ESKİ BELLEĞİ BOŞALT VE YENİSİNE GEÇ (Union'ın gücü)
    free(old_data);
    t->data.i8 = new_data;
    t->type = TENSOR_INT8;

    printf("\n[Sistem] Quantization tamamlandi. Bellek %75 oraninda kucultuldu!\n");
}

void print_tensor(Tensor* t) {
    for (int i = 0; i < t->rows * t->cols; i++) {
        if (t->type == TENSOR_FLOAT32) printf("%.2f ", t->data.f32[i]);
        else printf("%d ", t->data.i8[i]);
    }
    printf("\n");
}