// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

//Nima Vasseghi
//jump pin A0 for different mode!
//jump D5 for serial ip address (debug)

//START user vars
const int NEO_PIN = D4;
const int LEDSTATUS_PIN = D7;
const int MODE_PIN = D0;
const int PIX_COUNT = 95;
const bool debug = false;
//END user vars

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIX_COUNT, NEO_PIN , WS2812B);

UDP udp;

int colourpattern;
bool allsame=true;
int cycles;
double soundval = 0;
int average = 0;
double temp1;
long count;

//Set Strip Constants
const int length = PIX_COUNT;
const int half = length/2;

uint32_t half_array[half];



void setup() {
  pinMode(LEDSTATUS_PIN, OUTPUT);
  pinMode(MODE_PIN, INPUT_PULLDOWN);


  digitalWrite(LEDSTATUS_PIN, LOW);
  

if(debug)
{
  Serial1.begin(9600);
  Serial1.println("Debugging");
  
  IPAddress myIP = WiFi.localIP();
  String ips = String(myIP[0]) + "." +
                   String(myIP[1]) + "." +
                   String(myIP[2]) + "." +
                   String(myIP[3]);
  Serial1.println("my local ip is "+ ips);
}
  
  udp.begin(2223);
  
  for(int i=0; i<half;i++)
  {
    half_array[i] = 0;
  }
  
  
  strip.begin();
  strip.show();
}
//setup end

void loop() {

    
    if(digitalRead(MODE_PIN)>0) //change mode
    {
      allsame = false;
      digitalWrite(LEDSTATUS_PIN, LOW);
    }
    else //change mode
    {
      allsame = true;
      digitalWrite(LEDSTATUS_PIN, HIGH);
    }


  temp1 = temp1 - 50;
  average = temp1 * ((analogRead(A0)/2)/150);
  
  if (average < 20)
  {
    average = 0;
  }
  
  average = constrain(average, 0 , 255);


  
  //Set the hue (0-255) and 24 bit color depending on left channel value
  byte stringoutput = average;

  uint32_t color = Wheel(stringoutput);
  uint32_t nimamiddlecolor = nimamiddleWheel(stringoutput);


  
  //Shift the current values.
  for (int i = 0; i<half-1; i++)
  {
    half_array[i] = half_array[i+1];
    if(allsame) half_array[i] = color;
  }
  
  //Fill in the new value at the end of each array
  half_array[half-1] = color;
  
 //5*2 segments start
 
   for (int i=0; i<9; i++)
  {
    //set pixel color
    strip.setPixelColor(i, half_array[half-12-1]);
    strip.setPixelColor(length-i-1, half_array[half-12-1]);
  }
    for (int i=0; i<9; i++)
  {
    //set pixel color
    strip.setPixelColor(i+9, half_array[half-9-1]);
    strip.setPixelColor(length-i-1-9, half_array[half-9-1]);
  }
    for (int i=0; i<9; i++)
  {
    //set pixel color
    strip.setPixelColor(i+9+9, half_array[half-6-1]);
    strip.setPixelColor(length-i-1-9-9, half_array[half-6-1]);
  }
    for (int i=0; i<10; i++)
  {
    //set pixel color
    strip.setPixelColor(i+9+9+9, half_array[half-3-1]);
    strip.setPixelColor(length-i-1-9-9-9, half_array[half-3-1]);
  }
      for (int i=0; i<10; i++)
  {
    //set pixel color
    strip.setPixelColor(i+9+9+9+10, half_array[half-1]);
    strip.setPixelColor(length-i-1-9-9-9-10, half_array[half-1]);
  }
  
  
  //4*2 END


 if(length%2==1)
 {
     strip.setPixelColor(half, nimamiddlecolor);
 }
 

  //Display the new values
  strip.show();
  
  int x = 0;
  double sum;
  
    //debug
    
    
  while (x < 1)
  {
    
   if(udp.parsePacket() > 0 && udp.read() == 'M') {  
    soundval = udp.parseInt();
    
    //debug
    if(debug) Serial1.println("Here is the sound value...");
    if(debug) Serial1.println(soundval);
    
    x = x+1;
    sum = sum + soundval;
    }
  
  }
  
  temp1 = sum / 1;

}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition b - g - r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85 ) {
   return Color(0,0, WheelPos * 3);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(0, WheelPos * 3 , 255 - WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

// used for different middle color if num of leds is odd

uint32_t nimamiddleWheel(byte WheelPos)
{
  if (WheelPos < 85 ) {
   return nimamiddleColor(0,0, WheelPos * 3);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return nimamiddleColor(0, WheelPos * 3 , 255 - WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return nimamiddleColor(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

uint32_t nimamiddleColor(byte r, byte g, byte b)
{
  uint32_t c;
  c = b;
  c <<= 8;
  c |= r;
  c <<= 8;
  c |= g;
  return c;
}

