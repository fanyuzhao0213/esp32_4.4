# Install script for directory: F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/main")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "F:/esp_idf_4.4.8/tools/tools/xtensa-esp32s3-elf/esp-2021r2-patch5-8.4.0/xtensa-esp32s3-elf/bin/xtensa-esp32s3-elf-objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aesni.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/arc4.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/blowfish.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bn_mul.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/certs.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher_internal.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-1.3.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp_internal.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy_poll.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/havege.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md2.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md4.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md_internal.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/padlock.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk_internal.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs11.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa_internal.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_internal.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/mbedtls/xtea.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "F:/esp_idf_4.4.8/v4.4.8/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()
