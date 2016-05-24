





#include "chip.h"

#ifndef CIAATIMER_H_
#define CIAATIMER_H_


void ciaaTIMER1Init(void);
void ciaaTIMER1Set(uint32_t usec);
void ciaaTIMER1Enable(void);
void ciaaTIMER1Disable(void);
bool ciaaTIMER1Match(uint8_t match);
void ciaaTIMER1ClearMatch(uint8_t match);

#endif /* CIAATIMER_H_ */