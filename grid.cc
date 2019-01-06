#include "grid.h"
#include "state.h"
#include "cell.h"
#include "textdisplay.h"
#include "observer.h"
#include "info.h"
#include <vector>
#include <iostream>

using namespace std;

Grid::~Grid( ) {
	delete td;
	delete ob;
}
  
void Grid::setObserver(Observer<Info, State> *ob) { this->ob = ob; }
  
bool Grid::isFull() const { 
	for(int i=0; i < gridSize; ++i) {
		for(int j=0; j < gridSize; ++j) {
			// is the cell has piece?
			if(theGrid[i][j].getInfo().colour == Colour::NoColour) return false; //no
		}
	}
	return true;
}  // Is the game over, i.e., is the grid full?
  
Colour Grid::whoWon() const {
	int numBlack = 0; // number of black pieces
	int numWhite = 0; // number of white pieces
	for(int i=0; i < gridSize; ++i) {
		for(int j=0; j < gridSize; ++j) {
			// is the cell has black piece?
			if(theGrid[i][j].getInfo().colour == Colour::Black) {
				++numBlack; //yes
			}
			// the cell has white piece
			else  {
				++numWhite;
			}
		}
	}

	if(numBlack > numWhite) {
		return Colour::Black;
	}
	else if(numWhite > numBlack) {
		return Colour::White;
	}
	else {
		return Colour::NoColour;
	}
} // Who has more pieces when the board is full?
  
void Grid::init(size_t n) {
	gridSize = n;
	theGrid.clear();  // remove odd grid, set new grid
	for(int i=0; i < gridSize; ++i) {
		theGrid.emplace_back(); //increase row
		for(int j=0; j < gridSize; ++j) {
			size_t row = i;
			size_t col = j;
			theGrid[i].emplace_back(Cell{row,col}); //increase column
		}	
	}

	delete td;
	int size = n;
	td = new TextDisplay{size}; // set text display

	for(int i=0; i < gridSize; ++i) {
		for(int j=0; j < gridSize; ++j) {
			//attach cells as an observer for neighbours of cells
			if(i != 0) {
				theGrid[i-1][j].attach(&theGrid[i][j]);
				if( j != 0) theGrid[i-1][j-1].attach(&theGrid[i][j]);
				if( j != size - 1) theGrid[i-1][j+1].attach(&theGrid[i][j]);
			}
			if(i != size  - 1) {
				theGrid[i+1][j].attach(&theGrid[i][j]);
				if( j != 0) theGrid[i+1][j-1].attach(&theGrid[i][j]);
				if( j != size - 1) theGrid[i+1][j+1].attach(&theGrid[i][j]);
			}
			if( j != 0) theGrid[i][j-1].attach(&theGrid[i][j]);
			if( j != size - 1) theGrid[i][j+1].attach(&theGrid[i][j]);			
		//attach observers of the current cell
		theGrid[i][j].attach(td);
		theGrid[i][j].attach(ob);
		}	
	}
	
	// initialize cells
	theGrid[n / 2 - 1][n / 2 - 1].setPiece(Colour::Black);
	theGrid[n / 2 - 1][n / 2].setPiece(Colour::White);
	theGrid[n / 2][n / 2 - 1].setPiece(Colour::White);
	theGrid[n / 2][n / 2].setPiece(Colour::Black);
} // Sets up an n x n grid.  Clears old grid, if necessary.
  
void Grid::setPiece(size_t r, size_t c, Colour colour) {
	if(theGrid[r][c].getInfo().colour == Colour::NoColour) { // cell not occupied
		theGrid[r][c].setPiece(colour);
	}
	else {
		throw "Currently occupied by another piece.";
	}	
}  // Plays piece at row r, col c.
  
void Grid::toggle(size_t r, size_t c) {
	theGrid[r][c].toggle();
}  // Flips piece at row r, col c.

ostream &operator<<(ostream &out, const Grid &g) {
	out << *g.td;
	return out;
}


