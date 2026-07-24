class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAX_XOR = 2048;

        vector<bool> pairXor(MAX_XOR, false);
        vector<bool> tripletXor(MAX_XOR, false);

        for (int a : nums) {
            for (int b : nums) {
                pairXor[a ^ b] = true;
            }
        }

        for (int value = 0; value < MAX_XOR; value++) {
            if (!pairXor[value]) continue;

            for (int num : nums) {
                tripletXor[value ^ num] = true;
            }
        }

        int answer = 0;

        for (bool exists : tripletXor) {
            if (exists) answer++;
        }

        return answer;
    }
};