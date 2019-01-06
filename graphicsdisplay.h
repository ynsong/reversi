#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "window.h"
#include "observer.h"
#include "info.h"
#include "state.h"

class Xwindow;
class GraphicsDisplay : public Observer<Info, State> {
  Xwindow *xw = nullptr;
  int graphicSize = 500;
  
 public:
  GraphicsDisplay(int n);

  ~GraphicsDisplay();

  void notify(Subject<Info, State> &whoNotified) override;

};
#endif


