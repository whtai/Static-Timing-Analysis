#ifndef FINALGRAPH_H
#define FINALGRAPH_H

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <string.h>
#include <sstream>
#include <queue>
#include <iostream>
#include <iomanip>
#include <climits>
#include <set>
#include <tuple>
#include <thread>
#include <mutex>

using namespace std;

class Node;
class Table;

class Edge{
    public:
        Edge(const string &);
        void AddOutput(Node *, const string &);

        Node *input_gate;
        map<string ,Node *> output_gates_from_wire;

        string wire_name;
};

class Node{
    public:
        Node(const string &, int);
        void AddOutputGate(Node *, const string &);

        string gate_name;
        int delay, total_delay;
        Node *input_A, *input_B;
        map<string, Node *> outputs_Y;
        Edge *input_A_wire, *input_B_wire;
        int property; //0="input", 1="output", 2="NOT", 3="NAND", 4="NOR"

        int min0, max0, min1, max1;   //NEW
};

class Path{
    public:
        vector<Node *> path_gates;
        int prvs_longest_same_gate_index;
        int next_longest_same_gate_index;
        bool isFalse;
        Path(){
            prvs_longest_same_gate_index=-1;
            next_longest_same_gate_index=-1;
            isFalse = false;
        }
};

class Graph{
    friend void OutputPath(Graph &, Path *);

    public:
        Graph(const string&, int, int);
        ~Graph();
        void ReadTimingConstraint(const string&);
        void BuildGraph(const string &);
        void ConnectGates();
        void FindAllPaths();
        void SubFindAllPaths(Node *, Path *);
        void DisplayAllPaths();
        void AllNodesInformation();

        map<string, Edge *> wires;  //A container to store all the wires in the circuit
        map<string ,Node *> gates;  //A container to store all the internal gates in the circuit
        map<string ,Node *> inputs; //A container to store all the input nodes in the circuit
        map<string ,Node *> outputs;    //A container to store all the output nodes in the circuit
        vector<Path *> paths;  //A container to store all the possible paths from inputs to outputs in the circuit

        string GraphName;

        vector<Path *> TruePathsAfterImplication;
        vector<Path *> FalsePathsAfterImplication;

        //CORE ALGORITHMS
        void Implication();

        void Implication_Init();
        void Init_Stable_Time(Node *);
        bool Update_Stable_Time (Node *);
        bool Verify_True_Path(Path *, bool);
        bool Forward_Implication(Node *, bool &, bool = false);
        bool Backward_Implication(Node *, bool &, bool &);
        bool Apply(Node *, int, int, int, int);
        void Display_Implication_Results();

        void Display_All_Stable_Interval();

        bool Justification();
        bool GuessPI(int, vector<Node*> &);
        void Restore_Stable_Time(Table &);
        int CountKnownInputs();
        void FindTruePaths();
        void FindTruePaths_r1();
        void FindTruePaths_r2();
        void FindTruePaths_f1();
        void FindTruePaths_f2();

        int numberOfTruePaths_r;
        int numberOfFalsePaths_r;
        int numberOfTruePaths_f;
        int numberOfFalsePaths_f;

        int timing_constraint;
        int slack_constraint;
        int final_path_counter;

        int fail_index;

    private:
        bool isOne(Node *);
        bool isZero(Node *);
        bool isUnknown(Node *);
        bool isConflicted(Node *);
        int CountRelevantInputs(Node *, set<string> &);
};

class Table{
    public:
        void Record(Graph &);
        map<Node *, tuple<int, int, int, int> > FullTable;
};

#endif
