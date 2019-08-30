DimmerControlMaster is an abstraction of the Arduino pins intended for lights/drivers/relays.

A DimmerControlMaster (DCM) is a class object that provides the overall control structure for ALL
dimmers.

A Dimmer is a type that represents an output. They are manipulated using a DCM object and have many
properties. Typically, the pin is located on the local Arduino. However, a dimme
	1. Pin/Remote ID
		If a dimmer is intended to be located at this device