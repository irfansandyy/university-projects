public class Board {
    public static final int WIDTH = 10;
    public static final int HEIGHT = 20;
    private int[][] grid;

    public Board() {
        grid = new int[HEIGHT][WIDTH];
    }

    public int[][] getGrid() {
        return grid;
    }

    public void setGrid(int[][] newGrid) {
        if (newGrid == null) return;
        for (int y = 0; y < HEIGHT && y < newGrid.length; y++) {
            for (int x = 0; x < WIDTH && x < newGrid[y].length; x++) {
                grid[y][x] = newGrid[y][x];
            }
        }
    }

    public boolean isValidPosition(Tetromino piece) {
        int[][] shape = piece.getShape();
        int pieceX = piece.getX();
        int pieceY = piece.getY();

        for (int y = 0; y < shape.length; y++) {
            for (int x = 0; x < shape[y].length; x++) {
                if (shape[y][x] != 0) {
                    int boardX = pieceX + x;
                    int boardY = pieceY + y;

                    if (boardX < 0 || boardX >= WIDTH || boardY >= HEIGHT) {
                        return false;
                    }

                    if (boardY >= 0 && grid[boardY][boardX] != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    public void placePiece(Tetromino piece) {
        int[][] shape = piece.getShape();
        int pieceX = piece.getX();
        int pieceY = piece.getY();
        int colorValue = piece.getColorValue();

        for (int y = 0; y < shape.length; y++) {
            for (int x = 0; x < shape[y].length; x++) {
                if (shape[y][x] != 0) {
                    int boardX = pieceX + x;
                    int boardY = pieceY + y;
                    if (boardY >= 0 && boardY < HEIGHT && boardX >= 0 && boardX < WIDTH) {
                        grid[boardY][boardX] = colorValue;
                    }
                }
            }
        }
    }

    public int clearLines() {
        int linesCleared = 0;

        for (int y = HEIGHT - 1; y >= 0; y--) {
            if (isLineFull(y)) {
                removeLine(y);
                linesCleared++;
                y++;
            }
        }

        return linesCleared;
    }

    private boolean isLineFull(int row) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[row][x] == 0) {
                return false;
            }
        }
        return true;
    }

    private void removeLine(int row) {
        for (int y = row; y > 0; y--) {
            for (int x = 0; x < WIDTH; x++) {
                grid[y][x] = grid[y - 1][x];
            }
        }

        for (int x = 0; x < WIDTH; x++) {
            grid[0][x] = 0;
        }
    }

    public void clear() {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                grid[y][x] = 0;
            }
        }
    }
}