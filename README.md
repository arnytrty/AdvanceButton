# AdvanceButton
Arduino Library for detecting input events (click, hold, doubleclick). Can be used with any input source (button, capacitive senor, hall sensor, ...) that create bistate signal

*documentation in source code*

---

## Explaining example events.ino

```c++
AdvanceButton btn(5, INPUT_PULLUP, LOW);
```

This will create object button that is bind to pin 5 of Arduino, INPUT_PULLUP enable internal pullup on the pin. That means if nothing is connected to the pin, there will be logic hight (1). Third argument is active state of the button. I connected my button to ground so whenever i press it. There will be logic low (0) on the pin so I set it as active state.


```c++
btn.onClick(onclick);
btn.onDoubleClick(ondoubleclick);
btn.onHold(onhold);
```

*onClick*, *onDoubleClick* and *onHold* will bind function you defined inside your code, you can rebind to other function by simply swapping the parameter. After binding all functions, you can call

```c++
btn.init();
```

Then, in the loop you can call
```c++
btn.update();
```
witch will depending of the button state read millis() and call on of the binded function. 

