#include "Dimmers.h"
#include "Arduino.h"

//	Get properties of dimmer

uint8_t DimmerControlMaster::pin(dimmer_t *dim) {
	return dim->_pin;
}

uint8_t DimmerControlMaster::remoteID(dimmer_t *dim) {
	return dim->_pin;
}

uint8_t DimmerControlMaster::method(dimmer_t *dim) {
	return dim->_method;
}

uint8_t DimmerControlMaster::intensity(dimmer_t *dim) {
	return dim->_intensity;
}

uint8_t DimmerControlMaster::function(dimmer_t *dim) {
	return dim->_function;
}

uint8_t DimmerControlMaster::data(dimmer_t *dim, uint8_t index) {
	if (index < 5 && index >= 0) {
		return dim->_data[index];
	}
}

uint8_t DimmerControlMaster::data(dimmer_t *dim, uint8_t *arrayStart) {
	for (uint8_t i = 0; i < 5; i++) {
		arrayStart[i] = dim->_data[i];
	}
}

uint8_t DimmerControlMaster::isEnabled(dimmer_t *dim) {
	return dim->_enabled;
}

uint8_t DimmerControlMaster::isBipolar(dimmer_t *dim) {
	return dim->_bipolar;
}

uint8_t DimmerControlMaster::isInverse(dimmer_t *dim) {
	return dim->_inverse;
}

//	Set properties of dimmer

void DimmerControlMaster::setPin(dimmer_t *dim, uint8_t pin) {
	//Restores the old pin (if initialized) to its old state.
	if (dim->__initialized) {
		digitalWrite(dim->_pin, LOW);
		pinMode(dim->_pin, INPUT);
	}
	dim->_pin = pin;
	pinMode(pin, OUTPUT);
	dim->__initialized = true;
}

void DimmerControlMaster::setRemoteID(dimmer_t *dim, uint8_t id) {
	dim->_pin = id;	//If it is a remote dimmer, the pin doesn't matter, so we can store the ID here
}

void DimmerControlMaster::setMethod(dimmer_t *dim, uint8_t method) {
	dim->_method = method;
}

/* void DimmerControlMaster::makeLocal(dimmer_t *dim) {
	//Default option. Dimmer corresponds to a pin on this device.
	
}

void DimmerControlMaster::makeRemote(dimmer_t *dim) {
	
} */

void DimmerControlMaster::setFunction(dimmer_t *dim, uint8_t function) {
	dim->_function = function;
}

void DimmerControlMaster::setData(dimmer_t *dim, uint8_t index, uint8_t data) {
	dim->_data[index] = data;
}

void DimmerControlMaster::setData(dimmer_t *dim, uint8_t *data) {
	for (uint8_t i = 0; i < 5; i++) {
		dim->_data[i] = data[i];
	}
}

void DimmerControlMaster::enable(dimmer_t *dim) {
	dim->_enabled = true;
}

void DimmerControlMaster::disable(dimmer_t *dim) {
	dim->_enabled = false;
}

void DimmerControlMaster::bipolar(dimmer_t *dim) {
	dim->_bipolar = true;
}

void DimmerControlMaster::dimming(dimmer_t *dim) {
	dim->_bipolar = false;
}

void DimmerControlMaster::inverse(dimmer_t *dim) {
	dim->_inverse = true;
}

void DimmerControlMaster::direct(dimmer_t *dim) {
	dim->_inverse = false;
}
