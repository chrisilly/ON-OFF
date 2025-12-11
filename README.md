Malmö University

Internet of Things and People

Lab 5

## Communicating over Bluetooth

I changed the line `Serial.begin(115200);` in the provided code to `Serial.begin(9600);` and set the Serial Monitor baud-rate to match. The following is the Serial Monitor output of the final attempt.

```
����������������������������������������������������������������ello Wo����������������������������������������������������������������ld!
I can receive just fine!
Wait, no I can send just fine too!
����������������������������������������������������������������t first I realised that the baud rate in the serial monitor mismatched the baud rate in the code. I first changed both to 115200 which resulted only in empty square symbols. Then, I changed both to 9600. Then, we got this result :)
Hmm... The upper-case 'A' got scrambled still. I wonder what causes that...
```

## Running the webserver

1. Ran the provided webserver code
2. Connected to the wi-fi emitted by the ESP32
3. Connected to the webserver (`192.168.4.1`)

![Screenshot of a website titled "ESP32 LED Control" containing an ON button and an OFF button.](image.png)

> [!TIP] Turns out that refreshing triggers the last button-press again, haha.

## Combining Bluetooth and the webserver

At first, my sketch was too big for the `DOIT ESP32 DEVKIT V1` board. With Adam's wisdom, I switched the board to `ESP32 Dev Module` after which I could select `Tools` > `Partition Scheme` > `Huge APP (3MB No OTA/1MB SPIFFS)`. Then, after unplugging and replugging the USB cable, I was able to upload the sketch.

This problem aside, adding bluetooth connectivity to the code was trivial.

## Sending the LED ON/OFF status via Bluetooth

I wanted to send the LED ON/OFF status via Bluetooth to my phone, but I'm not understanding how the `BluetoothSerial` `write()` function works (it doesn't accept strings or chars). This makes me even more confused about how it turns `Serial.read()` (which returns an `int`??) into the text typed into the Serial Monitor. What??

Turns out there was a `println()` function that I missed 🫠
