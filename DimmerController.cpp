#include "Arduino.h"
#include "Dimmers.h"

void DimmerController::onBegin( void(*f)(Dimmer) ) {
	_beginFunc = f;
}
void DimmerController::onEnd( void(*f)(Dimmer) ) {
	_endFunc = f;
}
void DimmerController::onIntensityChanged( void(*f)(Dimmer) ) {
	_intensityFunc = f;
}
void DimmerController::onEffectChanged( void(*f)(uint8_t, Dimmer) ) {
	_effectFunc = f;
}
void DimmerController::onEffectDataChanged( void(*f)(uint8_t, uint8_t, Dimmer) ) {
	_dataFunc = f;
}
void DimmerController::onPropChanged( void(*f)(uint8_t, uint8_t, Dimmer) ) {
	_propFunc = f;
}
void DimmerController::onCheckPinValidity( uint8_t(*f)(uint8_t) ) {
	_pinFunc = f;
}