# Deprecated Project Notice
I have not updated or otherwise maintained this project since 2019, my first semester of undergrad. In its current state, the project may be incomplete, buggy, completely broken, or absolutely fabulous. The code hasn’t been relevant in any of my technical projects since then, and I have no intention of ever using this project again. My program design skills, quality standards, language preferences, and other technical abilities have developed a lot since 2019, assisted by my interest in maintaining projects outside of academia. That being said, I have decided to keep my old projects public as I reflect on my own educational journey.

# Dimmers Library
"Dimmers" is an abstraction of the Arduino pins intended for lights/drivers/relays.

A Dimmer is an object that represents one "output," whether it is actually on another device or corresponds directly to a pin, and it's properties. There are a wide variety of ways to control an output device, whether it is an LED driver, relay, or so on. Relays don't use PWM. Some are normally open and others are normally closed. LED drivers and transistors normally use PWM to control intensity. Alternatively, you may be chaining two Arduinos together in order to minimize the usage of wire to drive lights. All of this can be hard to keep track of and result in excessive code.

If you use a Dimmer, however, the necessary operational properties, including bipolarity (non-dimming, as in relays), inverted (normally open vs normally closed), and output method (a pin or user defined method) are all handled within the Dimmer object so that you don't have to worry about them.

Further, this library includes special effects such as strobing, fading, and sequences. These effects are carried out in the `run()` procedure, which does the calculations and brightness updates when a special effect (technically called "function") is enabled. `run()` should be called more frequently for greater resolution or less frequently for better device performance but less resolution. Typically, `run()` is called every 20ms or 50ms, depending on your preference. Because parameters (such as fade step size) are limited to one byte, using lower values might limit you from using longer fades, while using higher values might cause quicker fades to look more like a jump. In personal experience, 50ms works great for the Arduino that controls my bedroom lights, but I preferred 20ms on my bicycle lights, which were intended to be flashier.

# Included Functions

## Initialization

### `Dimmer.begin()`
Does whatever is necessary to start up a dimmer. If "pin" is the output method, it will set the pin mode to output. Make sure that the pin is defined before calling `begin()` or it will use whatever value is currently in "pin," which can be unpredictable! If the method is *not* pin and/or initializing the dimmer requires something else, look at the overload of this function (directly below)

### `Dimmer.begin(DimmerController dcr)`
DimmerControllers are a further abstraction of dimmers and are explained later. They allow for advanced control of dimmers, such as overriding the built-in "begin" function. `DimmerController.onBegin(yourBeginFunction)`, assuming that `void yourBeginFunction(Dimmer dim) {}` is defined and you have supplied this `DimmerController` to this procedure, will cause `yourBeginFunction(Dimmer dim)` to be called in place of the typical begin function.

### Example of initialization
```C++
DimmerController dcr;
Dimmer redLED;
Dimmer blueLED;

void setup() {
  dcr.onBegin(customBeginFunction);
  
  blueLED.setPin(6);
  blueLED.enable();
  
  redLED.setPin(7);
  redLED.enable();
  
  blueLED.begin(); //This uses the built-in begin function
  redLED.begin(dcr); //This will call customBeginFunction(Dimmer dim), where dim will be redLED
}

void customBeginFunction(Dimmer dim) {
}
```
## Deinitialization

### `Dimmer.end()`
The reverse of initialization. Restores pins to inputs, etc.

### `Dimmer.end(DimmerController dc)`
Allows for overriding the built-in end function if you have called `DimmerController.onEnd(yourEndFunction)` and `void yourEndFunction(Dimmer dim)` is defined.
