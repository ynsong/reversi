#include "graphicsdisplay.h"
#include "window.h"
#include "cell.h"
#include "info.h"
#include "state.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

GraphicsDisplay::GraphicsDisplay(int n) : xw{new Xwindow{n,n}} {
	//set empty cells with blue
	for(int i=0; i < n; ++i) {
		for(int j=0; j < n; ++j) {
			xw->fillRectangle(i, j, n, n, Xwindow::Blue);
		}
	}

}

GraphicsDisplay::~GraphicsDisplay() { delete xw; }

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
	if(whoNotified.getState().type != StateType::Relay) {
		int r = whoNotified.getInfo().row;
		int c = whoNotified.getInfo().col;
		Colour colour = whoNotified.getInfo().colour;
		// set cell's colour when notified
		if(colour == Colour::Black) {
			xw->fillRectangle(r, c, graphicSize, graphicSize, Xwindow::Black);
		}
		else {
			xw->fillRectangle(r, c, graphicSize, graphicSize, Xwindow::White);
		}
	}
}
