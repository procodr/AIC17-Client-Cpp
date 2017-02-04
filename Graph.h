#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>

#include "Node.h"

/**
 * Graph class.
 * Map of the game is graph consisting of Nodes.
 * Please do not change this class.
 */
class Graph
{
public:
    Graph(std::vector<Node*>& nodes);

    /**
     * get all nodes of the map.
     *
     * @return array of nodes
     */
    std::vector<Node*>& getNodes();

    /**
     * get node by its index.
     *
     * @param index index of the node
     * @return node at specified index
     */
    Node * getNode(int index);

private:
    std::vector<Node*> nodes;
};

#endif
