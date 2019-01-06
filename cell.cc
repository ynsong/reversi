#include "cell.h"
#include "state.h"
#include <iostream>

using namespace std;

Cell::Cell(size_t r, size_t c) : r{r}, c{c} {}

void Cell::setPiece(Colour colour) { 
	this->colour = colour; //set colour
	//set state
	State newS; 
	newS.type = StateType::NewPiece; // I am a new piece
	newS.colour = colour;
	this->setState(newS);
	this->notifyObservers();

}    // Place a piece of given colour here.
  
void Cell::toggle() {
 	if(colour == Colour::Black)  {
		colour = Colour::White;
	} 
 	else  {
		colour = Colour::Black; 
	}
 }         // Toggles my colour.

void Cell::notify(Subject<Info, State> &whoFrom) { // My neighbours will call this// when they've changed state
	if(colour == Colour::NoColour) return; // this cell has no piece

	State newS; //set new state of cell

 	//check direction
	size_t fromR = whoFrom.getInfo().row; // the row of whoFrom
	size_t fromC = whoFrom.getInfo().col; // the column of whoFrom
 	Direction d; //direction from whoFrom
 	if(r+1 == fromR) {
 		if(c+1 == fromC) {
			d = Direction::SE;
		} 
 		if(c == fromC) {
			d = Direction::S;
		}
 		if(c-1 == fromC) {	
			d = Direction::SW;
		}
 	} 
 	else if(r == fromR) {
 		if(c+1 == fromC) {
			d = Direction::E; 
		}
 		if(c-1 == fromC) {
			d = Direction::W;
		}
 	}
 	else {
 		if(c+1 == fromC)  {
			d = Direction::NE;
		} 
 		if(c == fromC) {
			d = Direction::N;
		}
 		if(c-1 == fromC) {
			d = Direction::NW;
		}
 	}

	if(whoFrom.getState().type == StateType::NewPiece) {
		if(colour == whoFrom.getState().colour) {
                       	return; // this cell has the same colour as the new piece
        	}	
        	else {
			newS.direction = d;
			newS.colour = whoFrom.getState().colour;
	          	newS.type = StateType::Relay; // this cell has different colour as the new piece
			this->setState(newS);
           		this->notifyObservers();
       		}
	}	
	else if(whoFrom.getState().type == StateType::Relay) {
		// in relay, check if the cell in the line of new piece
		if(d == whoFrom.getState().direction) { 
			newS.direction = d;
			// set colour state be the colour of new piece
		    	newS.colour = whoFrom.getState().colour;
           		// set type state
            		if(colour == whoFrom.getState().colour) {
            			newS.type = StateType::Reply; // this cell has the same colour as the new piece
				this->setState(newS);
                		this->notifyObservers();
            		}   			
           		else {
				newS.type = StateType::Relay; // this cell has different colour as the new piece
				this->setState(newS);
                		this->notifyObservers();
            		}   	
	 	}
	 	else { // not in the line
	 		return;
	 	}	
	}
 	// reply 
 	else  {
 	    Direction nd = whoFrom.getState().direction;
	    if(this->getState().type == StateType::NewPiece) return; // end at the new piece
 	    // check if the cell in the line of new piece 
 	    if(nd == Direction::NW && d != Direction::SE) return;  //no
 	    if(nd == Direction::N && d != Direction::S) return; 
 	    if(nd == Direction::NE && d != Direction::SW) return; 
 	    if(nd == Direction::W && d != Direction::E) return; 
 	    if(nd == Direction::E && d != Direction::W) return; 
 	    if(nd == Direction::SW && d != Direction::NE) return; 
 	    if(nd == Direction::S && d != Direction::N) return; 
 	    if(nd == Direction::SE && d != Direction::NW) return;
	    // yes, then flip 
	    this->toggle();
 	    // set this state
	    newS.direction = nd; 
	    newS.colour = whoFrom.getState().colour;
 	    newS.type = StateType::Reply;
	    this->setState(newS);
            this->notifyObservers();
	}
 }


Info Cell::getInfo() const {
 	Info info = {r, c, colour};
 	return info;
 }

