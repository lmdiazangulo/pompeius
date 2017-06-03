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
		Piece rotatedPiece;
		for (size_t j = 1; j < 4; j++) {
			rotatedPiece = rotate_(rotatedPiece);
			availablePieces.insert(rotatedPiece);
		}
	}
	size_t position = 0;
	while (position < dimensions_.first * dimensions_.second) {
		position = solveNext_(position, availablePieces);
	}
}

size_t Puzzle::solveNext_(
	const size_t position, 
	const Pieces& availablePieces) {
	
	size_t x = position / dimensions_.second;
	size_t y = position / dimensions_.first;

	UpperCorner corner;
	x == 0 ?
		corner[0] = 0 :	corner[0] = solution_[x-1][y][2];
	y == 0 ?
		corner[1] = 0 : corner[1] = solution_[x][y-1][3];
	Pieces pieces = findCandidates_(corner, availablePieces);
	for (Pieces::const_iterator it = pieces.begin(); it != pieces.end(); ++it) {
		solution_[x][y] = *it;
		if (position == dimensions_.first * dimensions_.second - 1) {
			return dimensions_.first * dimensions_.second;
		}
		return solveNext_(position + 1, availablePieces);
	}
}

Piece rotate_(const Piece& in) {
	Piece res;
	for (size_t s = 0; s < 4; s++) {
		res[(s + 1) % 4] = in[s];
	}
	return res;
}

Pieces Puzzle::findCandidates_(
	const UpperCorner corner,
	const Pieces& avail) const {
	
	Piece lower = { corner[0], corner[1], 0, 0 };
	const Type infty = std::numeric_limits<Type>::infinity();
	Piece upper = { corner[0], corner[1], infty, infty };

	Pieces::iterator low = lower_bound(avail.begin(), avail.end(), lower);
	Pieces::iterator up = upper_bound(avail.begin(), avail.end(), upper);
	return Pieces(low, up);
};


