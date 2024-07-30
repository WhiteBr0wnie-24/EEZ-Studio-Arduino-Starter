#define USER_SETUP_ID 62
#define ILI9341_DRIVER

#ifdef ARDUINO_ARCH_MBED
    #define TFT_MISO p4
    #define TFT_MOSI p7
    #define TFT_SCLK p6
    #define TFT_CS   p5
    #define TFT_DC   p21
    #define TFT_RST  p20
#else
    #define TFT_MISO D12
    #define TFT_MOSI D11
    #define TFT_SCLK D13
    #define TFT_CS   D10
    #define TFT_DC   D9
    #define TFT_RST  D8
#endif

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

#define SPI_FREQUENCY 20000000
#define SPI_READ_FREQUENCY 20000000
#define SPI_TOUCH_FREQUENCY 2500000
