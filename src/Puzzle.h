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
#include <algorithm>
#include <cmath>

typedef int Type;
typedef std::array<Type,4> Piece;
typedef std::multiset<Piece> Pieces;
typedef std::pair<Piece,int> OrientedPiece;
typedef std::vector<Type> Boundary;
typedef std::vector<std::vector<OrientedPiece>> Solution;

class Puzzle {
public:
    Puzzle(const std::string& filename);
    virtual ~Puzzle();

    void solve();
private:
    std::string filename_;
    std::pair<std::size_t,std::size_t> dimensions_;
    std::vector<Piece> originalPieces_;
	Solution solution_;

	size_t solveNext_(
		const size_t nextPosition,
		Pieces availablePieces);

	std::vector<OrientedPiece> findCandidates_(
		const Boundary type,
		const Pieces& availablePieces) const;
};

#endif /* PUZZLE_H_ */
