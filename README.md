# Controlling an IoT Device Using Amazon Alexa Workshop

In this workshop, you will work with a small microcontroller unit (MCU), connect it to the Internet and an MQTT broker, and also configure an Alexa Skill to query and control the device. Beyond that, there are also stretch goals to augment and enhance both your thing (connected device) and the Alexa skill.

**insert architecture diagram** here

This is a beginner  workshop, and beyond an understanding of how to use a command line interface (CLI, Windows Command Prompt or macOS Terminal), there is no specific technical expertise required.

At the end of the workshop you will come away with:

* Basics of how sensors are connected and operate on physical devices
* Understanding of how to create programs for constrained devices
* Connecting a device to the Internet via WiFi
* Communicate with the connected device by a publish/subscribe message broker
* Structure of an Alexa skill and how to create and test a development skill

This workshop will *not* cover the following:

* Programming skills in general
* Workflows for embedded system development
* Specifics on constructing an Alexa Skill
* Integration with \<insert your favorite product/service/cloud here\> beyond those used

## Prerequisites

To participate in this workshop, you will need a few hardware components, along with accounts on a few cloud services such as the [Amazon Developer Portal](https://developer.amazon.com/). The total cost of components is less than USD$20, and can be reused for other projects! Here are the components you need prior to the workshop:

* Hardware
  1. Your personal laptop - This can be Windows or macOS, with the ability to download and install the software in the Software section of the prerequisites. *Note*: Non-Windows/Mac laptops such as Chromebooks are not supported.
  2. ESP32 Microcontoller - The ESP32-DevKit-C [[Amazon]](https://www.amazon.com/Espressif-ESP32-ESP32-DEVKITC-ESP-WROOM-32-soldered/dp/B01N0SB08Q)[[Adafruit]](https://www.adafruit.com/product/3269) is a system development board with integrated Wi-Fi, Bluetooth Low Energy, and support for secure connections
  3. LED - A pre-configred module with included cable and resistor to connect to the MCU for turning on or off the LED.
  4. USB Cable - A high quality cable that provides both power and data. Please select a cable based on the ports your laptop supports such as Type-A or Type-C to [Micro USB](https://en.wikipedia.org/wiki/USB#Receptacle_(socket)_identification).
  5. Amazon Echo device (optional) - For testing (intermediate level as it requires you to create the skill within your own Amazon Developer account) skills via voice

Depending upon the workshop presenter, some or all of the hardware may be provided. For this repo, the above list is used for reference.

* Software on Laptop
  1. [Microsoft Visual Studio Code (VSCode)](https://code.visualstudio.com/download) - Used for the MCU development process
  2. [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode) - Follow the instructions to download and install within VSCode
  3. [ngrok](https://ngrok.com/download) - A reverse proxy that allows access to our locally running Alexa skill
  4. Python 3

As you will be installing, compiling, and running code on your laptop, is it recommended to use a recent laptop with sufficient disk space and CPU/memory.

## Modules

This section references the workshop modules. Each module will build upon the previous ones, so please make sure you have completed the *Success* section of each module before moving on to the next. All modules are structured as follows:

* Discrete - Each module is a separate document. It is recommended to open the module into a new tab.
* Comprehension - The steps of each module are designed to teach you something new. Look for the light bulb icons, :bulb:, for explanations of *why* you performed the steps, and *what* that achieves.
* Summary and Verbose - Each section or sub-section will have a concise set of steps to follow for those that are familiar with the steps, and also a detailed step-by-step process.

### [1 - Local Development Environment](docs/1_local_dev_env.md)

Upon completion a local editor, development tools, and clone of this repository will be setup locally on your laptop. Also, you will have verified all web sites and developer accounts needed.

### [2 - Local LED Toggle](docs/2_local_led.md)

Upon completion you will have programmed your development board to toggle the LED when pressing the user button.

### [3 - WiFi and IoT Connection](docs/3_wifi_mqtt.md)

Upon completion your development board will be connected to an MQTT broker endpoint and able to send and receive messages.

### [4 - Alexa Skill and End-to-End](docs/4_alex_skill.md)

Upon completion you will have created your skill in the Amazon console executing code on your local laptop. That, in turn, will send the messages to control the LED on your MCU.

## Reference

### Meetup Description

This is for the meetup page registration.

* Title: Create an Alexa Skill to Control You Very Own IoT Device
* Price: $15.00 /per person (non-Tinkermillians)

   ---

* Description (text only)

  ```Text
  Ever wanted to create an Amazon Alexa Skill where you can control a light or other sensors on your very own Internet of Things (IoT) device? In this workshop you will do that, and more. **Please read the requirements section at the end, as this workshop does require you to bring a laptop to perform the workshop activities, and does require a small amount of hardware.**
  
  This workshop will cover the end-to-end:
  
  * How to create a private Alexa Skill
  * Work with a small microcontroller hardware and program it
  * Use your Skill to communicate with the controller over the Internet
  
  This three hour course will start with a session covering the main topics and then a series of modules you will complete in the workshop:
  
  * Setting up your laptop for both Alexa skills development and programming the microcontroller
  * How to structure an Alexa Skill using the Amazon Developer Console
  * Running your skill locally to test, and how to take advantage of cloud computing to publish
  * Programming your microcontroller to be an IoT device that can listen for commands and publish sensor data
  * Using an Echo device (or the console) to command your microcontroller to toggle an LED
  * Where to go from here (enchancing the full Skill/Device experience)
  
  The price for the course is free for Tinkermill Members and $15 /per person for non-members--if you bring your own hardware. If you would like to be provided a kit (an ESP32 microcontoller, breadboard, and LED), there is an additonal $20 cost. **Please indicate when signing up if you would like a kit or will be bringing your own hardware.**
  
  **You need to bring a laptop capable of connecting to the Internet and with a local USB port**. Please review the prerequisites section of the workshop's GitHub repository(https://github.com/TinkerMill/workshop-ess-alexa-controlled-device) for specifics on the laptop specifications and hardware required.
  ```

  End of reference section.