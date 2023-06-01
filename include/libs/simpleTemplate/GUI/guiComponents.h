#pragma once
#include "vex.h"
#include <iostream>
#include <vector>
typedef void (*func)();

class Button {
  public:
    // attributes
    // -defined by constructor-
    double posx;
    double posy;
    double width;
    double height;
    std::string penColor;
    std::string label;
    std::string fillColor;
    func clicked;
    // -other-
    bool visible = true;
    // constructors
    /** 
     * Default constructor.
     * Creates empty button.
    */
    Button() {
      this->posx = 0;
      this->posy = 0;
      this->width = 0;
      this->height = 0;
      this->label = "";
      this->penColor = "";
      this->fillColor = "";
      this->clicked = []{};
    }
    /** 
     * Creates a new instance of the Button class.
     *
     * @param  {int}    posx        x position (pixels, 0-480) of the top left corner
     * @param  {int}    posy        y position (pixels, 0-240) of the top left corner
     * @param  {int}    width       width
     * @param  {int}    height      height
     * @param  {char*}  label       inner text 
     * @param  {char*}  penColor    color of border (if any) and font color of label
     * @param  {char*}  fillColor   background color
     * @param  {func}   clicked     defaults to doNothing (for labels without cick events), triggers when the button is clicked
    */
    Button(double posx, double posy, double width, double height, std::string label, std::string penColor="#FFFFFF", std::string fillColor="#000000", func clicked = []{}) {
      this->posx = posx;
      this->posy = posy;
      this->width = width;
      this->height = height;
      this->label = label;
      this->penColor = penColor;
      this->fillColor = fillColor;
      this->clicked = clicked;
    }
    
    // methods
    /**
     * Draws the button if visible.
    */
    void draw() {
      if (!visible) return;
      _brain.Screen.setPenColor("#000000");
      _brain.Screen.setFillColor(fillColor.c_str());
      _brain.Screen.drawRectangle(posx, posy, width, height);
      _brain.Screen.setPenColor(penColor.c_str());
      _brain.Screen.setCursor((posy + height / 2) / 20 + 1, posx / 10 + 1); // calculate center left of button
      _brain.Screen.print(label.c_str());
    }
};


// note: if drawing from buffer, use https://www.befunky.com/create/resize-image/ and http://tomeko.net/online_tools/file_to_hex.php
// see https://www.vexforum.com/t/drawing-images-from-memory-buffer/65630/4
class Image {
  private:
    // attributes
    // -defined by constructor-
    int posx;
    int posy;
    int width;
    int height;
    std::string src;
  public:
    // constructor
    Image() {
      this->posx = 0;
      this->posy = 0;
      this->width = 0;
      this->height = 0;
      this->src = "";
    }
    /* 
    * Creates an instance of the class Image
    *
    * @param {int} posx          x position of image
    * @param {int} posy          y position of image
    * @param {int} width         width of image
    * @param {int} height        height of image
    * @param {std::string} src   file path of image file
    */
    Image(int posx, int posy, int width, int height, std::string src) {
      this->posx = posx;
      this->posy = posy;
      this->width = width;
      this->height = height;
      this->src = src;
    }
};