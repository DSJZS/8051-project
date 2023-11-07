#ifndef __DS18B20_H__
#define __DS18B20_H__

#include <REGX52.H>
#include "OneWire.h"

void DS18B20_ConvertTEMP(void);
float DS18B20_ReadTEMP(void);

#endif