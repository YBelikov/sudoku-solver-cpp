#pragma once
#include "DancingNode.h"
#include <string>

struct ColumnNode : public DancingNode {
	ColumnNode(std::string);
	int size;
	std::string name;
	void cover();
	void uncover();
};