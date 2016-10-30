/*
305. Number of Islands II   QuestionEditorial Solution  My Submissions
Difficulty: Hard
Contributors: Admin
A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
Example:

Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0
We return the result as an array: [1, 1, 2, 3]
*/

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        vector<int> res;
        vector<int> parent(m*n, -1);
        vector<pair<int, int>> dir = {pair<int,int>(0,1), pair<int,int>(0,-1), pair<int,int>(1, 0), pair<int,int>(-1,0)};
        
        int count = 0;
        for(int k = 0; k < positions.size(); ++k){
            int i = positions[k].first;
            int j = positions[k].second;
            //mapping this 2-dimension to 1-dimension vector
            //because i = 0, 1, ````, m - 1
            // j = 0, 1, ````, n - 1
            // so id = n * i + j or id = m * j + i
            int id = n * i + j;
            parent[id] = id;//设置这个节点的祖先节点，就是其自身
            ++count;
            
            for(auto d : dir){
                //考察每一个方向的那个点是否
                i += d.first, j += d.second;
                int idx = n * i + j;
                if(i < 0 || i >= m || j < 0 || j >= n || idx < 0 || idx >= m*n || parent[idx] == -1){
                    i -= d.first, j -= d.second;//下标复原
                    continue;
                }//-1代表是水，说明这里不能走。
                int idx_root = find(idx,parent);//寻找四周的祖先节点
                if(idx_root != id){
                    --count;
                    parent[id] = idx_root;
                    id = idx_root;
                    //这里需要注意的就是，必须得每次更新parent[id] 以及 id，相当于compression，不然会让有些id的parent没有被compression从而导致多减了count
                }
                i -= d.first, j -= d.second;//下标复原
            }
            res.push_back(count);
        }
        return res;
    }
    
    int find(int k, vector<int>& parent){
        while(k != parent[k]){
            parent[k] = parent[parent[k]];//compression
            k = parent[k];
        }
        return parent[k];
    }
};
