// Include starting libraries
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

// Declare constant variables
const int NUM_LEDS = 10;
const int GO = 60;          // green
const int P1_COLOR = 250;   // red
const int P2_COLOR = 150;   // blue

bool p1_win = false;        // neither player has won
bool p2_win = false;
int p1_score = 0;           // set initial score for both players to 0
int p2_score = 0;
bool p1_scored = false;     // boolean variable for who has won
bool p2_scored = false;

// Indicate Player 1's score using LEDs 0-4
void p1_led_score(int score)
{
  // LEDs indicate Player 1's score
  for (int led = 0; led < score; led++)
  {
    CircuitPlayground.setPixelColor(led, CircuitPlayground.colorWheel(P1_COLOR)); // start at LED 0 for P1
  }
}

// Indicate Player 2's score using LEDs 5-9
void p2_led_score(int score)
{
  // LEDs indicate Player 2's score
  for (int led = 0; led < score; led++)
  {
    CircuitPlayground.setPixelColor(led+5, CircuitPlayground.colorWheel(P2_COLOR)); // start at LED 5 for P2
  }
}

// Light up all the LEDs with a specified color
void light_leds(int color)
{
  for (int led = 0; led < NUM_LEDS; led++)
  {
    CircuitPlayground.setPixelColor(led, CircuitPlayground.colorWheel(color));
  }
}

// Flash one LED to indicate the point scored and the player who scored the point
void flash_led(int led, int num_flash, int color)
{
  for (int flash = 0; flash < num_flash; flash++)
  {
    CircuitPlayground.setPixelColor(led, 0);
    delay(250);
    CircuitPlayground.setPixelColor(led, CircuitPlayground.colorWheel(color));
    delay(250);
  }
}

// Flash all LEDs to indicate who wins
void flash_leds(int num_flash, int color)
{
  for (int flash = 0; flash < num_flash; flash++)
  {
    CircuitPlayground.clearPixels();
    delay(500);
    light_leds(color);
    delay(500);
  }
}

void setup() {
  // initialize the circuit playground
  CircuitPlayground.begin();
}

void loop() {
  // Set LED brightness to 10
  CircuitPlayground.setBrightness(10);

  // Continue looping until someone wins
  while (!p1_win && !p2_win)
  {
    // players wait for a random amount of time between 1.5s and 3.0s
    delay(random(1500, 3000));

    // LEDs light up green and sound goes off
    light_leds(GO);
    CircuitPlayground.playTone(880, 50);

    // Wait for either player to press their button
    while (!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton())
    {
    }

    // Add point to player 1 if they press first
    if (CircuitPlayground.leftButton())
    {
      do
      {
      }while (CircuitPlayground.leftButton());
      p1_score++;
      p1_scored = true;
    }

    // Add point to player 2 if they press first
    else if (CircuitPlayground.rightButton())
    {
      do
      {
      }while (CircuitPlayground.rightButton());
      p2_score++;
      p2_scored = true;        
    }

    CircuitPlayground.clearPixels();    // Turn off LEDS
    p1_led_score(p1_score);   // Show P1 score
    p2_led_score(p2_score);   // Show P2 score
    
    // P1 wins when they score 5 points
    if (p1_score == 5)
    {
      p1_win = true;
    }
    
    // P2 wins when they score 5 points
    else if (p2_score == 5)
    {
      p2_win = true;
    }
    
    // Flash P1's scored point if they have not reached 5 points
    else if (p1_scored)
    {
      flash_led(p1_score-1, 3, P1_COLOR);
      p1_scored = false;
    }
    
    // Flash P2's scored point if they have not reached 5 points
    else if (p2_scored)
    {
      flash_led(p2_score+4, 3, P2_COLOR);
      p2_scored = false;
    }

    // Wait 0.5s before turning off all pixels
    delay(500);
    CircuitPlayground.clearPixels();
  }

  if (p1_win)       // Flash all LEDs P1's color if P1 wins
  {
    flash_leds(10, P1_COLOR);
  }
  else if (p2_win)  // Flash all LEDs P2's color if P2 wins
  {
    flash_leds(10, P2_COLOR);
  }

  // Turn off all LEDs
  while (p1_win || p2_win)
  {
    CircuitPlayground.clearPixels();
  }
}
