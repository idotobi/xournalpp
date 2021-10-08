## Autosaves
### Where are autosaves located?

There are two possible places. If you were working on an already-existing file, it should be in the same folder as the file, with the same name but `~` added to the end (example: `foo.xopp` is autosaved as `foo.xopp~`. Otherwise, the autosave will be located in `~/.xournalpp/autosave`.

## Crashes
### Xournal++ crashes when I open the Preferences window

If you're on Ubuntu and using our official releases, make sure the version of Ubuntu of the package matches the version of Ubuntu of your computer, as different versions of Ubuntu are generally not binary compatible.

Otherwise, please submit an issue.

### Why is Xournal++ crashing on Kubuntu when I open a file dialog?

Try installing `gnome-icon-theme`. See [this issue](https://github.com/xournalpp/xournalpp/issues/1347) for more information.

## Files and icons
### Why aren't thumbnails appearing?

If you are using the Nautilus file manager, you may be a [victim of a bug in Nautilus](http://www.bernaerts-nicolas.fr/linux/74-ubuntu/360-ubuntu-nautilus-external-thumbnailer-failure).

# Common Problems and how to solve them / workarounds
## Multi Monitor Systems
### My multi monitor system on Xorg does not map my Touch and Pen Pointer to the correct position.   Xournalpp draws with an offset when second monitor is connected.
Try to map your pointer devices to the Monitor xournalpp is working on:
```bash
# get the display name with:
xrandr --query
# get the pointer devices with:
xinput list
# map the pointer devices to the display with:
xinput map-to-output <device_id> <display_name>
```
This bug is for KDE's wacom-kcm: https://bugs.kde.org/show_bug.cgi?id=419392

### On my Windows machine connecting to an WQHD monitor causes Xournalpp to draw on a wrong position.
This is a known issue: [#1801](../issues/1801), [#1773](../issues/1773)
This seems to caused by a custom zoom factor set in the windows display settings.
Try to set both monitors to the same scaling.
We know, this is only a workaround and we work on a solution.

## Misc

### Is there a dark theme?

Xournal++ defers handling of dark themes to GTK.

On Linux, you can use set the environment variable `GTK_THEME` to a desired dark theme before launching Xournal++, edit `.gtkrc`, or use a theme that is dark by design.

On Windows, the default Adwaita theme that is distributed with the official Xournal++ Windows installer comes with dark theme enabled. You can enable it by creating a file called `etc\gtk-3.0\settings.ini` inside of the Xournal++ installation folder, with the following contents:
```ini
[Settings]
gtk-application-prefer-dark-theme=1
```