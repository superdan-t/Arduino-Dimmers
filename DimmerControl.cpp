#include "Dimmers.h"
#include "Arduino.h"

void DimmerControlMaster::initialize(dimmer_t *dim) {
	pinMode(dim->_pin, OUTPUT);
	//setIntensity(&dim, 0);
	dim->__initialized = true;
}