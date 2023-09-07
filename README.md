# TheAccordinotreally
![The Accordinotreally](Images/mainDisplay.jpg)
Repo for the code driving _The Accordinotreally_, a cheap and silly DIY project by BenHasNoBrain. More info to come! (when I get 'round to it :joy:)

---

## Changelog
### 12/8/23
* First commit, containing 3 weeks of initial code development (working prototype)
### 13/8/23
* Added new branch for reworking the Bass system, specifically in scanning and MIDI sending
### 21/8/23
* Fixed Bass system hanging (i.e. becoming completely unresponsive, while the rest of the system was fine) via RP2040 settings, see `Accord_Midi: 78`. Modifications to pressure sensing + displaying.
### 28/8/23
* Attempt to fix pressure system: changed MIDI ControlChange from aftertouch to channel volume. Re-added `panik` functionality.
### 4/9/23
* Merged `bass_revamped` and `main` branches. Removed all sampling + filtering from BMP280 sensor, to be calculated in a separate function and enveloped.
* Discovery: To get pressure volume, link the controller in the respective DAW (i.e. link volume knob in LMMS to the MIDI volume channel set by the Accordinotreally)
### 7/9/23
* Added second "external" pressure sensor (i.e. outside of bellows) for better reference for bellows pressure - now the Accordinotreally responds better to changes in atmosphere (temperature etc), rather than relying on a fixed value.

|   Known bugs  |   Description |
|   ---         |   ---         |
| Bass overlapping notes    |   When pressing 3 chords where some of the keys overlap, some of the notes don't release when all of the keys are released.   |

|   Todo    |
|   ---     |
| Stick the OLED somewhere visible on the body  |
| Make a longer USB cable   |
| Make a bellows clip for both sides of the body |
