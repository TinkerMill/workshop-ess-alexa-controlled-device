# Controlling an IoT Device Using an Amazon Alexa Skill Workshop

In this workshop, you will work with a small microcontroller unit (MCU), connect it to the Internet and an MQTT broker, and also configure an Alexa Skill to query and control the device. Beyond that, there are also stretch goals to augment and enhance both your thing (connected device) and the Alexa skill.

This is a beginner  workshop and beyond an understanding of how to use a command line interface (CLI, Windows Command Prompt or macOS Terminal) there are no specific expertise needed.

At the end of the workshop you will come away with:

* Basics of how sensors are connected and operate on physical devices,
* Understanding of how to create programs for constrained devices,
* Connecting a device to the Internet via WiFi,
* Communicate with the connected device by a publish/subscribe message broker,
* Structure of an Alexa skill and how to create and test a development skill

This workshop will *not* cover the following in any detail:

* Programming,
* Workflows for embedded system development,
* Specifics on constructing an Alexa Skill,
* Intergation with \<insert product/service/cloud here\> beyond those used

## Prerequisites

To participate in this workshop, you will need a few hardware components, along with accounts on a few services. The total cost of components is less than USD$20, and can be reused for other projects! Here are the components you need prior to the workshop:

- Hardware
  1. Your personal laptop - This can be Windows or macOS, with the ability to download and install the software in the Software section of the prerequisites
  2. ESP32 Microcontoller - The ESP32-DevKit-C [[Amazon]](https://www.amazon.com/Espressif-ESP32-ESP32-DEVKITC-ESP-WROOM-32-soldered/dp/B01N0SB08Q)[[Adafruit]](https://www.adafruit.com/product/3269) is a system development board with integrated Wi-Fi, Bluetooth Low Energy, and support for secure connections
  3. 3 Color LED Module - A pre-configred module with included cable to connect to the MCU for turning on or off the LED by color
  4. USB Cable - A high quality cable that provides both power and data. Please select a cable based on the ports your laptop supports such as Type-A or Type-C to [Micro USB](https://en.wikipedia.org/wiki/USB#Receptacle_(socket)_identification).
  5. Amazon Echo device (optional) - For testing (intermediate level as it requires you to create the skill within your own Amazon Developer account)
- Software
  1. [Microsoft Visual Studio Code (VSCode)](https://code.visualstudio.com/download) - Used for the MCU development process
  2. [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode) - Follow the instructions to download and install within VSCode
  3. [ngrok](https://ngrok.com/download) - A reverse proxy that allows access to our locally running Alexa skill
  4. Python 3

