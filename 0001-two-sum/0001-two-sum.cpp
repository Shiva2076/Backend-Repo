class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int,int>>arr;
        int n=nums.size();
        for(int i=0;i<n;i++){
            arr.push_back({nums[i],i});
        }
        int left=0;
        int right=nums.size()-1;
        sort(arr.begin(),arr.end());
        while(left<right){
            if(arr[left].first+arr[right].first==target){
                return {arr[left].second,arr[right].second};
            }
            else if(arr[left].first+arr[right].first>target){
                right--;
            }
            else{
                left++;
            }
        }
        return {};
    }
};