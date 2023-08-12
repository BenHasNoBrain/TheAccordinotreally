long lowerAtmos = 0;
long upperAtmos = 0;

void setup_Midi() {
  lowerAtmos = averagePressure - 300;
  upperAtmos = averagePressure + 300;

  TinyUSB_Device_Init(0);
  usb_midi.setStringDescriptor("The Accordionotreally");

  MIDI.begin(MIDI_CHANNEL_OMNI);
  //MIDI.setHandleNoteOn(handleNoteOn);
  //MIDI.setHandleNoteOff(handleNoteOff);
  while (!TinyUSBDevice.mounted())  {delay(1);}
}

void midi_stuff() {
  sendMIDI_KB();
  sendMIDI_Bass();
  if (bellowsMode)  {
    if (pressureConnected)  {
      setPressure();
    }
  } else  {
    pressureVelocity = 127;
  }

  if (volChange)  {
    if (mainVolume > 100) {mainVolume = 100;} else if (mainVolume < 0)  {mainVolume = 0;}
      MIDI.send(midi::ControlChange, 0x07, map(mainVolume, 0, 100, 0, 127), 1);
      MIDI.send(midi::ControlChange, 0x07, map(mainVolume, 0, 100, 0, 127), 2);
      volChange = false;
  }


  MIDI.read();
}


void setPressure()  {
  pressureVelocity = map(currentPressure, 0, pressureSensitivity, 0, 127);  //Needs to be here otherwise fluctuates all over the place
  MIDI.sendAfterTouch(pressureVelocity, 1);
  MIDI.sendAfterTouch(pressureVelocity, 2);
}

void sendMIDI_KB() {
  for (int i = 0; i < 5; i++)  {
    if ((fingers[i] == currentlyOn[i]) && (fingers[i] != 0)) {
      MIDI.sendNoteOn(fingers[i], pressureVelocity, 1);
    } else if (fingers[i] != currentlyOn[i])  {
      MIDI.sendNoteOff(currentlyOn[i], 0, 1);
      currentlyOn[i] = 0;
      fingers[i] = 0;
    }
  }
    
}
void sendMIDI_Bass()  {
  for (byte i = 0; i < 3; i++)  {
    if ((bassList[i] != 0) && (bassList[i] == bassCurrentlyOn[i]))  {
      for (byte j = 0; j < 3; j++)  {
        for (byte k = 0; k < 3; k++)  {
          MIDI.sendNoteOn(bassOn[j][k], pressureVelocity, 2);
        }
      }
    } else if (bassList[i] != bassCurrentlyOn[i])  {  //Turn off bassOnCurrently[i][0/1/2]
      byte bassOverlapNote = 0;
      byte bassOffs[3] = {0, 0, 0};
      for (byte j = 0; j < 3; j++)  {
        bassOffs[j] = bassOnCurrently[i][j];
      }
      for (byte j = 0; j < 3; j++)  { //Check each other bundle in bassList, except current "i"
        if (j != i) {
          for (byte k = 0; k < 3; k++)  {
            for (byte m = 0; m < 3; m++)  {
              if (bassOffs[m] == bassOnCurrently[j][k]) {
                bassOffs[m] = 0;
              }
            }
          }
        }
      }

      for (byte j = 0; j < 3; j++)  {
        MIDI.sendNoteOff(bassOffs[j], 0, 2);
        bassOnCurrently[i][j] = 0;
        bassList[i] = 0;
      }

    }
  }
}
