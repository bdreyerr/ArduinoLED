#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 30

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


uint32_t raindrop = strip.Color(100,255,255);
uint32_t white =  strip.Color(255,255,255); 
uint32_t black = strip.Color(0,0,0);

int raindrop_speed = 80;
int raindrop_gap = 6;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...
  //etAll(white);
  //raindrop_fall(raindrop,raindrop_speed);
  setAll(black);
  raindrop_fall(raindrop,raindrop_speed);
}

void setAll(uint32_t color){
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
  strip.show();                          //  Update strip to match
}

void raindrop_fall(uint32_t color, int wait){
  uint32_t cur_color_1 ;
  uint32_t cur_color_2;
  uint32_t cur_color_3;
  
  for(int i=0; i<strip.numPixels(); i++ ) { 
    cur_color_1 = strip.getPixelColor(i);
    cur_color_2 = strip.getPixelColor(i+raindrop_gap);
    cur_color_3 = strip.getPixelColor(i+raindrop_gap*2);
    
    strip.setPixelColor(i, color); 
    strip.setPixelColor(i+raindrop_gap, color);     
    strip.setPixelColor(i+raindrop_gap*2, color); 
    strip.show();
    delay(wait);
    strip.setPixelColor(i, cur_color_1);
    strip.setPixelColor(i+raindrop_gap, cur_color_2);
    strip.setPixelColor(i+raindrop_gap*2, cur_color_3);             
    strip.show();
  } 
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
