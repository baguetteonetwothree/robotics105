PROJECT(SimulatorNativeClient)

#ADD_SUBDIRECTORY(practical_socket)
#ADD_SUBDIRECTORY(client)
#ADD_SUBDIRECTORY(libsimpletext)
#ADD_SUBDIRECTORY(libsimpletools)

INCLUDE_DIRECTORIES(${SimulatorNativeClient_SOURCE_DIR}/Client
  ${SimulatorNativeClient_SOURCE_DIR}/Practical_Socket
  ${SimulatorNativeClient_SOURCE_DIR}/Simple_Libraries/PropellerGCC)

ADD_LIBRARY(client STATIC

  # Network library
  Practical_Socket/PracticalSocket.cpp

  # Client library
  Client/Console.cpp
  Client/ServerConnection.cpp
  Client/launcher.cpp
  Client/simulator.cpp

  # Servo library
  Simple_Libraries/Motor/libservo/servo.cpp
  
  # Shim propeller library
  Simple_Libraries/PropellerGCC/cog.cpp
  Simple_Libraries/PropellerGCC/CogManager.cpp
  Simple_Libraries/PropellerGCC/propeller.cpp
  Simple_Libraries/PropellerGCC/PropellerGCCStarter.cpp

  # Protcol library
#  Simple_Libraries/Protocol/libsimplei2c/libsimplei2c.c
#  Simple_Libraries/Protocol/libsimplei2c/simplei2c.c
  Simple_Libraries/Protocol/libsimplei2c/simplei2c.cpp

# Robotics library
  Simple_Libraries/Robotics/ActivityBot/libabcalibrate/abcalibrate.c
#  Simple_Libraries/Robotics/ActivityBot/libabcalibrate/libabcalibrate.c
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/Display.c
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/abdrive.c
  Simple_Libraries/Robotics/ActivityBot/libabdrive/abdrive.cpp
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/debug.c
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/getticks.c
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/goto.c
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/goto_test.c
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/libabdrive.c
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/ramp.c
#  Simple_Libraries/Robotics/ActivityBot/libabdrive/servoPins.c
# Simple_Libraries/Robotics/ActivityBot/libabdrive/trimset.c

# Sensors
#  Simple_Libraries/Sensor/libping/libping.c
#Simple_Libraries/Sensor/libping/ping.c
Simple_Libraries/Sensor/libping/ping.cpp

# Text libraries
  Simple_Libraries/TextDevices/libfdserial/fdserial.c
  Simple_Libraries/TextDevices/libfdserial/fdserial_utils.c
#  Simple_Libraries/TextDevices/libfdserial/libfdserial.c
  Simple_Libraries/TextDevices/libsimpletext/LibSimpleTextStarter.cpp
  Simple_Libraries/TextDevices/libsimpletext/doscanf.c
  Simple_Libraries/TextDevices/libsimpletext/dosprint.c
  Simple_Libraries/TextDevices/libsimpletext/dosput.c
  Simple_Libraries/TextDevices/libsimpletext/dprint.c
  Simple_Libraries/TextDevices/libsimpletext/dprinti.c
  Simple_Libraries/TextDevices/libsimpletext/dscan.c
  Simple_Libraries/TextDevices/libsimpletext/dscani.c
  Simple_Libraries/TextDevices/libsimpletext/floatToString.c
  Simple_Libraries/TextDevices/libsimpletext/getBin.c
  Simple_Libraries/TextDevices/libsimpletext/getChar.c
  Simple_Libraries/TextDevices/libsimpletext/getDec.c
  Simple_Libraries/TextDevices/libsimpletext/getFloat.c
  Simple_Libraries/TextDevices/libsimpletext/getHex.c
  Simple_Libraries/TextDevices/libsimpletext/getStr.c
  Simple_Libraries/TextDevices/libsimpletext/gets.c
  Simple_Libraries/TextDevices/libsimpletext/intprint.c
 # Simple_Libraries/TextDevices/libsimpletext/libsimpletext.c
  Simple_Libraries/TextDevices/libsimpletext/print.c
  Simple_Libraries/TextDevices/libsimpletext/printNumber.c
  Simple_Libraries/TextDevices/libsimpletext/printi.c
  Simple_Libraries/TextDevices/libsimpletext/putBin.c
  Simple_Libraries/TextDevices/libsimpletext/putBinDigits.c
  Simple_Libraries/TextDevices/libsimpletext/putChar.c
  Simple_Libraries/TextDevices/libsimpletext/putDec.c
  Simple_Libraries/TextDevices/libsimpletext/putDecDigits.c
  Simple_Libraries/TextDevices/libsimpletext/putFloat.c
  Simple_Libraries/TextDevices/libsimpletext/putFloatPrecision.c
  Simple_Libraries/TextDevices/libsimpletext/putHex.c
  Simple_Libraries/TextDevices/libsimpletext/putHexDigits.c
  Simple_Libraries/TextDevices/libsimpletext/putLine.c
  Simple_Libraries/TextDevices/libsimpletext/putStr.c
  Simple_Libraries/TextDevices/libsimpletext/putStrDigits.c
  Simple_Libraries/TextDevices/libsimpletext/putln.c
  Simple_Libraries/TextDevices/libsimpletext/safe_gets.c
  Simple_Libraries/TextDevices/libsimpletext/scan.c
  Simple_Libraries/TextDevices/libsimpletext/scanf_getf.c
  Simple_Libraries/TextDevices/libsimpletext/scanf_getl.c
  Simple_Libraries/TextDevices/libsimpletext/serial_close.c
  Simple_Libraries/TextDevices/libsimpletext/serial_open.c
  Simple_Libraries/TextDevices/libsimpletext/serial_rxtx.c
  Simple_Libraries/TextDevices/libsimpletext/simpleterm.c
#  Simple_Libraries/TextDevices/libsimpletext/simpleterm_close.c
  Simple_Libraries/TextDevices/libsimpletext/simpleterm_close.cpp
  Simple_Libraries/TextDevices/libsimpletext/sprint.c
  Simple_Libraries/TextDevices/libsimpletext/sprinti.c
  Simple_Libraries/TextDevices/libsimpletext/sscan.c
  Simple_Libraries/TextDevices/libsimpletext/stringToFloat.c
  Simple_Libraries/TextDevices/libsimpletext/writeBin.c
  Simple_Libraries/TextDevices/libsimpletext/writeBinDigits.c
  Simple_Libraries/TextDevices/libsimpletext/writeChar.c
  Simple_Libraries/TextDevices/libsimpletext/writeDec.c
  Simple_Libraries/TextDevices/libsimpletext/writeDecDigits.c
  Simple_Libraries/TextDevices/libsimpletext/writeFloat.c
  Simple_Libraries/TextDevices/libsimpletext/writeFloatPrecision.c
  Simple_Libraries/TextDevices/libsimpletext/writeHex.c
  Simple_Libraries/TextDevices/libsimpletext/writeHexDigits.c
  Simple_Libraries/TextDevices/libsimpletext/writeLine.c
  Simple_Libraries/TextDevices/libsimpletext/writeStr.c
  Simple_Libraries/TextDevices/libsimpletext/writeStrDigits.c
  Simple_Libraries/Utility/libsimpletools/LibSimpleToolsStarter.cpp
  Simple_Libraries/Utility/libsimpletools/addfiledriver.c
  Simple_Libraries/Utility/libsimpletools/cogend.c
  Simple_Libraries/Utility/libsimpletools/cognum.c
  Simple_Libraries/Utility/libsimpletools/cogrun.c
  Simple_Libraries/Utility/libsimpletools/count.c
#  Simple_Libraries/Utility/libsimpletools/dac.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_getByte.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_getFloat.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_getInt.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_getStr.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_init.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_initSclDrive.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_putByte.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_putFloat.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_putInt.c
#  Simple_Libraries/Utility/libsimpletools/eeprom_putStr.c
Simple_Libraries/Utility/libsimpletools/eeprom.cpp
  Simple_Libraries/Utility/libsimpletools/endianSwap.c
#  Simple_Libraries/Utility/libsimpletools/freqout.c
#  Simple_Libraries/Utility/libsimpletools/freqout.cpp
  Simple_Libraries/Utility/libsimpletools/getDirection.c
  Simple_Libraries/Utility/libsimpletools/getDirections.c
  Simple_Libraries/Utility/libsimpletools/getOutput.c
  Simple_Libraries/Utility/libsimpletools/getOutputs.c
  Simple_Libraries/Utility/libsimpletools/getState.c
  Simple_Libraries/Utility/libsimpletools/getStates.c
#  Simple_Libraries/Utility/libsimpletools/high.c
  Simple_Libraries/Utility/libsimpletools/high.cpp
  Simple_Libraries/Utility/libsimpletools/i2c_busy.c
  Simple_Libraries/Utility/libsimpletools/i2c_in.c
  Simple_Libraries/Utility/libsimpletools/i2c_init.c
  Simple_Libraries/Utility/libsimpletools/i2c_out.c
  Simple_Libraries/Utility/libsimpletools/irSensor.cpp
#  Simple_Libraries/Utility/libsimpletools/input.c
  Simple_Libraries/Utility/libsimpletools/itoa.c
#  Simple_Libraries/Utility/libsimpletools/low.c
  Simple_Libraries/Utility/libsimpletools/low.cpp
  Simple_Libraries/Utility/libsimpletools/mark.c
#  Simple_Libraries/Utility/libsimpletools/pause.c
  Simple_Libraries/Utility/libsimpletools/pause.cpp
  Simple_Libraries/Utility/libsimpletools/pause_us.c
  Simple_Libraries/Utility/libsimpletools/pulseIn.c
  Simple_Libraries/Utility/libsimpletools/pulseOut.c
  Simple_Libraries/Utility/libsimpletools/pwm.c
  Simple_Libraries/Utility/libsimpletools/rcTime.c
  Simple_Libraries/Utility/libsimpletools/reverse.c
#  Simple_Libraries/Utility/libsimpletools/sddriverconfig.c
  Simple_Libraries/Utility/libsimpletools/sddriverconfig.cpp
  Simple_Libraries/Utility/libsimpletools/setDacBits.c
  Simple_Libraries/Utility/libsimpletools/setDirection.c
  Simple_Libraries/Utility/libsimpletools/setDirections.c
  Simple_Libraries/Utility/libsimpletools/setGetTimeOfDay.cpp
  Simple_Libraries/Utility/libsimpletools/setIoDt.c
  Simple_Libraries/Utility/libsimpletools/setOutput.c
  Simple_Libraries/Utility/libsimpletools/setOutputs.c
  Simple_Libraries/Utility/libsimpletools/setPauseDt.c
  Simple_Libraries/Utility/libsimpletools/setStates.c
#  Simple_Libraries/Utility/libsimpletools/setTimeout.c
  Simple_Libraries/Utility/libsimpletools/setTimeout.cpp
  Simple_Libraries/Utility/libsimpletools/shiftIn.c
  Simple_Libraries/Utility/libsimpletools/shiftOut.c
  Simple_Libraries/Utility/libsimpletools/squareWave.c
  Simple_Libraries/Utility/libsimpletools/timeTicks.c
  Simple_Libraries/Utility/libsimpletools/timeout.c
  Simple_Libraries/Utility/libsimpletools/toggle.c
  Simple_Libraries/Utility/libsimpletools/wait.c

#  Simple_Libraries/Utility/libstacktest/cogrunStackTest.c
#  Simple_Libraries/Utility/libstacktest/cogstopStackTest.c
#  Simple_Libraries/Utility/libstacktest/cogendStackTest.c
#  Simple_Libraries/Utility/libstacktest/cogstartStackTest.c
#Simple_Libraries/Utility/libstacktest/libstacktest.c
Simple_Libraries/Utility/libstacktest/cogStackTest.cpp
  )