#include "ColumnNode.h"

ColumnNode::ColumnNode(std::string name_) : DancingNode(){
	name = name_;
	size = 0;
	column = this;
}

void ColumnNode::cover() {
	unlinkLeftRight();
	for (DancingNode* node = bottom; node != this; node = node->bottom) {
		for (DancingNode* j = node->right; j != node; j = j->right) {
			j->unlinkTopBottom();
			j->column->size--;
		}
	}
}

void ColumnNode::uncover() {
	for (DancingNode* node = top; node != column; node = node->top) {
		for (DancingNode* j = node->left; j != node; j = j->left) {
			j->column->size++;
			j->reinsertTopBottom();
		}
	}
	reinsertLeftRight();
}