#include "FinalGraph.h"
//global variable
mutex gMutex;
fstream outfile;
int final_path_counter = 0;

void Table::Record(Graph &graph){
	for(map<string, Node *>::iterator it = graph.inputs.begin() ; it != graph.inputs.end() ; it++ ){
	    FullTable.insert(pair<Node *, tuple<int, int, int, int> >(it->second, make_tuple(it->second->min0,
		it->second->max0, it->second->min1, it->second->max1 ) ) );
	}

	for(map<string, Node *>::iterator it = graph.outputs.begin() ; it != graph.outputs.end() ; it++ ){
	    FullTable.insert(pair<Node *, tuple<int, int, int, int> >(it->second, make_tuple(it->second->min0,
		it->second->max0, it->second->min1, it->second->max1 ) ) );
	}

	for(map<string, Node *>::iterator it = graph.gates.begin() ; it != graph.gates.end() ; it++ ){
	    FullTable.insert(pair<Node *, tuple<int, int, int, int> >(it->second, make_tuple(it->second->min0,
		it->second->max0, it->second->min1, it->second->max1 ) ) );
	}
}
/*
void Graph::StartOutputFile(){
    string temp_name = GraphName + "_true_path_set";
    outfile.open(temp_name.c_str(), ios::out);
    outfile<<"Header  {  A True Path Set  }\n\n";
    outfile<<"  Benchmark  {  "<<GraphName<<"  }\n\n";
}

void Graph::OutputPath(Path *path){
    lock_guard<mutex> mLock( gMutex );

    ++final_path_counter;
    outfile<<"  Path  {  "<<final_path_counter<<"  }\n\n";
    outfile<<"A True Path List"<<endl;
    outfile<<"  {"<<endl;
    outfile<<"  ---------------------------------------------------------------------------"<<endl;
    outfile<<"  Pin    type                                Incr        Path delay"<<endl;
    outfile<<"  ---------------------------------------------------------------------------"<<endl;
    int path_delay = 0;
    for(int index=0; index < path->path_gates.size(); index++){
        Node *crnt_gate = path->path_gates[index];
        Node *prvs_gate;

        if(index>0)
            prvs_gate = path->path_gates[index-1];

        if(crnt_gate->property<=1){
            int name_index = 0;
            outfile<<"  "<<crnt_gate->gate_name<<" ";
            name_index += 3 + crnt_gate->gate_name.size();

            if(crnt_gate->property==0){
                outfile<<"(in)";
                name_index += 4;
            }
            else{
                outfile<<"(out)";
                name_index += 5;
            }
            for(int i=0; i<46-name_index; i++)
                outfile<<" ";
            outfile<<"0"<<setw(11)<<path_delay<<" ";
            if(isOne(crnt_gate))    outfile<<"r"<<endl;
            else if(isZero(crnt_gate))  outfile<<"f"<<endl;
            else outfile<<"unknown"<<endl;
        }
        else{
            int name_index = 0;
            outfile<<"  "<<crnt_gate->gate_name;
            if(prvs_gate==crnt_gate->input_A)
                outfile<<"/A ";
            else
                outfile<<"/B ";
            name_index += 5 + crnt_gate->gate_name.size();
            switch(crnt_gate->property){  //0="input", 1="output", 2="NOT", 3="NAND", 4="NOR"
            case 2:{
                outfile<<"(NOT1)";
                name_index += 6;
                break;
            }
            case 3:{
                outfile<<"(NAND2)";
                name_index += 7;
                break;
            }
            case 4:{
                outfile<<"(NOR2)";
                name_index += 6;
                break;
            }
            }
            for(int i=0; i<46-name_index; i++)
                outfile<<" ";
            outfile<<"0"<<setw(11)<<path_delay<<" ";
            if(isOne(prvs_gate))    outfile<<"r"<<endl;  //CHANGE  to prvs_gate
            else if(isZero(prvs_gate))  outfile<<"f"<<endl; //CHANGE
            else outfile<<"unknown"<<endl;

            name_index = 0;
            outfile<<"  "<<crnt_gate->gate_name<<"/Y ";
            name_index += 5 + crnt_gate->gate_name.size();
            switch(crnt_gate->property){  //0="input", 1="output", 2="NOT", 3="NAND", 4="NOR"
            case 2:{
                outfile<<"(NOT1)";
                name_index += 6;
                break;
            }
            case 3:{
                outfile<<"(NAND2)";
                name_index += 7;
                break;
            }
            case 4:{
                outfile<<"(NOR2)";
                name_index += 6;
                break;
            }
            }
            for(int i=0; i<46-name_index; i++)
                outfile<<" ";
            path_delay += 1;
            outfile<<"1"<<setw(11)<<path_delay<<" ";
            if(isOne(crnt_gate))    outfile<<"r"<<endl;
            else if(isZero(crnt_gate))  outfile<<"f"<<endl;
            else outfile<<"unknown"<<endl;
        }
    }
    outfile<<"  --------------------------------------------------------------------------"<<endl;
    outfile<<"    Data Required Time 	        "<<timing_constraint<<endl;
    outfile<<"    Data Arrival Time   	 "<<path_delay<<endl;
    outfile<<"    --------------------------------------------------------------------------"<<endl;
    outfile<<"    Slack            	         "<<(timing_constraint-path_delay)<<endl;
    outfile<<"  }"<<endl;
    outfile<<"  "<<endl;
    outfile<<"  Input Vector"<<endl;
    outfile<<"  {"<<endl;
    Node *leading_gate = path->path_gates[0];
    for(map<string, Node *>::iterator it = inputs.begin(); it != inputs.end(); it++){
        if( (it->second)==leading_gate ){
            if( isOne(it->second) ) outfile<<"    "<<(it->second)->gate_name<<"  =  r"<<endl;
            else if(isZero(it->second)) outfile<<"    "<<(it->second)->gate_name<<"  =  f"<<endl;
            else outfile<<"    "<<(it->second)->gate_name<<"  =  unknown"<<endl;
        }
        else{
            if( isOne(it->second) ) outfile<<"    "<<(it->second)->gate_name<<"  =  1"<<endl;
            else if(isZero(it->second)) outfile<<"    "<<(it->second)->gate_name<<"  =  0"<<endl;
            else outfile<<"    "<<(it->second)->gate_name<<"  =  unknown"<<endl;
        }

    }
    outfile<<"  }\n\n";
    
}

void Graph::EndOutputFile(){
    outfile<<"}";
    outfile.close();
}
*/

void StartOutputFile(string s){
    string temp_name = s + "_true_path_set";
    outfile.open(temp_name.c_str(), ios::out);
    outfile<<"Header  {  A True Path Set  }\n\n";
    outfile<<"  Benchmark  {  "<< s <<"  }\n\n";
}

void OutputPath(Graph &g, Path *path){
    lock_guard<mutex> mLock( gMutex );

    ++final_path_counter;
    outfile<<"  Path  {  "<<final_path_counter<<"  }\n\n";
    outfile<<"A True Path List"<<endl;
    outfile<<"  {"<<endl;
    outfile<<"  ---------------------------------------------------------------------------"<<endl;
    outfile<<"  Pin    type                                Incr        Path delay"<<endl;
    outfile<<"  ---------------------------------------------------------------------------"<<endl;
    int path_delay = 0;
    for(int index=0; index < path->path_gates.size(); index++){
        Node *crnt_gate = path->path_gates[index];
        Node *prvs_gate;

        if(index>0)
            prvs_gate = path->path_gates[index-1];

        if(crnt_gate->property<=1){
            int name_index = 0;
            outfile<<"  "<<crnt_gate->gate_name<<" ";
            name_index += 3 + crnt_gate->gate_name.size();

            if(crnt_gate->property==0){
                outfile<<"(in)";
                name_index += 4;
            }
            else{
                outfile<<"(out)";
                name_index += 5;
            }
            for(int i=0; i<46-name_index; i++)
                outfile<<" ";
            outfile<<"0"<<setw(11)<<path_delay<<" ";
            if(g.isOne(crnt_gate))    outfile<<"r"<<endl;
            else if(g.isZero(crnt_gate))  outfile<<"f"<<endl;
            else outfile<<"unknown"<<endl;
        }
        else{
            int name_index = 0;
            outfile<<"  "<<crnt_gate->gate_name;
            if(prvs_gate==crnt_gate->input_A)
                outfile<<"/A ";
            else
                outfile<<"/B ";
            name_index += 5 + crnt_gate->gate_name.size();
            switch(crnt_gate->property){  //0="input", 1="output", 2="NOT", 3="NAND", 4="NOR"
            case 2:{
                outfile<<"(NOT1)";
                name_index += 6;
                break;
            }
            case 3:{
                outfile<<"(NAND2)";
                name_index += 7;
                break;
            }
            case 4:{
                outfile<<"(NOR2)";
                name_index += 6;
                break;
            }
            }
            for(int i=0; i<46-name_index; i++)
                outfile<<" ";
            outfile<<"0"<<setw(11)<<path_delay<<" ";
            if(g.isOne(prvs_gate))    outfile<<"r"<<endl;  //CHANGE  to prvs_gate
            else if(g.isZero(prvs_gate))  outfile<<"f"<<endl; //CHANGE
            else outfile<<"unknown"<<endl;

            name_index = 0;
            outfile<<"  "<<crnt_gate->gate_name<<"/Y ";
            name_index += 5 + crnt_gate->gate_name.size();
            switch(crnt_gate->property){  //0="input", 1="output", 2="NOT", 3="NAND", 4="NOR"
            case 2:{
                outfile<<"(NOT1)";
                name_index += 6;
                break;
            }
            case 3:{
                outfile<<"(NAND2)";
                name_index += 7;
                break;
            }
            case 4:{
                outfile<<"(NOR2)";
                name_index += 6;
                break;
            }
            }
            for(int i=0; i<46-name_index; i++)
                outfile<<" ";
            path_delay += 1;
            outfile<<"1"<<setw(11)<<path_delay<<" ";
            if(g.isOne(crnt_gate))    outfile<<"r"<<endl;
            else if(g.isZero(crnt_gate))  outfile<<"f"<<endl;
            else outfile<<"unknown"<<endl;
        }
    }
    outfile<<"  --------------------------------------------------------------------------"<<endl;
    outfile<<"    Data Required Time 	        "<<g.timing_constraint<<endl;
    outfile<<"    Data Arrival Time   	 "<<path_delay<<endl;
    outfile<<"    --------------------------------------------------------------------------"<<endl;
    outfile<<"    Slack            	         "<<(g.timing_constraint-path_delay)<<endl;
    outfile<<"  }"<<endl;
    outfile<<"  "<<endl;
    outfile<<"  Input Vector"<<endl;
    outfile<<"  {"<<endl;
    Node *leading_gate = path->path_gates[0];
    for(map<string, Node *>::iterator it = g.inputs.begin(); it != g.inputs.end(); it++){
        if( (it->second)==leading_gate ){
            if( g.isOne(it->second) ) outfile<<"    "<<(it->second)->gate_name<<"  =  r"<<endl;
            else if(g.isZero(it->second)) outfile<<"    "<<(it->second)->gate_name<<"  =  f"<<endl;
            else outfile<<"    "<<(it->second)->gate_name<<"  =  unknown"<<endl;
        }
        else{
            if( g.isOne(it->second) ) outfile<<"    "<<(it->second)->gate_name<<"  =  1"<<endl;
            else if(g.isZero(it->second)) outfile<<"    "<<(it->second)->gate_name<<"  =  0"<<endl;
            else outfile<<"    "<<(it->second)->gate_name<<"  =  unknown"<<endl;
        }

    }
    outfile<<"  }\n\n";
    
}

void EndOutputFile(){
    outfile<<"}";
    outfile.close();
}


Edge::Edge(const string &name){
    wire_name = name;
    input_gate = NULL;
}

void Edge::AddOutput(Node *output_node, const string &output_node_name){
    output_gates_from_wire.insert( pair<string, Node *>(output_node_name, output_node) );
}

Node::Node(const string &name, int prop){
	gate_name = name;
	delay = 0;
	total_delay = 0;
	input_A = NULL;
	input_B = NULL;
	property = prop;
	min0 = -1;
	max0 = -1;
	min1 = -1;
	max1 = -1;
	input_A_wire = NULL;
	input_B_wire = NULL;
}

void Node::AddOutputGate(Node *output_node, const string &output_node_name){
    outputs_Y.insert( pair<string, Node *>(output_node_name, output_node) );
}

Graph::Graph(const string &n, int timing, int slack){
	GraphName = n;
	numberOfTruePaths_r = 0;
	numberOfFalsePaths_r = 0;
 	numberOfTruePaths_f = 0;
	numberOfFalsePaths_f = 0;
//  final_path_counter = 0;
  timing_constraint = timing;
  slack_constraint = slack;  
  fail_index = -1;
}

Graph::~Graph(){
	map<string, Edge *>::iterator itE;
	for ( itE = wires.begin() ; itE != wires.end() ; itE++ )
	{
		delete (*itE).second;
		(*itE).second = 0;
	}

	map<string, Node *>::iterator itN;
	for ( itN = gates.begin() ; itN != gates.end() ; itN++ )
	{
		delete (*itN).second;
		(*itN).second = 0;
	}
}

void Graph::ReadTimingConstraint(const string& filename){
    //check filename
    if(filename.substr(filename.size()-3, filename.size()-3)!="sdc")
        cout<<"wrong file while reading timing constraint!!"<<endl;
    else{
        fstream infile;
        infile.open(filename.c_str(), ios::in);
        string buffer1;
        infile>>buffer1;
        while(buffer1!="set_max_delay")
            infile>>buffer1;
        infile>>timing_constraint;
    }
}


void Graph::BuildGraph(const string& filename){
    fstream infile;
    infile.open(filename.c_str(), ios::in);

    string buffer1;
    int mode=0;
    infile>>buffer1;
    bool start_read = false;
    while(buffer1 != "endmodule"){
        string buffer2;
        if(buffer1 == "module") start_read = true;
        if(start_read){
          if(buffer1=="input") mode = 1;
          else if(buffer1=="output") mode = 2;
          else if(buffer1=="wire") mode = 3;
          else if(buffer1=="NOT1") mode = 4;
          else if(buffer1=="NAND2") mode = 5;
          else if(buffer1=="NOR2") mode = 6;
          else mode = 0;
        }
        //Node property : 0="input", 1="output", 2="NOT", 3="NAND", 4="NOR"
        if(mode!=0){
          buffer2 = "haha";
          switch(mode){
              case 1:{  //input
                  while(buffer2[buffer2.length()-1]!=';'){
                      infile>>buffer2;
                      string temp = buffer2.substr(0,buffer2.length()-1);
                      Node *a = new Node(temp, 0);
                      inputs.insert( pair<string,Node *>(temp, a));
                      Edge *b = new Edge(temp);
                      b->input_gate = a;
                      wires.insert(pair<string, Edge *>(temp, b));
                  }/*
                  cout<<"Input nodes have been read."<<endl;
                  cout<<"Inputs nodes are : "<<endl;
                  for(map<string, Node *>::iterator it = inputs.begin() ; it != inputs.end() ; it++ )
                      cout<<it->second->gate_name<<endl;*/
                  break;
              }
  
              case 2:{  //output
                  while(buffer2[buffer2.length()-1]!=';'){
                      infile>>buffer2;
                      string temp = buffer2.substr(0,buffer2.length()-1);
                      Node *a = new Node( temp, 1 );
                      outputs.insert( pair<string, Node *>( temp, a) );
                      Edge *b = new Edge(temp);
                      b->output_gates_from_wire.insert( pair<string, Node *>( temp, a) );
                      a->input_A_wire = b;
                      wires.insert(pair<string, Edge *>(temp, b));
                  }/*
                  cout<<"Output nodes have been read."<<endl;
                  cout<<"Outputs nodes are : "<<endl;
                  for(map<string, Node *>::iterator it = outputs.begin() ; it != outputs.end() ; it++ )
                      cout<<it->second->gate_name<<endl;*/
                  break;
              }
  
              case 3:{ //wire
                  while(buffer2[buffer2.length()-1]!=';'){
                      infile>>buffer2;
                      string temp = buffer2.substr(0,buffer2.length()-1);
                      Edge *a = new Edge(temp);
                      wires.insert( pair<string, Edge *>(temp, a ));
                  }/*
                  cout<<"Wires has been read."<<endl;
                  cout<<"Wires are : "<<endl;
                  for(map<string, Edge *>::iterator it = wires.begin() ; it != wires.end() ; it++ )
                      cout<<it->second->wire_name<<endl;*/
                  break;
              }
  
              case 4:{ //NOT
                  infile>>buffer2; //"[gate_name]"
                  string gate_name = buffer2;
                  Node *a = new Node(gate_name, 2);
                  gates.insert(pair<string, Node *>(gate_name, a));
  
                  infile>>buffer2; // "("
  
                  infile>>buffer2;
                  
                  if(buffer2[1]=='A'){
                  //it is the input wire of this gate
                      map<string, Edge *>::iterator it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                      (*it).second->AddOutput( a, gate_name );
                      a->input_A_wire = (*it).second;
                      
                      infile>>buffer2; // ".Y([wire_name])"
                      it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                      (*it).second->input_gate = a;
                  
                      infile>>buffer2;   //");"
                      //cout<<"Gate "<<gate_name<<" has been read."<<endl;                                 
                  }else{
                  //output wire is read first
                      map<string, Edge *>::iterator it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                      (*it).second->input_gate = a;
                      
                      infile>>buffer2; // ".A([wire_name]),"
                      it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                      (*it).second->AddOutput( a, gate_name );
                      a->input_A_wire = (*it).second;
                      
                      infile>>buffer2;   //");"
                      //cout<<"Gate "<<gate_name<<" has been read."<<endl;          
                  }
                  break;
              }
  
              case 5:{  //NAND
                  infile>>buffer2;  //"[gate_name]"
                  string gate_name = buffer2;
                  Node *a = new Node(gate_name, 3);
                  gates.insert(pair<string, Node *>(gate_name, a));
  
                  infile>>buffer2; // "("
  
                  infile>>buffer2;
                  
                  if(buffer2[1]=='A'){
                      map<string, Edge *>::iterator it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                      (*it).second->AddOutput( a , gate_name );
                      a->input_A_wire = (*it).second;
                      
                      infile>>buffer2;
                      if(buffer2[1]=='B'){
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_B_wire = (*it).second;
                          
                          infile>>buffer2; // ".Y([wire_name])"
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->input_gate = a;
                          
                          infile>>buffer2;   //");"
                          //cout<<"Gate "<<gate_name<<" has been read."<<endl;
                      }else{
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->input_gate = a;
                          
                          infile>>buffer2; // ".Y([wire_name])"
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_B_wire = (*it).second;  
                             
                          infile>>buffer2;   //");"                              
                      }
                  }else if(buffer2[1]=='B'){
                      map<string, Edge *>::iterator it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                      (*it).second->AddOutput( a , gate_name );
                      a->input_B_wire = (*it).second;
                      
                      infile>>buffer2;
                      if(buffer2[1]=='A'){
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_A_wire = (*it).second;
                          
                          infile>>buffer2; // ".Y([wire_name])"
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->input_gate = a;
                          
                          infile>>buffer2;   //");"
                          //cout<<"Gate "<<gate_name<<" has been read."<<endl;
                      }else{ //Y
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->input_gate = a;
                          
                          infile>>buffer2; // A
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_A_wire = (*it).second;  
                             
                          infile>>buffer2;   //");"                              
                      }    
                  }else{   //Y
                      map<string, Edge *>::iterator it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                      (*it).second->input_gate = a;
                      
                      infile>>buffer2;
                      if(buffer2[1]=='A'){
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_A_wire = (*it).second;
                          
                          infile>>buffer2; //B
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->AddOutput( a , gate_name );
                          a->input_B_wire = (*it).second;
                            
                          infile>>buffer2;   //");"
                          //cout<<"Gate "<<gate_name<<" has been read."<<endl;
                      }else{ //B
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->AddOutput( a , gate_name );
                          a->input_B_wire = (*it).second;
                     
                          infile>>buffer2; // A
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_A_wire = (*it).second;  
                             
                          infile>>buffer2;   //");"                              
                      }   
                  }
                  
                  //cout<<"Gate "<<gate_name<<" has been read."<<endl;
                  break;
              }
  
              case 6:{  //NOR
                  infile>>buffer2;
                  string gate_name = buffer2;
                  Node *a = new Node(gate_name, 4);
                  gates.insert(pair<string, Node *>(gate_name, a));
  
                  infile>>buffer2; //"("
  
                  infile>>buffer2;
                  
                  if(buffer2[1]=='A'){
                      map<string, Edge *>::iterator it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                      (*it).second->AddOutput( a , gate_name );
                      a->input_A_wire = (*it).second;
                      
                      infile>>buffer2;
                      if(buffer2[1]=='B'){
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_B_wire = (*it).second;
                          
                          infile>>buffer2; // ".Y([wire_name])"
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->input_gate = a;
                          
                          infile>>buffer2;   //");"
                          //cout<<"Gate "<<gate_name<<" has been read."<<endl;
                      }else{
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->input_gate = a;
                          
                          infile>>buffer2; // ".Y([wire_name])"
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_B_wire = (*it).second;  
                             
                          infile>>buffer2;   //");"                              
                      }
                  }else if(buffer2[1]=='B'){
                      map<string, Edge *>::iterator it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                      (*it).second->AddOutput( a , gate_name );
                      a->input_B_wire = (*it).second;
                      
                      infile>>buffer2;
                      if(buffer2[1]=='A'){
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_A_wire = (*it).second;
                          
                          infile>>buffer2; // ".Y([wire_name])"
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->input_gate = a;
                          
                          infile>>buffer2;   //");"
                          //cout<<"Gate "<<gate_name<<" has been read."<<endl;
                      }else{ //Y
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->input_gate = a;
                          
                          infile>>buffer2; // A
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_A_wire = (*it).second;  
                             
                          infile>>buffer2;   //");"                              
                      }    
                  }else{   //Y
                      map<string, Edge *>::iterator it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                      (*it).second->input_gate = a;
                      
                      infile>>buffer2;
                      if(buffer2[1]=='A'){
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_A_wire = (*it).second;
                          
                          infile>>buffer2; //B
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->AddOutput( a , gate_name );
                          a->input_B_wire = (*it).second;
                            
                          infile>>buffer2;   //");"
                          //cout<<"Gate "<<gate_name<<" has been read."<<endl;
                      }else{ //B
                          it = wires.find( buffer2.substr(3, buffer2.size()-5) );
                          (*it).second->AddOutput( a , gate_name );
                          a->input_B_wire = (*it).second;
                     
                          infile>>buffer2; // A
                          it = wires.find( buffer2.substr(3, buffer2.size()-4) );
                          (*it).second->AddOutput(a, gate_name );
                          a->input_A_wire = (*it).second;  
                             
                          infile>>buffer2;   //");"                              
                      }   
                  }
                  //cout<<"Gate "<<gate_name<<" has been read."<<endl;
                  break;
              }
              default:
                  break;
          }  //end of switch
        }
        infile>>buffer1;
    }
    infile.close();
}

void Graph::ConnectGates(){
    map<string, Node *>::iterator it1;  //connect input ports of every gate to their previous gates
	for( it1 = gates.begin() ; it1 != gates.end() ; it1++ ){
        Node *gatePtr = (*it1).second;
        Node *input_gate_Ptr;

        input_gate_Ptr = (gatePtr->input_A_wire)->input_gate;
        gatePtr->input_A = input_gate_Ptr;
        input_gate_Ptr->AddOutputGate(gatePtr ,gatePtr->gate_name);

        if(gatePtr->input_B_wire != NULL){
            input_gate_Ptr = (gatePtr->input_B_wire)->input_gate;
            gatePtr->input_B = input_gate_Ptr;
            input_gate_Ptr->AddOutputGate(gatePtr, gatePtr->gate_name);
        }
    }
    map<string, Node *>::iterator it2; //connect input ports of every output node to their previous gates
    for( it2 = outputs.begin() ; it2 != outputs.end() ; it2++ ){
        Node *gatePtr = (*it2).second;

        Node *input_gate_Ptr = (gatePtr->input_A_wire)->input_gate;
        gatePtr->input_A = input_gate_Ptr;
        input_gate_Ptr->AddOutputGate(gatePtr, gatePtr->gate_name);
	}
}

void Graph::FindAllPaths(){
    for(map<string, Node *>::iterator it1 = inputs.begin() ; it1 != inputs.end() ; it1++ ){
        Path *path = new Path();
        path->path_gates.push_back(it1->second);
        SubFindAllPaths(it1->second, path);
    }

    for(int i=0; i<(paths.size()-1); i++){
        int j=0;
        while(paths[i]->path_gates[j]==paths[i+1]->path_gates[j]){
            ++paths[i]->next_longest_same_gate_index;
            ++paths[i+1]->prvs_longest_same_gate_index;
            j++;
        }
    }
}

void Graph::SubFindAllPaths( Node *start_node, Path *old_path){
    if(start_node->outputs_Y.size()==0){ //the start_node is one of output node
        if(old_path->path_gates.size() >= (timing_constraint-slack_constraint+3))
            paths.push_back(old_path);
        return;
    }

        for(map<string, Node *>::iterator it1 = start_node->outputs_Y.begin(); it1 != start_node->outputs_Y.end(); it1++){
            Path *path = new Path();
            path->path_gates = old_path->path_gates;
            path->path_gates.push_back(it1->second);
            SubFindAllPaths(it1->second, path);
        }

}

void Graph::AllNodesInformation(){
	cout<<"(name; outputs; inputs)"<<endl;
	for(map<string, Node *>::iterator it = inputs.begin() ; it != inputs.end() ; it++ ){
	    cout<<"("<<it->second->gate_name<<"; ";
	    for(map<string, Node *>::iterator it1 = it->second->outputs_Y.begin() ; it1 != it->second->outputs_Y.end() ; it1++ ){
	    cout<<it1->second->gate_name<<", ";
	    }
	    cout<<"; ";
	    if(it->second->input_A!=NULL)   cout<<it->second->input_A->gate_name<<", ";
	    if(it->second->input_B!=NULL)   cout<<it->second->input_B->gate_name;
	    cout<<")"<<endl;
	}

	for(map<string, Node *>::iterator it = outputs.begin() ; it != outputs.end() ; it++ ){
	    cout<<"("<<it->second->gate_name<<"; ";
	    for(map<string, Node *>::iterator it1 = it->second->outputs_Y.begin() ; it1 != it->second->outputs_Y.end() ; it1++ ){
	    cout<<it1->second->gate_name<<", ";
	    }
	    cout<<"; ";
	    if(it->second->input_A!=NULL)   cout<<it->second->input_A->gate_name<<", ";
	    if(it->second->input_B!=NULL)   cout<<it->second->input_B->gate_name;
	    cout<<")"<<endl;
	}

	for(map<string, Node *>::iterator it = gates.begin() ; it != gates.end() ; it++ ){
	    cout<<"("<<it->second->gate_name<<"; ";
	    for(map<string, Node *>::iterator it1 = it->second->outputs_Y.begin() ; it1 != it->second->outputs_Y.end() ; it1++ ){
	    	cout<<it1->second->gate_name<<", ";
	    }
	    cout<<"; ";
	    if(it->second->input_A!=NULL)   cout<<it->second->input_A->gate_name<<", ";
	    if(it->second->input_B!=NULL)   cout<<it->second->input_B->gate_name;
	    cout<<")"<<endl;
	}
}

void Graph::DisplayAllPaths(){
	/*
	int x=0;
    for(int i=0; i<paths.size(); i++){
    	if(paths[i]->path_gates.size()>=0)
    	{
	        cout<<"path"<<(i+1)<<"(length="<<paths[i]->path_gates.size()-2<<") : "<<endl;
	        for(int j=0; j<(paths[i]->path_gates).size(); j++){
	            cout<<paths[i]->path_gates[j]->gate_name<<" -> ";
	        }
	        cout<<"end of path"<<endl;
	        x++;
   		}
    }
    cout << "x = " << x << endl;
    cout << "Total: " << paths.size() << endl;
    */
    /*Path *a = paths[0];
        cout<<"path1(length="<<a->path_gates.size()<<") : "<<endl;
        for(int j=0; j<(a->path_gates).size(); i++){
            cout<<a->path_gates[j]->gate_name<<" -> ";
        }
        cout<<"end of path"<<endl;*/

    cout<<"Longest same path list : "<<endl;
    for(int i=0; i<paths.size()-1;i++){
        cout<<"path "<<(i+1)<<" and "<<(i+2)<<" : "<<paths[i]->next_longest_same_gate_index<<endl;
    }
}


//CORE ALGORITHMS
void Graph::Implication_Init(){
	for(map<string, Node *>::iterator it = gates.begin(); it != gates.end(); it++){
		it->second->min0 = -1;
		it->second->max0 = -1;
		it->second->min1 = -1;
		it->second->max1 = -1;
	}

	for(map<string, Node *>::iterator it = outputs.begin(); it != outputs.end(); it++){
		it->second->min0 = -1;
		it->second->max0 = -1;
		it->second->min1 = -1;
		it->second->max1 = -1;
	}

	for(map<string, Node *>::iterator it = inputs.begin(); it != inputs.end(); it++){
		it->second->min0 = 0;
		it->second->max0 = 0;
		it->second->min1 = 0;
		it->second->max1 = 0;
	}

	for(map<string, Node *>::iterator it = outputs.begin(); it != outputs.end(); it++){
		Init_Stable_Time((*it).second);  //(*it).second
	}
}

void Graph::Init_Stable_Time(Node *g){
	if(g->input_A->min0 == -1)
		Init_Stable_Time(g->input_A);
	if(g->input_B != NULL){
		if(g->input_B->min0 == -1)
			Init_Stable_Time(g->input_B);
	}

	bool dummy;
	Forward_Implication(g, dummy, true);
}

bool Graph::Update_Stable_Time(Node *g){ //return false if conflicted detected
	bool a_changed = false, b_changed = false, output_changed = false;

	if(g->input_A != NULL){
		if( ! Backward_Implication(g, a_changed, b_changed) ){
			return false;
		}
	}

	if(a_changed){
		if(! Update_Stable_Time(g->input_A)){
			return false;
		}
	}

	if(b_changed){
		if(! Update_Stable_Time(g->input_B)){
			return false;
		}
	}

	for(map<string, Node *>::iterator it1 = g->outputs_Y.begin(); it1 != g->outputs_Y.end(); ++it1){
		if(! Forward_Implication(it1->second, output_changed ) ){
			return false;
		}
		if(output_changed){
			if(! Update_Stable_Time(it1->second) )  	return false;
		}
	}

	return true;
}

/*
bool Forward_Update(Node *g, bool changed){
	bool output_changed = false;
	int old_min0 = g->min0;
	int old_max0 = g->max0;
	int old_min1 = g->min1;
	int old_max1 = g->max1;

	for(map<string, Node *>::iterator it1 = g->outputs_Y.begin(); it1 != g->outputs_Y.end(); ++it1){
		if(! Forward(it1->second, output_changed ) ){
			g->min0 = old_min0;
			g->max0 = old_max0;
			g->min1 = old_min1;
			g->max1 = old_max1;
			return false;
		}
		if(output_changed){
			if(! Forward(it1->second, output_changed ) )  	return false;
		}
	}
}
*/

bool Graph::Verify_True_Path(Path *p, bool rise){
	Implication_Init();

	if(rise)	Apply(p->path_gates[0], INT_MAX, 0, 0, 0);
	else		Apply(p->path_gates[0], 0, 0, INT_MAX, 0);

	if(!Update_Stable_Time(p->path_gates[0])){  //This will never lead to a conflict, right?
		//cout <<"Conflict during update after assignment of input." << endl;
		return false;
	}

	//Display_All_Stable_Interval();
	//system("pause");

	bool changed = false;

	for(int i=1; i < p->path_gates.size() -1 ; ++i)  //for each gate on path p not including primary i/o
	{
		int type = (p->path_gates[i])->property;
		switch(type)
		{
			case 2:  //NOT
				break;
			case 3:  //NAND
				if( isZero( p->path_gates[i-1] ) ){ //controlling input 0
					if(p->path_gates[i-1] == p->path_gates[i]->input_A){ //B is the side input
						changed = Apply(p->path_gates[i]->input_B, p->path_gates[i-1]->min0, INT_MAX, 0, INT_MAX);
						if(isConflicted(p->path_gates[i]->input_B)){
							//Debug Messages
							/*cout << "Conflict at " << p->path_gates[i]->input_B->gate_name << "after apply." << endl;
							cout << "NAND gate. On-input is controlling 0. " << endl;
							cout << "[ " << p->path_gates[i]->input_B->min0 << ", " << p->path_gates[i]->input_B->max0
								<< "][" << p->path_gates[i]->input_B->min1 << ", " << p->path_gates[i]->input_B->max1 << endl;*/

							fail_index = i;
              return false;
						}
						if(changed){
							if(! Update_Stable_Time(p->path_gates[i]->input_B) ){
								//Debug Messages
								/*cout << "Conflict at " << p->path_gates[i]->input_B->gate_name << "during update." << endl;
								cout << "NAND gate. On-input is controlling 0. " << endl;
								cout << "[ " << p->path_gates[i]->input_B->min0 << ", " << p->path_gates[i]->input_B->max0
								<< "][" << p->path_gates[i]->input_B->min1 << ", " << p->path_gates[i]->input_B->max1 << endl;*/
								fail_index = i;
                return false;
							}
						}
					}
					else{ // A is the side input
						changed = Apply(p->path_gates[i]->input_A, p->path_gates[i-1]->min0, INT_MAX, 0, INT_MAX);
						if(isConflicted(p->path_gates[i]->input_A)){
							//Debug Messages
							//cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "after apply." << endl;
							//cout << "NAND gate. On-input is controlling 0. " << endl;
							//cout << "[ " << p->path_gates[i]->input_A->min0 << ", " << p->path_gates[i]->input_A->max0
								//<< "][" << p->path_gates[i]->input_A->min1 << ", " << p->path_gates[i]->input_A->max1 << endl;
							fail_index = i;
              return false;
						}
						if(changed){
							if(! Update_Stable_Time(p->path_gates[i]->input_A) ){
								//Debug Messages
								/*cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "during update." << endl;
								cout << "NAND gate. On-input is controlling 0. " << endl;
								cout << "[ " << p->path_gates[i]->input_A->min0 << ", " << p->path_gates[i]->input_A->max0
								<< "][" << p->path_gates[i]->input_A->min1 << ", " << p->path_gates[i]->input_A->max1 << endl;*/

								fail_index = i;
                return false;
							}
						}
					}
				}
				else if( isOne( p->path_gates[i-1] )){ //non-controlling input 1
					if(p->path_gates[i-1] == p->path_gates[i]->input_A){ //B is the side input
						changed = Apply(p->path_gates[i]->input_B, INT_MAX, 0, 0, p->path_gates[i-1]->max1);
						if(isConflicted(p->path_gates[i]->input_B)){
							//Debug Messages
							/*cout << "Conflict at " << p->path_gates[i]->input_B->gate_name << "after apply." << endl;
							cout << "NAND gate. On-input is non-controlling 1. " << endl;
							cout << "[ " << p->path_gates[i]->input_B->min0 << ", " << p->path_gates[i]->input_B->max0
								<< "][" << p->path_gates[i]->input_B->min1 << ", " << p->path_gates[i]->input_B->max1 << endl;*/

							fail_index = i;
              return false;
						}
						if(changed){
							if(! Update_Stable_Time(p->path_gates[i]->input_B) ){
								//Debug Messages
								/*cout << "Conflict at " << p->path_gates[i]->input_B->gate_name << "during update." << endl;
								cout << "NAND gate. On-input is non-controlling 1. " << endl;
								cout << "[ " << p->path_gates[i]->input_B->min0 << ", " << p->path_gates[i]->input_B->max0
								<< "][" << p->path_gates[i]->input_B->min1 << ", " << p->path_gates[i]->input_B->max1 << endl;*/

								fail_index = i;
                return false;
							}
						}
					}
					else{ // A is the side input
						changed = Apply(p->path_gates[i]->input_A, INT_MAX, 0, 0, p->path_gates[i-1]->max1);
						if(isConflicted(p->path_gates[i]->input_A)){
							//Debug Messages
							/*cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "after apply." << endl;
							cout << "NAND gate. On-input is non-controlling 1. " << endl;
							cout << "[ " << p->path_gates[i]->input_A->min0 << ", " << p->path_gates[i]->input_A->max0
								<< "][" << p->path_gates[i]->input_A->min1 << ", " << p->path_gates[i]->input_A->max1 << endl;*/

							fail_index = i;
              return false;
						}
						if(changed){
							if(! Update_Stable_Time(p->path_gates[i]->input_A) ){
								//Debug Messages
								/*cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "during update." << endl;
								cout << "NAND gate. On-input is non-controlling 1. " << endl;
								cout << "[ " << p->path_gates[i]->input_A->min0 << ", " << p->path_gates[i]->input_A->max0
								<< "][" << p->path_gates[i]->input_A->min1 << ", " << p->path_gates[i]->input_A->max1 << endl;*/

								fail_index = i;
                return false;
							}
						}
					}
				}
				else{
					//cout << "NAND--Something is wrong here...Previous nodes on p should have known values." << endl;

        			/* DEBUG
					cout<<"ERROR path: " <<endl;
				    for(int j=0; j < p->path_gates.size(); j++){
				        cout<< p->path_gates[j]->gate_name<<" -> ";
				    }
				    cout<<"end of ERROR path"<<endl;
				    */
				}

				break;

			case 4:  //NOR
				if( isOne( p->path_gates[i-1] ) ){ //controlling input 1
					if(p->path_gates[i-1] == p->path_gates[i]->input_A){ //B is the side input
						changed = Apply(p->path_gates[i]->input_B, 0, INT_MAX, p->path_gates[i-1]->min1, INT_MAX);
						if(isConflicted(p->path_gates[i]->input_B)){
							//Debug Messages
							/*cout << "Conflict at " << p->path_gates[i]->input_B->gate_name << "after apply." << endl;
							cout << "NAND gate. On-input is controlling 1. " << endl;
							cout << "[ " << p->path_gates[i]->input_B->min0 << ", " << p->path_gates[i]->input_B->max0
								<< "][" << p->path_gates[i]->input_B->min1 << ", " << p->path_gates[i]->input_B->max1 << endl;*/

							fail_index = i;
              return false;
						}
						if(changed){
							if(! Update_Stable_Time(p->path_gates[i]->input_B) ){
								//Debug Messages
								/*cout << "Conflict at " << p->path_gates[i]->input_B->gate_name << "during update." << endl;
								cout << "NAND gate. On-input is controlling 1. " << endl;
								cout << "[ " << p->path_gates[i]->input_B->min0 << ", " << p->path_gates[i]->input_B->max0
								<< "][" << p->path_gates[i]->input_B->min1 << ", " << p->path_gates[i]->input_B->max1 << endl;*/

								fail_index = i;
                return false;
							}
						}
					}
					else{ // A is the side input
						changed = Apply(p->path_gates[i]->input_A, 0, INT_MAX, p->path_gates[i-1]->min1, INT_MAX);
						if(isConflicted(p->path_gates[i]->input_A)){
							//Debug Messages
							/*cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "after apply." << endl;
							cout << "NAND gate. On-input is controlling 1. " << endl;
							cout << "[ " << p->path_gates[i]->input_A->min0 << ", " << p->path_gates[i]->input_A->max0
								<< "][" << p->path_gates[i]->input_A->min1 << ", " << p->path_gates[i]->input_A->max1 << endl;*/

							fail_index = i;
              return false;
						}
						if(changed){
							if(! Update_Stable_Time(p->path_gates[i]->input_A) ){
								//Debug Messages
								/*cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "during update." << endl;
								cout << "NAND gate. On-input is controlling 1. " << endl;
								cout << "[ " << p->path_gates[i]->input_A->min0 << ", " << p->path_gates[i]->input_A->max0
								<< "][" << p->path_gates[i]->input_A->min1 << ", " << p->path_gates[i]->input_A->max1 << endl;*/

								fail_index = i;
                return false;
							}
						}
					}
				}
				else if( isZero( p->path_gates[i-1] )){ //non-controlling input 0
					if(p->path_gates[i-1] == p->path_gates[i]->input_A){ //B is the side input
						changed = Apply(p->path_gates[i]->input_B, 0, p->path_gates[i-1]->max0, INT_MAX, 0);
						if(isConflicted(p->path_gates[i]->input_B)){
							//Debug Messages
							/*cout << "Conflict at " << p->path_gates[i]->input_B->gate_name << "after apply." << endl;
							cout << "NAND gate. On-input is non-controlling 0. " << endl;
							cout << "[ " << p->path_gates[i]->input_B->min0 << ", " << p->path_gates[i]->input_B->max0
								<< "][" << p->path_gates[i]->input_B->min1 << ", " << p->path_gates[i]->input_B->max1 << endl;*/


							fail_index = i;
              return false;
						}
						if(changed){
							if(! Update_Stable_Time(p->path_gates[i]->input_B) ){
								//Debug Messages
								/*cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "during update." << endl;
								cout << "NAND gate. On-input is non-controlling 0. " << endl;
								cout << "[ " << p->path_gates[i]->input_B->min0 << ", " << p->path_gates[i]->input_B->max0
								<< "][" << p->path_gates[i]->input_B->min1 << ", " << p->path_gates[i]->input_B->max1 << endl;*/
								fail_index = i;
                return false;
							}
						}
					}
					else{ // A is the side input
						changed = Apply(p->path_gates[i]->input_A, 0, p->path_gates[i-1]->max0, INT_MAX, 0);
						if(isConflicted(p->path_gates[i]->input_A)){
							//Debug Messages
							/*cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "after apply." << endl;
							cout << "NAND gate. On-input is non-controlling 0. " << endl;
							cout << "[ " << p->path_gates[i]->input_A->min0 << ", " << p->path_gates[i]->input_A->max0
								<< "][" << p->path_gates[i]->input_A->min1 << ", " << p->path_gates[i]->input_A->max1 << endl;*/

							fail_index = i;
              return false;
						}
						if(changed){
							if(! Update_Stable_Time(p->path_gates[i]->input_A) ){
								//Debug Messages
								/*cout << "Conflict at " << p->path_gates[i]->input_A->gate_name << "during update." << endl;
								cout << "NAND gate. On-input is non-controlling 0. " << endl;
								cout << "[ " << p->path_gates[i]->input_A->min0 << ", " << p->path_gates[i]->input_A->max0
								<< "][" << p->path_gates[i]->input_A->min1 << ", " << p->path_gates[i]->input_A->max1 << endl;*/

								fail_index = i;
                return false;
							}
						}
					}
				}
				else{
					//cout << "NOR--Something is wrong here...Previous nodes on p should have known values." << endl;

					/*DEBUG

					cout<<"ERROR path: " <<endl;
				    for(int j=0; j < p->path_gates.size(); j++){
				        cout<< p->path_gates[j]->gate_name<<" -> ";
				    }
				    cout<<"end of ERROR path"<<endl;

				    cout << p->path_gates[i-1]->gate_name <<endl;
				    cout << p->path_gates[i-1]->min0 << endl
				    	<<  p->path_gates[i-1]->max0 << endl
						<< p->path_gates[i-1]->min1 << endl
						<< p->path_gates[i-1]->max1 << endl;

					*/
				}

				break;

			default:
				cout << "ERROR! What type of node is this? " << type << endl;
				break;
		}

	}

	return true;
}

bool Graph::isOne(Node *g){
	return (g->min1 <= g->max1) && (g->min0 > g->max0);
}

bool Graph::isZero(Node *g){
	return (g->min0 <= g->max0) && (g->min1 > g->max1);
}

bool Graph::isUnknown(Node *g){
	return (g->min0 <= g->max0) && (g->min1 <= g->max1);
}

bool Graph::isConflicted(Node *g){
	return (g->min0 > g->max0) && (g->min1 > g->max1);
}

bool Graph::Apply(Node *g, int min0, int max0, int min1, int max1){ //return true if g[,][,] has changed
	if(min0==-1 && max0==-1 && min1==-1 && max1==-1)	return false;

	int original_min0 = g->min0;
	int original_max0 = g->max0;
	int original_min1 = g->min1;
	int original_max1 = g->max1;

	if(min0 != -1)	g->min0 = max(g->min0, min0);
	if(max0 != -1)  g->max0 = min(g->max0, max0);
	if(min1 != -1)	g->min1 = max(g->min1, min1);
	if(max1 != -1)	g->max1 = min(g->max1, max1);

	if(g->min0 > g->max0){
		g->min0 = INT_MAX;
		g->max0 = 0;
	}

	if(g->min1 > g->max1){
		g->min1 = INT_MAX;
		g->max1 = 0;
	}

	if(original_min0 != g->min0)	return true;
	if(original_max0 != g->max0)	return true;
	if(original_min1 != g->min1)	return true;
	if(original_max1 != g->max1)	return true;

	return false;
}

bool Graph::Forward_Implication(Node *g, bool &Output_changed, bool exact_apply){
	int new_min0 = -1, new_max0 = -1, new_min1 = -1, new_max1 = -1;

	int type = g->property;
	switch(type)
	{
		case 1:  //output
			new_min0 = g->input_A->min0;
			new_max0 = g->input_A->max0;
			new_min1 = g->input_A->min1;
			new_max1 = g->input_A->max1;
			break;

		case 2:  //NOT
			if(isZero(g->input_A)){
				//input is 0
				//apply [INF, 0][ Tmin0+d(G), Tmax0+d(G)] at g
				new_min0 = INT_MAX;
				new_max0 = 0;
				new_min1 = g->input_A->min0 + 1;
				new_max1 = g->input_A->max0 + 1;
			}
			else if(isOne(g->input_A)){
				//input is 1
				//apply [ Tmin1+d(G), Tmax1+d(G)] [INF, 0] at g
				new_min0 = g->input_A->min1 + 1;
				new_max0 = g->input_A->max1 + 1;
				new_min1 = INT_MAX;
				new_max1 = 0;
			}
			else{
				//input is unknown
				new_min0 = g->input_A->min1 + 1;
				new_max0 = g->input_A->max1 + 1;
				new_min1 = g->input_A->min0 + 1;
				new_max1 = g->input_A->max0 + 1;
			}

			break;

		case 3:  //NAND
			if(isOne(g->input_A) && isOne(g->input_B)){
				//all inputs are 1
		 		//apply [max(Timin1, 1)+d(G), max(Timax1, 1) +d(G)][INF, 0] at g
		 		new_min0 = max(g->input_A->min1, g->input_B->min1) + 1;
				new_max0 = max(g->input_A->max1, g->input_B->max1) + 1;
				new_min1 = INT_MAX;
				new_max1 = 0;
			}
			else if(isZero(g->input_A) || isZero(g->input_B)){
				//any input is 0
				//apply [INF, 0][MIN(min(Timin0, 0), min(Timin0, ?)) +d(G), min(Timax0, 0) +d(G) ] at g
				if(isZero(g->input_A)){
					if(isZero(g->input_B)){
						new_min0 = INT_MAX;
						new_max0 = 0;
						new_min1 = min(g->input_A->min0, g->input_B->min0) + 1;
						new_max1 = min(g->input_A->max0, g->input_B->max0) + 1;
					}
					else if(isOne(g->input_B)){
						new_min0 = INT_MAX;
						new_max0 = 0;
						new_min1 = g->input_A->min0 + 1;
						new_max1 = g->input_A->max0 + 1;
					}
					else{ //B unknown
						new_min0 = INT_MAX;
						new_max0 = 0;
						new_min1 = min(g->input_A->min0, g->input_B->min0) + 1;
						new_max1 = g->input_A->max0 + 1;
					}
				}
				else if(isOne(g->input_A)){ //input_B is 0
					new_min0 = INT_MAX;
					new_max0 = 0;
					new_min1 = g->input_B->min0 + 1;
					new_max1 = g->input_B->max0 + 1;
				}
				else{ //input_A is unknown, B is 0
					new_min0 = INT_MAX;
					new_max0 = 0;
					new_min1 = min(g->input_A->min0, g->input_B->min0) + 1;
					new_max1 = g->input_B->max0 + 1;
				}
			}
			else{
				//apply [MAX(max(Timin1, 1), max(Timin1, ?)) +d(G), MAX(max(Timax1, 1), max(Timax1, ?)) +d(G)]
				//      [ min(Timin0, ?) +d(G), max(Timax0, ?) +d(G)]
				if(isUnknown(g->input_A) && isUnknown(g->input_B)){
					new_min0 = max(g->input_A->min1, g->input_B->min1) + 1;
					new_max0 = max(g->input_A->max1, g->input_B->max1) + 1;
					new_min1 = min(g->input_A->min0, g->input_B->min0) + 1;
					new_max1 = max(g->input_A->max0, g->input_B->max0) + 1;
				}
				else if(isOne(g->input_A)){ //B is unknown
					new_min0 = max(g->input_A->min1, g->input_B->min1) + 1;
					new_max0 = max(g->input_A->max1, g->input_B->max1) + 1;
					new_min1 = g->input_B->min0 + 1;
					new_max1 = g->input_B->max0 + 1;
				}
				else{ //A is unknown, B is 1
					new_min0 = max(g->input_A->min1, g->input_B->min1) + 1;
					new_max0 = max(g->input_A->max1, g->input_B->max1) + 1;
					new_min1 = g->input_A->min0 + 1;
					new_max1 = g->input_A->max0 + 1;
				}
			}

			break;

		case 4:  //NOR
			if(isZero(g->input_A) && isZero(g->input_B)){
				//all inputs are 0
		 		//apply [INF, 0][ max(Timin0, 0)+d(G), max(Timax0, 0) +d(G) ] at g
				new_min0 = INT_MAX;
				new_max0 = 0;
				new_min1 = max(g->input_A->min0, g->input_B->min0) + 1;
				new_max1 = max(g->input_A->max0, g->input_B->max0) + 1;
			}
			else if(isOne(g->input_A) || isOne(g->input_B)){
				//any input is 1
				//apply [MIN(min(Timin1, 1), min(Timin1, ?)) +d(G), min(Timax1, 1) +d(G) ][INF, 0] at g
				new_min1 = INT_MAX;
				new_max1 = 0;

				if(isOne(g->input_A)){
					if(isOne(g->input_B)){
						new_min0 = min(g->input_A->min1, g->input_B->min1) + 1;
						new_max0 = min(g->input_A->max1, g->input_B->max1) + 1;
					}
					else if(isZero(g->input_B)){
						new_min0 = g->input_A->min1 + 1;
						new_max0 = g->input_A->max1 + 1;
					}
					else{ //B unknown
						new_min0 = min(g->input_A->min1, g->input_B->min1) + 1;
						new_max0 = g->input_A->max1 + 1;
					}
				}
				else if(isZero(g->input_A)){ //input_B is 1
					new_min0 = g->input_B->min1 + 1;
					new_max0 = g->input_B->max1 + 1;
				}
				else{ //input_A is unknown, B is 1
					new_min0 = min(g->input_A->min1, g->input_B->min1) + 1;
					new_max0 = g->input_B->max1 + 1;
				}
			}
			else{
				//apply [ min(Timin1, ?) +d(G), max(Timax1, ?) +d(G)]
				//      [MAX(max(Timin0, 0), max(Timin0, ?)) +d(G), MAX(max(Timax0, 0), max(Timax0, ?)) +d(G)]
				if(isUnknown(g->input_A) && isUnknown(g->input_B)){
					new_min0 = min(g->input_A->min1, g->input_B->min1) + 1;
					new_max0 = max(g->input_A->max1, g->input_B->max1) + 1;
					new_min1 = max(g->input_A->min0, g->input_B->min0) + 1;
					new_max1 = max(g->input_A->max0, g->input_B->max0) + 1;
				}
				else if(isZero(g->input_A)){ //B is unknown
					new_min0 = g->input_B->min1 + 1;
					new_max0 = g->input_B->max1 + 1;
					new_min1 = max(g->input_A->min0, g->input_B->min0) + 1;
					new_max1 = max(g->input_A->max0, g->input_B->max0) + 1;
				}
				else{ //A is unknown, B is 0
					new_min0 = g->input_A->min1 + 1;
					new_max0 = g->input_A->max1 + 1;
					new_min1 = max(g->input_A->min0, g->input_B->min0) + 1;
					new_max1 = max(g->input_A->max0, g->input_B->max0) + 1;
				}
			}

			break;

		default:
			cout << "ERROR! What type of node is this? " << g->property << endl;
			break;
	}

	if(exact_apply){
		g->min0 = new_min0;
		g->max0 = new_max0;
		g->min1 = new_min1;
		g->max1 = new_max1;
		return true;
	}
	else{

	Output_changed = Apply(g, new_min0, new_max0, new_min1, new_max1);

	if(isConflicted(g))	return false;
	return true;

	}
}

bool Graph::Backward_Implication(Node *g, bool &A_changed, bool &B_changed){
	int new_A_min0 = -1, new_A_max0 = -1, new_A_min1 = -1, new_A_max1 = -1;
	int new_B_min0 = -1, new_B_max0 = -1, new_B_min1 = -1, new_B_max1 = -1;

	int type = g->property;
	switch(type)
	{
		case 1:  //output
			new_A_min0 = g->min0;
			new_A_max0 = g->max0;
			new_A_min1 = g->min1;
			new_A_max1 = g->max1;
			break;

		case 2:  //NOT
			if(isZero(g)){
				//outputput is 0
				new_A_min0 = INT_MAX;
				new_A_max0 = 0;
				new_A_min1 = g->min0 - 1;
				new_A_max1 = g->max0 - 1;
			}
			else if(isOne(g)){
				//outputput is 1
				new_A_min0 = g->min1 - 1;
				new_A_max0 = g->max1 - 1;
				new_A_min1 = INT_MAX;
				new_A_max1 = 0;
			}
			else{
				//output is unknown
				new_A_min0 = g->min1 - 1;
				new_A_max0 = g->max1 - 1;
				new_A_min1 = g->min0 - 1;
				new_A_max1 = g->max0 - 1;
			}

			break;

		case 3:  //NAND
			if(isZero(g)){
				//all inputs must be 1
				if( (g->input_A->max1 >= (g->min0 - 1)) && (g->input_B->max1 < (g->min0 - 1))){
					new_A_min0 = INT_MAX;
					new_A_max0 = 0;
					new_A_min1 = g->min0 -1;
					new_A_max1 = g->max0 -1;

					new_B_min0 = INT_MAX;
					new_B_max0 = 0;
					new_B_min1 = 0;
					new_B_max1 = g->max0 -1;
				}
				else if((g->input_B->max1 >= (g->min0 - 1)) && (g->input_A->max1 < (g->min0 - 1))){
					new_A_min0 = INT_MAX;
					new_A_max0 = 0;
					new_A_min1 = 0;
					new_A_max1 = g->max0 -1;

					new_B_min0 = INT_MAX;
					new_B_max0 = 0;
					new_B_min1 = g->min0 -1;
					new_B_max1 = g->max0 -1;
				}
				else{ //Can't determine dominant input gate at this moment
					new_A_min0 = INT_MAX;
					new_A_max0 = 0;
					new_A_min1 = 0;
					new_A_max1 = g->max0 -1;
					new_B_min0 = INT_MAX;
					new_B_max0 = 0;
					new_B_min1 = 0; //BUG
					new_B_max1 = g->max0 -1;
				}
			}
			else if(isOne(g)){
				if(isOne(g->input_A) && isOne(g->input_B)){
					return false; //conflict
				}
				else if(isOne(g->input_B) && (isZero(g->input_A) || isUnknown(g->input_A))){
					// A is dominant gate
					new_A_min0 = g->min1 -1;
					new_A_max0 = g->max1 -1;
					new_A_min1 = INT_MAX;
					new_A_max1 = 0;
				}
				else if(isOne(g->input_A) && (isZero(g->input_B) || isUnknown(g->input_B))){
					//B is dominant gate
					new_B_min0 = g->min1 -1;
					new_B_max0 = g->max1 -1;
					new_B_min1 = INT_MAX;
					new_B_max1 = 0;
				}
				else if(( g->input_A->min0 <= (g->max1 - 1) ) && ( g->input_B->min0 > (g->max1 - 1) )){
					//A is dominant gate
					new_A_min0 = g->min1 -1;
					new_A_max0 = g->max1 -1;
					new_A_min1 = INT_MAX;
					new_A_max1 = 0;
				}
				else if(( g->input_A->min0 <= (g->max1 - 1) ) && ( g->input_B->min0 > (g->max1 - 1) )){
					//B is dominant gate
					new_B_min0 = g->min1 -1;
					new_B_max0 = g->max1 -1;
					new_B_min1 = INT_MAX;
					new_B_max1 = 0;
				}
				else{
					//can't determine dominant input at this moment
					new_A_min0 = g->min1 -1;
					new_A_max0 = INT_MAX;
					new_A_min1 = 0;
					new_A_max1 = INT_MAX;
					new_B_min0 = g->min1 -1;
					new_B_max0 = INT_MAX;
					new_B_min1 = 0;
					new_B_max1 = INT_MAX;
				}
			}
			else{
				//output unknown
				new_A_min0 = g->min1 -1;
				new_A_max0 = INT_MAX;
				new_A_min1 = 0;
				new_A_max1 = INT_MAX;
				new_B_min0 = g->min1 -1;
				new_B_max0 = INT_MAX;
				new_B_min1 = 0;
				new_B_max1 = INT_MAX;
			}

			break;

		case 4:  //NOR
			if(isOne(g)){
				//all inputs must be 0
				if( (g->input_A->max0 >= (g->min1 - 1)) && (g->input_B->max0 < (g->min1 - 1))){
					new_A_min0 = g->min1 -1;
					new_A_max0 = g->max1 -1;
					new_A_min1 = INT_MAX;
					new_A_max1 = 0;

					new_B_min0 = 0;
					new_B_max0 = g->max1 -1;
					new_B_min1 = INT_MAX;
					new_B_max1 = 0;
				}
				else if((g->input_B->max0 >= (g->min1 - 1)) && (g->input_A->max0 < (g->min1 - 1))){
					new_B_min0 = g->min1 -1;
					new_B_max0 = g->max1 -1;
					new_B_min1 = INT_MAX;
					new_B_max1 = 0;

					new_A_min0 = 0;
					new_A_max0 = g->max1 -1;
					new_A_min1 = INT_MAX;
					new_A_max1 = 0;
				}
				else{ //Can't determine dominant input gate at this moment
					new_A_min0 = 0;
					new_A_max0 = g->max1 -1;
					new_A_min1 = INT_MAX;
					new_A_max1 = 0;
					new_B_min0 = 0;
					new_B_max0 = g->max1 -1;
					new_B_min1 = INT_MAX;
					new_B_max1 = 0;
				}
			}
			else if(isZero(g)){
				if(isZero(g->input_A) && isZero(g->input_B)){
					return false; //conflict
				}
				else if(isZero(g->input_B) && (isOne(g->input_A) || isUnknown(g->input_A))){
					// A is dominant gate
					new_A_min0 = INT_MAX;
					new_A_max0 = 0;
					new_A_min1 = g->min0 -1;
					new_A_max1 = g->max0 -1;
				}
				else if(isZero(g->input_A) && (isOne(g->input_B) || isUnknown(g->input_B))){
					//B is dominant gate
					new_B_min0 = INT_MAX;
					new_B_max0 = 0;
					new_B_min1 = g->min0 -1;
					new_B_max1 = g->max0 -1;
				}
				else if(( g->input_A->min1 <= (g->max0 - 1) ) && ( g->input_B->min1 > (g->max0 - 1) )){
					//A is dominant gate
					new_A_min0 = INT_MAX;
					new_A_max0 = 0;
					new_A_min1 = g->min0 -1;
					new_A_max1 = g->max0 -1;
				}
				else if(( g->input_B->min1 <= (g->max0 - 1) ) && ( g->input_A->min1 > (g->max0 - 1) )){
					//B is dominant gate
					new_B_min0 = INT_MAX;
					new_B_max0 = 0;
					new_B_min1 = g->min0 -1;
					new_B_max1 = g->max0 -1;
				}
				else{
					//can't determine dominant input at this moment
					new_A_min0 = 0;
					new_A_max0 = INT_MAX;
					new_A_min1 = g->min0 -1;
					new_A_max1 = INT_MAX;

					new_B_min0 = 0;
					new_B_max0 = INT_MAX;
					new_B_min1 = g->min0 -1;
					new_B_max1 = INT_MAX;
				}
			}
			else{
				//output unknown
				new_A_min0 = 0;
				new_A_max0 = INT_MAX;
				new_A_min1 = g->min0 -1;
				new_A_max1 = INT_MAX;

				new_B_min0 = 0;
				new_B_max0 = INT_MAX;
				new_B_min1 = g->min0 -1;
				new_B_max1 = INT_MAX;
			}

			break;

		default:
			cout << "ERROR! What type of node is this? " << g->property << endl;
			break;
	}

	A_changed = Apply(g->input_A, new_A_min0, new_A_max0, new_A_min1, new_A_max1);

	B_changed = false;
	if(g->input_B != NULL)
		B_changed = Apply(g->input_B, new_B_min0, new_B_max0, new_B_min1, new_B_max1);

	if(isConflicted(g->input_A))	return false; //conflicted detected

	if(g->input_B != NULL){
		if(isConflicted(g->input_B))	return false;
	}

	return true;
}

int Graph::CountKnownInputs(){
	int known = 0;
	cout << "Already determined inputs: ";
	for(map<string, Node *>::iterator it = inputs.begin(); it != inputs.end(); it++){
		if(isOne(it->second)){
			cout << it->second->gate_name << "(1) ";
			known++;
		}
		else if(isZero(it->second)){
			cout << it->second->gate_name << "(0) ";
			known++;
		}
	}
	cout << endl;

	return known;
}

int Graph::CountRelevantInputs(Node *g, set<string> &PI){  //Start with a primary output
	if(g->input_A == NULL && g->input_B == NULL){ //is a primary input
		PI.insert(g->gate_name);
	}

	if(g->input_A != NULL)
		CountRelevantInputs(g->input_A, PI);
	if(g->input_B != NULL)
		CountRelevantInputs(g->input_B, PI);

	return PI.size();
}



void Graph::Implication()
{
	for(int i=0; i<paths.size(); i++){
		//這個地方就是分別將每個path對應r/f去檢查是否為false path
		//只能確認部份false path，剩餘當中尚有可能存在false path
		//我先測試 falling inputs，length >=4(slack<7)
		if(paths[i]->path_gates.size() < 6) continue;

		if(Verify_True_Path(paths[i], 0 )){
			set<string> s;
			cout << "Path" << i+1 <<" (f) is still true after Implication." << endl;
			cout << "Number of already determined inputs: " << CountKnownInputs() << endl;
			cout << "Number of relevant inputs " << CountRelevantInputs(paths[i]->path_gates.back(), s) << endl<<endl;
			TruePathsAfterImplication.push_back(paths[i]);
		}
		else{
			cout << "Path" << i+1 << " (f) is a false path." << endl << endl;
			FalsePathsAfterImplication.push_back(paths[i]);
		}
	}

	for(int i=0; i<paths.size(); i++){
		//這個地方就是分別將每個path對應r/f去檢查是否為false path
		//只能確認部份false path，剩餘當中尚有可能存在false path
		//我先測試 falling inputs，length >=4(slack<7)
		if(paths[i]->path_gates.size() < 6) continue;

		if(Verify_True_Path(paths[i], 1 )){
			set<string> t;
			cout << "Path" << i+1 <<" (r) is still true after Implication." << endl;
			cout << "Number of already determined inputs: " << CountKnownInputs() << endl;
			cout << "Number of relevant inputs " << CountRelevantInputs(paths[i]->path_gates.back(), t) << endl<<endl;
			TruePathsAfterImplication.push_back(paths[i]);
		}
		else{
			cout << "Path" << i+1 << " (f) is a false path." << endl << endl;
			FalsePathsAfterImplication.push_back(paths[i]);
		}
	}
}

bool Graph::Justification(){
	vector<Node*> undeterminedPI;
	for(map<string, Node *>::iterator it = inputs.begin(); it != inputs.end(); it++){
		if(isOne(it->second)){
			continue;
		}
		else if(isZero(it->second)){
			continue;
		}
		else{
			undeterminedPI.push_back(it->second);
		}
	}

	if(undeterminedPI.empty()){
		//SUCCESS print
		//cout << "All PIs determined already. True path!" << endl;
		//Display_All_Stable_Interval();
		return true;
	}

	if( !GuessPI(0, undeterminedPI) ){
		//cout << "Cannot be justified. False path." << endl;
    return false;
	}
  else{
    return true;
  }
}

bool Graph::GuessPI(int i, vector<Node*> &undeterminedPI){ //return false if conflict
	Table t;
	t.Record(*this);
	//Display_All_Stable_Interval();

	if(i > undeterminedPI.size()-1){
		//cout << "Successfully justified. True path!" << endl;
		//Display_All_Stable_Interval();
		return true;
	}

    Node *g = undeterminedPI[i];

	if(! isUnknown(g) ){
		if(GuessPI(i+1, undeterminedPI)){
			return true;
		}
		else{
		    //cout << g->gate_name << " has known value already but cannot place the next PI." << endl;
		    return false;
		}
	}

    //cout << "Assign 1 to " << g->gate_name << endl;

	Apply(g, INT_MAX, 0, 0, 0);
	if( Update_Stable_Time (g) ){
		if(GuessPI(i+1, undeterminedPI)){
			return true;
		}
	    else{
	        //cout << "Assigned 1 to " << g->gate_name << " but cannot place the next PI." << endl;
	    }
	}
	else{
		//restore all stable time
    	//cout << "Fail after assign 1 to " << g->gate_name << endl;
	}

	Restore_Stable_Time(t);
    //Display_All_Stable_Interval();


    //cout << "Assign 0 to " << g->gate_name << endl;
	Apply(g, 0, 0, INT_MAX, 0);
	if( Update_Stable_Time (g) ){
		if(GuessPI(i+1, undeterminedPI)){
			return true;
		}
   		else{
     		//cout << "Assigned 0 to " << g->gate_name << " but cannot place the next PI." << endl;
   		}
	}
	else{
    	//cout << "Fail after assign 0 to " << g->gate_name << endl;
	}
	//restore all stable time
    Restore_Stable_Time(t);

	return false;
}

void Graph::Restore_Stable_Time(Table &s){
	Node *g;
	for(map<Node *, tuple<int, int, int, int> >::iterator it = s.FullTable.begin() ; it != s.FullTable.end() ; ++it ){
	    g = it->first;
	    g->min0 = get<0>(it->second);
	    g->max0 = get<1>(it->second);
	    g->min1 = get<2>(it->second);
	    g->max1 = get<3>(it->second);
	}

}


void Graph::Display_Implication_Results(){
	cout << "True Paths after Implication:" << endl;
	for(int i=0; i<TruePathsAfterImplication.size(); i++){
        cout<<"True path"<<(i+1)<<" (delay="<<TruePathsAfterImplication[i]->path_gates.size()-2<<") : "<<endl;
        for(int j=0; j<(TruePathsAfterImplication[i]->path_gates).size(); j++){
            cout<<TruePathsAfterImplication[i]->path_gates[j]->gate_name<<" -> ";
        }
        cout<<"end of true path"<<endl;
    }

    //cout << endl;
    cout << "False Paths after Implication:" << endl;
    for(int i=0; i< FalsePathsAfterImplication.size(); i++){
        cout<<"False path"<<(i+1)<<" (delay="<< FalsePathsAfterImplication[i]->path_gates.size()-2<<") : "<<endl;
        for(int j=0; j<( FalsePathsAfterImplication[i]->path_gates).size(); j++){
            cout<< FalsePathsAfterImplication[i]->path_gates[j]->gate_name<<" -> ";
        }
        cout<<"end of false path"<<endl;
    }

    cout << "# of true paths after Implication: " << TruePathsAfterImplication.size() << endl;
 	cout << "# of false paths after Implication: " << FalsePathsAfterImplication.size() << endl;

}

void Graph::Display_All_Stable_Interval(){
	for(map<string, Node *>::iterator it = inputs.begin() ; it != inputs.end() ; it++ ){
	    cout<<it->second->gate_name<<" ";
	    cout << it->second->min0 <<" " << it->second->max0 << " "
          << it->second->min1 << " " << it->second->max1 << endl;
	}

	for(map<string, Node *>::iterator it = outputs.begin() ; it != outputs.end() ; it++ ){
		cout<<it->second->gate_name<<" ";
	    cout << it->second->min0 <<" " << it->second->max0 << " "
          << it->second->min1 << " " << it->second->max1 << endl;
	}

	for(map<string, Node *>::iterator it = gates.begin() ; it != gates.end() ; it++ ){
		cout<<it->second->gate_name<<" ";
	    cout << it->second->min0 <<" " << it->second->max0 << " "
          << it->second->min1 << " " << it->second->max1 << endl;
	}

}

void Graph::FindTruePaths(){

	for(int i=0; i<paths.size(); i++){
    
    if(paths[i]->isFalse){
      numberOfFalsePaths_f++;
      paths[i]->isFalse = false;
      //cout << "USEFUL!" << endl;
      continue;
    }

		if( Verify_True_Path(paths[i], false) ){
      //fail_index = -1;
			//set<string> s;
			//cout << "Path" << i+1 <<" (f) passes Implication." << endl;
			//cout << "Number of already determined inputs: " << CountKnownInputs() << endl;
    		if( Justification() ){
           OutputPath(*this, paths[i]);
           numberOfTruePaths_f++;
        }
        else{
           numberOfFalsePaths_f++;
        }
			//cout << "Number of relevant inputs " << CountRelevantInputs(paths[i]->path_gates.back(), s) << endl<<endl;
			//TruePathsAfterImplication.push_back(paths[i]);
		}
		else{
			//cout << "Path" << i+1 << " (f) fails Implication." << endl << endl;
			//FalsePathsAfterImplication.push_back(paths[i]);
      
      int j=i+1;
      while( j<paths.size() && (paths[j]->prvs_longest_same_gate_index) >= fail_index ){
        paths[j]->isFalse = true;
        j++;
      }     
			numberOfFalsePaths_f++;
		}
	}
 
  for(int i=0; i<paths.size(); i++){
    
    if(paths[i]->isFalse){
      numberOfFalsePaths_r++;
      //cout << "USEFUL!" << endl;
      continue;
    }
  
  	if( Verify_True_Path(paths[i], true) ){
       //fail_index = -1;
  		//set<string> t;
  		//cout << "Path" << i+1 <<" (r) passes Implication." << endl;
  		//cout << "Number of already determined inputs: " << CountKnownInputs() << endl;
    		if( Justification() ){
          OutputPath(*this, paths[i]);
          numberOfTruePaths_r++;
        }
        else{
          numberOfFalsePaths_r++;
        }
  		//cout << "Number of relevant inputs " << CountRelevantInputs(paths[i]->path_gates.back(), t) << endl<<endl;
  		//TruePathsAfterImplication.push_back(paths[i]);
  	}
  	else{
  		//cout << "Path" << i+1 << " (r) fails Implication." << endl << endl;
  		//FalsePathsAfterImplication.push_back(paths[i]);
      
      int j=i+1;
      while(  j<paths.size() && (paths[j]->prvs_longest_same_gate_index) >= fail_index){
        paths[j]->isFalse = true;
        j++;
      }     
  		numberOfFalsePaths_r++;
  	}
  }
}

void Graph::FindTruePaths_r1(){

  for(int i=0; i<paths.size()/2; i++){
    
    if(paths[i]->isFalse){
      numberOfFalsePaths_r++;
      paths[i]->isFalse = false;
      //cout << "USEFUL!" << endl;
      continue;
    }
  
  	if( Verify_True_Path(paths[i], true) ){
       //fail_index = -1;
  		//set<string> t;
  		//cout << "Path" << i+1 <<" (r) passes Implication." << endl;
  		//cout << "Number of already determined inputs: " << CountKnownInputs() << endl;
    		if( Justification() ){
          OutputPath(*this, paths[i]);
          numberOfTruePaths_r++;
        }
        else{
          numberOfFalsePaths_r++;
        }
  		//cout << "Number of relevant inputs " << CountRelevantInputs(paths[i]->path_gates.back(), t) << endl<<endl;
  		//TruePathsAfterImplication.push_back(paths[i]);
  	}
  	else{
  		//cout << "Path" << i+1 << " (r) fails Implication." << endl << endl;
  		//FalsePathsAfterImplication.push_back(paths[i]);
      
      int j=i+1;
      while(  j<paths.size() && (paths[j]->prvs_longest_same_gate_index) >= fail_index){
        paths[j]->isFalse = true;
        j++;
      }     
  		numberOfFalsePaths_r++;
  	}
  }
}

void Graph::FindTruePaths_r2(){

  for(int i=paths.size()/2; i<paths.size(); i++){
    
    if(paths[i]->isFalse){
      numberOfFalsePaths_r++;
      paths[i]->isFalse = false;
      //cout << "USEFUL!" << endl;
      continue;
    }
  
  	if( Verify_True_Path(paths[i], true) ){
       //fail_index = -1;
  		//set<string> t;
  		//cout << "Path" << i+1 <<" (r) passes Implication." << endl;
  		//cout << "Number of already determined inputs: " << CountKnownInputs() << endl;
    		if( Justification() ){
          OutputPath(*this, paths[i]);
          numberOfTruePaths_r++;
        }
        else{
          numberOfFalsePaths_r++;
        }
  		//cout << "Number of relevant inputs " << CountRelevantInputs(paths[i]->path_gates.back(), t) << endl<<endl;
  		//TruePathsAfterImplication.push_back(paths[i]);
  	}
  	else{
  		//cout << "Path" << i+1 << " (r) fails Implication." << endl << endl;
  		//FalsePathsAfterImplication.push_back(paths[i]);
      
      int j=i+1;
      while(  j<paths.size() && (paths[j]->prvs_longest_same_gate_index) >= fail_index){
        paths[j]->isFalse = true;
        j++;
      }     
  		numberOfFalsePaths_r++;
  	}
  }
}

void Graph::FindTruePaths_f1(){

	for(int i=0; i<paths.size()/2; i++){
    
    if(paths[i]->isFalse){
      numberOfFalsePaths_f++;
      paths[i]->isFalse = false;
      //cout << "USEFUL!" << endl;
      continue;
    }

		if( Verify_True_Path(paths[i], false) ){
      //fail_index = -1;
			//set<string> s;
			//cout << "Path" << i+1 <<" (f) passes Implication." << endl;
			//cout << "Number of already determined inputs: " << CountKnownInputs() << endl;
    		if( Justification() ){
           OutputPath(*this, paths[i]);
           numberOfTruePaths_f++;
        }
        else{
           numberOfFalsePaths_f++;
        }
			//cout << "Number of relevant inputs " << CountRelevantInputs(paths[i]->path_gates.back(), s) << endl<<endl;
			//TruePathsAfterImplication.push_back(paths[i]);
		}
		else{
			//cout << "Path" << i+1 << " (f) fails Implication." << endl << endl;
			//FalsePathsAfterImplication.push_back(paths[i]);
      
      int j=i+1;
      while( j<paths.size() && (paths[j]->prvs_longest_same_gate_index) >= fail_index ){
        paths[j]->isFalse = true;
        j++;
      }     
			numberOfFalsePaths_f++;
		}
	}
}

void Graph::FindTruePaths_f2(){

	for(int i=paths.size()/2; i<paths.size(); i++){
    
    if(paths[i]->isFalse){
      numberOfFalsePaths_f++;
      paths[i]->isFalse = false;
      //cout << "USEFUL!" << endl;
      continue;
    }

		if( Verify_True_Path(paths[i], false) ){
      //fail_index = -1;
			//set<string> s;
			//cout << "Path" << i+1 <<" (f) passes Implication." << endl;
			//cout << "Number of already determined inputs: " << CountKnownInputs() << endl;
    		if( Justification() ){
           OutputPath(*this, paths[i]);
           numberOfTruePaths_f++;
        }
        else{
           numberOfFalsePaths_f++;
        }
			//cout << "Number of relevant inputs " << CountRelevantInputs(paths[i]->path_gates.back(), s) << endl<<endl;
			//TruePathsAfterImplication.push_back(paths[i]);
		}
		else{
			//cout << "Path" << i+1 << " (f) fails Implication." << endl << endl;
			//FalsePathsAfterImplication.push_back(paths[i]);
      
      int j=i+1;
      while( j<paths.size() && (paths[j]->prvs_longest_same_gate_index) >= fail_index ){
        paths[j]->isFalse = true;
        j++;
      }     
			numberOfFalsePaths_f++;
		}
	}
}