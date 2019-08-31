#include "Arduino.h"
#include "Dimmers.h"

//	CONTROL

void Dimmer::begin() {
	if (_enabled) {
		if (_method == 0) {
			pinMode(_pin, OUTPUT);
		}
		clearEffect();
		setIntensity(0);
		_initialized = true;
	}
}

void Dimmer::begin(DimmerController dc) {
	if (_method == 0) begin();
	else if (_enabled) {
		dc._beginFunc(*this);
		clearEffect();
		setIntensity(0, dc);
	}
}

void Dimmer::end() {
	if (_initialized) {
		if (_method == 0) {
			digitalWrite(_pin, LOW);
			pinMode(_pin, INPUT);
		}
		_initialized = false;
	}
}

void Dimmer::end(DimmerController dc) {
	if (_initialized) {
		if (_method == 0) {
			end();
		} else {
			dc._endFunc(*this);
		}
		_initialized = false;
	}
}

void Dimmer::run() {
	run(false);
}

void Dimmer::run(bool force) {
	if (_enabled && _method != 2) {
		switch (_effect) {
			case 0:
				if (force) {
					setIntensity(_intensity);
				}
				break;
			case 1:
				//A fading function. data[0] is the final value, data[1] is the step size, and data[2] is the tick skip (runs every data[2] + 1 ticks, so 0 runs on every tick, 1 every other tick, and so on...)
				if (_effectData[2] == _effectData[3]) {
				_effectData[3] = 0;

					if (abs(_effectData[0] - _intensity) < _effectData[1]) {
						setIntensity(_effectData[0]);
						_effect = 0;
						_effectData[0] = 0;
						_effectData[1] = 0;
						_effectData[2] = 0;
					} else {
						if (_effectData[0] > _intensity) {
							setIntensity(_effectData[0]);
						} else {
							setIntensity(_effectData[0]);
						}
					}
				} else {
					_effectData[3]++;
				}
				break;
			case 2:
				//Alternate between two states (strobe). data[0] is up ticks, data[1] is down ticks, data[2] is up value, data[3] is down value
				if (_effectData[4] == 0) {
					//Meaning that the function was just applied
					setIntensity(_effectData[0]);
					_effectData[4] = _effectData[0];
				} else if (_intensity == _effectData[2]) {
					//The dimmer is currently up
					_effectData[4]--;
					if (_effectData[4] == 0) {
						//Time to switch
						setIntensity(_effectData[0]);
						_effectData[4] = _effectData[1];
					}
				} else if (_intensity == _effectData[3]) {
					//The dimmer is currently down
					_effectData[4]--;
					if (_effectData[4] == 0) {
						setIntensity(_effectData[0]);
						_effectData[4] = _effectData[0];
					}
				} else {
					//Something else changed the value. Instead of breaking, just restart the process
					_effectData[4] = 0;
				}
				break;
			case 3:
				//Sequence. data[0] on value, data[1] exit value, data[2] on time, data[3] is next in sequence + 1, since data[3] = 0 means stop
				if (_effectData[4] == 0) {
					_effectData[4] = _effectData[2];
				}
				if (_intensity != _effectData[0]) {
					setIntensity(_effectData[0]);
				}
				if (_effectData[2] == 0) {
					_effectData[2] = _effectData[4];
					setIntensity(_effectData[0]);
					_effect = 0;
					if (_effectData[3] != 0) {
						_nextInSequence->_effect = 3;
					}
				} else {
					_effectData[2]--;
				}
				break;
			case 4:
				//Flicker and return. data[0] is value, data[1] is time
				if (_effectData[3] == 0) {
					//Was just set
					_effectData[2] = _intensity;
					_effectData[3] = 1;
				}
				if (_intensity != _effectData[0]) {
					setIntensity(_effectData[0]);
				}
				if (_effectData[1] == 0) {
					setIntensity(_effectData[0]);
					_effect = 0;
				} else {
					_effectData[1]--;
				}
				break;
		}
	}
}

void Dimmer::run(DimmerController dc) {
	run(dc, false);
}

void Dimmer::run(DimmerController dc, bool force) {
	if (_enabled && _method != 2) {
		switch (_effect) {
			case 0:
				if (force) {
					setIntensity(_intensity, dc);
				}
				break;
			case 1:
				//A fading function. data[0] is the final value, data[1] is the step size, and data[2] is the tick skip (runs every data[2] + 1 ticks, so 0 runs on every tick, 1 every other tick, and so on...)
				if (_effectData[2] == _effectData[3]) {
				_effectData[3] = 0;

					if (abs(_effectData[0] - _intensity) < _effectData[1]) {
						setIntensity(_effectData[0], dc);
						_effect = 0;
						_effectData[0] = 0;
						_effectData[1] = 0;
						_effectData[2] = 0;
					} else {
						if (_effectData[0] > _intensity) {
							setIntensity(_effectData[0], dc);
						} else {
							setIntensity(_effectData[0], dc);
						}
					}
				} else {
					_effectData[3]++;
				}
				break;
			case 2:
				//Alternate between two states (strobe). data[0] is up ticks, data[1] is down ticks, data[2] is up value, data[3] is down value
				if (_effectData[4] == 0) {
					//Meaning that the function was just applied
					setIntensity(_effectData[0], dc);
					_effectData[4] = _effectData[0];
				} else if (_intensity == _effectData[2]) {
					//The dimmer is currently up
					_effectData[4]--;
					if (_effectData[4] == 0) {
						//Time to switch
						setIntensity(_effectData[0], dc);
						_effectData[4] = _effectData[1];
					}
				} else if (_intensity == _effectData[3]) {
					//The dimmer is currently down
					_effectData[4]--;
					if (_effectData[4] == 0) {
						setIntensity(_effectData[0], dc);
						_effectData[4] = _effectData[0];
					}
				} else {
					//Something else changed the value. Instead of breaking, just restart the process
					_effectData[4] = 0;
				}
				break;
			case 3:
				//Sequence. data[0] on value, data[1] exit value, data[2] on time, data[3] is next in sequence + 1, since data[3] = 0 means stop
				if (_effectData[4] == 0) {
					_effectData[4] = _effectData[2];
				}
				if (_intensity != _effectData[0]) {
					setIntensity(_effectData[0], dc);
				}
				if (_effectData[2] == 0) {
					_effectData[2] = _effectData[4];
					setIntensity(_effectData[0], dc);
					_effect = 0;
					if (_effectData[3] != 0) {
						_nextInSequence->_effect = 3;
					}
				} else {
					_effectData[2]--;
				}
				break;
			case 4:
				//Flicker and return. data[0] is value, data[1] is time
				if (_effectData[3] == 0) {
					//Was just set
					_effectData[2] = _intensity;
					_effectData[3] = 1;
				}
				if (_intensity != _effectData[0]) {
					setIntensity(_effectData[0], dc);
				}
				if (_effectData[1] == 0) {
					setIntensity(_effectData[0], dc);
					_effect = 0;
				} else {
					_effectData[1]--;
				}
				break;
		}
	}
}

//	OPERATION

void Dimmer::setIntensity(uint8_t intensity) {
	if (!_enabled) return;
	_intensity = intensity;
	if (_bipolar) {
		if (intensity > 127) intensity = 255;
		else intensity = 0;
	}
	if (_inverse) intensity = 255 - intensity;
	switch (_method) {
		case 0:
			analogWrite(_pin, intensity);
			break;
	}
}

void Dimmer::setIntensity(uint8_t intensity, DimmerController dc) {
	if (!_enabled) return;
	_intensity = intensity;
	if (_bipolar) {
		if (intensity > 127) intensity = 255;
		else intensity = 0;
	}
	if (_inverse) intensity = 255 - intensity;
	switch (_method) {
		case 0:
			analogWrite(_pin, intensity);
			break;
		case 1:
			dc._intensityFunc(*this);
			break;
	}
}

void Dimmer::clearEffect() {
	_effect = 0;
	_effectData[0] = 0;
	_effectData[1] = 0;
	_effectData[2] = 0;
	_effectData[3] = 0;
	_effectData[4] = 0;
}

//	SET PROPERTIES

void Dimmer::enable() {
	_enabled = true;
}

void Dimmer::setPin(uint8_t pin) {
	if (_initialized) {
		pinMode(_pin, INPUT);
		pinMode(pin, OUTPUT);
		_pin = pin;
	}
}

void Dimmer::setPin(uint8_t pin, DimmerController dc) {
	if (dc._pinFunc(pin)) {
		setPin(pin);
	}
}