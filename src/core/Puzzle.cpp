/*
 * Puzzle.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: luis
 */

#include "Puzzle.h"

Puzzle::Puzzle(const std::string& filename) {
	filename_ = filename;
	std::ifstream file(filename, std::ifstream::in);

	if (!file.is_open()) {
		throw std::logic_error("Problem opening file");
	}

	file >> dimensions_.first;
	file >> dimensions_.second;
	for (size_t i = 0; i < dimensions_.first*dimensions_.second; i++) {
		Piece current;
		for (size_t j = 0; j < 4; j++) {
			file >> current[j];
		}
		originalPieces_.push_back(current);
	}

	solution_.resize(dimensions_.first);
	for (size_t i = 0; i < solution_.size(); i++) {
		solution_[i].resize(dimensions_.second);
	}
}

Puzzle::~Puzzle() {
    // TODO Auto-generated destructor stub
}

void Puzzle::solve() {
    Pieces availablePieces;
	for (size_t i = 0; i < originalPieces_.size(); i++) {
		availablePieces.insert(originalPieces_[i]);
		Piece rotatedPiece = originalPieces_[i];
		for (size_t j = 1; j < 4; j++) {
			rotatedPiece = rotate_(rotatedPiece);
			availablePieces.insert(rotatedPiece);
		}
	}
	size_t position = 0;
	position = solveNext_(position, availablePieces);
}

bool Puzzle::isSolved() const {
	bool isRight = true;
	bool isEmpty = false;
	for (size_t x = 0; x < dimensions_.first; x++) {
		for (size_t y = 0; y < dimensions_.second; y++) {
			isEmpty |= solution_[x][y] == Piece({{0, 0, 0, 0}});
			if (x == 0) {
				isRight &= (solution_[x][y][0] == 0);
			}
			else if (x == dimensions_.first - 1) {
				isRight &= (solution_[x][y][2] == 0);
			} 
			else {
				isRight &= (solution_[x][y][0] == solution_[x - 1][y][2]);
				isRight &= (solution_[x][y][2] == solution_[x + 1][y][0]);
			}
			if (y == 0) {
				isRight &= (solution_[x][y][1] == 0);
			}
			else if (y == dimensions_.second - 1) {
				isRight &= (solution_[x][y][3] == 0);
			}
			else {
				isRight &= (solution_[x][y][1] == solution_[x][y-1][3]);
				isRight &= (solution_[x][y][3] == solution_[x][y+1][1]);
			}
		}
	}
	return isRight && !isEmpty;
}

size_t Puzzle::solveNext_(
	const size_t position,
	Pieces availablePieces) {
	
	size_t x = position % dimensions_.first;
	size_t y = position / dimensions_.first;

	UpperCorner corner;
	x == 0 ?
		corner[0] = 0 :	corner[0] = solution_[x-1][y][2];
	y == 0 ?
		corner[1] = 0 : corner[1] = solution_[x][y-1][3];
	Pieces pieces = findCandidates_(corner, position, availablePieces);
	for (Pieces::const_iterator it = pieces.begin(); it != pieces.end(); ++it) {
		solution_[x][y] = *it;
		removeFrom_(availablePieces, *it);
		if (position == dimensions_.first * dimensions_.second - 1) {
			return dimensions_.first * dimensions_.second;
		}
		return solveNext_(position + 1, availablePieces);
	}
}

Pieces Puzzle::findCandidates_(
	const UpperCorner corner,
	const size_t position,
	const Pieces& avail) const {
	
	Piece lower = { corner[0], corner[1], 0, 0 };
	const Type infty = std::numeric_limits<Type>::max();
	Piece upper = { corner[0], corner[1], infty, infty };

	Pieces::iterator low = lower_bound(avail.begin(), avail.end(), lower);
	Pieces::iterator up = upper_bound(avail.begin(), avail.end(), upper);
	Pieces res(low, up);

	// Removes corner pieces from candidate list when appropriate.
	const size_t x = position % dimensions_.first;
	const size_t y = position / dimensions_.first;
	const size_t Lx = dimensions_.first;
	const size_t Ly = dimensions_.second;
	bool isInEdge = true;
	isInEdge &= (x == 0    && y > 0 && y < Ly - 1);
	isInEdge &= (x == Lx-1 && y > 0 && y < Ly - 1);
	isInEdge &= (y == 0    && x > 0 && x < Lx - 1);
	isInEdge &= (y == Ly-1 && x > 0 && x < Lx - 1);
	
	for (Pieces::iterator it = res.begin(); it != res.end(); ++it) {
		size_t zeros;
		for (size_t i = 0; i < 4; i++) {
			if ((*it)[i] == 0) {
				zeros++;
			}
		}
		if (zeros > 1) {
			res.erase(it);
		}
	}
};


