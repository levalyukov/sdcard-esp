#include <stdio.h>
#include <lib/sd.h>

#define CS    GPIO_NUM_5
#define SCK   GPIO_NUM_18
#define MOSI  GPIO_NUM_23
#define MISO  GPIO_NUM_19

void app_main(void) {
  if (sdcard_init(CS,SCK,MOSI,MISO) != ESP_OK) {
    printf("SD Card not initialized.\n"); 
  } else printf("SD Card initialized.\n");

  /* Creating it .txt file if there is none */
  if (sd) {
    FILE* file = fopen(filename, "a");
    if (file) {
      fputs(message,file);
      fclose(file);
      printf("The content has been added to the file '%s'\n", filename);
    } else printf("Error while open/create text.txt\n");
  } else printf("SD Card not initialized: %p\n", sd);

  /* Reading the previously created file */
  if (sd) {
    printf("Opening %s file...\n", filename);
    FILE* file = fopen(filename, "r");
    char buffer[128];
    if (file) {
      while (fgets(buffer,sizeof(buffer),
      file) != NULL) printf("%s\n", buffer);
      fclose(file);
    } else printf("Error while open/create text.txt\n");
  } else printf("SD Card not initialized: %p\n", sd);
};