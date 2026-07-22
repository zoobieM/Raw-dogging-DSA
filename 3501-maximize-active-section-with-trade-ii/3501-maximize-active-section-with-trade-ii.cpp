class Solution {
private:
    class SegmentTree {
        int size;
        vector<int> tree;

    public:
        SegmentTree(const vector<int>& values) {
            int n = values.size();
            size = 1;

            while (size < n) {
                size *= 2;
            }

            tree.assign(2 * size, 0);

            for (int i = 0; i < n; i++) {
                tree[size + i] = values[i];
            }

            for (int i = size - 1; i >= 1; i--) {
                tree[i] = max(tree[2 * i], tree[2 * i + 1]);
            }
        }

        int query(int left, int right) {
            if (left > right) {
                return 0;
            }

            left += size;
            right += size;

            int answer = 0;

            while (left <= right) {
                if (left % 2 == 1) {
                    answer = max(answer, tree[left]);
                    left++;
                }

                if (right % 2 == 0) {
                    answer = max(answer, tree[right]);
                    right--;
                }

                left /= 2;
                right /= 2;
            }

            return answer;
        }
    };

public:
    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries
    ) {
        int n = s.size();

        int totalOnes = 0;

        for (char ch : s) {
            totalOnes += (ch == '1');
        }

        vector<int> zeroStart;
        vector<int> zeroEnd;
        vector<int> zeroRunId(n, -1);

        // Store every maximal block of zeroes.
        for (int i = 0; i < n;) {
            if (s[i] == '1') {
                i++;
                continue;
            }

            int left = i;

            while (i < n && s[i] == '0') {
                i++;
            }

            int right = i - 1;
            int id = zeroStart.size();

            zeroStart.push_back(left);
            zeroEnd.push_back(right);

            for (int j = left; j <= right; j++) {
                zeroRunId[j] = id;
            }
        }

        int numberOfZeroRuns = zeroStart.size();

        /*
        Candidate i represents:

            zero run i
            + the one-run between them
            + zero run i + 1

        The increase in active sections is:

            length(zero run i) + length(zero run i + 1)
        */
        vector<int> gain;

        for (int i = 0; i + 1 < numberOfZeroRuns; i++) {
            int leftLength = zeroEnd[i] - zeroStart[i] + 1;
            int rightLength = zeroEnd[i + 1] - zeroStart[i + 1] + 1;

            gain.push_back(leftLength + rightLength);
        }

        SegmentTree segmentTree(gain);

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& query : queries) {
            int left = query[0];
            int right = query[1];

            int bestGain = 0;

            /*
            Find candidates whose two zero-runs lie completely
            inside [left, right].
            */
            int firstCandidate =
                lower_bound(zeroStart.begin(), zeroStart.end(), left)
                - zeroStart.begin();

            int lastContainedZeroRun =
                upper_bound(zeroEnd.begin(), zeroEnd.end(), right)
                - zeroEnd.begin() - 1;

            int lastCandidate = lastContainedZeroRun - 1;

            if (firstCandidate <= lastCandidate &&
                firstCandidate < static_cast<int>(gain.size())) {
                lastCandidate =
                    min(lastCandidate, static_cast<int>(gain.size()) - 1);

                bestGain = max(
                    bestGain,
                    segmentTree.query(firstCandidate, lastCandidate)
                );
            }

            // Candidate whose left zero-run is cut by query[left].
            if (s[left] == '0') {
                int id = zeroRunId[left];

                if (id + 1 < numberOfZeroRuns &&
                    zeroStart[id + 1] <= right) {

                    int leftPart = zeroEnd[id] - left + 1;

                    int rightPart =
                        min(zeroEnd[id + 1], right)
                        - zeroStart[id + 1] + 1;

                    bestGain = max(bestGain, leftPart + rightPart);
                }
            }

            // Candidate whose right zero-run is cut by query[right].
            if (s[right] == '0') {
                int id = zeroRunId[right];

                if (id > 0 && zeroEnd[id - 1] >= left) {
                    int leftPart =
                        zeroEnd[id - 1]
                        - max(zeroStart[id - 1], left) + 1;

                    int rightPart = right - zeroStart[id] + 1;

                    bestGain = max(bestGain, leftPart + rightPart);
                }
            }

            answer.push_back(totalOnes + bestGain);
        }

        return answer;
    }
};