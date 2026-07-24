class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }

private:
    bool solve(vector<vector<char>>& board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {

                // Find an empty cell
                if (board[row][col] == '.') {

                    // Try digits from 1 to 9
                    for (char digit = '1'; digit <= '9'; digit++) {
                        if (isValid(board, row, col, digit)) {
                            board[row][col] = digit;

                            // Continue solving
                            if (solve(board)) {
                                return true;
                            }

                            // Backtrack
                            board[row][col] = '.';
                        }
                    }

                    // No digit worked
                    return false;
                }
            }
        }

        // No empty cells remain
        return true;
    }

    bool isValid(vector<vector<char>>& board, int row, int col, char digit) {
        for (int i = 0; i < 9; i++) {

            // Check current row
            if (board[row][i] == digit) {
                return false;
            }

            // Check current column
            if (board[i][col] == digit) {
                return false;
            }

            // Check current 3 × 3 box
            int boxRow = 3 * (row / 3) + i / 3;
            int boxCol = 3 * (col / 3) + i % 3;

            if (board[boxRow][boxCol] == digit) {
                return false;
            }
        }

        return true;
    }
};