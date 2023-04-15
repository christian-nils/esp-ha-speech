#pragma once
#include "esp_err.h"
#include "secrets.h"
#include "app_rhasspy.h"
#include "cJSON.h"

#ifdef __cplusplus
extern "C"
{
#endif

  // string audioFrameTopic("hermes/audioServer/" + MQTT_SITE_ID + "/audioFrame");
  // string playBytesTopic = "hermes/audioServer/" + MQTT_SITE_ID + "/playBytes/#";
  // string playFinishedTopic = "hermes/audioServer/" + MQTT_SITE_ID + "/playFinished";
  // std::string hotwordTopic = "hermes/hotword/#";
  // std::string audioTopic = MQTT_SITE_ID + std::string("/audio");
  // std::string restartTopic = MQTT_SITE_ID + std::string("/restart");
  // std::string sayTopic = "hermes/tts/say";
  // std::string sayFinishedTopic = "hermes/tts/sayFinished";
  // std::string errorTopic = "hermes/nlu/intentNotRecognized";
  // std::string setVolumeTopic = "rhasspy/audioServer/setVolume";

  void app_api_mqtt_start(void);
  void app_api_mqtt_send_cmd(char *topic, char *payload);
  void app_api_mqtt_send(char *topic, char *payload);
#ifdef __cplusplus
}
#endif
