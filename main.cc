#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "graphicsdisplay.h"

using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;
  // Add code here

  try {
  bool isBlack = 1; //true if is setting Black piece, false otherwise
  while (true) {
    cin >> cmd;
    if(g.isFull()) break; //the grid is Full
    if (cmd == "new") {
      int n;
      cin >> n;
      if(n >=4 && n % 2 == 0) {
        isBlack = 1; //Black first
	GraphicsDisplay graphic{n};
        g.setObserver(&graphic);
        g.init(n);
        cout << g;
      }
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      try{
        if(isBlack) {
          g.setPiece(r, c, Colour::Black);
          isBlack = 0;
        }
        else {
          g.setPiece(r, c, Colour::White);
          isBlack = 1;
        }
        cout << g;
      } catch(const char *e) {}
    }
  }

  //check who win when the grid is full
  if(g.whoWon() == Colour::Black) {
    cout << "Black wins!" << endl;
  }
  else if(g.whoWon() == Colour::White) {
    cout << "White wins!" << endl;
  }
  else {
    cout << "Tie!" << endl;
  }

  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
