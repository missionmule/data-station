# Data Station

This repository holds all information necessary to build a Mission Mule Data Station.

## Raspberry Pi Software
Zane is a little girl.

## Hardware (~$275)
### Ordering the PCB
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
    
**Estimated Cost: $6.90**

### Ordering the Components

Items in BOM 1  are less ubiquotous and should be ordered on a per data station basis. Items in BOM 2 often arrive in bulk, so order accordingly. Items in BOM 3 should be ordered on a per PMC basis. 

BOM 1 - Enclosure - DigiKey Components - [Octopart Link](https://octopart.com/bom-tool/w3m3v7al)

| Item                                      | Qty | Part Number            | Unit Price  | Line Total  | 
|-------------------------------------------|-----|------------------------|-------------|-------------| 
| Bud Industries Enclosure                  | 1   | PTS-25319-C            | 17.46       | 17.46       | 
| 3D Printed Base Plate                     | 1   | 3mm PLA Base Plate     | 0.00        | 0.000       | 
| Voltaic V44 battery, 12,000 mAh USB LiPo  | 1   | V44 Voltaic Battery    | 69.00       | 69.00       | 
| Voltaic 9W Solar Panel                    | 1   | 9W Voltaic Solar Panel | 79.00       | 79.00       | 
| Bulkhead, USB A to USB B                  | 1   | PX0842/A               | 11.12       | 11.12       | 
| Bulkhead, USB Mini to unterminated wires, | 1   | PX0457                 | 7.93        | 7.93        | 
| Sealed Cable, USB A to USB Mini           | 1   | PX0441/2M00            | 16.58       | 16.58       |
| XBee Antenna                              | 1   | 001-0002               | 13.61       | 13.61       | 
| Bulkhead Pass-through, Xbee Antenna       | 1   | AIO-CSPG16             | 2.23        | 2.23        | 
| WiFi Antenna                              | 1   | ICEFINLDMN             | 46.52       | 46.52       | 
| Cable, USB A to USB B, 30cm               | 1   | 321010003              | 1.70        | 1.70        |

**Estimated Total Cost: $110.15**

BOM 2 - Enclosure - Other Components

| Item       | Qty | Unit Price | Line Total | Link | 
|------------|-----|------------|------------|------|
|M4 Standoffs| 4   | 0.894      | 3.576      | [Amazon](https://www.amazon.com/gp/product/B0177VG4Q8/ref=oh_aui_detailpage_o09_s00?ie=UTF8&psc=1) |
|M4 Screws   | 8   | 0.04       | 0.30       | [Amazon](https://www.amazon.com/gp/product/B07DF7GVRB/ref=oh_aui_detailpage_o09_s00?ie=UTF8&psc=1) |
|90mm RP-SMA extension| 1 | 3.50 | 3.50 | [Amazon](https://www.amazon.com/gp/product/B076TCPTKL/ref=oh_aui_detailpage_o05_s00?ie=UTF8&psc=1) |
|30 cm RP-SMA extension | 1 | 4.00 | 4.00 | [Amazon](https://www.amazon.com/Male-Female-Antenna-Extension-Cable/dp/B072VMHXSQ/ref=sr_1_sc_3?s=electronics&ie=UTF8&qid=1534375207&sr=1-3-spell&keywords=30+cm+rpsma+extesion) |

**Estimated Total Cost: $11.38**

BOM 3 - Power Management Circuit - [Octopart Link](https://octopart.com/bom-tool/1G1U2eW2#)

| Description          | Qty | Line Item          | Unit Price                                            | Line Total | 
|----------------------|-----|--------------------|-------------------------------------------------------|------------| 
| GPS Module           | 1   | 746                | 34.95                                                 | 34.95      | 
| Raspberry Pi 0W      | 1   | ADA3400            | 10                                                    | 10         | 
| Arduino Pro Mini     | 1   | 2378               | 9.95                                                  | 9.95       | 
| Voltage Regulator    | 1   | POLOLU-2118        | 4.97                                                  | 4.97       | 
| FET Switch           | 2   | POLOLU-2808        | 4.5                                                   | 9          | 
| XBee Explorer        | 1   | WRL-11373          | 9.95                                                  | 9.95       | 
| XBee Pro S3B         | 1   | 602-1349-ND        | 37.97                                                 | 37.97      | 
| Logic Converter      | 1   | BOB-12009          | 2.003                                                 | 2.003      | 
| Reed Switches        | 4   | 59165-1-S-00-A     | 0.715                                                 | 2.86       | 
| LEDs                 | 4   | 204-10SURD/S530-A3 | 0.0619                                                | 0.2476     | 
| Opto Isolator        | 1   | LTV-816            | 0.077                                                 | 0.077      | 
| 1K Resistors         | 4   | CF14JT1K00         | 0.01                                                  | 0.04       | 
| 2.1K Resistor        | 3   | RNF14FTE2K10       | 0.39                                                  | 1.17       | 
| Temp/Humidity Sensor | 1   | HIH8120-021-001    | 5.38                                                  | 5.38       | 
| USB Micro Breakout   | 1   | 1833               | 1.5                                                   | 1.5        | 
| Debug Switches       | 6   | [link](https://www.amazon.com/gp/product/B06XJN3K8K/ref=oh_aui_detailpage_o03_s00?ie=UTF8&psc=1) | 0.15 | 0.91 |
| USB Hub              | 1   | [link](https://www.amazon.com/MakerSpot-Stackable-Raspberry-Connector-Bluetooth/dp/B01IT1TLFQ) | 13.99 | 13.99 |

**Estimated Total Cost: $144.96**

### Assembly
#### Power Management Circuit
Right now, the PMC is made with through hole components. Seeed Studio manufactures the PCB, and Mission Mule separately buys and solders all of the electronic components. For max eficiency, remove regulator and led on the Arduino Pro Mini (easily done with a small knife or pliers).

IMPORTANT: The XBee Pro S3B [does not work with loads connected to the RSSI signal](https://www.sparkfun.com/products/11634). Thus, the RSSI pin on the XBee explorer must be removed. Additionally, remove the RSSI LED on the explorer (easily done with a small knife or pliers). 

#### Enclosure
assemble and stuff...

## Power Management Firmware
### Requirements
1. Arduino IDE
2. [Adafruit GPS Arduino Library](https://github.com/adafruit/Adafruit_GPS)

Download the code in the [DataStation](https://github.com/missionmule/data-station/tree/master/Microcontroller) and compile for "Arduino Pro or Pro Mini". Upload  using an [FTDI Basic Breakout Board](https://www.sparkfun.com/products/9716).

### XBee Module
Download [XCTU](https://www.digi.com/products/xbee-rf-solutions/xctu-software/xctu) in order to configure the XBee module:
* ID: 1005
* HP: 1
* DT: 10
* MY: 20
* BD: 57600
