#ifndef CAPAMEASURE_H
#define CAPAMEASURE_H

#include <avr/io.h>
#include <stdbool.h>

#include <avr/interrupt.h>

#include <avr/sleep.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Referenz: https://www.elektronik-labor.de/AVR/LPtiny85/LPtiny85_8.html

/*

CrefPin -------+
              ---  Cref
              ---
CxPin ---------+
              ---
              ---  Cx
GND -----------+

*/
/*

Cr  -----------+
              ---  Cref
              ---
C+Cr  ---------+
              ---
              ---  Cx
C-  -----------+

*/


class capaMeasure
{
  public:
    capaMeasure(PORT_t *cPort,uint8_t CxPin,uint8_t CrefPin);
    virtual ~capaMeasure();

    uint16_t Getthreshold() { return threshold; }
    void Setthreshold(uint16_t val) { threshold = val; }
    uint16_t Getcounter() { return counter; }
    void Setcounter(uint16_t val) { counter = val; }
    float makeMeasure();

  protected:

  private:
    uint16_t threshold;
    uint16_t counter;
    PORT_t*   _cPort;
    uint8_t  _CxPin;
    uint8_t  _CrefPin;
};

#endif // CAPAMEASURE_H
