byte bassValues[132][3] = {
	{0, 0, 0} /*DONUT MODIFY*/, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 		          	// 0 F9 0 F5 F3 F1 F2 F12
	{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 	          		// 0 F10 F8 F6 F4 TAB ` 0
	{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {13, 0, 25}, {17, 0, 29}, {0, 0, 0},         		// 0 LALT LSFT LCTRL q 1 0
	{0, 0, 0}, {0, 0, 0}, {37, 40, 32}, {32, 36, 39}, {37, 32, 41}, {20, 0, 32}, {24, 0, 36}, {0, 0, 0},   	// 0 0 z s a w 2 0
	{0, 0, 0}, {39, 42, 34}, {32, 35, 39}, {39, 43, 34}, {15, 0, 27}, {26, 0, 38}, {19, 0, 31}, {0, 0, 0}, 	// 0 c x d e 4 3 0
	{0, 0, 0}, {0, 0, 0}, {34, 37, 41}, {34, 38, 41}, {17, 0, 29}, {22, 0, 34}, {21, 0, 33}, {0, 0, 0},   	// 0 ' ' v f t r 5 0
	{0, 0, 0}, {36, 39, 43}, {41, 44, 36}, {36, 40, 43}, {41, 45, 36}, {24, 0, 36}, {28, 0, 40}, {0, 0, 0}, // 0 n b h g y 6 0
	{0, 0, 0}, {0, 0, 0}, {43, 46, 38}, {43, 47, 38}, {19, 0, 31}, {23, 0, 35}, {30, 0, 42}, {0, 0, 0}, 		// 0 0 m j u 7 8 0
	{0, 0, 0}, {38, 41, 45}, {38, 42, 45}, {26, 0, 38}, {21, 0, 33}, {32, 0, 44}, {25, 0, 37}, {0, 0, 0}, 	// 0 ',' k i o '0' 9 0
	{0, 0, 0}, {45, 48, 40}, {40, 43, 47}, {45, 49, 40}, {40, 44, 47}, {28, 0, 40}, {27, 0, 39}, {0, 0, 0}, // 0 . / l ; p - 0
	{0, 0, 0}, {0, 0, 0}, {47, 51, 42}, {0, 0, 0}, {23, 0, 35}, {34, 0, 46}, {0, 0, 0}, {0, 0, 0}, 		      // 0 0 ' 0 [ = 0 0
	{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {30, 0, 42}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 		          // 0 CAPS 0 RHFT ENTER ] 0 \\ 0 0
	{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 		          	// 0 0 0 0 0 BCKSP 0
	{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 		          	// 0 n1 0 n4 n7 0 0 0
	{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 		          	// n0 n. n2 n5 n6 n8 ESC NUMLCK
	{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 		          	//F11 n+ n3 n- n* n9 SCRLL 0
	{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}											                                      	// 0 0 0 F7
};


// Keyboard = F3 to E6 == 41 to 76
// Counterbass = A#1 to F3 == 22 to 41
// Root = F#1 to Db3 == 18 to 37
// Missing F#M, Bm, F#m. Need to be able to shift 2 <<

#define CLOCK 16 //D-
#define DATA 17  //D+

const int clockPin = 16;
const int dataPin = 17;

int bassNum = 0;

void setup_Bass()  {
  pinMode(clockPin, INPUT_PULLUP);
  pinMode(dataPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(CLOCK), scan_Bass, FALLING);
}

void scan_Bass()  {
  uint16_t scanVal = nextValue();

  if (scanVal != 0) {       //End of keystroke signal

    switch(scanVal) {
      case 105: //END
        bellowsMode = !bellowsMode;
        dispMode = 1;
        return;
        break;
      case 108: //HOME
        pressureSensitivity = 250;
        dispMode = 1;
        return;
        break;
      case 122: //PGDWN
        pressureSensitivity -= 5;
        dispMode = 1;
        return;
        break;
      case 125: //PGUP
        pressureSensitivity += 5;
        dispMode = 1;
        return;
        break;
      case 112: //INSERT
        mainVolume += 5;
        volChange = true;
        dispMode = 0;
        return;
        break;
      case 113: //DELETE
        mainVolume -= 5;
        volChange = true;
        dispMode = 0;
        return;
        break;

      
      case 41: //SPACE
        panik();
        return;

      //Octave control
      case 3: //F5
        keyModifier += 12;
        dispMode = 0;
        return;
        break;
      case 11: //F6
        keyModifier -= 12;
        dispMode = 0;
        return;
        break;
      case 107: //LEFT
        keyModifier += 7;
        dispMode = 0;
        return;
        break;
      case 116: //RIGHT
        keyModifier -= 7;
        dispMode = 0;
        return;
        break;
      case 117: //UP
         keyModifier += 1;
        dispMode = 0;
        return;
        break;
      case 114: //DOWN
        keyModifier -= 1;
        dispMode = 0;
        return;
        break;

      //pressureZero & filter
      case 5: //F1
        pressureZero -= 5;
        dispMode = 2;
        return;
        break;
      case 6: //F2
        pressureZero += 5;
        dispMode = 2;
        return;
        break;
      case 4: //F3
        filter -= 0.1;
        nfilter = 1 - filter;
        dispMode = 2;
        return;
        break;
      case 12:  //F4
        filter += 0.1;
        nfilter = 1 - filter;
        dispMode = 2;
        return;
        break;
      
        

      //Display control
      case 126:
        dispMode = 3;
        return;
        break;
      
    }

    if ((scanVal != 240) && (scanVal > 131)) {
      scanVal = 0;    //Prevent overflow of array
      return;         //So not sending NoteOn(0)
    }

    bassNum = 0;
    for (byte i = 0; i < 3; i++)  {
      if (bassList[i] != 0) {bassNum++;}    //Prevent bass notes on overflow
    }

  if (bassNum <= 3) {
    if (scanVal != 240) {
      if ((bassList[0] != scanVal) && (bassList[1] != scanVal) && (bassList[2] != scanVal)) {
        for (byte i = 0; i < 3; i++)  {
          if (bassList[i] == 0) {
            bassList[i] = scanVal;
            bassCurrentlyOn[i] = scanVal;
            i = 99;
          }
        }
      }
    } else  {
      uint16_t tmp = nextValue();
      for (byte i = 0; i < 3; i++)  {
        if (bassList[i] == tmp) {
          bassList[i] = 0;
        }
      }
    }  
  }

    applyChords();
  }
}

uint16_t nextValue() {
  uint16_t tmp;
  for(int i = 0; i<11; i++)    {
      long tme = millis();
      while(digitalRead(CLOCK)) {
        if ((millis() - tme) > 10){
          return 0;
        }
      };
      tmp |= digitalRead(DATA) << i;
      while(!digitalRead(CLOCK));
    }
  tmp >>= 1;
  tmp &= 0xFF;
  return tmp;
}

void applyChords()  {
  for (byte i = 0; i < 3; i++)  {
    for (byte j = 0; j < 3; j++)  {
      bassOn[i][j] = bassValues[bassList[i]][j] + keyModifier;
      bassOnCurrently[i][j] = bassValues[bassCurrentlyOn[i]][j] + keyModifier;
    }
  }
}

void panik()  {
  for (byte i = 0; i < 128; i++)  {
    MIDI.sendNoteOff(i, 0, 1);
    MIDI.sendNoteOff(i, 0, 2);
  }
  for (byte i = 0; i < 3; i++)  {
    for (byte j = 0; j < 3; j++)  {
      bassOn[i][j] = 0;
    }
    bassList[i] = 0;
    bassCurrentlyOn[i] = 0;
  }
  for (byte i = 0; i < 5; i++)  {
    fingers[i] = 0;
    currentlyOn[i] = 0;
  }

  MIDI.send(midi::ControlChange, 0x7B, 0, 1);
  MIDI.send(midi::ControlChange, 0x7B, 0, 2);
  
  
  //fingerCount = 0;
  panikMode = true;
}
