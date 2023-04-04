#pragma once
#include <esp_err.h>

#ifdef __cplusplus
extern "C"
{
#endif

  void app_hass_init();
  bool app_hass_is_connected(void);

  void app_hass_send_cmd(char *cmd);

  void app_hass_add_cmd(char *msg);
  void app_hass_rm_all_cmd();
  void app_hass_speaker_mute_cmd();
  void app_hass_mic_mute_cmd();

#ifdef __cplusplus
}
#endif
