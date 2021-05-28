#include "Bewaesserungsstation.h"
#include "capaMeasure.h"
#include <avr/cpufunc.h>

capaMeasure::capaMeasure(PORT_t *cPort,uint8_t CxPin,uint8_t CrefPin)
{
  //ctor
  _cPort = cPort;
  _CxPin  = CxPin;
  _CrefPin  = CrefPin;
}

capaMeasure::~capaMeasure()
{
  //dtor
}

float capaMeasure::makeMeasure()
{
register uint16_t i;
PORT_t *locPort = _cPort;
register uint8_t aBit,bBit;

  aBit = 1<<_CxPin;
  bBit = 1<<_CrefPin;
  locPort->DIRSET = bBit | aBit; // A und B Ausgang
  uint16_t c0 = 1000;
  cli();
  for(i=0;i<1500;i++)
  {
    locPort->DIRCLR = bBit; // Eingang hochohmig?
    locPort->OUTSET = aBit;
    locPort->DIRSET = aBit; // Eingang hochohmig?
    _NOP();
    _NOP();
    _NOP();


    if( (locPort->IN & (bBit)) == 0 )
    {
      sei();
      break;
    }
    locPort->DIRCLR   = aBit;    // A Eingang
//    PORTCFG.MPCMASK  = _CxPin;   // A Pullups aus
//    _cPort->PIN0CTRL = 0;
    locPort->DIRSET = bBit;
    //_delay_us(1);
  }
  PORTCFG.MPCMASK  = aBit | bBit;  // A und B Pullups aus
  locPort->PIN0CTRL = 0;
  locPort->OUTCLR   = bBit | aBit;
  locPort->DIRSET   = bBit | aBit;   // A und B Ausgang
  //return(7500.0/i);
  return(i);
}
