/*
	DimmerControlMaster by Daniel Tierney
	Provides functions, special effects, and controls for outputs at an abstracted level
*/

#ifndef DimmerControlMaster_h
#define DimmerControlMaster_h

#include "Arduino.h"

typedef struct dimmer_t {
	uint8_t _pin;
	uint8_t _method = 0;
	uint8_t _intensity = 0;
	uint8_t _function = 0;
	uint8_t _data[5];
	uint8_t _enabled = false;
	uint8_t _bipolar = false;
	uint8_t _inverse = false;
	uint8_t __initialized = false;
} Dimmer;

class DimmerControlMaster {
	public:
		DimmerControlMaster();
		
		//	Control
		
		void initialize(dimmer_t *dim);
		
		void update(dimmer_t *dim);
		void setIntensity(dimmer_t *dim, uint8_t intensity);
		
		//	Input
		
		static void dimmerReceiveEvent(int16_t amount);
		static void dimmerRequestEvent();
		
		//	Output
		
		void enableWireMethod(uint8_t address);
		void disableWireMethod();
		
		//	Get properties of dimmer
		
		uint8_t pin(dimmer_t *dim);
		uint8_t remoteID(dimmer_t *dim);
		uint8_t method(dimmer_t *dim);
		uint8_t intensity(dimmer_t *dim);
		uint8_t function(dimmer_t *dim);
		uint8_t data(dimmer_t *dim, uint8_t index);
		uint8_t data(dimmer_t *dim, uint8_t *arrayStart);
		uint8_t isEnabled(dimmer_t *dim);
		uint8_t isBipolar(dimmer_t *dim);
		uint8_t isInverse(dimmer_t *dim);
		
		//	Set properties of dimmer
		
		void setPin(dimmer_t *dim, uint8_t pin);
		void setRemoteID(dimmer_t *dim, uint8_t id);
		void setMethod(dimmer_t *dim, uint8_t method);
		void setFunction(dimmer_t *dim, uint8_t function);
		void setData(dimmer_t *dim, uint8_t index, uint8_t data);
		void setData(dimmer_t *dim, uint8_t *data);
		void enable(dimmer_t *dim);
		void disable(dimmer_t *dim);
		void bipolar(dimmer_t *dim);
		void dimming(dimmer_t *dim);
		void inverse(dimmer_t *dim);
		void direct(dimmer_t *dim);
		
	private:
		uint8_t _tickDelay;
		uint8_t _wireEnabled;
		uint64_t _nextTick;
};

#endif