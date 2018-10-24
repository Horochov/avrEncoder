# avrEncoder
Code to use rotary encoder with AVR MCU. It was written for Atmega328p, but probably will work with other Atmega MCUs.

This lib uses my [avrElapsedTime lib](https://github.com/Horochov/avrElapsedTime). It is probably unnecessary. Feel free to erase it.

# How to use this lib
## Set pins
Set _ENC_PIN_Px and _ENC_PORT_Px to appropriate pin values.

P1 is interrupt pin, and P2 is another pin.
## encoder_init()
Just call it in init section.
## encoder_status()
When encoder is rotated, will increment/decrement value returned by this function. Incr/decr operation is dependant on rotation direction.
## _ENC_INTERRUPT_TYPE
### set to _ENC_HW_INT
Will use INTx pin. You will also have to set _ENC_INTx to 0 (INT0) or 1 (INT1).
### set to _ENC_PCINT
Will use PCINTx. Set _ENC_PCINTx to PCINTx 'x' minus first element from PCIEx register. I.e. PCINT18 will be 18-16 (16 is first in PCIE2, alco here is 18).

_ENC_PCIEx - set it to PCIEx register in which is placed PCINTx.

You will have to manually call encoder_pcintIsrCall(); in ISR(PCINTx_vect). For PCINT18, call it in PCINT2_vect.
