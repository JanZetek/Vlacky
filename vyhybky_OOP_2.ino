#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <string.h>

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

class ABC
{
  private:
    int RELE_PIN;
    int LED_PIN;

    // LED se rozsvítí, pokud je systém ABC zapnut

  public:
    bool stav;
    bool can = false;

    // Konstruktor
    ABC(int rele_pin, int led_pin) : RELE_PIN(rele_pin), LED_PIN(led_pin) {}

    void begin()
    {
      // Inicializuje pin
      pinMode(RELE_PIN, OUTPUT);
      pinMode(LED_PIN, OUTPUT);
    }

    void onChange()
    {
      can = true;
    }

    void offChange()
    {
      can = false;
    }

    void on()
    {
      // Zapne systém ABC
      if (can == true) {
        digitalWrite(RELE_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
      }
    }

    void off()
    {
      // Vypne systém ABC
      digitalWrite(RELE_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }

    void change()
    {
      stav = !stav;

      switch(stav)
      {
        case false:
          off();
          break;
        case true:
          on();
          break;
      }
    }
};

class ServoManager 
{
  private:
    Servo servo;   // Instance objektu Servo
    int servoPin;  // Pin, na kterém je servo připojeno

  public:
    // Konstruktor
    ServoManager(int pin)
      : servoPin(pin) {}

    // Inicializace spojení s servomotorem
    void begin() {
      servo.attach(servoPin);  // Připojení serva k pinu
    }

    // Deinicializace spojení s servomotorem
    ~ServoManager() {
      servo.detach();  // Odpojení serva
    }

    // Ovládání servomotoru na zadaný úhel
    void setAngle(int angle) {
      servo.write(angle);
    }
};

class Semafor 
{
  private:
    int LED_GREEN_PIN;
    int LED_RED_PIN;
    int LED_YELLOW_PIN;
    ABC A;

  public:
    int semafor_stav;
    int type = 0; // 0 -> GR; 1 -> GYR; 2 -> BW

    // Konstruktor
    Semafor(int led_green_pin, int led_red_pin, ABC a) : LED_GREEN_PIN(led_green_pin), LED_RED_PIN(led_red_pin), A(a) {}

    // led_green_pin & led_red_pin jsou u typu BW pužívány jako blue a white

    void begin()
    {
      // Inicializace
      pinMode(LED_GREEN_PIN, OUTPUT);
      pinMode(LED_RED_PIN, OUTPUT);

      semafor_stav = 0;
    }

    void GYR(int led_yellow_pin)
    {
      LED_YELLOW_PIN = led_yellow_pin;

      type = 1;

      pinMode(LED_YELLOW_PIN, OUTPUT);
    }

    void BW()
    {
      type = 2;

      // led_green_pin & led_red_pin jsou u typu BW pužívány jako blue a white
    }

    void disable() 
    {
      // Zapne červenou diodu, vypne zelenou a zapne relé
      digitalWrite(LED_GREEN_PIN, LOW); 
      digitalWrite(LED_RED_PIN, HIGH);

      if (type == 1)
        digitalWrite(LED_YELLOW_PIN, LOW);

      semafor_stav = 0;
    }

    void enable()
    {
      // Zapne zelou, vypne červenou a relé
      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_RED_PIN, LOW);

      if (type == 1)
        digitalWrite(LED_YELLOW_PIN, LOW);

      semafor_stav = 1;
    }

    void next()
    {
      semafor_stav = 2;

      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_YELLOW_PIN, HIGH);
    }

};

class Vyhybka 
{
  private:
    int LED_1_PIN;
    int LED_2_PIN;
    int SERVO_PIN;
    int RELE_PIN;
    bool srdcova = false;
    ServoManager Servo;
    Semafor S1;
    Semafor S2;
  
  public:
    bool stav; // false -> vlevo; true -> vpravo

    // konstruktor
    Vyhybka(int led_1_pin, int led_2_pin, int servo_pin, Semafor s1, Semafor s2) : Servo(servo_pin), LED_1_PIN(led_1_pin), LED_2_PIN(led_2_pin), SERVO_PIN(servo_pin), S1(s1), S2(s2) {}


    void begin() 
    {
      // Nastavení LED jakou OUTPUT
      pinMode(LED_1_PIN, OUTPUT);
      pinMode(LED_2_PIN, OUTPUT);

      // Inicialzizace serva
      Servo.begin();

      // Semafory nastaví na červenou
      S1.disable();
      S2.disable();

      change();

    }

    void set_srdcova(int rele_pin) 
    {
      srdcova = true;

      RELE_PIN = rele_pin;

      pinMode(RELE_PIN, OUTPUT);
    }

    void change()
    {
      if (stav == false) {
        stav = true; // přepna orientaci výhybky vpravo
      } else {
        stav = false;
      }

      Servo.begin(); // Vůbvec nevím, proč to tady je, ale bez toho to nefunguje
      Servo.setAngle(stav ? 0 : 180); // přepne servo na základě orientace do požadovaného úhlu

      digitalWrite(LED_1_PIN, stav ? HIGH : LOW);
      digitalWrite(LED_2_PIN, stav ? LOW : HIGH);

      // Pokud je kolej srdcová, přepne se relé
      if (srdcova == true)
        digitalWrite(RELE_PIN, stav ? LOW : HIGH);

      // Nastaví na obou dvou semaforech červenou
      S1.disable(); 
      S2.disable();
    }

    void blick()
    {
      Serial.println("Zablikam");

      switch (stav)
      {
        case false:
          digitalWrite(LED_1_PIN, HIGH);
          delay(250);
          digitalWrite(LED_1_PIN, LOW);
          break;
        case true:
          digitalWrite(LED_2_PIN, HIGH);
          delay(250);
          digitalWrite(LED_2_PIN, LOW);
          break;
      }
    }

};

bool ableToGreen(bool* right_way, Vyhybka* array, Semafor S) 
{

  for (int i = 0; i < (sizeof(right_way) / sizeof(right_way[0])); i++) {
    // porovná vždy hodnoty výhybky a správné cesty na stejné pozici v poli
    if (array[i].stav != right_way[i]) {
      return false;
    }
  }

  return true;

};

Semafor S1(19, 26);
Semafor S2(24, 15);

Vyhybka V1(30, 29, 52, S1, S2);

void setup() {

  Serial.begin(9600);

  V1.begin();
  S1.begin();
  S2.begin();
}

void loop() {

  if (digitalRead(46) == HIGH)
  {
    while (digitalRead(46) == HIGH) {} // Nedělá nic

    V1.change();
  }

  else if (digitalRead(42) == HIGH)
  {
    while (digitalRead(42) == HIGH) {} // Nedělá nic

    bool pole_1[] = {false};
    Vyhybka pole_2[] = {V1};

    if (S1.semafor_stav == 0 && ableToGreen(pole_1, pole_2, S1) == true)
    {
      S1.enable();
    } 
    else if (S1.semafor_stav == 0 && ableToGreen(pole_1, pole_2, S1) == false)
    {
      V1.blick();
    }
    else
    {
      S1.disable();
    }
  }

  else if (digitalRead(44) == HIGH)
  {
    while (digitalRead(44) == HIGH) {}

    bool pole_3[] = {true};
    Vyhybka pole_4[] = {V1};

    if (S2.semafor_stav == 0 && ableToGreen(pole_3, pole_4, S2) == true)
    {
      S2.enable();
    }
    else if (S2.semafor_stav == 0 && ableToGreen(pole_3, pole_4, S2) == false)
    {
      V1.blick();
    }
    else
    {
      S2.disable();
    }
  }

}