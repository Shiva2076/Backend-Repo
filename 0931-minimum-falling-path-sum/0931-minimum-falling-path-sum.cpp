class Solution {
public:
    int path(int r,int c,vector<vector<int>>& matrix,vector<vector<int>> &dp){
        int m=matrix.size();
        int n=matrix[0].size();
        if(c <0 || c>=n){
            return INT_MAX/2;
        }
        if(r == m-1){
            return matrix[r][c];
        }
        if(dp[r][c]!=INT_MAX)
            return dp[r][c];

        int dd=path(r+1,c,matrix,dp);
        int dr=path(r+1,c+1,matrix,dp);
        int dl=path(r+1,c-1,matrix,dp);
        return dp[r][c]=matrix[r][c]+min({dd , dr , dl});
    }

    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

        int ans=INT_MAX;
        for(int j=0;j<n;j++){
            ans=min(ans,path(0,j,matrix,dp));
        }
        return ans;
    }
};