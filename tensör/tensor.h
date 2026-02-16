//
// Created by Şeymanur Eke on 16.02.2026.
//
#ifndef TENSOR_H
#define TENSOR_H

#include <stdint.h>
#include <stdlib.h>

// 1. Veri Tiplerini Tanımla
typedef enum {
    TENSOR_FLOAT32,
    TENSOR_INT8     // Sıkıştırılmış veri
} TensorType;

// 2. Dinamik Tensör Yapısı
typedef struct {
    TensorType type;
    uint16_t rows;
    uint16_t cols;
    float scale;        // Quantization katsayısı
    int8_t zero_point;  // Quantization kayması

    union {
        float* f32;     // Normal veriler için
        int8_t* i8;     // Quantized veriler için
    } data;
} Tensor;

// 3. Fonksiyon Prototipleri
Tensor* create_tensor(uint16_t rows, uint16_t cols);
void quantize_tensor(Tensor* t);
void print_tensor(Tensor* t);
void free_tensor(Tensor* t);

#endif
//UNTITLED57_TENSOR_H