/*
 * Puzzle.h
 *
 *  Created on: Jun 2, 2017
 *      Author: luis
 */

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include <array>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

typedef int Type;

typedef std::array<Type,4> Piece;
typedef std::multiset<Piece> Pieces;

typedef std::array<Type, 2> UpperCorner;

typedef std::vector<std::vector<Piece>> Solution;

class Puzzle {
public:
    Puzzle(const std::string& filename);
    virtual ~Puzzle();

    void solve();
	bool isSolved() const;
	
	void write(const std::string surname = "") const;

private:
    std::string filename_;
    std::pair<std::size_t,std::size_t> dimensions_;
    std::map<Piece, size_t> originalPieces_;
	Solution solution_;
	size_t maxSolution_;

	bool solveNext_(
		const size_t nextPosition,
		Pieces availablePieces);

	Pieces findCandidates_(
		const UpperCorner corner,
		const size_t position,
		const Pieces& availablePieces) const;

	static Piece rotate_(const Piece& in) {
		Piece res;
		for (size_t s = 0; s < 4; s++) {
			res[(s + 1) % 4] = in[s];
		}
		return res;
	}

	static void removeFrom_(Pieces& pieces, Piece toRemove) {
		for (size_t i = 0; i < 4; i++) {
			toRemove = rotate_(toRemove);
			Pieces::iterator it = pieces.find(toRemove);
			if (it != pieces.end()) {
				pieces.erase(it);
			}
		}
	}

	static void addTo_(Pieces& pieces, Piece rhs) {
		pieces.insert(rhs);
		Piece rotatedPiece = rhs;
		for (size_t j = 1; j < 4; j++) {
			rotatedPiece = rotate_(rotatedPiece);
			pieces.insert(rotatedPiece);
		}
	}
};

#endif /* PUZZLE_H_ */
