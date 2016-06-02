//Meeshaan Shah
//CPSC 350
//Assignment 5
//main driver for assignment 5
//uses boost libraries for various algorithms assosiated with graphs

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/range/iterator_range_io.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>

const int SIZE = 11000;
const int SKIP_LINE = 4;
const int NUM_EDGES = 39994;

using namespace std;

//class for displaying breadth first search of a graph
class custom_bfs_visitor : public boost::default_bfs_visitor
{
public:
 
  template < typename Vertex, typename Graph >
  void discover_vertex(Vertex u, const Graph & g) const
  {
    cout << u << "->";
  }
};

//class for displaying depth first seach of a graph
class custom_dfs_visitor : public boost::default_dfs_visitor
{
public:
 
  template < typename Vertex, typename Graph >
  void discover_vertex(Vertex u, const Graph & g) const
  {
    cout << u << "->";
  }
};

//function displays menu
void displayMenu()
{
	cout << "Program uses p2p gnutella data set from snap.stanford.edu from August 2002" << endl;
	cout << "A decent computer maybe required for maximum efficiency" << endl;
	cout << endl;
	cout << "1.  Print Breadth first search" << endl;
	cout << "2.  Print Depth first search" << endl;
	cout << "3.  Display node with the highest degree" << endl;
	cout << "4.  Dispaly node with the highest in degree" << endl;
	cout << "5.  Display node with the highest out degree" << endl;
	cout << "6.  Data relevant to a given node" << endl;
	cout << "7.  Print graph" << endl;
	cout << "8.  Exit" << endl;
}

//main
int main()
{
	using namespace boost::graph;
	int answer;
	int count = 0;
	ifstream inFile("p2p-Gnutella04.txt");
	
	typedef boost::adjacency_matrix<boost::directedS> Graph;
	Graph g(SIZE);
	
	string line;
	int a, b;
	
	//read file	
	if (inFile.is_open())
	{
		for (int i = 0; i < SKIP_LINE; ++i)
		{
			getline(inFile, line);
		}
   		while (count < NUM_EDGES)
    	{
    		getline(inFile, line);
    		istringstream iss(line);
    		iss >> a >> b;
    		add_edge(a,b,g);
    		++count;
    	}
	}
	else
	{
		cout << "File failed to open" << endl;
	}
	
	displayMenu();
	cout << endl;
	cout << "Enter Choice: "; cin >> answer;
	
	while (answer != 8)
	{
		//switch on the answer
		switch (answer)
		{
			//breadth first search
			case 1:
			{
				custom_bfs_visitor bfsVis;
				breadth_first_search(g, boost::vertex(0, g), boost::visitor(bfsVis));
			}
			break;
			
			//depth first search
			case 2:
			{
				custom_dfs_visitor dfsVis;
				depth_first_search(g, visitor(dfsVis));
			}
			break;
			
			//highest degree
			case 3:
			{
				int max = 0;
				int degree;
				int maxNode;
				for (int v = 0; v < SIZE; ++v)
				{
					degree = in_degree(v,g) + out_degree(v,g);
					if (degree > max)
					{
						max = degree;
						maxNode = v;
					}
				}
				cout << "Node " << maxNode << " has the highest degree of " << max << endl;
			}
			break;
			
			//highest in degree
			case 4:
			{
				int maxInDegree = 0;
				int inDegree;
				int maxNodeIn;
				for (int v = 0; v < SIZE; ++v)
				{
					inDegree = in_degree(v,g);
					if (inDegree > maxInDegree)
					{
						maxInDegree = inDegree;
						maxNodeIn = v;
					}
				}
				cout << "Node " << maxNodeIn << " has the highest in degree of " << maxInDegree << endl;	
			}
			break;
			
			//highest out degree
			case 5:
			{
				int maxOutDegree = 0;
				int outDegree;
				int maxNodeOut;
				for (int v = 0; v < SIZE; ++v)
				{
					outDegree = out_degree(v,g);
					if (outDegree > maxOutDegree)
					{
						maxOutDegree = outDegree;
						maxNodeOut = v;
					}
				}
				cout << "Node " << maxNodeOut << " has the highest out degree of " << maxOutDegree << endl;
			}
			break;
			
			//data on given node
			case 6:
			{
				int node;
				cout << "Enter Node number: "; cin >> node;
				cout << endl;
				cout << "Degree: " << in_degree(node,g) + out_degree(node,g) << endl;
				cout << "In degree: " << in_degree(node,g) << endl;
				cout << "Out degree: " << out_degree(node,g) << endl;			
			}
			
			//prints graph
			case 7:
			{
				print_graph(g);	
			}
			break;
			
			//default
			default:
			{
				cout << "You did not enter correct command." << endl;
			}
			break;
		}//end of switch
		
		//to make output screen cleaner, asks user to hit enter to continue
		cout << endl;
		cout << "Press enter to continue..." << endl;
		cin.ignore();
		cin.ignore();
		
		//clears screen
		system("clear");
		
		//display menu and get answer to loop back into menu, or exit if user wants to exit
		displayMenu();
		cout << endl;
		cout << "Enter Choice: "; cin >> answer;
	}//end while
		
	return 0;
}