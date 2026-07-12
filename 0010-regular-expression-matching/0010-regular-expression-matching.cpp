class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();

        vector<vector<bool>> dp(
            m + 1,
            vector<bool>(n + 1, false)
        );

        // Empty string matches empty pattern.
        dp[0][0] = true;

        // Patterns such as a*, a*b*, a*b*c* can match an empty string.
        for (int j = 2; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {

                // Current characters match directly,
                // or pattern has '.'.
                if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                }

                // Handle '*'.
                else if (p[j - 1] == '*') {
                    // Case 1: Use zero occurrences of preceding character.
                    dp[i][j] = dp[i][j - 2];

                    // Case 2: Use one or more occurrences.
                    char previous = p[j - 2];

                    if (previous == s[i - 1] || previous == '.') {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }
};