# Module 3: WiFi and MQTT

In this module, you will create the next Platformio project and configure the MCU to connect to WiFi and connect to the CloudMQTT broker to *subscribe* for commands from the Alexa Skill.

Upon completion you will have created a new Platformio application and programmed your development board to act as a smart device for your Alexa skill.

This module covers:

* Creating a new Platformio project
* Configuring for WiFi and Internet connectivity
* Use the on-board USER button to send a test message
* Use the CloudMQTT console to monitor messages
* Using the monitor to verify connections

## Create and Configure Smart Device Application

Follow the procedure from module 2 to create a new Platformio application and copy the template code:

1. Create new Platformio project and enter the following:

   **Name**: smart_device

   **Board**: Espressif ESP32 Dev Module

   **Framework**: ESP-IDF

   **Location**: Uncheck and select the `tm_iot` directory then click Finish

This should complete almost immediately because the dependencies have been installed from the first application.

❗️ If the folder does not get added automatically, right-click in the Explorer pane and select *Add Folder to Workspace...,* navigate to the `tm_iot` and select the `smart_device` folder and click *Add*.

There are more files and directories that need to be copied than the previous module. Make sure the following are copied over the existing files from the `tm_iot/workshop-ess-alexa-controlled-device/code/mod_3-smart_device` location:

* `src/main.c`
* `platformio.ini`

And then *create* the `data` directory and copy over the `cloudmqtt.pem` file, which is the certificate of the signing certificate authority (Comodo) for the CloudMQTT service.

## Modify Parameters

The main C code, `main.c` has values that need to be set for your specific CloudMQTT account. In VSCode, click on the `main.c` file and scroll down to the *Set parameters here* section. First, change the values for WiFi by entering, case-sensitive, the SSID and password. For, example, if the SSID is *Tinkermill* and the password is *notTheActualPassword*, the `#define` statements would look like this:

```c
// Set WiFi credentials - CASE is important!
#define CONFIG_WIFI_SSID        "TinkerMill"
#define CONFIG_WIFI_PASSWORD    "notTheActualPassword"
```

Next, login into your CloudMQTT account, select your instance, and place the values for *Server*, *User*, *Password*, and *Websockets Port (TLS only)* into the next section of `main.c`:

```c
// Enter your CloudMQTT endpoint and credentials
#define MQTT_HOST               "FQDN"            // <--- Server value
#define MQTT_WEBSOCKET_PORT     "00000"           // <--- Websockets Port (TLS only) value
#define MQTT_USERNAME           "paste_here"      // <--- User value
#define MQTT_PASSWORD           "paste_here"      // <--- Password value
```

Save the changes to `main.c`. Leave the browser open to CloudMQTT, you will be using this in the next step.

## Build, Load, Test

Follow the same steps in the previous module to build, upload, and monitor serial the new application. You will see a lot for information steps as the MCU connects to WiFi and the connects and subscribes to the *command* topic on CloudMQTT. Here is an example of the *monitor serial* output:

```
GAA - monitor serial output
```

Once connected, from the CloudMQTT website, click on the *Websocket UI*, and once connected, enter the following into the *Send message* fields:

* Topic: `command`
* Message: `led=on`

and then click *Send*. This will publish the *message* (or payload) of `led=on` to the *topic* of `command`, which your MCU is subscribed. Sending the *on* command should do two things, 1) turn the LED on and 2) log an info statement in the *monitor serial* window.

:bulb: What is happening in the code is that it is listening for messages on the subscribed topic, and then when one of interest comes through, take action. In this case, `led=on` will raise the GPIO pin and turn on the LED. The `led=off` command lowers the GPIO, hence turning off the LED.

In this case, the LED is our device that the Alexa skill will act on, by sending a message:

"*Alexa, ask smart device to turn on the light*" would send a `led=on` to the topic `command` on CloudMQTT.

## What Was Learned

In this module you:

* practiced creating another application for you MCU (this is common!)
* configured and tested the application connecting to an MQTT broker in a secure way
* verified messages sent were received by the MCU and acted upon

