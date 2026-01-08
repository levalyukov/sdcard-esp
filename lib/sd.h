#ifndef SDCARD_H
#define SDCARD_H

#include <stdint.h>
#include "esp_err.h"
#include "esp_vfs_fat.h"
#include "driver/gpio.h"
#include "driver/sdspi_host.h"
#include "driver/sdmmc_host.h"
#include "driver/spi_master.h"

#define SD_MAX_MOUNT_ATTEMPS 10

typedef struct {
  gpio_num_t cs,sck,mosi,miso;
  sdmmc_card_t* card;
  sdmmc_host_t hostcfg;
  spi_bus_config_t buscfg;
  sdspi_device_config_t devcfg;
  esp_vfs_fat_sdmmc_mount_config_t mountcfg;
  sdmmc_slot_config_t slotcfg;
} sdcard;

extern sdcard* sd;

esp_err_t sdcard_init(gpio_num_t cs, gpio_num_t sck, gpio_num_t mosi, gpio_num_t miso);
esp_err_t sdcard_spi_connect(sdcard* sd);

#endif