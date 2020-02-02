#include "ColumnNode.h"

DancingNode::DancingNode() {
	left = right = top = bottom = this;
}

DancingNode::DancingNode(ColumnNode* column_) {
	left = right = top = bottom = this;
	column = column_;
}

DancingNode* DancingNode::linkRight(DancingNode* node) {
	node->right = right;
	node->right->left = node;
	node->left = this;
	right = node;
	return node;
}

DancingNode* DancingNode::linkDown(DancingNode* node) {
	node->bottom = bottom;
	node->bottom->top = node;
	node->top = this;
	bottom = node;
	return node;
}

void DancingNode::unlinkLeftRight() {
	left->right = right;
	right->left = left;
}

void DancingNode::unlinkTopBottom() {
	top->bottom = bottom;
	bottom->top = top;
}

void DancingNode::reinsertLeftRight() {
	left->right = this;
	right->left = this;
}

void DancingNode::reinsertTopBottom() {
	top->bottom = this;
	bottom->top = this;
}
