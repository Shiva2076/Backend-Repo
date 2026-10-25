class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>ans=nums1;
        ans.insert(ans.end(),nums2.begin(),nums2.end());
        sort(ans.begin(),ans.end());
        int n=ans.size();
        int k=n/2;
        if(n%2!=0){
            return ans[k];
        }
        else{
           return ((double)ans[k - 1] + ans[k]) / 2.0;
        }

    }
};