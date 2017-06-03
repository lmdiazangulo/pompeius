/*
 * Puzzle.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: luis
 */

#include "Puzzle.h"

Puzzle::Puzzle(const std::string& filename) {
}

Puzzle::~Puzzle() {
    // TODO Auto-generated destructor stub
}

void Puzzle::solve() {
    Pieces availablePieces;
	for (size_t i = 0; i < originalPieces_.size(); i++) {
		availablePieces.insert(originalPieces_[i]);
	}
	size_t position = 0;
	while (position < dimensions_.first * dimensions_.second) {
		position = solveNext_(position, availablePieces);
	}
}

size_t Puzzle::solveNext_(
	const size_t position, 
	Pieces availablePieces) {
	
	size_t x = position / dimensions_.second;
	size_t y = position / dimensions_.first;

	Boundary type(4, -1);
	if (y == 0) {
		type[0] = 0;
	} else {
		OrientedPiece neigh = solution_[x][y - 1];
		type[0] = neigh.first[(2 - neigh.second) % 4];
	}
	if (x == dimensions_.first - 1) {
		type[1] = 0;
	}
	if (y == dimensions_.second - 1) {
		type[2] = 0;
	}
	if (x == 0) {
		type[3] = 0;
	}
	else {
		OrientedPiece neigh = solution_[x - 1][y];
		type[3] = neigh.first[(1 - neigh.second) % 4];
	}

	std::vector<OrientedPiece> pieces = findCandidates_(type, availablePieces);
	for (size_t i = 0; i < pieces.size(); i++) {
		solution_[x][y] = pieces[i];
		if (position == dimensions_.first * dimensions_.second - 1) {
			return dimensions_.first * dimensions_.second;
		}
		return solveNext_(position + 1, availablePieces);
	}
}

std::vector<OrientedPiece> Puzzle::findCandidates_(
	const Boundary type,
	const Pieces& availablePieces) const {


}