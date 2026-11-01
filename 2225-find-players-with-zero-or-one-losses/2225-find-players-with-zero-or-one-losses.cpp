class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int,int>lost_map;
        for(int i=0;i<matches.size();i++){
            int loser=matches[i][1];
            lost_map[loser]++;
        }

        vector<int>not_lost;
        vector<int>lostOnce;

        for(int i=0;i<matches.size();i++){
            int winner=matches[i][0];
            int loser=matches[i][1];

            if(lost_map.find(winner)==lost_map.end()){
                not_lost.push_back(winner);
                lost_map[winner]=0;
            }

            if(lost_map[loser]==1){
                lostOnce.push_back(loser);
            }
        }

        sort(lostOnce.begin(),lostOnce.end());
        sort(not_lost.begin(),not_lost.end());
        return {not_lost,lostOnce};

    }
};