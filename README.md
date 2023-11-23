This project is designed to show reading and writing values over bacnet. It uses bacnet-stack, and is implemented using ESP-IDF.

# Usage

Flash two ESP32s with the code, and connect them to the same network. When a button is pressed on one, the other will light up. You can manually set the wifi network and other settings in the Kconfig file. You will have to change the device instance number in the code to be unique for each device.

![Demo](./demo.gif)
