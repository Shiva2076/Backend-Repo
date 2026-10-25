class Solution {
public:

    bool dfs(vector<vector<int>>& grid,int r, int c){
        int m=grid.size(), n=grid[0].size();

        if(r<0 || c<0 || r>=m ||c >=n){
            return false;
        }
        if(grid[r][c]==1){
            return true;
        }
        grid[r][c]= 1;

        bool up=dfs(grid,r-1,c);
        bool down=dfs(grid,r+1,c);
        bool right=dfs(grid,r,c+1);
        bool left=dfs(grid,r,c-1);

        return up && down && right && left;

    }


    int closedIsland(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int count=0;

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==0){
                    if(dfs(grid,i,j)){
                        count++;
                    }
                }
            }
        }
        return count;

    }
};