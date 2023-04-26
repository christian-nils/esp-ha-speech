#include "app_rhasspy.h"

static const char *TAG = "app_api_mqtt";
rhasspy_session_struct rhasspy_session = {
    .opened = 0,
    .session_id = "00000000-0000-0000-0000-000000000000"};

void rhasspy_start_session()
{
  // start a session with Rhasspy, this needs to be done after the hotword is detected. Mute the mic, wait for Rhasspy dialogue manager to reply with the new session Id, then play the WAKE sound. Unmute the mic. Sample the mic data and send it to MQTT broker via the topic hermes/audioServer/SITE_ID/audioFrame, see https://github.com/Romkabouter/ESP32-Rhasspy-Satellite/blob/df4cd1f90fc39999fb6fe77663e7359b10aef47e/PlatformIO/src/StateMachine.hpp#L877-L880
  if (rhasspy_session.opened == 0)
  {
    char *payload = malloc(1000);
    sprintf(payload, "{\"init\":{\"type\":\"action\",\"canBeEnqueued\": false},\"siteId\":\"%s\"}", MQTT_SITE_ID);
    app_api_mqtt_send(&"hermes/dialogueManager/startSession", payload, 0);
  }
  else
  {
    ESP_LOGI(TAG, "reuse opened session: %s", rhasspy_session.session_id);
  }
  return;
}

void rhasspy_send_audio_frame(uint8_t *payload, int len)
{
  if (rhasspy_session.opened == 1)
  {
    char *audio_topic = malloc(strlen(MQTT_SITE_ID) + 30);
    sprintf(audio_topic, "hermes/audioServer/%s/audioFrame", MQTT_SITE_ID);
    app_api_mqtt_send(audio_topic, (char *)payload, len); // important to set the length (because the uint8 does not have a null termination as a char array can have), otherwise there will be some issue when using the auto detection of the length. This was seen on https://github.com/nopnop2002/esp-idf-mqtt-camera/blob/fd3582061b3feb2b23e6318cabf66984a4fc0929/main/main.c#L553.
  }
  else
  {
    ESP_LOGI(TAG, "Error, cannot send the audio frame, the dialogue session is not opened.");
  }
}
// void rhasspy_set_session(rhasspy_session_struct *_rhasspy_session)
// {
//   rhasspy_session.opened = _rhasspy_session->opened;
//   strcpy(rhasspy_session.session_id, _rhasspy_session->session_id);
//   return;
// }