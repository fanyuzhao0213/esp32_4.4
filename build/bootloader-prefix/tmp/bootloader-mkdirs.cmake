# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/bootloader/subproject"
  "G:/test_project/esp32_4.4/build/bootloader"
  "G:/test_project/esp32_4.4/build/bootloader-prefix"
  "G:/test_project/esp32_4.4/build/bootloader-prefix/tmp"
  "G:/test_project/esp32_4.4/build/bootloader-prefix/src/bootloader-stamp"
  "G:/test_project/esp32_4.4/build/bootloader-prefix/src"
  "G:/test_project/esp32_4.4/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "G:/test_project/esp32_4.4/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
