class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0, maxLen = 1;

        auto expand = [&](int left, int right) {
            while (left >= 0 && right < s.size() && s[left] == s[right]) {
                left--;
                right++;
            }

            int len = right - left - 1;
            if (len > maxLen) {
                maxLen = len;
                start = left + 1;
            }
        };

        for (int i = 0; i < s.size(); i++) {
            expand(i, i);       // odd length palindrome
            expand(i, i + 1);   // even length palindrome
        }

        return s.substr(start, maxLen);
    }
};