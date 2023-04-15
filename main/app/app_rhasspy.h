#pragma once

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_err.h"
#include "secrets.h"
#include "app_api_mqtt.h"

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct rhasspy_session_struct
  {
    bool opened;
    char session_id[36];
  } rhasspy_session_struct;

  extern rhasspy_session_struct rhasspy_session;

  void rhasspy_start_session();

#ifdef __cplusplus
}
#endif