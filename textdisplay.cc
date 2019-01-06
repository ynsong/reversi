#include "textdisplay.h"
#include "info.h"
#include "state.h"
#include "cell.h"

using namespace std;

TextDisplay::TextDisplay(int n) : gridSize{n}{ 
	vector<vector<char>> v(n, vector<char>(n, '-'));
	theDisplay = v;
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	if(whoNotified.getState().type != StateType::Relay) {
		unsigned int r = whoNotified.getInfo().row;
		unsigned int c = whoNotified.getInfo().col;
		Colour colour = whoNotified.getInfo().colour;
		if(colour == Colour::Black) theDisplay[r][c] = 'B';
		if(colour == Colour::White) theDisplay[r][c] = 'W';
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for(int i=0; i < td.gridSize; ++i) {
		for(int j=0; j < td.gridSize; ++j) {
			out << td.theDisplay[i][j];
		}
		out << endl;
	}
	return out;
}

