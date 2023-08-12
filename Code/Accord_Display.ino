unsigned long tme;
unsigned long paniktme;

void setup_Display()  {
  //21 characters wide, at regular settings
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setFont(NULL);

  tme = millis();
}

void display_stuff()  {
  if ((millis() - tme) > 100)  {
    display.clearDisplay();
    display.setCursor(0, 3);
    display.println("The Accordinotreally");
    display.drawLine(0, 14, 127, 14, 1);
    display.setCursor(0, 20);
    switch (dispMode) {
      case 0:
        display.print("Pitch: "); display.print(keyModifier); display.print(" | Vol:"); display.print(mainVolume);
        break;
      case 1:
        display.print("Bellows: "); display.print(bellowsMode); display.print(" | PS: "); display.print(pressureSensitivity);
        break;
      case 2:
        display.print("p0: "); display.print(pressureZero); display.print("  |  fltr: "); display.print(filter, 2);
        break;
      case 3:
        display_bass();
        break;
    }
    
    display.display();


    display_panik();

    tme = millis();
  }
}

void display_bass() {
  display.clearDisplay();
  display.setCursor(0, 5);
    
  for (byte i = 0; i < 3; i++)  {
    display.print(bassList[i]); display.print(", ");
  }
  display.setCursor(0, 15);
  for (byte i = 0; i < 3; i++)  {
    display.print(bassCurrentlyOn[i]); display.print(", ");
  }
}

void display_panik()  {
  if (panikMode)  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("PANIK!!!");
    display.display();
    tme = millis() + 1100;
    panikMode = false;
  }
}
