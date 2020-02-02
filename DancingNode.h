#pragma once
struct ColumnNode;

struct DancingNode {
	DancingNode* left;
	DancingNode* right;
	DancingNode* top;
	DancingNode* bottom;
	ColumnNode* column;
	DancingNode();
	DancingNode(ColumnNode*);
	DancingNode* linkRight(DancingNode*);
	DancingNode* linkDown(DancingNode*);
	void unlinkLeftRight();
	void unlinkTopBottom();
	void reinsertLeftRight();
	void reinsertTopBottom();
};

