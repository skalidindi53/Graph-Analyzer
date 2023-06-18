
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



//************************** Node *************************

class Node{
public:
    int data;
    Node *next;
    Node(){
        data = 0;
        next = NULL;
    }

    Node(int data){
        this->data = data;
        this->next = NULL;
    }


};

//************************** Graph ****************************


class Graph {


	public:

		//add the node with neighborId as the neighbor of nodeId
		void addNeighbor(int nodeId, int neighborId){


           // int size = 0;
            //default constructor
            Node *head = NULL;
            int resize = 0;
            if(neighborId>nodeId){
                resize = neighborId + 1;
            }
            else{
                resize = nodeId+1;
            }


            if(vertices.size() == 0) {
                vertices.resize(resize, NULL); //resize the vector to have neighborId/nodeId + 1 elements
            }
            else if (vertices.size()!=0 && vertices.size() < resize){
                vertices.resize(resize, NULL); //resize the vector to have neighborId/nodeId + 1 elements
            }
            else{
                //do nothing
            }

            Node *newNode = new Node(neighborId);
                if(vertices.at(nodeId) == NULL){ // if the vertices vector at nodeId is empty
                    head = newNode;
                    vertices.at(nodeId) = head;
                }

                else{
                    Node *currNode = vertices.at(nodeId);
                    if(currNode->data > newNode->data){
                        newNode->next = currNode;
                        head = newNode;
                        vertices.at(nodeId) = head;
                    }
                    else {
                        while (currNode->next != NULL && currNode->data != neighborId) {
                            if (currNode->next->data > newNode->data) {
                                newNode->next = currNode->next;
                                currNode->next = newNode;
                            } else {
                                currNode = currNode->next;
                            }
                        }
                    }

                    if(currNode->next == NULL && currNode->data != neighborId){
                        if(currNode->data > newNode->data){
                            newNode->next = currNode;
                            head = newNode;
                            vertices.at(nodeId) = head;
                        }
                        else{
                            currNode->next = newNode;

                        }
                    }

                }


        };



		//reads the edge list from file and creates the adjacency list data structure
		void loadGraph(string edgeListFileName){
          ifstream file(edgeListFileName);
          while(!file.eof()){
             int nodeId, neighborId;
                file >> nodeId;
                file >> neighborId;
                addNeighbor(nodeId, neighborId);
              addNeighbor(neighborId, nodeId);
          }


        };

		//writes the adjacency list into the file
		void dumpGraph(string adjListFileName){
            ofstream outputFileStream;
            outputFileStream.open(adjListFileName);
            for(int i = 0; i < vertices.size(); i++){
                if(vertices.at(i) != NULL){
                    outputFileStream << i << ": ";
                    Node* tempHead = vertices.at(i);
                    while(tempHead->next != NULL){
                        outputFileStream << tempHead->data << " ";
                        tempHead = tempHead->next;
                    }
                    outputFileStream << tempHead->data << endl;
                }
            }
            outputFileStream.close();
        };

		//Prints number of nodes, number of edges, and maximum degree on terminal
		void printGraphInfo(){
            int numNodes = 0;
            int numEdges = 0;
            int maxDegree = 0;
            int tempNum = 0;
            for(int i = 0; i < vertices.size(); i++){
                if(vertices.at(i) != NULL){
                    numNodes++;
                    Node* tempHead = vertices.at(i);
                    while(tempHead->next != NULL){
                        numEdges++;
                        tempHead = tempHead->next;
                    }
                    numEdges++;
                    if(maxDegree < numEdges){
                        maxDegree = numEdges;
                    }
                    tempNum += numEdges;
                    numEdges = 0;
                }
            }
            cout << "Number of nodes: " << numNodes << endl;
            cout << "Number of edges: " << tempNum/2 << endl;
            cout << "Maximum degree: " << maxDegree << endl;
        };

		//returns the number of neighbor (degree) of a node
		int getNumNeighbors(int nodeId){
            int numNeighbors = 0;
            if(vertices.at(nodeId) != NULL){
                Node* tempHead = vertices.at(nodeId);
                while(tempHead->next != NULL){
                    numNeighbors++;
                    tempHead = tempHead->next;
                }
                numNeighbors++;
            }
            return numNeighbors;
        };

		//returns the number of nodes in the graph
		int getNumVertices(){
            int numNodes = 0;
            for(int i = 0; i < vertices.size(); i++){
                if(vertices.at(i) != NULL){
                    numNodes++;
                }
            }
            return numNodes;
        };

	private:
    vector<Node*> vertices;


};


void run(string edgeListFileName, string adjListFileName) {

    Graph graph;
   graph.loadGraph(edgeListFileName);
    graph.dumpGraph(adjListFileName);
    graph.printGraphInfo();

}

//*****************************************************************************


// The main will be removed for testing, do not add any code in the main function
int main() {
	//Change the filenames according to your local path.
    string edgeListFileName("youtube.txt");
    string adjListFileName("karate_adj.txt");
	run(edgeListFileName, adjListFileName);
    return 0;
}
