# Data Station

This repository holds all information necessary to build a Mission Mule Data Station.

## Raspberry Pi Software
Zane is a little girl. 

## Hardware
### Power Management Circuit
Right now, the PMC is made with through hole components. Seeed Studio manufactures the PCB, and Mission Mule separately buys and solders all of the electronic components.

#### Ordering the PCB
1. Download both zip folders in the latest version of fabrication files folder.
2. Upload them to [Seeed Studio Fusion PCB Manufacturing](https://www.seeedstudio.com/fusion_pcb.html).
3. Make the following selections:
    1. Base Material: FR4 TG130
    2. No. of Layers: 2
    3. PCB Dimensions: 155mm x 80mm
    4. PCB Quantity: whatever you want
    5. No. of Different Designs: 1
    6. PCB Thickness: 1.60 mm
    7. PCB Color: Green
    8. Surface Finish: HASL
    9. Minimum Solder Mask Dam: 0.4mm
    10. Copper Weight: 1oz.
    11. Minimum Drill Hole Size: 0.3mm
    12. Trace Width / Spacing: 6/6 mil
    13. Blind or Buried Vias: No
    14. Plated Half-holes / Castellated Holes: No
    15. Impedance Control: No

#### Ordering the Components
Download the latest bill of materials. Follow the Octopart link to the PMC BOM. Order components, choosing vendor according to availability, price and time requirements.

### Enclosure
Download the the latest bill of materials.  Follow the Octopart link to the Data Station Major Component BOM. Order components, choosing vendor according to availability, price and time requirements. Order materials from the Data Tools and Consumables BOM as necessary.

Assemble enclosure? Shien...

## Power Management Firmware
### Requirements
1. Arduino IDE
2. [Adafruit GPS Arduino Library](https://github.com/adafruit/Adafruit_GPS)

Download the code in the [DataStation](https://github.com/missionmule/data-station/tree/master/DataStation) and compile for "Arduino Pro or Pro Mini". Upload  using an [FTDI Basic Breakout Board](https://www.sparkfun.com/products/9716).
