set(src_dirs
            LED
            KEY
            ESPTIM
            PWM
            UART
            WIFI
            WEATHER
            MQTT
            IIC
            QMI8658
            RTC
            SD
            ADC
            PWR_KEY
            BLE)

set(include_dirs
            LED
            KEY
            ESPTIM
            PWM
            UART
            WIFI
            WEATHER
            MQTT
            IIC
            QMI8658
            RTC
            SD
            ADC
            PWR_KEY
            BLE)

set(requires
            driver
            esp_timer
            esp_lcd
            nvs_flash
            esp_wifi
            esp_http_client
            json
            mqtt
            fatfs
            esp_adc_cal
            bt)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)