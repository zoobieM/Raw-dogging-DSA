class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool rows[9][9] = {};
        bool cols[9][9] = {};
        bool boxes[9][9] = {};

        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                char cell = board[row][col];

                if (cell == '.') {
                    continue;
                }

                int digit = cell - '1';
                int boxIndex = (row / 3) * 3 + (col / 3);

                if (rows[row][digit] ||
                    cols[col][digit] ||
                    boxes[boxIndex][digit]) {
                    return false;
                }

                rows[row][digit] = true;
                cols[col][digit] = true;
                boxes[boxIndex][digit] = true;
            }
        }

        return true;
    }
};