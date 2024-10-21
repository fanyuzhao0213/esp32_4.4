# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/esp_idf_v4.4/v4.4.8/esp-idf/components/bootloader/subproject"
  "E:/esp32_project/esp32_4.4/build/bootloader"
  "E:/esp32_project/esp32_4.4/build/bootloader-prefix"
  "E:/esp32_project/esp32_4.4/build/bootloader-prefix/tmp"
  "E:/esp32_project/esp32_4.4/build/bootloader-prefix/src/bootloader-stamp"
  "E:/esp32_project/esp32_4.4/build/bootloader-prefix/src"
  "E:/esp32_project/esp32_4.4/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/esp32_project/esp32_4.4/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
