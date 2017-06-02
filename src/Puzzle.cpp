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

void Puzzle::solve() const {
    std::set<Piece> availablePieces = pieces_;

    if (dimensions_.first != dimensions_.second) {
        throw std::logic_error("Only square puzzles allowed.");
    }
    const size_t N = dimensions_.first / 2 + dimensions_.first % 2;
    for (size_t iteration = 0; iteration < N; iteration += 2) {
        Boundary boundary((N-iteration)*4, 0);
        Solution solveForBoundary_(availablePieces, boundary);
    }
}
