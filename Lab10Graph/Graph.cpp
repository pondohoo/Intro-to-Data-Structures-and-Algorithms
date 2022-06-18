#include "Graph.h"

Graph::Graph(ifstream& inFS)
{
    // inFS first gives the max vertices
    int maxVertices = 0;
    inFS >> maxVertices;
    // inFS then gives max edges
    int maxEdges = 0;
    inFS >> maxEdges;
    // inFS then gives the labels for all the vertices
    for (int i = 0; i < maxVertices; ++i)
    {
        Vertex curr;
        string label;
        inFS >> label;
        curr.label = label;
        vertices.push_back(curr);
    }
    // inFS then gives the edges between two vertices and their weights
    for (int i = 0; i < maxEdges; ++i)
    {
        // find first vertex and second vertex in the vector
        int firstVertex = -1;
        int secondVertex = -1;
        string currLabel;
        inFS >> currLabel;
        for (int i = 0; i < maxVertices; ++i)
        {
            if (vertices.at(i).label == currLabel)
            {
                firstVertex = i;
            }
        }
        inFS >> currLabel;
        for (int i = 0; i < maxVertices; ++i)
        {
            if (vertices.at(i).label == currLabel)
            {
                secondVertex = i;
            }
        }
        if (firstVertex == -1 || secondVertex == -1)
        {
            cout << "Invalid label for part of vertex pair" << endl;
            return;
        }
        // assign weight between them
        int weight;
        inFS >> weight;
        pair<int, int> neighbor(secondVertex, weight);
        vertices.at(firstVertex).neighbors.push_back(neighbor);
    }
}
void Graph::bfs()
{
    queue<Vertex> frontierQueue;
    if (vertices.size() > 0)
    {
        vertices.at(0).setDistance(0);
        cout << vertices.at(0).distance << endl;
        vertices.at(0).prev = nullptr;
        // initialize frontierQueue and use color as discoveredSet
        vertices.at(0).color = "RED";
        frontierQueue.push(vertices.at(0));
        while (frontierQueue.size() != 0)
        {
            // take the Vertex first in the queue out of the queue
            Vertex currVertex = frontierQueue.front();
            frontierQueue.pop();
            // iterate through the neighbors of currVertex
            for (auto v : currVertex.neighbors) // can't get rid of squiggles but it's right
            {
                // find if current neighbor is in discovered set or not
                if (vertices.at(v.first).color == "WHITE")
                {
                    vertices.at(v.first).color = "RED";
                    vertices.at(v.first).distance = currVertex.distance + 1;
                    vertices.at(v.first).prev = &currVertex;
                    frontierQueue.push(vertices.at(v.first));
                }
                
            }
            
        }
        
    }
}
void Graph::output_graph(const string& fileName)
{

    ofstream outFS(fileName);
    if (!outFS.is_open()) {
        cerr << "ERROR: Could not open " << fileName << endl;
    }
    else {
        outFS << "digraph G {" << endl;

        for (unsigned int i = 0; i < vertices.size(); ++i) {
            if (vertices.at(i).distance != INT_MAX) {
                outFS << "	" << vertices.at(i).label << " [label=\"" << vertices.at(i).label << ", distance = " << vertices.at(i).distance << "\", color=\"" << vertices.at(i).color << "\"];" << endl;
                for (auto j = vertices.at(i).neighbors.begin(); j != vertices.at(i).neighbors.end(); j++) {
                    outFS << "	" << vertices.at(i).label << " -> " << vertices.at(j->first).label << endl;
                }
            }
        }

        outFS << "}";
        outFS.close();

        string systemCommand = "dot -T jpg " + fileName + " -o pic.jpg";

        system(systemCommand.c_str());
    }

}