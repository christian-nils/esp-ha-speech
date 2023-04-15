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
    app_api_mqtt_send(&"hermes/dialogueManager/startSession", payload);
  }
  else
  {
    ESP_LOGI(TAG, "reuse opened session: %s", rhasspy_session.session_id);
  }
  return;
}

// void rhasspy_set_session(rhasspy_session_struct *_rhasspy_session)
// {
//   rhasspy_session.opened = _rhasspy_session->opened;
//   strcpy(rhasspy_session.session_id, _rhasspy_session->session_id);
//   return;
// }