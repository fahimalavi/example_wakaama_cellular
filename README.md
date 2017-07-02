# mbed-os-example-wakaama
    Example for Eclipse Wakaama client integration on mbed-os platform.

## Integration Environment:
* hardware
    * [NXP LPC1768](https://developer.mbed.org/platforms/mbed-LPC1768/)
    * [MBED APPLICATION BOARD](https://developer.mbed.org/cookbook/mbed-application-board)
        * LM75B
        * C12832
* software 
    * [mbed-os V5.4](https://github.com/ARMmbed/mbed-os)
    * [wakaama client](https://github.com/eclipse/wakaama)

## how to run:
### mbed online compiler:
* Select platform to mbed LPC1768
* Import code via url
    * github: https://github.com/tz-arm/mbed-os-example-wakaama
    * mbed developer: https://developer.mbed.org/users/terencez/code/mbed-os-example-wakaama/
* Plugin hardware platform to you computer: LPC1768 + MBED APPLICATION BOARD
* Compile and download image to device
* Connect device to ethernet and reboot，some message come to LCD
* Open [Leshan Server Demo](http://leshan.eclipse.org/#/clients) via browser
* A client named MBED-OS-EXAMPLE-WAKAAMA will display in the list.
* Feel free to click :)

![](http://github.com/tz-arm/mbed-os-example-wakaama/raw/master/image/mbed-os-example-wakaama-image-01.jpg)
![](http://github.com/tz-arm/mbed-os-example-wakaama/raw/master/image/mbed-os-example-wakaama-image-02.jpg)