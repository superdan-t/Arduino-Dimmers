#include "Arduino.h"
#include "Dimmers.h"
#include "Wire.h"

DimmerControlMaster::DimmerControlMaster() {
	_tickDelay = 50;
}

//	Control

void DimmerControlMaster::update(dimmer_t *dim) {
	
}

void setIntensity(dimmer_t *dim, uint8_t intensity) {
	
}

//	Input

void DimmerControlMaster::dimmerReceiveEvent(int16_t amount) {

}

void DimmerControlMaster::dimmerRequestEvent() {
	
}

//	Output

void DimmerControlMaster::enableWireMethod(uint8_t address) {
	_wireEnabled = true;
	Wire.begin(address);
	Wire.onReceive(DimmerControlMaster::dimmerReceiveEvent);
	Wire.onRequest(dimmerRequestEvent);
}

void DimmerControlMaster::disableWireMethod() {
	_wireEnabled = false;
	Wire.end();
}



