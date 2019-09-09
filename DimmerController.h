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
		void onEffectDataChanged( void(*f)(uint8_t, uint8_t, Dimmer) );
		void onPropChanged( void(*f)(uint8_t, uint8_t, Dimmer) );
		void onCheckPinValidity( bool(*f)(uint8_t) );
		void (*_beginFunc)(Dimmer);
		void (*_endFunc)(Dimmer);
		void (*_intensityFunc)(Dimmer);
		void (*_effectFunc)(uint8_t, Dimmer);
		void (*_dataFunc)(uint8_t, uint8_t, Dimmer);
		uint8_t (*_pinFunc)(uint8_t);
	private:
	
};

#endif