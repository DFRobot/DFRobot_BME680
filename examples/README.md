# Attention:

IAQ process is for experienced people.
Wait about 5 minutes to get correct IAQ data.

IAQ example compatibility

platform                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
ESP8266  |      √       |             |            | SDK -V 2.3.0

Others can't work now.

## How to get IAQ?

Processing.(Reference in docs_for_iaq\BST-BME680-AN008-45.pdf chapter 2.4, page 15)

### Platform

#### esp8266

1.We need to copy the file docs_for_iaq\esp8266\libalgobsec.a and paste the file into the hardware\esp8266\2.3.0\tools\sdk\lib folder.

2.Find eagle.app.v6.common.ld in your esp8266 SDK folder.

(if you do't modify it before, you can copy docs_for_iaq/esp8266/platform.txt to replace)

The linker file found at hardware\esp8266\2.3.0\tools\sdk\ld\eagle.app.v6.common.ld needs to be modifed.
Inserting the line *libalgobsec.a:(.literal .text .literal.* .text.*) after the line *libm.a:(.literal .text .literal.* .text.*).

3.Find platform.txt in your esp8266 SDK folder.

(if you do't modify it before, you can copy docs_for_iaq/esp8266/platform.txt to replace)

Finally, we need to change the linker argument, telling the linker to include BSEC file. This is achieved by adding the
argument -lalgobsec to the line compiler.c.elf.libs=-lm -lgcc ... found in hardware\esp8266\2.3.0\platform.txt.
