class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> lastIndex(26);

        for (int i = 0; i < s.size(); i++) {
            lastIndex[s[i] - 'a'] = i;
        }

        vector<bool> used(26, false);
        string result;

        for (int i = 0; i < s.size(); i++) {
            char current = s[i];
            int index = current - 'a';

            if (used[index]) {
                continue;
            }

            while (!result.empty() &&
                   result.back() > current &&
                   lastIndex[result.back() - 'a'] > i) {
                
                used[result.back() - 'a'] = false;
                result.pop_back();
            }

            result.push_back(current);
            used[index] = true;
        }

        return result;
    }
};