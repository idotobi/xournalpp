This manual is a draft and a work in progress. If you have the time you can help write some paragraphs ;-)

# Introduction
Xournal++ is a notetaking and PDF annotation tool that is based on Xournal but written from scratch in C++, using GTK3 instead of GTK2. It supports pressure sensitive pens (e.g. Wacom), text input, image input, LaTeX formula entry as well as a number of other useful features such as shape recognition and layers.

Feel free to report any bugs you encounter or make feature requests on our [Issue Tracker](https://github.com/xournalpp/xournalpp/issues). You're also welcome to [submit pull requests](https://github.com/xournalpp/xournalpp/pulls).

# Getting Started

Although Xournal++ is designed to be intuitive and simple to use, we realize that setting it up and getting used to all of the options is non-trivial. Here, we'll briefly outline how Xournal++ is used and how it should be set up. If you're a first time user, we strongly recommend that you read this section in its entirely before using Xournal++.

## General Usage

A typical Xournal++ workflow looks like the following:
1. Use the `File` menu to load an existing Xournal++ project, create a new document, or load a PDF file.
2. Annotate or markup the document using one of the tools in the toolbar, such as the Stroke tool, the Text tool, or the Image tool.
3. Save periodically.
4. If needed, export the document as a PDF file by selecting `File > Export as PDF` in the menu. You can also export in more formats or export custom page ranges using `File > Save As...`.

Once you are ready to begin editing a document, you can draw strokes and add objects using some of the [tools described below](#tools).

If you need more space, you can add more pages using one of the `Journal > ...` options or by right clicking a page in the Page Panel (in the default layout, it is on the left side of the program).

## Scrolling and Annotation
If you edit and annotate a PDF document you may want to combine the keyboard and a Wacom tablet. In this case
* **(Cursor)** use the cursor keys (up, down) for moving up and down in the document and
* **(Stylus/Wacom)** use the Wacom tablet with the stylus to annotate the PDF document.
Of course you can scroll with the stylus but sometimes you forget to return the focus from the scrollbar back to the document and then the movement of the stylus move the document instead of annotating the document at the Wacom tablet (helpful e.g. on [Operating System MacOSX with  Xounral++ - Version 1.0.18](https://github.com/xournalpp/xournalpp/releases)). 

## Customization

Xournal++ is highly customizable and has many configurable settings, as it is designed to work on a variety of devices. You can edit the settings by selecting `Edit > Preferences` from the menu.

For example:
* You can try enabling the optional "Experimental Input System" (in the `Input System` tab), which fixes many input-related issues and is a better experience overall.
* You can customize mouse/stylus/touchscreen controls.
* You can edit how Xournal++'s interface is organized in the `View` tab.
* You can adjust zoom and layout settings.

### Setting up devices

One of the most important settings that you should tweak are the input settings. The options you choose are going to depend on the exact devices that you are using as well as your habits and workflow.

In the `Input System` tab, you should check that your devices are properly detected by Xournal++. If you have the new input system enabled (we strongly recommend that you enable this setting), you will have the capability to assign different devices classes to your detected input devices. For example, if you have a graphical tablet, ensure that your stylus is set to a `Pen` device, not `Disabled` or `Mouses`. Otherwise, your stylus may not work or its pressure sensitivity may be disabled.

If the button settings for your stylus are not working, you may want to enabled `Merge button events with stylus tip events`.

### Default tool buttons

In the `Mouse` and `Stylus` tabs, you can set which tools should be assigned to your button presses. For example, you may want to set the middle mouse button for the mouse to activate the hand tool, or you may want to set one of the stylus buttons to activate the eraser. When a secondary button is pressed, the activate tool will temporarily change to the selected tool until the secondary button is released.

### Touchscreen Configuration

If you have a computer with a touchscreen, you will want to check out the options in the `Touchscreen` tab so that Xournal++ behaves in a way that you expect.

There is a "Touch Workaround" option in the `Touchscreen` tab. By default, Xournal++ will treat touches as scrolling. If you would instead like to use the touchscreen for drawing, you should enable the "Touch Workaround". (Note: in a future version of Xournal++, the "Touch Workaround" will be renamed to "Touch Drawing", as the current "Touch Workaround" has some serious bugs).

### Cursor Configuration

By default, the cursor for the stylus is a 1-pixel wide dot. If you would like to see a bigger cursor, you can enable the `Big cursor for pen` option in the `View` tab.

If you would like to highlight the cursor positions at all times (useful for e.g. giving presentations), you can enable the `Highlight cursor position` option in the `View` tab.

### Toolbar Customization

Additionally, you can also edit how Xournal++'s interface is organized (e.g. where buttons are, where the panels should be located) by selecting one of the options in `View > Toolbars`.

The configuration files are generally located at `$HOME/.xournalpp` or `$HOME/.config/com.github.xournalpp.xournalpp/` on Linux:
 * `toolbar.ini` - it's possible to create new toolbars layouts manually and precisely.
 * `colornames.ini` - in case you've added custom colors in your toolbar, you can add a label to them following this format:
   
   ```
   [custom]
   ff00ff=4bit Magenta
   ff00bb=Hot pink
   ff0000=4bit Red
   ...
   ```
   Note that this *six-hex-digits* format does not include the `0x` prefix, which is actually mandatory for `toolbar.ini`.
   
   Example: `COLOR(0xff00bb)`

# Tools
## Handwriting Tools

The handwriting tools allow you to write on the document using a mouse or a pressure-sensitive stylus. There are three such tools: **Pen**, **Highlighter**, and **Eraser**.

### Pen

The **Pen** tool allows you to draw lines on the document. It supports mouse input, as well as pressure-sensitive styluses (e.g. with a graphics tablet).

### Highlighter

### Eraser

The **Eraser** tool can remove strokes or parts of strokes. It has three modes:
1. **Standard**: remove parts of strokes that the cursor moves over.
2. **Whiteout**: paint a white stroke.
3. **Delete Stroke**: remove the entirety of any stroke that the cursor touches.

### Colors and Thickness

The **Pen** and **Highlighter** tools can be used to draw strokes of different colors and thicknesses.

To change the color of any selected stroke or any future strokes you draw, click on one of the color buttons (in the default layout, the color buttons are at the right side of the toolbar second from the top). Besides the preset color buttons, you can also set a custom color by clicking on the **Select color** button.

To change the thickness, press one of the thickness buttons (in the default layout, they are to the left of the color buttons).

It is also possible to automatically fill in the area enclosed by a stroke; this **Fill Mode** can be toggled by selecting the paint bucket icon (in the default layout, it is to the left of the color buttons).

### Shapes

The **Pen** and **Highlighter** tool can also draw shapes instead of strokes. In the default layout, you can find the **Shapes Toggle Menu** to the right of the **Text Tool** (the big "T"). The Shapes Toggle Menu will have a dropdown arrow on its right. After selecting one of the shape modes in the menu, the Pen and Highlighter will place down the selected shape instead of strokes.

The selectable shapes are:

* **Draw Rectangle**: Draws a rectangle.
* **Draw Circle**: Draws a circle.
* **Draw Arrow**: Draws an arrow from the initial point of contact to wherever you finish the stroke.
* **Draw Line**: Draws a line.
* **Draw Coordinate System**: Draws an "L" shape.
* **Draw Spline**: Draws a spline through the knots you set by clicking or click-dragging. In the latter case the spline will be smooth at the corresponding knot and tangent to the direction you set. 
* **Stroke Recognizer**: After you finish the stroke, it will attempt to convert the stroke into one of the shape types above (it will leave the stroke as-is if it cannot).

## Object Tools
### Text

The **Text** tool inserts text (objects) onto the document. To do so, click anywhere on the document to begin editing. Any existing text objects can be altered by clicking on them with the text tool.

A text object's color and font can be customized by clicking the corresponding buttons in the toolbar.

### Image

The **Image** button inserts an image onto the document. Clicking on the Image button will bring up a file dialog, which will allow you to choose which image you want to insert.

An image can be repositioned or resized with one of the selection tools.

### LaTeX

The **LaTeX** button inserts a LaTeX formula onto the document. Note that the LaTeX feature requires a working version of LaTeX to be installed on your computer (specifically, the feature needs to be able to call `pdflatex`). In addition, LaTeX `standalone` package needs to be installed, which typically requires installation of `texlive-latex-extra` or `texlive-standalone`.  On Ubuntu or similar Linux systems this means
```
sudo apt-get install texlive-latex-extra
```
For other operating systems you will need to consult your LaTeX installation manual on how to add the `standalone` LaTeX package.

Clicking on the LaTeX button will bring up a dialog which will allow you to type in a formula. A preview will be displayed in the center of the dialog, which will updating as you type and indicate whether your formula is valid. Once you are done, you can click the OK button to insert the LaTeX onto the document; the rendered formula will appear at the center of the current page. The formula can be selected, moved scaled and edited as desired.

## Selection and Movement Tools

### Selection

### Vertical Space

### Hand

## Snapping

# Audio Recording and Playback

* Go to `Edit > Preferences > Audio Recording` and set the `Audio Folder` as well as the appropriate `Input Device` and `Output Device`.
* If you need to edit the recording audio gain, take a look at the preferences tab mentioned above.

**Please test this new feature in advance before relying on it to work. It could contain undiscovered bugs specific to some hardware or software that we have not tested.**

## Usage

To record audio, first press the **Start/Stop Recording** button (icon: a solid red circle). Recording will begin when you create the next stroke or object and will stop when the button is pressed again. The audio playback will be attached to that object.

To playback audio, use the `Play Object` tool and click on the object for which you recorded audio. You can pause and stop the playback of the audio with the buttons next to the recording button in the toolbar.

# Menu Entries
## File
The **File** menu has the usual entries along with an **Annotate PDF** option which allows you to open a PDF and draw on top, and an **Export PDF** option that allows you to save your document as a PDF.

## Edit
The **Edit** menu is also pretty standard, with a **Find** function that allows you to search in any text, as well as a **Preferences** dialog.

## View

## Navigation

## Journal
The **Journal** menu allows you to configure settings for the document that is currently being edited.

## Tools

## Help

![](https://github.com/xournalpp/xournalpp/blob/string_new/development/documentation/wiki/Xournalpp.png)