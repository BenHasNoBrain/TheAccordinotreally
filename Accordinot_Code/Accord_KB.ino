const byte rows = 8;
const byte columns = 8;
byte rowPins[rows] = {0, 1, 2, 3, 4, 5, 6, 7};
byte columnPins[columns] = {8, 9, 10, 11, 12, 13, 14, 15};
byte singleNote = 0;
byte KB_values[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {41, 42, 43, 44, 45, 46, 47, 48},
  {49, 50, 51, 52, 53, 54, 55, 56},
  {57, 58, 59, 60, 61, 62, 63, 64},
  {65, 66, 67, 68, 69, 70, 71, 72},
  {73, 74, 75, 76, 0, 0, 0}
};

void setup_KB()  {
    for (int i = 0; i < rows; i++) {
        pinMode(rowPins[i], INPUT_PULLUP);
    }
    for (int i = 0; i < columns; i++) {
        pinMode(columnPins[i], OUTPUT);
        digitalWrite(columnPins[i], HIGH);
    }
}

void scan_KB() {
  int fingerCount = 0;
  byte fingerData[5] = {0, 0, 0, 0, 0};
    for (byte row = 0; row < rows; row++) {
      digitalWrite(columnPins[row], LOW);
      for (byte column = 0; column < columns; column++) {
          if (digitalRead(rowPins[column]) == LOW) {
              byte tmp = KB_values[column][row - 1];
              fingerData[fingerCount] = tmp;
              fingerCount++;

              bool exists = false;
              for (byte i = 0; i < 5; i++)  {
                if (fingers[i] == tmp)  {
                  exists = true;
                }
              }
              if (!exists)  {
                for (byte i = 0; i < 5; i++)  {
                  if (fingers[i] == 0)  {
                    fingers[i] = tmp;
                    currentlyOn[i] = tmp;
                    currentlyCount++;
                    i = 99;
                  }
                }
              }

              
          }
      }
      digitalWrite(columnPins[row], HIGH);
    }


    //Remove lifted keys
    for (byte i = fingerCount; i < 5; i++)  {
      fingerData[i] = 0;
    }
    for (byte i = 0; i < 5; i++) {
      if (fingers[i] != 0)  {
        bool exists = false;
        for (byte j = 0; j < fingerCount; j++)  {
          if (fingers[i] == fingerData[j]) {
            exists = true;
          }
        }
        if (!exists)  {
          fingers[i] = 0;
          currentlyCount--;
        }
      }
    }
    //return keys, check Accord_Midi(midi_stuff)
}