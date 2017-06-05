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
		originalPieces_[current] = i + 1;
	}

	solution_.resize(dimensions_.first);
	for (size_t i = 0; i < solution_.size(); i++) {
		solution_[i].resize(dimensions_.second);
	}

	maxSolution_ = 0;
}

Puzzle::~Puzzle() {
	// TODO Auto-generated destructor stub
}

void Puzzle::write(const std::string surname) const {
	size_t lastindex = filename_.find_last_of(".");
	std::string rawname = filename_.substr(0, lastindex);
	std::string outputFilename = rawname + surname + "_solution.txt";
	std::ofstream of(outputFilename);

	std::map<Piece, size_t> original = originalPieces_;
	for (size_t x = 0; x < dimensions_.first; x++) {
		for (size_t y = 0; y < dimensions_.second; y++) {
			std::map<Piece, size_t>::iterator it;
			Piece toWrite = solution_[x][y];
			for (size_t i = 0; i < 4; i++) {
				toWrite = rotate_(toWrite);
				it = original.find(toWrite);
				if (it != original.end()) {
					of << it->second << " ";
					original.erase(it);
					break;
				}
			}
		}
		of << std::endl;
	}
	of.close();
}

void Puzzle::solve() {
    Pieces availablePieces;
	for (std::map<Piece, size_t>::iterator it = originalPieces_.begin();
		 it != originalPieces_.end(); ++it) {
		addTo_(availablePieces, it->first);
	}
	solveNext_(0, availablePieces);
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

bool Puzzle::solveNext_(
	const size_t position,
	Pieces availablePieces) {

	if (position+1 > maxSolution_+1) {
		maxSolution_ = position+1;
		std::cout << " " << maxSolution_;
	}
	
	const size_t x = position % dimensions_.first;
	const size_t y = position / dimensions_.first;

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
			return true;
		}
		if (solveNext_(position + 1, availablePieces)) {
			return true;
		} 
		addTo_(availablePieces, *it);
	}
	return false;
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
	bool isInEdge = false;
	isInEdge |= (x == 0    && y > 0 && y < Ly - 1);
	isInEdge |= (x == Lx-1 && y > 0 && y < Ly - 1);
	isInEdge |= (y == 0    && x > 0 && x < Lx - 1);
	isInEdge |= (y == Ly-1 && x > 0 && x < Lx - 1);
	
	if (isInEdge) {
		Pieces candidates;
		for (Pieces::iterator it = res.begin(); it != res.end(); ++it) {
			size_t zeros = 0;
			for (size_t i = 0; i < 4; i++) {
				if ((*it)[i] == 0) {
					zeros++;
				}
			}
			if (zeros <= 1) {
				candidates.insert(*it);
			}
		}
		res = candidates;
	}

	return res;
};


