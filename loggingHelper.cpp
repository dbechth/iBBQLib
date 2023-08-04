#include "loggingHelper.h"

int vprintf_into_SD(const char *szFormat, va_list args)
{
    //write evaluated format string into buffer
    int ret = vsnprintf(log_print_buffer, sizeof(log_print_buffer), szFormat, args);

    //output is now in buffer. write to file.
    if (ret >= 0)
    {
        if (!SD_MMC.exists("/LOGS.txt"))
        {
            File writeLog = SD_MMC.open("/LOGS.txt", FILE_WRITE);
            if (!writeLog)
                Serial.println("Couldn't open LOGS.txt");
            delay(50);
            writeLog.close();
        }

        File SDLogFile = SD_MMC.open("/LOGS.txt", FILE_APPEND);
        //debug output
        printf("[Writing to SD_MMC] %.*s\r\n", ret, log_print_buffer);
        SDLogFile.write((uint8_t *)log_print_buffer, (size_t)ret);
        SDLogFile.println("");
        //to be safe in case of crashes: flush the output
        SDLogFile.flush();
        SDLogFile.close();
    }
    return ret;
}

int vprintf_into_spiffs(const char *szFormat, va_list args)
{
    //write evaluated format string into buffer
    int ret = vsnprintf(log_print_buffer, sizeof(log_print_buffer), szFormat, args);

    //output is now in buffer. write to file.
    if (ret >= 0)
    {
        if (!SPIFFS.exists("/LOGS.txt"))
        {
            File writeLog = SPIFFS.open("/LOGS.txt", FILE_WRITE);
            if (!writeLog)
                Serial.println("Couldn't open spiffs_log.txt");
            delay(50);
            writeLog.close();
        }

        File spiffsLogFile = SPIFFS.open("/LOGS.txt", FILE_APPEND);
        //debug output
        //printf("[Writing to SPIFFS] %.*s", ret, log_print_buffer);
        spiffsLogFile.write((uint8_t *)log_print_buffer, (size_t)ret);
        //to be safe in case of crashes: flush the output
        spiffsLogFile.flush();
        spiffsLogFile.close();
    }
    return ret;
}

void setLogLevel(){
    // esp_log_level_set("TAG", ESP_LOG_DEBUG);
    esp_log_level_set("*", ESP_LOG_ERROR);  
    esp_log_level_set("BBQ",ESP_LOG_DEBUG);
}