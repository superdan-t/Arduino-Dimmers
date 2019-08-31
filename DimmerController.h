#ifndef DimmerController_h
#define DimmerController_h

#include "Arduino.h"
#include "Dimmers.h"

class Dimmer;

class DimmerController {
	public:
		void onBegin( void(*f)(Dimmer) );
		void onEnd( void(*f)(Dimmer) );
		void onIntensityChanged( void(*f)(Dimmer) );
		void onEffectChanged( void(*f)(uint8_t, Dimmer) );
		void checkPinValidity( bool(*f)(uint8_t) );
		void (*_beginFunc)(Dimmer);
		void (*_endFunc)(Dimmer);
		void (*_intensityFunc)(Dimmer);
		void (*_effectFunc)(uint8_t, Dimmer);
		bool (*_pinFunc)(uint8_t);
	private:
	
};

#endif