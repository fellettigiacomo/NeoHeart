# NeoHeart - Revision 2.2🎉
Hardware and Software design for an Open Source ATtiny816-based heart shaped PCB with Addressable LEDs.
<br><br>⚠️ **Warning**: Unfortunately, this release is not yet ready for production. There are still issues with the CR2032 battery not providing enough power, causing glitches and freezes in the LEDs. I'm currently working on a fix. ⚠️
<br><br>![board-render](https://github.com/fellettigiacomo/NeoHeart/blob/main/images/render.png?raw=true)
## Project sponsor: PCBWay
Thanks to [PCBWay](https://www.pcbway.com/) for sponsoring this open-source project. Check out the sponsorship section below to learn more about their support.

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
  
## 2.2 Upgrades

- **Efficient power design**: the TPS61240 boost converter has been fully redesigned—now controlled by the MCU via the Enable pin (no more external MOSFET). Improved input stability with additional capacitors, removed feedback resistors for better overall efficiency.
- **Extended Battery Life**: ultra-low 0.14 µA quiescent current enables over 10 years of idle operation and supports 1000+ button presses on a single CR2032 cell.
- **Enhanced ATiny816 Stability**: added decoupling capacitors to ensure reliable and noise-free microcontroller performance.
- **Upgraded Battery Holder**: replaced the CR2032 holder with a more robust and durable version to prevent mechanical failure.
- **Improved Grounding**: added a dedicated ground plane for better signal integrity and reduced noise.
    
## Getting Started

To get started with NeoHeart, follow these steps:
1. **Assembly**: 
   - If you didn't assemble the back using economic PCBA (which I recommend), solder the [battery holder](https://aliexpress.com/item/1005005506756152.html).
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

## Manufacturing
Without including taxes, shipping and with current parts pricing 5 assembled boards (front only, having to solder the battery holder yourself) will cost around 52 USD dollars, so around 10 bucks a board.
<br><br>You can find all the files for production in the *releases* tab of this repository.
<br>All parts should available and ready to order, otherwise, feel free to send me a pull request.

## Contributing
Any contribution aimed to improving the software or the hardware of NeoHeart are very welcomed. 
Please feel free to fork this repo, make changes, and submit pull requests.

## PCBWay
I've been able to prototype the latest NeoHeart Release thanks to PCBWay that reached out to sponsor this project.
<br> You can see a photo of the boards that PCBWay sent me down here, you can also watch my unboxing video [here](https://youtu.be/b7MC2HfKiS8)
### Why PCBWay?
- **Quality and Reliability**: PCBWay's PCBs meet the highest standards of quality and reliability, they are also capable of meeting the technical demands of any project, from simple projects like mine to very complicated projects.
- **Customization and Flexibility**: They offer extensive customization options, allowing board designers to tailor their PCBs precisely to their project's needs.
- **Community Support**: PCBWay is a strong supporter of open-source projects, offering sponsorships and discounts to help bring these community-beneficial projects to life. Their commitment to the open-source community makes them a particularly good match for community-driven initiatives.
- **Rapid Prototyping**: Time is very important in project development, and PCBWay’s rapid prototyping service allows for quick turnarounds without sacrificing quality.

### My Experience with PCBWay
It's been fantastic: our collaboration not only consisted in receiving high-quality PCBs (with PCBA), experiencing a seamless process facilitated by their expert team, from selecting the right components to checking for errors. 
<br>I've also received photos of the assembled boards before shipping to ensure everything was perfect!.
<br><br>Despite different time zones, the response time from their support team was impressive, which I found incredibly helpful.
<br><br>As I said before, I think it's fantastic that big companies like PCBWay are committed to the open-source community, helping students worldwide bring their projects to life. <b> Thanks again PCBWay!! </b>

## License
CERN Open Hardware License - Strongly Reciprocal (CERN-OHL-S)
