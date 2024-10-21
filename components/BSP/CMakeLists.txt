set(src_dirs
            LED
            KEY
            ESPTIM
            PWM
            UART
            WIFI
            WEATHER
            MQTT)

set(include_dirs
            LED
            KEY
            ESPTIM
            PWM
            UART
            WIFI
            WEATHER
            MQTT)

set(requires
            driver
            esp_timer
            esp_lcd
            nvs_flash
            esp_wifi
            esp_http_client
            json
            mqtt)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)