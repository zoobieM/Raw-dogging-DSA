class Solution {
public:
    vector<vector<int>> ans;
    vector<int> current;

    void backtrack(int start, vector<int>& candidates, int target) {
        if (target == 0) {
            ans.push_back(current);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {

            // Skip duplicate candidates at the same level
            if (i > start && candidates[i] == candidates[i - 1]) {
                continue;
            }

            // Since array is sorted, further elements will also be too large
            if (candidates[i] > target) {
                break;
            }

            current.push_back(candidates[i]);

            // i + 1 because each element can only be used once
            backtrack(i + 1, candidates, target - candidates[i]);

            current.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        backtrack(0, candidates, target);

        return ans;
    }
};