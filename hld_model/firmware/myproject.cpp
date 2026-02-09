#include <iostream>

#include "myproject.h"
#include "parameters.h"


void myproject(
    input_t x[5*5],
    result_t layer7_out[10]
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS ARRAY_RESHAPE variable=x complete dim=0
    #pragma HLS ARRAY_PARTITION variable=layer7_out complete dim=0
    #pragma HLS INTERFACE ap_vld port=x,layer7_out 
    #pragma HLS PIPELINE

    // hls-fpga-machine-learning insert load weights
#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        nnet::load_weights_from_txt<model_1_weight_t, 800>(w3, "w3.txt");
        nnet::load_weights_from_txt<model_1_bias_t, 32>(b3, "b3.txt");
        nnet::load_weights_from_txt<model_3_weight_t, 512>(w5, "w5.txt");
        nnet::load_weights_from_txt<model_3_bias_t, 16>(b5, "b5.txt");
        nnet::load_weights_from_txt<model_5_weight_t, 160>(w7, "w7.txt");
        nnet::load_weights_from_txt<model_5_bias_t, 10>(b7, "b7.txt");
        loaded_weights = true;    }
#endif
    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    auto& layer2_out = x;
    model_1_result_t layer3_out[32];
    #pragma HLS ARRAY_PARTITION variable=layer3_out complete dim=0

    layer4_t layer4_out[32];
    #pragma HLS ARRAY_PARTITION variable=layer4_out complete dim=0

    model_3_result_t layer5_out[16];
    #pragma HLS ARRAY_PARTITION variable=layer5_out complete dim=0

    layer6_t layer6_out[16];
    #pragma HLS ARRAY_PARTITION variable=layer6_out complete dim=0

    nnet::dense<input_t, model_1_result_t, config3>(layer2_out, layer3_out, w3, b3); // model_1

    nnet::relu<model_1_result_t, layer4_t, relu_config4>(layer3_out, layer4_out); // model_2

    nnet::dense<layer4_t, model_3_result_t, config5>(layer4_out, layer5_out, w5, b5); // model_3

    nnet::relu<model_3_result_t, layer6_t, relu_config6>(layer5_out, layer6_out); // model_4

    nnet::dense<layer6_t, result_t, config7>(layer6_out, layer7_out, w7, b7); // model_5

}

