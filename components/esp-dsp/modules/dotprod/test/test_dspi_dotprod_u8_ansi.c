// Copyright 2018-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string.h>
#include "unity.h"
#include "dsp_platform.h"
#include "esp_log.h"

#include "dspi_dotprod.h"
#include "dsp_tests.h"

static const char *TAG = "";

TEST_CASE("dspi_dotprod_u8_ansi functionality", "[dspi]")
{
    uint8_t check_value1 = 67;
    uint8_t check_value2 = 73;
    int shift = 7;

    int max_N = 1024;
    uint8_t *x = (uint8_t *)malloc(max_N * sizeof(uint8_t));
    uint8_t *y = (uint8_t *)malloc(max_N * sizeof(uint8_t));
    uint8_t *z = (uint8_t *)malloc(max_N * sizeof(uint8_t));
    for (size_t i = 0; i < 256; i++) {
        x[i] = i % 8 + 20;
        y[i] = i % 8 + 20;
        z[i] = 0;
    }
    image2d_t image1 = {x, 2, 2, 8, 8, 8, 8}; // Image 8x8
    image2d_t image2 = {y, 2, 2, 8, 8, 8, 8}; // Umage 8x8
    uint8_t result = -1;
    dspi_dotprod_u8_ansi(&image1, &image2, &result, 4, 4, shift);
    ESP_LOGI(TAG, "result 1 = %i", result);
    TEST_ASSERT_EQUAL( result, check_value1);
    image1.data = &x[1];
    image2.data = &y[1];
    result = -1;
    dspi_dotprod_u8_ansi(&image1, &image2, &result, 4, 4, shift);
    ESP_LOGI(TAG, "result 2 = %i", (int)result);
    TEST_ASSERT_EQUAL( result, check_value2);
    image1.data = &x[image1.stride_x];
    image2.data = &y[image2.stride_x];
    result = -1;
    dspi_dotprod_u8_ansi(&image1, &image2, &result, 4, 4, shift);
    ESP_LOGI(TAG, "result 3 = %i", (int)result);
    TEST_ASSERT_EQUAL( result, check_value1);
    image1.data = &x[image1.stride_x + 1];
    image2.data = &y[image2.stride_x + 1];
    result = -1;
    dspi_dotprod_u8_ansi(&image1, &image2, &result, 4, 4, shift);
    ESP_LOGI(TAG, "result 4 = %i", (int)result);
    TEST_ASSERT_EQUAL( result, check_value2);

    free(x);
    free(y);
    free(z);
}
