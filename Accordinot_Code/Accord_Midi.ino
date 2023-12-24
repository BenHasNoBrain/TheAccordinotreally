void setup_Midi() {

  TinyUSB_Device_Init(0);
  usb_midi.setStringDescriptor("The Accordionotreally");

  MIDI.begin(MIDI_CHANNEL_OMNI);
  //MIDI.setHandleNoteOn(handleNoteOn);
  //MIDI.setHandleNoteOff(handleNoteOff);
  while (!TinyUSBDevice.mounted())  {delay(1);}
}

void midi_stuff() {
  if (bellowsMode)  {
    if (pressureConnected)  {
      setPressure();
    }
  } else  {
    MIDI.sendControlChange(7, 127, 1); //Use 1 channel to control volume sliders in DAW
  }

  sendMIDI_KB();
  sendMIDI_Bass();

  MIDI.read();
}


void setPressure()  {
  pressureVelocity = map(constrain(currentPressure, 0, pressureSensitivity), 0, pressureSensitivity, 0, 127);  //Needs to be here otherwise fluctuates all over the place

  MIDI.sendControlChange(7, pressureVelocity, 1); //Use 1 channel to control volume sliders in DAW
}

void sendMIDI_KB() {
  for (int i = 0; i < 5; i++)  {
    if ((fingers[i] == currentlyOn[i]) && (fingers[i] != 0)) {
      MIDI.sendNoteOn(fingers[i], 127, 1);
    } else if (fingers[i] != currentlyOn[i])  {
      MIDI.sendNoteOff(currentlyOn[i], 0, 1);
      currentlyOn[i] = 0;
      fingers[i] = 0;
    }
  }
    
}
void sendMIDI_Bass()  {
  for (byte i = 0; i < 9; i++)  {
    if (bassOn[i] != 0) {
      MIDI.sendNoteOn(bassOn[i], 127, 2);
    }
  }

  for (byte i = 0; i < 9; i++)  {
    if (bassOff[i] == bassOn[i])  {
      bassOff[i] = 0;
    }
  }
  for (byte i = 0; i < 9; i++)  {
    if (bassOff[i] != 0)  {
      MIDI.sendNoteOff(bassOff[i], 0, 2);
      bassOff[i] = 0;
    }
  }

  //NOTE TO SELF: One potential (currently working) fix for the hung Bass problem: 1. {Tools -> Optimize -> Optimize(-O) from Small(-Os)}, 2. {CPU Speed -> 125MHZ from 133MHZ}
}
