class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxValue = *max_element(nums.begin(), nums.end());

        vector<long long> frequency(maxValue + 1, 0);
        vector<long long> exactGcdPairs(maxValue + 1, 0);

        for (int x : nums) {
            frequency[x]++;
        }

        // Process possible GCD values from large to small
        for (int g = maxValue; g >= 1; g--) {
            long long divisibleCount = 0;

            // Count numbers divisible by g
            for (int multiple = g; multiple <= maxValue; multiple += g) {
                divisibleCount += frequency[multiple];
            }

            // All pairs where both numbers are divisible by g
            long long pairs = divisibleCount * (divisibleCount - 1) / 2;

            // Remove pairs whose exact GCD is a larger multiple of g
            for (int multiple = 2 * g;
                 multiple <= maxValue;
                 multiple += g) {
                pairs -= exactGcdPairs[multiple];
            }

            exactGcdPairs[g] = pairs;
        }

        // prefixPairs[g] = number of pairs having GCD <= g
        vector<long long> prefixPairs(maxValue + 1, 0);

        for (int g = 1; g <= maxValue; g++) {
            prefixPairs[g] = prefixPairs[g - 1] + exactGcdPairs[g];
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (long long query : queries) {
            // query is 0-indexed, so search for the (query + 1)-th pair
            long long requiredPosition = query + 1;

            int gcdValue = lower_bound(
                prefixPairs.begin() + 1,
                prefixPairs.end(),
                requiredPosition
            ) - prefixPairs.begin();

            answer.push_back(gcdValue);
        }

        return answer;
    }
};