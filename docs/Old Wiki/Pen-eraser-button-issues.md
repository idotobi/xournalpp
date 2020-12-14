If your pen has a programmable button, you can map it to eraser or any other tool of your choice.

However, depending on the display server you're actually using, it could happen that:

1. pressing the button while hovering the screen engages the tool (e.g: eraser) and start erasing
2. actually touching the screen with the pen tip while doing so, just writes instead of erasing

That depends on your pen's driver settings.

Suppose you've created `/usr/share/X11/xorg.conf.d/30-wacom.conf` configuration file for X11

If you're using "wacom" driver you probably want to enable `TPCButton` or `TabletPCButton` to avoid the described behaviour.

Here's an example:

```
# N-Trig Duosense Electromagnetic Digitizer
Section "InputClass"
	Identifier "Wacom N-Trig class"
	MatchProduct "HID 1b96:0001|N-Trig Pen|N-Trig DuoSense|1B96:1B05 Pen"
	MatchDevicePath "/dev/input/event*"
	MatchIsTablet "on"
	Driver "wacom"
	Option "Button2" "3"
	Option "TabletPCButton" "on"
	Option "TPCButton" "on"
EndSection
```