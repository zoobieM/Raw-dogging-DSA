class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> answer;

        int n = s.size();
        int wordLength = words[0].size();
        int wordCount = words.size();
        int totalLength = wordLength * wordCount;

        if (totalLength > n) {
            return answer;
        }

        unordered_map<string, int> required;

        for (const string& word : words) {
            required[word]++;
        }

        for (int offset = 0; offset < wordLength; offset++) {
            int left = offset;
            int right = offset;
            int usedWords = 0;

            unordered_map<string, int> current;

            while (right + wordLength <= n) {
                string word = s.substr(right, wordLength);
                right += wordLength;

                // Word belongs to our required list
                if (required.count(word)) {
                    current[word]++;
                    usedWords++;

                    // Remove extra occurrences of the current word
                    while (current[word] > required[word]) {
                        string leftWord = s.substr(left, wordLength);

                        current[leftWord]--;
                        left += wordLength;
                        usedWords--;
                    }

                    // Complete concatenation found
                    if (usedWords == wordCount) {
                        answer.push_back(left);

                        // Move left forward to search for overlapping answers
                        string leftWord = s.substr(left, wordLength);

                        current[leftWord]--;
                        left += wordLength;
                        usedWords--;
                    }
                }
                // Invalid word resets the current window
                else {
                    current.clear();
                    usedWords = 0;
                    left = right;
                }
            }
        }

        return answer;
    }
};