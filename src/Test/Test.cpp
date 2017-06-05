#include <gtest/gtest.h> 

#include "../core/Puzzle.h"

TEST(Puzzle, ctor) {
	EXPECT_THROW(Puzzle("caca"), std::logic_error);

	EXPECT_NO_THROW(Puzzle("data/4x4.txt"));
}

TEST(Puzzle, solve2x2) {
	Puzzle puzzle("data/2x2.txt");
	EXPECT_FALSE(puzzle.isSolved());
	puzzle.solve();
	EXPECT_TRUE(puzzle.isSolved());
}

TEST(Puzzle, solve4x4) {
	Puzzle puzzle("data/4x4.txt");
	EXPECT_FALSE(puzzle.isSolved());
	puzzle.solve();
	EXPECT_TRUE(puzzle.isSolved());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
