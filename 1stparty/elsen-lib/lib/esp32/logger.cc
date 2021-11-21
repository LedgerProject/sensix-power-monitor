#include "logger.hh"

#include <esp_log.h>

using namespace elsen;

void Logger::platform_log_trace(const char *application_id, const char *message)
{
    ESP_LOGV(application_id, "%s", message);
}

void Logger::platform_log_debug(const char *application_id, const char *message)
{
    ESP_LOGD(application_id, "%s", message);
}

void Logger::platform_log_info(const char *application_id, const char *message)
{
    ESP_LOGI(application_id, "%s", message);
}

void Logger::platform_log_warn(const char *application_id, const char *message)
{
    ESP_LOGW(application_id, "%s", message);
}

void Logger::platform_log_error(const char *application_id, const char *message)
{
    ESP_LOGE(application_id, "%s", message);
}