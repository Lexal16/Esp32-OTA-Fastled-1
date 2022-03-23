/*
  Rui Santos
  Complete project details
   - Arduino IDE: https://RandomNerdTutorials.com/esp32-ota-over-the-air-arduino/
   - VS Code: https://RandomNerdTutorials.com/esp32-ota-over-the-air-vs-code/
  
  This sketch shows a Basic example from the AsyncElegantOTA library: ESP32_Async_Demo
  https://github.com/ayushsharma82/AsyncElegantOTA
*/

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>


const char* ssid = "G8WMD";                //"REPLACE_WITH_YOUR_SSID";
const char* password = "29P2VFYQ47KCSWTQ"; //"REPLACE_WITH_YOUR_PASSWORD";

AsyncWebServer server(80);
#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS    300          // FastLED definitions
#define LED_PIN     5
CRGB g_LEDs[NUM_LEDS] = {0};    // Frame buffer for FastLED

//uint8_t initialHue = 0;
//const uint8_t deltaHue = 20;
//const uint8_t hueDensity = 4;
const uint8_t MaxTime = 20;


void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32-OTA-Fastled-1");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);               // Add our LED strip to the FastLED library
  FastLED.setBrightness(50);          //  set brightness 1 - 255
}


void loop(void) {
  // Handle LEDs
//acn fill_rainbow(g_LEDs, NUM_LEDS, initialHue += hueDensity, deltaHue);

static uint8_t start_hue = 0;
static uint8_t stop_hue  = 0;
static uint8_t start_sat = 0;
static uint8_t stop_sat  = 0;
static uint8_t start_val = 0;
static uint8_t stop_val  = 0;
static uint16_t start_pixel = 0;
static uint16_t stop_pixel  = 0;
static uint8_t wait_time;

wait_time = random8(1,15);

	Serial.print("x");
  EVERY_N_SECONDS(wait_time) {
    start_pixel = random16(0, NUM_LEDS-1);
    stop_pixel  = random16(0, NUM_LEDS-1);

    start_hue = random8();
    stop_hue  = random8();
    start_sat = random8();
    stop_sat  = random8();
    start_val = random8();
    stop_val  = random8();

    fill_gradient(g_LEDs,start_pixel, CHSV(start_hue, start_sat, start_val), stop_pixel, CHSV(stop_hue, stop_sat, stop_val));

		// Show the leds
		FastLED.show();   
  }

	// Serial.print("x");

}
