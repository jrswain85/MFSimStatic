/*------------------------------------------------------------------------------*
 *                       (c)2014, All Rights Reserved.     						*
 *       ___           ___           ___     									*
 *      /__/\         /  /\         /  /\    									*
 *      \  \:\       /  /:/        /  /::\   									*
 *       \  \:\     /  /:/        /  /:/\:\  									*
 *   ___  \  \:\   /  /:/  ___   /  /:/~/:/        								*
 *  /__/\  \__\:\ /__/:/  /  /\ /__/:/ /:/___     UCR DMFB Synthesis Framework  *
 *  \  \:\ /  /:/ \  \:\ /  /:/ \  \:\/:::::/     www.microfluidics.cs.ucr.edu	*
 *   \  \:\  /:/   \  \:\  /:/   \  \::/~~~~ 									*
 *    \  \:\/:/     \  \:\/:/     \  \:\     									*
 *     \  \::/       \  \::/       \  \:\    									*
 *      \__\/         \__\/         \__\/    									*
 *-----------------------------------------------------------------------------*/
/*------------------------------Algorithm Details-------------------------------*
 * Type: Pin Mapper																*
 * Name: Clique Pin Mapper														*
 *																				*
 * Inferred from the following paper:											*
 * Authors: Tao Xu and Krishnendu Chakrabarty									*
 * Title:Broadcast Electrode-Addressing for Pin-Constrained Multi-Functional	*
 * 		 Digital Microfluidic Biochips											*
 * 																				*
 * 																				*
 * Details: This pin mapper uses the pin activations generated by a router in	*
 * order to optimize the number of electrodes that need to be independently		*
 * addressed. This leads to a reduction in the number of pins necessary to run	*
 * the particular assay and hopefully an easier wiring problem for the wire	*
 * router.																		*
 *-----------------------------------------------------------------------------*/


#ifndef CLIQUE_PIN_MAPPER_H_
#define CLIQUE_PIN_MAPPER_H_

#include "../Models/dmfb_arch.h"
#include "indiv_addr_pin_mapper.h"

class CliquePinMapper : public IndivAddrPinMapper
{
	public:


		class Graph {
			public:
				map<string,vector<string> > graph;
				map<string,int> coloring;


				/* Mutators */
				void add_edge(string source,string sink);
				void add_node(string new_node) { graph.insert(pair<string,vector<string> >(new_node,vector<string>())); }

				//Coloring Algorithm
				void dsatur();

				/* Accessors */
				unsigned size() { return graph.size(); }
				map<string,int> get_coloring() { return coloring; }
				string get_color_string(int color,int max_color);
				int find_max_color();

				/* Mutators */
				void set_graph(map<string,vector<string> > new_graph) { graph = new_graph; }
				void set_coloring(map<string,int> new_coloring) { coloring = new_coloring; }

				/* Print functions */
				void print_coloring();
				void write_graph(string graph_name = "",  bool colored = false);

				//void print_chromatic();
		};

		CliquePinMapper();
		CliquePinMapper(DmfbArch *dmfbArch);
		virtual ~CliquePinMapper();

		// Methods
		void setMapPostRoute(vector<vector<int> *> *pinActivations);
		vector<vector<int> > initActivationMatrix(const vector<vector<int> *> *pinActivations);
		void setInterferenceRegion(vector<vector<int> > &matrix, int row, int column, bool lookahead);
		Graph convertMatrixToGraph(const vector< vector<int> > &matrix);
		void setPinMapping(Graph &coloringGraph);

		//Debug Methods
		void printBoardAtActivation(int n, const vector< vector< int> > &AMatrix, ofstream &output);

		//Fields
		map<int, bool> trivialElectrodes;
};

#endif /* CLIQUE_PIN_MAPPER_H_ */
