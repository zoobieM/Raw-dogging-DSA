class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int originalOnes = 0;

        for (char ch : s) {
            if (ch == '1') {
                originalOnes++;
            }
        }

        // Add the virtual active sections.
        string t = "1" + s + "1";

        vector<pair<char, int>> runs;

        // Run-length encoding of t.
        for (char ch : t) {
            if (runs.empty() || runs.back().first != ch) {
                runs.push_back({ch, 1});
            } else {
                runs.back().second++;
            }
        }

        int maximumGain = 0;

        // Search for: zero block, one block, zero block.
        for (int i = 1; i + 1 < runs.size(); i++) {
            if (runs[i].first == '1' &&
                runs[i - 1].first == '0' &&
                runs[i + 1].first == '0') {

                int gain = runs[i - 1].second + runs[i + 1].second;
                maximumGain = max(maximumGain, gain);
            }
        }

        return originalOnes + maximumGain;
    }
};