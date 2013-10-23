NameThatStyle
=============

For Name that Style Discovery Museum exhibit.


How to upload the program using Arduino IDE
===========================================
1. Add the following to the \arduino\hardware\arduino\boards.txt file (works for Arduino 1.0)

  ##############################################################

  atmega328smd16e.name=ATmega328 SMD (16Mhz Ext, no boot)

  atmega328smd16e.upload.protocol=stk500
  atmega328smd16e.upload.maximum_size=30720
  atmega328smd16e.upload.speed=57600

  atmega328smd16e.bootloader.low_fuses=0xFF
  atmega328smd16e.bootloader.high_fuses=0xDA
  atmega328smd16e.bootloader.extended_fuses=0x05
  atmega328smd16e.bootloader.path=arduino:atmega
  atmega328smd16e.bootloader.unlock_bits=0x3F
  atmega328smd16e.bootloader.lock_bits=0x0F

  atmega328smd16e.build.mcu=atmega328p
  atmega328smd16e.build.f_cpu=16000000L
  atmega328smd16e.build.core=arduino:arduino
  atmega328smd16e.build.variant=arduino:eightanaloginputs

  ##############################################################

  atmega328smd8i.name=ATmega328 SMD (8Mhz Int, no boot)

  atmega328smd8i.upload.protocol=stk500
  atmega328smd8i.upload.maximum_size=30720
  atmega328smd8i.upload.speed=57600

  atmega328smd8i.bootloader.low_fuses=0xE2
  atmega328smd8i.bootloader.high_fuses=0xD7
  atmega328smd8i.bootloader.extended_fuses=0x05
  atmega328smd8i.bootloader.unlock_bits=0x3F
  atmega328smd8i.bootloader.lock_bits=0x0F

  atmega328smd8i.build.mcu=atmega328p
  atmega328smd8i.build.f_cpu=8000000L
  atmega328smd8i.build.core=arduino:arduino
  atmega328smd8i.build.variant=arduino:eightanaloginputs

  ##############################################################

  atmega328smd1i.name=ATmega328 SMD (1Mhz Int, no boot)

  atmega328smd1i.upload.protocol=stk500
  atmega328smd1i.upload.maximum_size=30720
  atmega328smd1i.upload.speed=57600

  atmega328smd1i.bootloader.low_fuses=0x62
  atmega328smd1i.bootloader.high_fuses=0xD7
  atmega328smd1i.bootloader.extended_fuses=0x05
  atmega328smd1i.bootloader.unlock_bits=0x3F
  atmega328smd1i.bootloader.lock_bits=0x0F

  atmega328smd1i.build.mcu=atmega328p
  atmega328smd1i.build.f_cpu=1000000L
  atmega328smd1i.build.core=arduino:arduino
  atmega328smd1i.build.variant=arduino:eightanaloginputs

2. Restart Arduino IDE
3. Set the correct board Menu > Tools > Boards > ATmega328 SMD (8Mhz Int, no boot)
4. Select your programmer Menu > Tools > Programmer
5. Upload via Menu > File > Upload using programmer

