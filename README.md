# teensy-dac8568
A library for the Teensy 3.X devices to communicate with the DAC8568 module.

Use:

Be sure to designate your chip select pin right on bootup and set it HIGH right away to avoid issues.

```
pinMode(CHIP_SEL_DAC, OUTPUT);
digitalWrite(CHIP_SEL_DAC, HIGH);
```

This library can be used with any SPI channel.  

```
SPI.setDataMode(SPI_MODE1);
```

The data mode must be set to data mode 1 for proper functionality.

The SCK can be set to anywhere between 1MHz and 50MHz.

```
SPI1.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE1));
```

Each function returns a 4 byte (32 bit) message which can then be transfered over SPI either by the use of a buffer, or by bit shifting the message.

Example:

```
uint32_t writeInputReg = DAC8568_Write_Input_Reg_And_Update_All(CH_A, 8191);
SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE1));
digitalWrite(CHIP_SEL_DAC, LOW);
SPI.transfer(setup_msg >> 24);
SPI.transfer(setup_msg >> 16);
SPI.transfer(setup_msg >> 8);
SPI.transfer(setup_msg);
digitalWrite(CHIP_SEL_DAC, HIGH);
SPI.endTransaction();
```
