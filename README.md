# NeoHeart - Revision 2.0
Hardware and Software design for an Open Source ATtiny816-based heart shaped PCB with Addressable LEDs.
<br>![board-render](https://github.com/fellettigiacomo/NeoHeart/blob/main/3d/board-render.png?raw=true)
## Features

- **Microcontroller**: ATtiny816
- **LEDs**: 25 SK6805-MINIJ Addressable RGB LEDs
- **Power**: 3V CR2032 battery
- **Programming**: UPDI programming interface
- **Software**: Built using Adafruit's Neopixel library, featuring 10 built-in animations and efficient power management
- **Additional Features**:
  - Low current consumption design
  - Integrated MOSFET for powering down LEDs to save power
  - Additional digital/analog exposed GPIO to hack your NeoHeart in unexpected ways
    
## Getting Started

To get started with NeoHeart, follow these steps:
1. **Assembly**: 
   - Ensure your NeoHeart board is fully assembled. If you didn't assemble the back using economic PCBA (which I recommend), solder the [battery holder](https://aliexpress.com/item/1005005506756152.html).
2. **Powering the Board**:
   - Insert a CR2032 battery into the battery holder, ensuring the positive side of the battery matches the positive marking on the board. Alternatively, you can also power the board with the 5V and GND headers
3. **Installing Software**:
   - Install the Legacy version of the [Arduino IDE](https://www.arduino.cc/en/software) (otherwise you will get the *a programmer is required to upload* error) or [PlatformIO](https://platformio.org/platformio-ide)
   - Install the Adafruit NeoPixel library.
4. **Connecting the Programmer**:
   - Connect your UPDI programmer to the UPDI header on your NeoHeart board. If using an Arduino or any other serial adapter that supports JTAG, follow the instructions provided [here](https://github.com/ElTangas/jtag2updi).
5. **Uploading the Firmware**:
   - Open the firmware sketch provided in the repository.
   - Select the correct board and port in your IDE of choice.
   - Click on the upload button to flash your NeoHeart.
6. **Enjoy**:
   - Once programmed, your NeoHeart will be ready to go. Just hit the button and watch those LEDs light up!
     
#### Dependencies
- [Adafruit's NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel)

## Manufacturing
This board was made with JLCPCB's manufacturing in mind, so all components were selected upon checking their available parts, trying to use as many basics parts as possible.
<br>Without including taxes, shipping and with current parts pricing 5 assembled boards (front only, having to solder the battery holder yourself) will cost around 52 USD dollars, so around 10 bucks a board.
<br><br>You can find all the files for production in the *releases* tab of this repository.
<br>All parts should available and ready to order, otherwise, feel free to send me a pull request.

## Contributing
Any contribution aimed to improving the software or the hardware of NeoHeart are very welcomed. 
Please feel free to fork this repo, make changes, and submit pull requests.

## License
CERN Open Hardware License - Strict (CERN-OHL-S)
