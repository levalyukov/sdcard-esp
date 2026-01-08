# SD Card Library 

Basic library for initialized sd-card via ESP-IDF v5.5.1. The library has been tested on a Micro SD Card Adapter.

To work with files, use the abstraction of the C standard library `FILE` from `stdio.h`

> [!WARNING]
> Stable power is needed to initialize the SD card, so if the `0xffffffff` error is thrown when mounting the SD card, there are problems with the contacts or with the power supply (stable 5V should be supplied, but 3.3V when connected directly).

## Methods

Initialize the card
```c
esp_err_t sdcard_init(gpio_num_t cs, gpio_num_t sck, gpio_num_t mosi, gpio_num_t miso);
```

### Output
```txt
I (331) main_task: Calling app_main()
Bus initialized.
Adding device...
I (671) sdspi_transaction: cmd=52, R1 response: command not supported
I (711) sdspi_transaction: cmd=5, R1 response: command not supported
SD Card initialized.
The content has been added to the file '/sdcard/test.txt'
Opening /sdcard/test.txt file...
Hello from ESP32!

I (891) main_task: Returned from app_main()
```