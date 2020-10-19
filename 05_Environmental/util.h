#pragma once
#include <stdbool.h>

typedef char* String;
#define new(type) malloc(sizeof(type))
#define newa(type, size) malloc(sizeof(type) * size)
#define static_cast(T) (T)
#define nullptr NULL
