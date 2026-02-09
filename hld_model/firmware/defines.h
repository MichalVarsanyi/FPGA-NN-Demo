#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "nnet_utils/nnet_types.h"
#include <array>
#include <cstddef>
#include <cstdio>
#include <tuple>
#include <tuple>


// hls-fpga-machine-learning insert numbers

// hls-fpga-machine-learning insert layer-precision
typedef ap_fixed<16,6> input_t;
typedef ap_fixed<16,6> model_default_t;
typedef ap_fixed<38,18> model_1_result_t;
typedef ap_fixed<16,6> model_1_weight_t;
typedef ap_fixed<16,6> model_1_bias_t;
typedef ap_uint<1> layer3_index;
typedef ap_fixed<16,6> layer4_t;
typedef ap_fixed<18,8> model_2_table_t;
typedef ap_fixed<38,18> model_3_result_t;
typedef ap_fixed<16,6> model_3_weight_t;
typedef ap_fixed<16,6> model_3_bias_t;
typedef ap_uint<1> layer5_index;
typedef ap_fixed<16,6> layer6_t;
typedef ap_fixed<18,8> model_4_table_t;
typedef ap_fixed<37,17> result_t;
typedef ap_fixed<16,6> model_5_weight_t;
typedef ap_fixed<16,6> model_5_bias_t;
typedef ap_uint<1> layer7_index;

// hls-fpga-machine-learning insert emulator-defines


#endif
