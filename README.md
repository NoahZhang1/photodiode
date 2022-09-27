### Quick Start

Go to File/Preference and paste this url (http://arduino.esp8266.com/stable/package_esp8266com_index.json) to the additional board manager
![image](https://user-images.githubusercontent.com/41597923/192609700-5f04c9fc-1ad6-4b0d-815b-82b21585d8ec.png)

Go to Tools/boards/board manager, search esp8266 and install it 
![image](https://user-images.githubusercontent.com/41597923/192610410-df366e90-66af-47e3-ae88-a160d4e83b69.png)

After installation, go to Tools/boards and select NodeMCU 1.0
![image](https://user-images.githubusercontent.com/41597923/192610593-cd122ef3-d9be-4b51-b48f-70137d9a4ce6.png)

Last, go to the port selection and select the right port you plug in
![image](https://user-images.githubusercontent.com/41597923/192611018-212a8a3a-4428-4fb9-9b79-0cfd162136d5.png)






### Files and Directories:

The architecture of files and directories are as follows:

* esp8266_blinking.ino
* interrupt_adc_read.ino


# interrupt_adc_read
An photodiode frequency reader build based on LTC1050 amplifier and ESP8266
[LTC1050 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/1050fb.pdf)



# BlinkingLED_esp8266
--Design for SSVEP signal experiments
A simple NodeMCU based code that makes LED blink at certain frequency

Two LED blinking from 4Hz to 100Hz with aggregating and declining frequency change
serial begin with 115200, use 9600 or 250000 if it does not work
