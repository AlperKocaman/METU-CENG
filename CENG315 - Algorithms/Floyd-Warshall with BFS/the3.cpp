#include "the3.h"

// You  can define extra functions here

void ApplyFloydWarshall(int n, int**& modifiedEdgeList, double*& scores, std::vector<int> &vertexSet){

    int i,j,k, ikEnrty, kjEntry;
    double ratio=0;

    for(k=0 ; k<n ; ++k){

        for(i=0 ; i<n ; ++i){

            if(i == k){
                continue;
            }
            ikEnrty = (k>i)?modifiedEdgeList[k][i]:modifiedEdgeList[i][k];
            if(!ikEnrty){
                continue;
            }
            for(j=0 ; j<i ; ++j){
                if(j == k){
                    continue;
                }
                kjEntry = (k>j)?modifiedEdgeList[k][j]:modifiedEdgeList[j][k];
                if(!kjEntry){
                    continue;
                }
                if((!modifiedEdgeList[i][j]) || (ikEnrty + kjEntry < modifiedEdgeList[i][j])){
                    modifiedEdgeList[i][j] = ikEnrty + kjEntry;
                }
            }
        }
    }

    for(k=0; k<n ; ++k){

        for(i=0 ; i<n ; ++i){

            if(i == k) {
                continue;
            }
            ikEnrty = (k>i)?modifiedEdgeList[k][i]:modifiedEdgeList[i][k];
            for(j=0 ; j<=i ; ++j){

                if(j < k){
                    if(j == i) {
                        ratio += (double) (ikEnrty + modifiedEdgeList[k][j]) / (modifiedEdgeList[i][j]);
                    }
                    else{
                        ratio += 2*((double)(ikEnrty + modifiedEdgeList[k][j]) / (modifiedEdgeList[i][j]));
                    }
                }
                else if(j > k){
                    if(j == i) {
                        ratio += (double) (ikEnrty + modifiedEdgeList[j][k]) / (modifiedEdgeList[i][j]);
                    }
                    else{
                        ratio += 2*((double)(ikEnrty + modifiedEdgeList[j][k]) / (modifiedEdgeList[i][j]));
                    }
                }
            }
        }
        scores[vertexSet[k]] = ratio;
        ratio = 0;
    }
}

void InsertionSort(int* arr, int n) {
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// INPUT :
//            n         : number of nodes in the graph
//            edgeList  : edges in the graph
//            scores    : importance scores
// return value : 
//                 number of disconnected components
int Important (int n, int**& edgeList, double*& scores)
{ 
    if(!n){
        return 0;
    }
    int i, j, k, index=0, partition=0;
    int unvisitedVertices = n;
    bool visited[n] = {false};

    int** modifiedEdgeList = new int*[n];
    for(i=0; i<n ; ++i){
        modifiedEdgeList[i] = new int[i+1];
        for(j=0; j<=i ; ++j){
            modifiedEdgeList[i][j] = 0;
        }
    }

    i=0;

    while (unvisitedVertices){

        if(visited[index]){
            index++;
            continue;
        }

        i = index;
        index++;
        visited[i] = true;
        unvisitedVertices --;

        std::vector<int> vertexSet;
        vertexSet.push_back(i);

        for(j=0; j<vertexSet.size() ; ++j){
            i= vertexSet[j];
            for(k=0 ; k<n ; ++k){
                if(edgeList[i][k] && !visited[k]){
                        visited[k] = true;
                        vertexSet.push_back(k);
                        unvisitedVertices--;
                }
            }
        }

        InsertionSort(&vertexSet[0], vertexSet.size());

        for(j=0; j<vertexSet.size() ; ++j){
            for(k=0 ; k<=j ; ++k){
                if(j == k) {
                    modifiedEdgeList[j][k] = 1;
                }
                else {
                    modifiedEdgeList[j][k] = edgeList[vertexSet[j]][vertexSet[k]];
                }
            }
        }

        ApplyFloydWarshall(vertexSet.size(), modifiedEdgeList, scores, vertexSet);
        partition++;

    }
    return partition;
}
