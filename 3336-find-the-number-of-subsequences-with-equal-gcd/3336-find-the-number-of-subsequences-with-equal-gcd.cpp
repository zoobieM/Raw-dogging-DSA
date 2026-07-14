class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAX_VAL = 200;

        // dp[g1][g2] = number of ways to form two disjoint subsequences
        // having GCD g1 and g2.
        // GCD 0 means the subsequence is currently empty.
        vector<vector<int>> dp(MAX_VAL + 1,
                               vector<int>(MAX_VAL + 1, 0));

        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> next = dp;

            for (int g1 = 0; g1 <= MAX_VAL; g1++) {
                for (int g2 = 0; g2 <= MAX_VAL; g2++) {
                    if (dp[g1][g2] == 0)
                        continue;

                    int ways = dp[g1][g2];

                    // Put x into subsequence 1
                    int newG1 = gcd(g1, x);
                    next[newG1][g2] =
                        (next[newG1][g2] + ways) % MOD;

                    // Put x into subsequence 2
                    int newG2 = gcd(g2, x);
                    next[g1][newG2] =
                        (next[g1][newG2] + ways) % MOD;

                    // Not selecting x is already included because next = dp
                }
            }

            dp = move(next);
        }

        long long answer = 0;

        // Both subsequences must be non-empty and have equal GCD.
        for (int g = 1; g <= MAX_VAL; g++) {
            answer = (answer + dp[g][g]) % MOD;
        }

        return answer;
    }
};