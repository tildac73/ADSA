#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int> > parseIntegerMatrix(const string &input) {
    vector<vector<int> > matrix;
    stringstream ss(input);
    string row;

    while (getline(ss, row, ',')) {
        vector<int> matrixRow;
        for (char c : row) {
            matrixRow.push_back(c - '0');  
        }
        matrix.push_back(matrixRow);
    }
    return matrix;
}

vector<vector<char> > parseCharMatrix(const string &input) {
    vector<vector<char> > matrix;
    stringstream ss(input);
    string row;

    while (getline(ss, row, ',')) {
        vector<char> matrixRow(row.begin(), row.end());
        matrix.push_back(matrixRow);
    }
    return matrix;
}

void printIntegerMatrix(const vector<vector<int> > &matrix) {
    for (const auto &row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void printCharMatrix(const vector<vector<char> > &matrix) {
    for (const auto &row : matrix) {
        for (char val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

class UnionFind {
    private:
        vector<int> parent;
        vector<int> seniority;
    public:
        UnionFind(int n) {
            parent.resize(n);
            seniority.resize(n, 0);
            for (int i = 0; i < n; ++i) {
                parent[i] = i;  
            }
        }

        int find(int i){
            if (parent[i]==i){
                return i;
            }else{
                parent[i] = find(parent[i]);
                return parent[i];
            }
        }

        void link(int i, int j){
            if (seniority[i] < seniority[j]){
                parent[i] = j;
            }else{
                parent[j] = i;
                if (seniority[i]==seniority[j]){
                    seniority[i]++;
                }
            }
        }

        void unite(int i, int j){
            int rootI = find(i);
            int rootJ = find(j);
            if (rootI != rootJ) {
                link(rootI, rootJ);
            }
        }

        void printElements() {
            for (int i = 0; i < parent.size(); ++i) {
                cout << "Element: " << i << ", Parent: " << parent[i] << endl;
            }
        }

        
};

int main() {

    string input1; string input2; string input3;

    cin >> input1 >> input2 >> input3;

    vector<vector<int> > country = parseIntegerMatrix(input1);
    vector<vector<char> > build = parseCharMatrix(input2);
    vector<vector<char> > destroy = parseCharMatrix(input3);

    int N = country.size();
    int W = country[0].size();
    UnionFind msp(N);


    int totalCost = 0;

    priority_queue<vector<int>, vector<vector<int> >, greater<vector<int> > > edges;
    priority_queue<vector<int> > zeroCostEdges;

    for (int i = 0; i < N; i++){
        for (int j = i+1; j < W; j++){
            vector<int> edge;

            if (country[i][j]==1){
                if ((int)build[i][j]>=65 && (int)build[i][j]<97){
                    edge.push_back((int)destroy[i][j]-65);
                }else{
                    edge.push_back((int)destroy[i][j]-71);
                }
                edge.push_back(i);
                edge.push_back(j);
                zeroCostEdges.push(edge);
            }else{
                if ((int)build[i][j]>=65 && (int)build[i][j]<97){
                    edge.push_back((int)build[i][j]-65);
                }else{
                    edge.push_back((int)build[i][j]-71);
                }
                edge.push_back(i);
                edge.push_back(j);
                edges.push(edge);
            }
        }
    }

    while (!zeroCostEdges.empty()) {
        auto edge = zeroCostEdges.top();
        zeroCostEdges.pop();

        int cost = edge[0];
        int city1 = edge[1];
        int city2 = edge[2];

        if (msp.find(city1) != msp.find(city2)) {
            msp.unite(city1, city2);
        } else {
           totalCost += cost; 
        }

    }

    while (!edges.empty()) {
        auto edge = edges.top();
        edges.pop();

        int cost = edge[0];
        int city1 = edge[1];
        int city2 = edge[2];

        if (msp.find(city1) != msp.find(city2)) {
            msp.unite(city1, city2);
            totalCost += cost; 
        }
    }

    cout << totalCost << endl;

    return 0;
}
