#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "clog.h"
#include "opus.h"

namespace {
struct OpusEncoder* g_opus_encoder = nullptr;
constexpr uint32_t kAudioSampleRate = 16000;
constexpr uint32_t kAudioFrameMs = 60;
constexpr uint32_t kOpusComplexity = 3;

void AudioDecoderThread(void*) {
  CLOG();
  uint32_t opus_samples_size = kAudioSampleRate / 1000 * kAudioFrameMs;
  int16_t* opus_samples = new int16_t[opus_samples_size];

  int opus_bits_size = 1500;
  uint8_t* opus_bits = new uint8_t[opus_bits_size];

  while (true) {
    auto ret = opus_encode(g_opus_encoder, opus_samples, opus_samples_size,
                           opus_bits, opus_bits_size);
    CLOG("ret: %d", ret);
    delay(1);
  }
}
}  // namespace

void setup() {
  Serial.begin(115200);
  CLOG("setup");
  int error = 0;
  g_opus_encoder = opus_encoder_create(16000, 1, OPUS_APPLICATION_VOIP, &error);
  opus_encoder_ctl(g_opus_encoder, OPUS_SET_DTX(1));
  opus_encoder_ctl(g_opus_encoder, OPUS_SET_COMPLEXITY(kOpusComplexity));

  xTaskCreate(AudioDecoderThread, "AudioDecoderThread", 4096 * 8, nullptr,
              tskIDLE_PRIORITY, nullptr);
}

void loop() {}