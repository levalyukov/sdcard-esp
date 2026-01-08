#include "sd.h"

sdcard* sd = NULL;
esp_err_t sdcard_init(gpio_num_t cs, gpio_num_t sck, 
  gpio_num_t mosi, gpio_num_t miso) {
  sd = (sdcard*)malloc(sizeof(sdcard));
  if (!sd) {
    printf("Error while allocate sdcard struct.\n");
    return ESP_FAIL;
  }; 

  sd->cs = cs;
  sd->sck = sck;
  sd->mosi = mosi;
  sd->miso = miso;

  if (sdcard_spi_connect(sd) != ESP_OK) {
    printf("Error initializing the spi interface of the sd card.\n");
    return ESP_FAIL;
  }; return ESP_OK;
};

esp_err_t sdcard_spi_connect(sdcard* sd) {
  if (!sd) {
    printf("SD is NULL of sdcard.\n");
    return ESP_FAIL;
  };

  sd->hostcfg = (sdmmc_host_t)SDSPI_HOST_DEFAULT();
  sd->hostcfg.max_freq_khz = 200;
  sd->hostcfg.command_timeout_ms = 10000;

  sd->devcfg = (sdspi_device_config_t)SDSPI_DEVICE_CONFIG_DEFAULT();
  sd->devcfg.gpio_cs = sd->cs;
  sd->devcfg.host_id = SPI2_HOST;

  sd->buscfg = (spi_bus_config_t) {
    .mosi_io_num = sd->mosi,
    .miso_io_num = sd->miso,
    .sclk_io_num = sd->sck,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .flags = 0
  };

  sd->mountcfg = (esp_vfs_fat_sdmmc_mount_config_t) {
    .format_if_mount_failed = false,
    .disk_status_check_enable = false,
    .allocation_unit_size = 4*1024,
    .max_files = 5
  };

  esp_err_t bus = spi_bus_initialize(SPI2_HOST, &sd->buscfg, SPI_DMA_CH_AUTO);
  if (bus != ESP_OK) {
    printf("Error while initializing SPI bus. (0x%x)\n", bus);
  } else {
    printf("Bus initialized.\n");  
    printf("Adding device...\n");
  };

  vTaskDelay(pdMS_TO_TICKS(300));
  for (int attempt = 0; attempt <= SD_MAX_MOUNT_ATTEMPS; attempt++) {
    esp_err_t ret = esp_vfs_fat_sdspi_mount("/sdcard", &sd->hostcfg, 
    &sd->devcfg, &sd->mountcfg, &sd->card);
    if (ret == ESP_OK) break;
    if (attempt == SD_MAX_MOUNT_ATTEMPS) {
      printf("Error while mount file system in sd card: 0x%x\n", ret);
      return ESP_FAIL;
    }; printf("Trying again mount file system through %i ms...\n", 100*attempt);
    vTaskDelay(pdMS_TO_TICKS(100*attempt));
  }; return ESP_OK;
};