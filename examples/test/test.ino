#include "opus.h"

void setup() {
  opus_encoder_create(0, 0, OPUS_APPLICATION_VOIP, nullptr);
  opus_encode(nullptr, nullptr, 0, nullptr, 0);
  opus_encoder_ctl(nullptr, OPUS_RESET_STATE);
  opus_encoder_ctl(nullptr, OPUS_SET_DTX(1));
  opus_encoder_ctl(nullptr, OPUS_SET_COMPLEXITY(3));
  opus_encoder_destroy(nullptr);
  opus_decoder_create(0, 0, nullptr);
  opus_decode(nullptr, nullptr, 0, nullptr, 0, 0);
  opus_decoder_ctl(nullptr, OPUS_RESET_STATE);
}

void loop() {}