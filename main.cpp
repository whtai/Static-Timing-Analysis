#include "FinalGraph.h"
void StartOutputFile(string);
void EndOutputFile();
extern int final_path_counter;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Format: ./cadb105 [case_name] [timing_constraint] [slack_constraint]" << endl;
        return 1;
    }
    string case_name = argv[1];
    int timing = atoi(argv[2]);
    int slack = atoi(argv[3]);

    string name2 = case_name + "/input/" + case_name;
    
    StartOutputFile(case_name);
    
    if(case_name[4] == '2' || case_name[4] == '3' || case_name[4] == '4'){
	    Graph G(case_name, timing, slack);
	    G.BuildGraph(name2);
	    G.ConnectGates();
	    G.FindAllPaths();

	    G.FindTruePaths_f1();
	    G.FindTruePaths_f2();
	    G.FindTruePaths_r1();
	    G.FindTruePaths_r2();

	    EndOutputFile();   
    }else{
        Graph G(case_name, timing, slack);
        Graph H(case_name, timing, slack);
        Graph I(case_name, timing, slack);
        Graph J(case_name, timing, slack);

        G.BuildGraph(name2);
        H.BuildGraph(name2);
        I.BuildGraph(name2);
        J.BuildGraph(name2);

        G.ConnectGates();
        H.ConnectGates();
        I.ConnectGates();
        J.ConnectGates();

        G.FindAllPaths();
        H.FindAllPaths();
        I.FindAllPaths();
        J.FindAllPaths();   

        thread Thread1([&](){ G.FindTruePaths_r1(); });
        thread Thread2([&](){ H.FindTruePaths_f1();});
        thread Thread3([&](){ I.FindTruePaths_r2(); });   
        thread Thread4([&](){ J.FindTruePaths_f2();});

        Thread1.join();
        Thread2.join();      
        Thread3.join();
        Thread4.join();

        EndOutputFile(); 
    }
	return 0;
}
