#include "gtest/gtest.h"

#include "../src/map.hpp"
#include "../src/cell.hpp"
#include "../src/node.hpp"
#include "../src/astarsearch.hpp"

namespace my {
namespace project {
namespace {

// The fixture for testing class Astar.
class AstarTest : public ::testing::Test {};

TEST_F(AstarTest, MapConstructorCreatesAMapContainer) {
	astar::Map map{"../test/test_map_1.csv", 20};
  	
	EXPECT_EQ(map.getHeight(), 5);
  	EXPECT_EQ(map.getWidth(), 10);
}

TEST_F(AstarTest, CellConstructorCreatesACell) {
	astar::Cell cell{0, 2, 0, 2, 20, 20, 4};
  	
	EXPECT_EQ(cell.getXCoord(), 0);
  	EXPECT_EQ(cell.getYCoord(), 2);
	EXPECT_EQ(cell.getX(), 0);
	EXPECT_EQ(cell.getY(), 2);
  	EXPECT_EQ(cell.getName(), "(0,2)");
  	EXPECT_EQ(cell.getValue(), 4);
  	EXPECT_EQ(cell.getIsSolution(), false);
  	EXPECT_EQ(cell.getIsStart(), false);
  	EXPECT_EQ(cell.getIsGoal(), false);
  	EXPECT_EQ(cell.getIsReached(), false);
}

TEST_F(AstarTest, NodeConstructorCreatesANode) {
	astar::Cell child{0, 2, 0, 2, 20, 20, 4};
	astar::Cell parent{0, 1, 0, 1, 20, 20, 3};
	astar::Node node{&child, &parent, 7, 9};
  	
	EXPECT_EQ(node.getState(), &child);
  	EXPECT_EQ(node.getParent(), &parent);
	EXPECT_EQ(node.getF(), 16);
	EXPECT_EQ(node.getG(), 7);
  	EXPECT_EQ(node.getH(), 9);
}

TEST_F(AstarTest, AstarSearchConstructorCreatesAnAstarSearch) {
    astar::Map map{"../test/test_map_1.csv", 20};
    std::array<int, 2> north{0,1};
    std::array<int, 2> south{0,-1};
    std::array<int, 2> west{-1,0};
    std::array<int, 2> est{1,0};
    std::array<std::array<int, 2>, 4> actions{north, south, west, est};
	astar::AstarSearch astar{
		map,
		std::array<int, 2>{0,0},
		std::array<int, 2>{9,4},
		actions};
	
	astar::Cell child{9, 4, 9, 4, 20, 20, 1};
	astar::Cell parent{8, 4, 9, 4, 20, 20, 1};
	astar::Node node{&child, &parent, 16, 14};

  	EXPECT_EQ(astar.BestFirstSearch().value().getState()->getName(), node.getState()->getName());
}

}  // namespace
}  // namespace project
}  // namespace my
