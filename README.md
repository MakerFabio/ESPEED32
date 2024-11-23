# SlotEsp32
WARNING: the magnetic sensor TLE493D-P3B6 A0 is the version 3 silicon and will be available on Digikey or mouser very likely in feb 2025
Cutting edge Slot car controller that has an ESP32 at its heart.
How to built it video:
https://github.com/MakerFabio/ESPEED32
![image](https://github.com/user-attachments/assets/4723fd13-3b00-4878-848c-b52d67ece3f5)

# Release note

* V2.11 Antispin stats from ANTISPIN_PERC_START instead of min speed, in order to rise the current earlier and have a more flat current during the ramp
* V2.08 Fixed negative derivate at 0 speed, this was impacting initial speed using antispin and producing random 90% duty glitches at startup or very low duty due to dual curve 

