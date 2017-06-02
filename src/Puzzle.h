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

typedef std::array<int,4> Piece;
typedef int Orientation;
typedef std::vector<int> Boundary;
typedef std::vector<std::pair<Piece,Orientation>> Solution;

class Puzzle {
public:
    Puzzle(const std::string& filename);
    virtual ~Puzzle();

    void solve() const;
private:
    std::string filename_;
    std::pair<std::size_t,std::size_t> dimensions_;
    std::set<Piece> pieces_;

    Solution solveForBoundary_() const;
};

#endif /* PUZZLE_H_ */
