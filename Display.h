#ifndef Display_h
#define Display_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class Display {
  private:
    int CS;
    int RST;
    int DC;

    Adafruit_ST7735 TFT;

  public:
    Display(int cs, int rst, int dc)
      : CS(cs), RST(rst), DC(dc), TFT(cs, dc, rst) {}

    void begin() {
      TFT.initR(INITR_BLACKTAB);  // Použijte tuto inicializaci pro černobílý displej

      // Nastavení barev
      TFT.fillScreen(ST7735_BLACK);    // Černá pozadí
      TFT.setTextColor(ST7735_WHITE);  // Bílá barva textu

      // Nastavení velikosti textu
      TFT.setTextSize(2);  // Nastaví velikost textu na 2
    }

    void write(String text) {

      TFT.setCursor(10, 10);
      TFT.println(text);
    }

    void clear() {
      TFT.fillRect(0, 0, 128, 160, ST7735_BLACK);
    }
};

#endif