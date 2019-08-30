#ifndef Dimmers_h
#define Dimmers_h

#include "Arduino.h"

class Dimmer {
	public:
	
		//	Control
		
		void begin();
		void end();
		
		//	Operation
		
		void setIntensity(uint8_t intensity);
		void setFunction(uint8_t function);
		void setFunctionData(uint8_t data, uint8_t place);
		void setFunctionData(uint8_t data[]);
		void clearFunction();
		void run();
		void run(bool force);
		
		//	Set properties
		
		void enable();
		void disable();
		void setBipolar();
		void setDimming();
		void setInverse();
		void setDirect();
		void setNextInSequence(Dimmer *dim);
		
		//	Get Properties
		
		bool enabled();
		bool disabled();
		bool bipolar();
		bool dimming();
		bool inverse();
		bool direct();
		Dimmer *nextInSequence();
	
	private:
	
		//	Variables
	
		uint8_t _pin;
		uint8_t _method;
		uint8_t _intensity;
		uint8_t _function;
		uint8_t _functionData[5];
		bool _enabled;
		bool _bipolar;
		bool _inverse;
		bool _initialized;
		Dimmer *_nextInSequence;
		
};

#endif