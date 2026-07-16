class Solution {
public:
    vector<string> ans;

    vector<string> mp = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    void backtrack(string &digits, int index, string current) {
        // Base case
        if (index == digits.size()) {
            ans.push_back(current);
            return;
        }

        string letters = mp[digits[index] - '0'];

        for (char ch : letters) {
            backtrack(digits, index + 1, current + ch);
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};

        backtrack(digits, 0, "");

        return ans;
    }
};