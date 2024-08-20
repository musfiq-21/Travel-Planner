#include <bits/stdc++.h>
using namespace std;
#define inf -10000
//vector<vector<pair<int, pair<int, int>>>> v(5);        //city idx, (cost, travel time)

vector<vector<pair<int, pair<int, int>>>> readData(){
    vector<vector<pair<int, pair<int, int>>>> list(10);

    ifstream fin("input.txt");
    ofstream fout("citymap.txt");

    string data;
    
    //array of vector of structure pointers, each index represent a unique city. the
    
    map<string, int> mp;
    string src, dest;
    while(fin>>src>>dest){

        int cost;
        float travelTime;
        
        //adding the cities on hashmap, giving them a unique index
        if(mp.find(src) == mp.end()){
            mp[src] = mp.size();
            fout<<src<<" "<<mp[src]<<"\n";
        }
        if(mp.find(dest) == mp.end()){
            mp[dest] = mp.size();
            fout<<dest<<" "<<mp[dest]<<"\n";
        }

        fin>>cost>>travelTime;
        
        if(mp[src]==list.size()){
            vector<pair<int, pair<int, int>>> temp;
            list.push_back(temp);
        }
        
        list[mp[src]].push_back({mp[dest], {cost, travelTime}});
     
    }

    return list;
}

vector<int> djk(vector< vector<pair<int, pair<int, int>>>> *v, int idx, int priority){  //prior 1 for cost, 2 for time

    vector<bool> visited(v->size());
    vector<int> dist(v->size());

    for(int i=0; i<dist.size(); i++){
        dist[i]= inf;
        visited[idx] = false;
    }

    priority_queue<pair<int, int>> pq;  //priority(time/cost(neg value for min heap), city idx)
    
    pq.push({0, idx});
    dist[idx] = 0;
    
    while(!pq.empty()){
        
        visited[pq.top().second] = true;
//v->[pq.top().second]
        for(auto ngbr: v->at(pq.top().second)){
            if(visited[ngbr.first])   continue;

            int newDist;
            if(priority==1){
                newDist = -ngbr.second.first + pq.top().first;  //based in cost
            }
            else if(priority == 2){
                newDist = -ngbr.second.second + pq.top().first;     //based on traveltime
            }

            if(newDist > dist[ngbr.first]){     //sign is opposite bc we're comparing neg val
                dist[ngbr.first] = newDist;
                pq.push({newDist, ngbr.first});
                
            }
        }
        
        pq.pop();
        
    }

    return dist;
}


int shortestPath(vector< vector<pair<int, pair<int, int>>>> *v, string src, string end, string pr){
    
    vector<int> path;
    ifstream fin("citymap.txt");
    int s=-1, e=-1;

    while(s==-1 or e==-1){
        string city;
        int idx;
        fin>>city>>idx;

        if(city == src){
            s=idx;
        }
        if(city == end){
            e=idx;
        }
        
    }

    if(pr=="cheapest")
        path = djk(v, s, 1);
    else if(pr=="fastest")
        path = djk(v, s, 2);

    return -path[e];
}
