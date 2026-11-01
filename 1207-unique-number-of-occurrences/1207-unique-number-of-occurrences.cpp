class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int>freq;
        for(int &x:arr){
            freq[x]++;
        }

        unordered_set<int>st;
        for(auto &it:freq){
            int freq=it.second;

            if(st.find(freq)!=st.end())
            return false;
            st.insert(freq);
        }
        return true;
    }
};