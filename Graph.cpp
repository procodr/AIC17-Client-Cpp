#include "Graph.h"

Graph::Graph(std::vector<Node*>& nodes)
{
	for(auto &node : nodes)
		this->nodes.push_back(node);
}

std::vector<Node*>& Graph::getNodes()
{
	return this->nodes;
}

Node* Graph::getNode(int index)
{
	return nodes[index];
}
