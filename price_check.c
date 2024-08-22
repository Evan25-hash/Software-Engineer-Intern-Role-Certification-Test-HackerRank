#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

float parse_float(char*);
int parse_int(char*);

/*
 * Complete the 'priceCheck' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY products
 *  2. FLOAT_ARRAY productPrices
 *  3. STRING_ARRAY productSold
 *  4. FLOAT_ARRAY soldPrice
 */

int priceCheck(int products_count, char** products, int productPrices_count, float* productPrices, int productSold_count, char** productSold, int soldPrice_count, float* soldPrice) {
    int error_count = 0;
    for (int i = 0; i < productSold_count; i++) {
        int index = -1;
        for (int j = 0; j < products_count; j++) {
            if (strcmp(productSold[i], products[j]) == 0) {
                index = j;
                break;
                }
    }    
        if (index != -1 && productPrices[index] != soldPrice[i]) {
            error_count++;
        }
    }
    return error_count;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    int products_count = parse_int(ltrim(rtrim(readline())));
    char** products = malloc(products_count * sizeof(char*));
    for (int i = 0; i < products_count; i++) {
        char* products_item = readline();
        *(products + i) = products_item;
    }
    int productPrices_count = parse_int(ltrim(rtrim(readline())));
    float* productPrices = malloc(productPrices_count * sizeof(float));
    for (int i = 0; i < productPrices_count; i++) {
        float productPrices_item = parse_float(ltrim(rtrim(readline())));
        *(productPrices + i) = productPrices_item;
    }
    int productSold_count = parse_int(ltrim(rtrim(readline())));
    char** productSold = malloc(productSold_count * sizeof(char*));
    for (int i = 0; i < productSold_count; i++) {
        char* productSold_item = readline();
        *(productSold + i) = productSold_item;
    }
    int soldPrice_count = parse_int(ltrim(rtrim(readline())));
    float* soldPrice = malloc(soldPrice_count * sizeof(float));
    for (int i = 0; i < soldPrice_count; i++) {
        float soldPrice_item = parse_float(ltrim(rtrim(readline())));
        *(soldPrice + i) = soldPrice_item;
    }

    int result = priceCheck(products_count, products, productPrices_count, productPrices, productSold_count, productSold, soldPrice_count, soldPrice);
    fprintf(fptr, "%d\n", result);
    fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;
        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

float parse_float(char* str) {
    char* endptr;
    float value = strtof(str, &endptr);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
