// azaye group in tamrin : Mona Radad , Zeinab Ghane
// algorithm piadesazi shode : floyd warshall


#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <string>
#include <thread>
#include <chrono>

#define INF 9999

using namespace std;

const int cost_value_range = 10;
const double probability = 0.5;

class Node{
public:
    int id;
    map<int, int> nodesCosts; //Holds the distance (cost) to each node

    Node(int id, vector<Node*>& nodesList){
        this->id = id;
        nodesList.push_back(this);
        srand(time(0));

        for(int i = 0; i < nodesList.size(); i++){
            int cost = rand() % cost_value_range + 1;
            if(i == this->id)
                nodesList.at(this->id)->nodesCosts[i] = 0;
            else if(cost <= cost_value_range * probability){
                nodesList.at(this->id)->nodesCosts[i] = cost;
                nodesList.at(i)->nodesCosts[this->id] = cost;
            }
            else{
                nodesList.at(this->id)->nodesCosts[i] = INF;
                nodesList.at(i)->nodesCosts[this->id] = INF;
            }
        }
    }
};



void cost_minimizer(vector<Node*>& nodesList, int id){
    // It's your turn!
    int v_size = nodesList.size();
    for(int k = v_size-1; k >= 0; k--){  
        for(int i = v_size-1; i >= id; i--){
            for(int j = v_size-1; j >= 0; j--){
                if(nodesList[i]->nodesCosts[k] != INF && nodesList[k]->nodesCosts[j] != INF){
                    if (nodesList[i]->nodesCosts[k] + nodesList[k]->nodesCosts[j] < nodesList[i]->nodesCosts[j]){
                        nodesList[i]->nodesCosts[j] = nodesList[i]->nodesCosts[k] + nodesList[k]->nodesCosts[j];
                        nodesList[j]->nodesCosts[i] = nodesList[i]->nodesCosts[k] + nodesList[k]->nodesCosts[j];
                    }
                }
            }  
        }  
    }  
}


void print_costs(vector<Node*>& nodesList){
    cout<<"\033[1m\033[37m"<<"=============================================\n";
    for (int i = 0; i < nodesList.size(); i++){
        for(int j = 0; j < nodesList.size(); j++){

            string cost;
            if (nodesList[i]->nodesCosts[j] != INF)
                cost = to_string(nodesList[i]->nodesCosts[j]);
            else
                cost  = "\u221E";

            cout<<cost<<"    ";
        }
        cout<<endl;
    }
    cout<<"\033[37m";
}


vector<Node*> nodesList; //Holds all of the nodes available in the graph
int main(){
    cout<<"Enter the initial number of nodes: ";
    int n;
    cin>>n;

    int id;
    for(id = 0; id < n; id++)
        new Node(id, nodesList);

    print_costs(nodesList);
    while(true){ //Each 5 seconds a new node is added to graph
        this_thread::sleep_for(chrono::milliseconds(5000));
        cout<<"\033[1m\033[32m"<<"\nNext Round!"<<"\033[37m"<<endl;

        Node* node = new Node(id++, nodesList);
        if(id-2 == n)
            cost_minimizer(nodesList, 0);
        else
            cost_minimizer(nodesList, id-1);

        print_costs(nodesList);
    }
    return 0;
}
