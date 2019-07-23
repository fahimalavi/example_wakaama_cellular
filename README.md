# example_wakaama_Cellular
    Example for Eclipse Wakaama client integration on mbed-os platform. (Forked from https://github.com/tz-arm/mbed-os-example-wakaama)

## Integration Environment:
* hardware
    * [C030-R412M](https://os.mbed.com/platforms/ublox-C030-R412M/)
* software 
    * [mbed-os V5.12.4](https://github.com/ARMmbed/mbed-os)
    * [wakaama client](https://github.com/eclipse/wakaama)

## how to Build:
* Download mbed-cli
* clone this repo
* mbed config root .
* mbed deploy
* mbed compile -t ARM -m UBLOX_C030_R412M 
### How to run:
* Drag and drop .bin (The board provides simple USB drag-ndrop programming and ST-Link debug interface for the Host microcontroller.)
* Open [Leshan Server Demo](https://leshan.eclipseprojects.io/#/clients) via browser
