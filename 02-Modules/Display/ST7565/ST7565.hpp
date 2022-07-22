#ifndef PROJECT_PICOLIBS_ST7565_HPP
#define PROJECT_PICOLIBS_ST7565_HPP

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"
namespace Display {

    class ST7565 {
    public:
        int pinRed;
        int pinGreen;
        int pinBlue;
        int pinCLK;
        int pinMOSI;
        int pinCS;
        spi_inst_t *spiInstance;
        int pinA0;
        int pinRst;
        int firstLineCorrector{};
        //ST7565();
        ST7565(int _redPin,
               int _greenPin,
               int _bluePin,
               int _clockPin,
               int _mosiPin,
               int _csPin,
               int _a0Pin,
               int _rstPin,
               spi_inst *_spiInstance,
               int _firstLineCorrection);
        void SetFirstLine(uint8_t _line);
        void SetColor(int _red, int _green, int _blue);
        void WritePixels(uint8_t _page, uint8_t _column, uint8_t *_src, int _len);
        void __writeAllToZero__();

    private:
        void __ST7565InitializationWithOnBoardPower__() const;

    };

    class James : public ST7565 {
    public:
        void SetColor();
    };

};

#endif //PROJECT_PICOLIBS_ST7565_HPP
