#include "FinalGraph.h"
void StartOutputFile(string);
void EndOutputFile();
extern int final_path_counter;


int main(int argc, char* argv[]) {
    if(argc!=4) cout<<"Format: ./cadb105 [case_name] [timing_constraint] [slack_constraint]"<<endl;

    string case_name = argv[1];
    int timing = atoi(argv[2]);
    int slack = atoi(argv[3]);
    //cout << "timing constraint: "<< timing <<endl;
    //cout<<"slack : "<< slack << endl;

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
    
   	//cout << endl;
    //cout << "# of total true paths: " << final_path_counter << endl;
	  //cout <<"# of g true paths: " << G.numberOfTruePaths_r + G.numberOfTruePaths_f << endl;
	  //cout <<"# of g false paths: " << G.numberOfFalsePaths_r + G.numberOfFalsePaths_f << endl;
    
    }else{
    
    //Graph G(case_name, timing, slack);
    //Graph H(case_name, timing, slack);

    //G.BuildGraph(name2);
    //H.BuildGraph(name2);
    
    //G.ConnectGates();
    //H.ConnectGates();
    
    //G.FindAllPaths();
    //H.FindAllPaths();
    //G.DisplayAllPaths();

    //StartOutputFile(G);
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
    /*
    thread Threada([&](){G.FindAllPaths(); });
    thread Threadb([&](){H.FindAllPaths(); });
    thread Threadc([&](){I.FindAllPaths(); });   
    thread Threadd([&](){J.FindAllPaths();});
    
    Threada.join();
    Threadb.join();      
    Threadc.join();
    Threadd.join();*/
    
    //G.FindTruePaths_r();
    //H.FindTruePaths_f();
    thread Thread1([&](){ G.FindTruePaths_r1(); });
    thread Thread2([&](){ H.FindTruePaths_f1();});
    thread Thread3([&](){ I.FindTruePaths_r2(); });   
    thread Thread4([&](){ J.FindTruePaths_f2();});
    
    Thread1.join();
    Thread2.join();      
    Thread3.join();
    Thread4.join();
    
    EndOutputFile();

   	/*cout << endl;
    cout << "# of total true paths: " << final_path_counter << endl;
	  cout <<"# of g true paths: " << G.numberOfTruePaths_r + G.numberOfTruePaths_f << endl;
	  cout <<"# of g false paths: " << G.numberOfFalsePaths_r + G.numberOfFalsePaths_f << endl;    
    cout <<"# of h true paths: " << H.numberOfTruePaths_r + H.numberOfTruePaths_f << endl;
	  cout <<"# of h false paths: " << H.numberOfFalsePaths_r + H.numberOfFalsePaths_f << endl;
    cout <<"# of i true paths: " << I.numberOfTruePaths_r + I.numberOfTruePaths_f << endl;
	  cout <<"# of i false paths: " << I.numberOfFalsePaths_r + I.numberOfFalsePaths_f << endl; 
    cout <<"# of j true paths: " << J.numberOfTruePaths_r + J.numberOfTruePaths_f << endl;
	  cout <<"# of j false paths: " << J.numberOfFalsePaths_r + J.numberOfFalsePaths_f << endl;    */
     
    }

	return 0;
}
