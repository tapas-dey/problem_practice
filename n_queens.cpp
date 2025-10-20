#include <vector>
#include <algorithm>
using namespace std;

bool IsValidPosition(vector<int>& cols){
    //Which row are we validating
    int row_id = cols.size() - 1;
    for (int ii = 0; ii < row_id; ++ii){
        int diff = abs(cols[ii] - cols[row_id]);
        if (diff == 0 || diff == row_id - ii){
            //same column or diagnoal assignment not valid
            return false;
        }
    }
    return true;
}


void SolveNQueens(int n, int row, vector<int>& cols, vector<vector<int>>& results){

        if (row == n)
        {
            //We've a solution
            results.push_back(cols);
        }
        for (int col = 0; col < n; ++col){
            cols.push_back(col);
            if (IsValidPosition(cols))
            {
                SolveNQueens(n, row + 1, cols, results);
            }
            cols.pop_back();
        }
}

int main() {

    vector<vector<int>> results;
    int n = 4;
    vector<int> cols;
    SolveNQueens(n, 0, cols, results);
    return 0;
}