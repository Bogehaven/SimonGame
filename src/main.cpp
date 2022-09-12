#include <FastLED.h>
#include <Wire.h>  
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 


// How many leds are in the strip?
#define NUM_LEDS 4
#define DATA_PIN 19
CRGB leds[NUM_LEDS];

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

#define B_RIGHT 13
#define B_DOWN 14
#define B_LEFT 27
#define B_UP 12

#define RIGHT_T 24
#define DOWN_T 22
#define LEFT_T 29
#define UP_T 24

long randNumber;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);


int sel_1 = -1;
int sel_2 = -1;
int sel_3 = -1;
int selected = 0;
int menu_layer = 0;

const char *root_menu[2] = {
  "PLAY",
  "SETTINGS",
};

const char *game_options[2] = {
  "SINGLE PLAYER",
  "MULTI PLAYER",
};

const char *single_player_options[4] = {
  "EASY",
  "MEDIUM",
  "HARD",
  "VHARD",
};

const char *multi_player_options[2] = {
  "MODE1",
  "MODE2",
};

const char *setting_options[2] = {
  "COLORS",
  "SENSITIVITY",
};

const char *colors_options[2] = {
  "RGB",
  "BGR",
};

const char *sens_options[3] = {
  "SOFT",
  "MEDIUM",
  "HARD",
};

uint32_t color[] = {CRGB::Blue, CRGB::Yellow, CRGB::Red, CRGB::Green};


void Game(int cnt){
  int gameInts[cnt];
  int userInts[cnt];

  int j = 0;

  display.clearDisplay();
  display.display();
  FastLED.clear();
  FastLED.show();
  delay(1000);

  

  for (int i = 0; i < cnt; i++) {
    gameInts[i] = random(4);
  }

  for (int i = 0; i < cnt; i++) {
    FastLED.clear();
    FastLED.show();
    delay(300);
    leds[gameInts[i]] = color[gameInts[i]];
    FastLED.show();
    delay(200);
  }

  FastLED.clear();
  FastLED.show();

  while (j < cnt) {
    int down = touchRead(B_DOWN);
    int up = touchRead(B_UP);
    int left = touchRead(B_LEFT);
    int right = touchRead(B_RIGHT);

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println(j);
    display.display();
    if (left < LEFT_T) {
      userInts[j] = 0;
      leds[0] = color[0];
      FastLED.show();
      delay(300);
      FastLED.clear();
      FastLED.show();
      j = j+1;
    }
    if (up < UP_T) {
      userInts[j] = 3;
      leds[3] = color[3];
      FastLED.show();
      delay(300);
      FastLED.clear();
      FastLED.show();
      j = j+1;
    }
    if (right < RIGHT_T) {
      userInts[j] = 2;
      leds[2] = color[2];
      FastLED.show();
      delay(300);
      FastLED.clear();
      FastLED.show();
      j = j+1;
    }
    if (down < DOWN_T) {
      userInts[j] = 1;
      leds[1] = color[1];
      FastLED.show();
      delay(300);
      FastLED.clear();
      FastLED.show();
      j = j+1;
    }
  }

  int corrects = 0;
  for (int i = 0; i < cnt; i++) {
    if (gameInts[i]==userInts[i]) {
      corrects += 1;
    }
    else {

    }
  }

  if (corrects == cnt) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("WIN");
    display.display();
    delay(1000);
  }
  else {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("LOOSER");
    display.display();
    delay(1000);
  }
  }



void displaymenu(void) {
  int down = touchRead(B_DOWN);
  int up = touchRead(B_UP);
  int left = touchRead(B_LEFT);
  int right = touchRead(B_RIGHT);


  if (down < DOWN_T) {
    selected += 1;
    delay(200);
  };
  if (up < UP_T) {
    selected -= 1;
    delay(200);
  };
  if (right < RIGHT_T) {
    if (menu_layer == 0) {
      sel_1 = selected;
    }
    else if (menu_layer == 1) {
      sel_2 = selected;
    }
    else if (menu_layer == 2) {
      sel_3 = selected;
    }
    menu_layer += 1;
    selected = 0;
    delay(200);
  };
  if (left < LEFT_T) {
    menu_layer = 0;
    selected = 0;
    sel_1 = -1;
    sel_2 = -1;
    sel_3 = -1;
    delay(200);
  };


  Serial.print(sel_2);

  if (menu_layer == 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    for (int i = 0; i < 2; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(root_menu[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(root_menu[i]);
      }
    }
  // Play -> Single Player -> easy
  } else if (sel_1 == 0 && sel_2 == 0 && sel_3 == 0) {
    Game(8);
    menu_layer = 0;
    selected = 0;
    sel_1 = -1;
    sel_2 = -1;
    sel_3 = -1;
    delay(200);
  // Play -> Single Player -> medium
  } else if (sel_1 == 0 && sel_2 == 0 && sel_3 == 1) {
    Game(14);
    menu_layer = 0;
    selected = 0;
    sel_1 = -1;
    sel_2 = -1;
    sel_3 = -1;
    delay(200);
  // Play -> Single Player -> hard
  } else if (sel_1 == 0 && sel_2 == 0 && sel_3 == 2) {
    Game(20);
    menu_layer = 0;
    selected = 0;
    sel_1 = -1;
    sel_2 = -1;
    sel_3 = -1;
    delay(200);
  // Play -> Single Player -> vhard
  } else if (sel_1 == 0 && sel_2 == 0 && sel_3 == 3) {
    Game(31);
    menu_layer = 0;
    selected = 0;
    sel_1 = -1;
    sel_2 = -1;
    sel_3 = -1;
    delay(200);
  // Play -> Multi Player -> 1
  } else if (sel_1 == 0 && sel_2 == 1 && sel_3 == 0) {
    display.clearDisplay();
  // Play -> Multi Player -> 2
  } else if (sel_1 == 0 && sel_2 == 1 && sel_3 == 1) {
    display.clearDisplay();
  // Settings -> Colors -> RGB
  } else if (sel_1 == 1 && sel_2 == 0 && sel_3 == 0) {
    FastLED.show();
  // Settings -> Colors -> BBB
  } else if (sel_1 == 1 && sel_2 == 0 && sel_3 == 1) {
    leds[0] = 0xD81B60;
    leds[1] = 0xD81B60;
    leds[2] = 0xFFC107;
    leds[3] = 0x004D40;
    FastLED.show();
  // Settings -> sensitivity -> soft
  } else if (sel_1 == 1 && sel_2 == 1 && sel_3 == 0) {
    display.clearDisplay();
  // Settings -> sensitivity -> med
  } else if (sel_1 == 1 && sel_2 == 1 && sel_3 == 1) {
    display.clearDisplay();
  // Settings -> sensitivity -> hard
  } else if (sel_1 == 1 && sel_2 == 1 && sel_3 == 2) {
    display.clearDisplay();
  // Settings -> sensitivity
  } else if (sel_1 == 1 && sel_2 == 1) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    for (int i = 0; i < 3; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(sens_options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(sens_options[i]);
      }
    }
  // Settings -> color
  } else if (sel_1 == 1 && sel_2 == 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    for (int i = 0; i < 2; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(colors_options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(colors_options[i]);
      }
    }
  // play -> single player
  } else if (sel_1 == 0 && sel_2 == 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    for (int i = 0; i < 4; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(single_player_options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(single_player_options[i]);
      }
    }
  // play -> multi player
  } else if (sel_1 == 0 && sel_2 == 1) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    for (int i = 0; i < 2; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(multi_player_options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(multi_player_options[i]);
      }
    }
  // play
  } else if (sel_1 == 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    for (int i = 0; i < 2; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(game_options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(game_options[i]);
      }
    }
  // settings
  } else if (sel_1 == 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    for (int i = 0; i < 2; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(setting_options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(setting_options[i]);
      }
    }
  }
  display.display();
}

void debug_buttons(void) {
  int down = touchRead(B_DOWN);
  int up = touchRead(B_UP);
  int left = touchRead(B_LEFT);
  int right = touchRead(B_RIGHT);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 22);
  display.println(left);
  display.setCursor(54, 0);
  display.println(up);
  display.setCursor(92, 22);
  display.println(right);
  display.setCursor(54, 42);
  display.println(down);
  display.display();
}

// This function sets up the ledsand tells the controller about them
void setup() {
  Serial.begin(9600);
  pinMode(B_DOWN, INPUT);
  pinMode(B_UP, INPUT);
  pinMode(B_LEFT, INPUT);
  pinMode(B_RIGHT, INPUT);


  FastLED.addLeds<WS2813, DATA_PIN, RGB>(leds, NUM_LEDS);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);

  leds[0] = CRGB::Blue;
  leds[1] = CRGB::Yellow;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Green;
  FastLED.show();


  delay(1000);
}

void loop() {
  //debug_buttons();
  displaymenu();
}

