class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        vector<int> prefixGcd;
        prefixGcd.reserve(nums.size());

        int currentMax = 0;

        for (int x : nums) {
            currentMax = max(currentMax, x);
            prefixGcd.push_back(gcd(x, currentMax));
        }

        sort(prefixGcd.begin(), prefixGcd.end());

        long long answer = 0;
        int left = 0;
        int right = prefixGcd.size() - 1;

        while (left < right) {
            answer += gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }

        return answer;
    }
};