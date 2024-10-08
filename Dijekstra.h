#include<iostream>
#include<vector>
#include<cstdlib>
#include<math.h>
#include<string>
#include<climits>
using namespace std;
class ShortestPath{
	public:
	vector< vector<int> > paths; //added this to save paths, using two loops, i to n, and j = n to 0, to print paths starting from 0
	
	int findMinimumVertex(vector<int>& distance, bool*& vis, const int& n) {
	    int ans = -1;
	    for (int i = 0; i < n; ++i) {
	        if (!vis[i] && (ans == -1 || distance[i] < distance[ans])) {
	            ans = i;
	        }
	    }
	    return ans;
	}
	void dijkstra(vector< vector<int> >& graph,vector<int>& distance, const int& n, int s) {
	    
	    bool* vis = new bool[n];
	    vector<int> parent(n, 0);
	    for (int i = 0; i < n; ++i) {
	        distance[i] = INT_MAX;
	        vis[i] = 0;
	    }
	
	    distance[s] = 0;
	    parent[s] = -1;  
	
	    for (int i = 0; i < n - 1; ++i) {
	        int minimumVertex = findMinimumVertex(distance, vis, n);
	        vis[minimumVertex] = 1;
	        for (int j = 0; j < n; ++j) {
	            if (graph[minimumVertex][j] && !vis[j]) {
	                int newDistance = distance[minimumVertex] + graph[minimumVertex][j];
	                if (newDistance < distance[j]) {
	                    distance[j] = newDistance;
	                    parent[j] = minimumVertex; 
	                }
	            }
	        }
	    }
//	    for (int i = 0; i < n; ++i) {
//	        cout << i << " " << distance[i] << " \n";
//	    }
	    for (int i = 0; i < n; ++i) {
	        // cout << "Path to " << i << ": ";
	        int current = i;
	        vector<int> temp;
	        while (current != -1) {
	            temp.push_back(current);
	            current = parent[current];
	        }
	        paths.push_back(temp);
	    }
	
	    delete[] vis;
	    vis = NULL;
	}
};
void Setup(int** edges){
	/* Police */	edges[0][4]=2;/*Shah Latif*/ edges[0][1]=8;/*Market*/	edges[0][2]=5;/*Garden*/    edges[0][22]=10;/*Gulshan*/ 
	/* Market */	edges[1][2]=2;/*Garden*/     edges[1][0]=4;/*Police*/   edges[1][9]=11;/*Quidabad*/
	/* Garden */	edges[2][0]=3;/*Police*/  	 edges[2][1]=2;/*Market*/	edges[2][9]=6;/*Quidabad*/
	/* Hospital */	edges[3][2]=6;/*Garden*/	 edges[3][0]=7;/*Police*/  	edges[3][9]=3;/*Quidabad*/
	/* Shah Latif */edges[4][0]=2;/*Police*/     edges[4][22]=11;/*Gulshan*/edges[4][5]=2;  edges[4][6]=2;  edges[4][7]=1;  edges[4][8]=1;
	/* House-1 */	edges[5][4]=2;
	/* House-2 */	edges[6][4]=2;
	/* House-3 */	edges[7][4]=1;
	/* House-4 */	edges[8][4]=1;
	/* Quidabad */  edges[9][3]=3;/*Hospital*/ edges[9][2]=6;/*Garden*/  edges[9][0]=11;/*Police*/
	edges[9][10] = 1; edges[9][11] = 1;  edges[9][12] = 2; edges[9][13] = 2;  edges[9][14] = 3;  edges[9][15] = 3;  edges[9][16] = 4;  edges[9][17] = 4; edges[9][18] = 5; edges[9][19] = 5; edges[9][20] = 6; edges[9][21] = 6; 
	for (int i = 10; i < 22; i++) {
    	edges[i][9] = edges[9][i];
  	}
	/* From Gulshan to: */	edges[22][3]=4;/* Hospital */
	edges[22][23] = 5; edges[22][24] = 5; edges[22][25] = 4; edges[22][26] = 4; edges[22][27] = 3;
    edges[22][28] = 3; edges[22][29] = 2; edges[22][30] = 2; edges[22][31] = 1; edges[22][32] = 1;
    edges[22][33] = 1; edges[22][34] = 1; edges[22][35] = 1; edges[22][36] = 2; edges[22][37] = 2;
    edges[22][38] = 3; edges[22][39] = 3; edges[22][40] = 4; edges[22][41] = 4; edges[22][42] = 5;
    edges[22][43] = 5;
	for (int i = 23; i <= 43; i++) {
        edges[i][22] = edges[22][i];
    }
}


int ApplyDijekstra(int Start,int end,string& CompletePath){
	string mystringpath[44] = {
        "Police", "market", "garden", "hospital", "Bahadurabad",
        "ZBA", "YBB", "XBC", "WBD", "Quidabad",
        "1QA", "1QB", "2QC", "2QD", "1QE",
        "1QF", "2QG", "2QH", "1QI", "1QJ",
        "2QK", "2QL", "gulshan", "1GA", "1GB",
        "2GC", "2GD", "1GE", "1GF", "2GG",
        "2GH", "1GI", "1GJ", "2GK", "2GL",
        "1GM", "1GN", "2GO", "2GP", "1GQ",
        "1GR", "2GS", "2GT", "1GU"
    };
    int n = 44;

    int **hardcodedEdges=new int*[44];
    for(int i=0;i<44;i++){
    	hardcodedEdges[i]=new int[44]();
	}
	
	ShortestPath obj;
	Setup(hardcodedEdges);
    vector< vector<int> > graph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            graph[i][j] = hardcodedEdges[i][j];
        }
    }
    vector<int> distance(n, 0);
    obj.dijkstra(graph, distance, n, Start);  // Calculate All Path Here
	//cout << "\n\n";
	int Sum=0;
	//cout<<distance[end]<<endl;
	for(int j = obj.paths[end].size() - 1; j >= 0; --j){
        //cout << mystringpath[ obj.paths[end][j] ] << "-> ";
        CompletePath+=mystringpath[ obj.paths[end][j] ];
        CompletePath+=" -> ";
	}
	cout<<endl<<endl<<CompletePath<<endl;
    return distance[end];
}

