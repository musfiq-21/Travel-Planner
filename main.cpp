#include <bits/stdc++.h>
#include <func.h>

using namespace std;



int main(){
    
    vector<vector<pair<int, pair<int, int>>>> list = readData();
    
    string src, dest, priority;

    cout<<"==Welcome to skibidi travel planner==\n\nWhere will you board on?\n";
    cin>>src;

    cout<<"Where do you wish to go?\n";
    cin>>dest;

    cout<<"We can find the fastest or cheapest route for you. Let us help you\nWhat's your priority(fastest, cheapest)?";
    cin>>priority;

    float travel_cost = shortestPath(&list, src, dest, priority);

    if(priority == "fastest"){
        cout<<"The fastest route will cost you TK"<<travel_cost<<"\n";
    }
    else if(priority== "cheapest"){
        cout<<"The cheapest route will cost you TK"<<travel_cost<<"\n";
    }
    else{
        cout<<"Wrong priority\n";
        exit(0);
    }
}