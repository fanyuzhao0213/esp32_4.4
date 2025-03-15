# idf_component_register(SRCS "main.c" "my_gui.c" "img_cool.c" "img_dry.c" "img_warm.c" "my_weather.c"
#                     INCLUDE_DIRS ".")
file(GLOB_RECURSE srcs *.c
                    GUI/custom/*.c
                    GUI/generated/*.c
                    GUI/generated/guider_customer_fonts/*.c
                    GUI/generated/guider_fonts/*.c
                    GUI/generated/images/*.c
                    )

set(include_dirs
    .
    GUI/custom
    GUI/generated
    GUI/generated/guider_customer_fonts
    GUI/generated/guider_fonts
    GUI/generated/images
    )

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    )
