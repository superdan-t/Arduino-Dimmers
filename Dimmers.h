#ifndef Dimmers_h
#define Dimmers_h

#include "Arduino.h"
#include "DimmerController.h"

class DimmerController;

class Dimmer {
	public:
	
		//	Control
		
		void begin();
		void begin(DimmerController dc);
		void end();
		void end(DimmerController dc);
		
		//	Operation
		
		void setIntensity(uint8_t intensity);
		void setIntensity(uint8_t intensity, DimmerController dc);
		void setEffect(uint8_t effect);
		void setEffect(uint8_t effect, DimmerController dc);
		void setEffectData(uint8_t data, uint8_t place);
		void setEffectData(uint8_t data[]);
		void clearEffect();
		void run();
		void run(bool force);
		void run(DimmerController dc);
		void run(DimmerController dc, bool force);
		
		//	Set properties
		
		void enable();
		void disable();
		void setBipolar();
		void setDimming();
		void setInverse();
		void setDirect();
		void setNextInSequence(Dimmer *dim);
		void setPin(uint8_t pin);
		void setPin(uint8_t pin, DimmerController dc);
		void setMethod(uint8_t method);
		
		//	Get Properties
		
		bool enabled();
		bool disabled();
		bool bipolar();
		bool dimming();
		bool inverse();
		bool direct();
		uint8_t pin();
		uint8_t intensity();
		uint8_t method();
		uint8_t effect();
		bool initialized(); //Note that there is no "set" for this
		Dimmer nextInSequence();
		
		//	Functions abstract
		
		//void makeStatic();
	
	private:
	
		//	Variables
	
		uint8_t _pin;
		uint8_t _method;
		uint8_t _intensity;
		uint8_t _effect;
		uint8_t _effectData[5];
		bool _enabled;
		bool _bipolar;
		bool _inverse;
		bool _initialized;
		Dimmer *_nextInSequence;
		
};

#endif
