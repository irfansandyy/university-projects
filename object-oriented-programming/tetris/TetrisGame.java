import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TetrisGame extends JFrame {
    private Board board;
    private Tetromino currentPiece;
    private Tetromino[] nextPieces;
    private GamePanel gamePanel;
    private Timer timer;
    private int score;
    private int highScore;
    private int level;
    private int linesCleared;
    private String difficulty;
    private boolean isPaused;
    private boolean gameOver;
    private String playerName;

    public TetrisGame(DatabaseManager.SavedGameState state) {
        setTitle("Tetris Game - OOP Java");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);

        board = new Board();
        score = state != null ? state.score : 0;
        highScore = DatabaseManager.getHighestScore();
        level = state != null ? state.level : 1;
        linesCleared = state != null ? state.linesCleared : 0;
        difficulty = (state != null && state.difficulty != null) ? state.difficulty : "MEDIUM";
        isPaused = false;
        gameOver = false;

        String name = (state != null && state.username != null) ? state.username : System.getProperty("tetris.playerName");
        if (name == null || name.trim().isEmpty()) {
            name = "Player";
        }
        this.playerName = name;

        gamePanel = new GamePanel();
        add(gamePanel);
        pack();
        setLocationRelativeTo(null);

        if (state != null) {
            loadFromState(state);
        } else {
            startGame();
            return;
        }

        startTimer();
    }

    public TetrisGame() {
        setTitle("Tetris Game - OOP Java");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);

        board = new Board();
        score = 0;
        highScore = DatabaseManager.getHighestScore();
        level = 1;
        linesCleared = 0;
        difficulty = "MEDIUM";
        isPaused = false;
        gameOver = false;

        String name = System.getProperty("tetris.playerName");
        if (name == null || name.trim().isEmpty()) {
            name = "Player";
        }
        this.playerName = name;

        gamePanel = new GamePanel();
        add(gamePanel);
        pack();
        setLocationRelativeTo(null);

        startGame();
    }

    public void startGame() {
        nextPieces = new Tetromino[3];
        for (int i = 0; i < nextPieces.length; i++) {
            nextPieces[i] = Tetromino.createRandomTetromino();
        }
        currentPiece = nextPieces[0];
        spawnPiece();

        startTimer();
    }

    private void startTimer() {
        int delay = getSpeed();
        timer = new Timer(delay, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!isPaused && !gameOver) {
                    gameLoop();
                }
            }
        });
        timer.start();
    }

    private void gameLoop() {
        if (!movePiece(0, 1)) {
            board.placePiece(currentPiece);
            int cleared = board.clearLines();
            
            if (cleared > 0) {
                updateScore(cleared);
            }
            
            spawnNextPiece();
            spawnPiece();

            if (!board.isValidPosition(currentPiece)) {
                gameOver = true;
                timer.stop();
                DatabaseManager.deleteGameState(playerName);
            } else {
                saveState();
            }
        }
        gamePanel.repaint();
    }

    private void saveState() {
        DatabaseManager.SavedGameState state = new DatabaseManager.SavedGameState();
        state.username = playerName;
        state.difficulty = difficulty;
        state.score = score;
        state.level = level;
        state.linesCleared = linesCleared;
        state.boardData = serializeBoard(board.getGrid());
        state.currentPieceType = currentPiece != null ? currentPiece.getColorValue() : 0;
        state.currentPieceX = currentPiece != null ? currentPiece.getX() : 0;
        state.currentPieceY = currentPiece != null ? currentPiece.getY() : 0;
        state.nextPiecesData = serializeNextPieces();
        DatabaseManager.saveGameState(playerName, state);
    }

    private String serializeBoard(int[][] grid) {
        StringBuilder sb = new StringBuilder();
        for (int y = 0; y < Board.HEIGHT; y++) {
            for (int x = 0; x < Board.WIDTH; x++) {
                sb.append(grid[y][x]);
                if (x < Board.WIDTH - 1) sb.append(',');
            }
            if (y < Board.HEIGHT - 1) sb.append(';');
        }
        return sb.toString();
    }

    private String serializeNextPieces() {
        if (nextPieces == null) return "";
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < nextPieces.length; i++) {
            int type = (nextPieces[i] != null) ? nextPieces[i].getColorValue() : 0;
            sb.append(type);
            if (i < nextPieces.length - 1) sb.append(',');
        }
        return sb.toString();
    }

    private int[][] parseBoard(String data) {
        int[][] result = new int[Board.HEIGHT][Board.WIDTH];
        if (data == null || data.isEmpty()) return result;
        String[] rows = data.split(";");
        for (int y = 0; y < rows.length && y < Board.HEIGHT; y++) {
            String[] cols = rows[y].split(",");
            for (int x = 0; x < cols.length && x < Board.WIDTH; x++) {
                try {
                    result[y][x] = Integer.parseInt(cols[x]);
                } catch (NumberFormatException e) {
                    result[y][x] = 0;
                }
            }
        }
        return result;
    }

    private int[] parseNextPiecesTypes(String data) {
        if (data == null || data.isEmpty()) return new int[0];
        String[] parts = data.split(",");
        int[] types = new int[parts.length];
        for (int i = 0; i < parts.length; i++) {
            try {
                types[i] = Integer.parseInt(parts[i]);
            } catch (NumberFormatException e) {
                types[i] = 0;
            }
        }
        return types;
    }

    private void loadFromState(DatabaseManager.SavedGameState state) {
        if (state.boardData != null) {
            board.setGrid(parseBoard(state.boardData));
        }
        this.difficulty = state.difficulty != null ? state.difficulty : this.difficulty;
        this.score = state.score;
        this.level = state.level;
        this.linesCleared = state.linesCleared;

        int[] types = parseNextPiecesTypes(state.nextPiecesData);
        if (types.length > 0) {
            nextPieces = new Tetromino[types.length];
            for (int i = 0; i < types.length; i++) {
                nextPieces[i] = Tetromino.createTetrominoByType(types[i]);
            }
        } else {
            nextPieces = new Tetromino[3];
            for (int i = 0; i < nextPieces.length; i++) {
                nextPieces[i] = Tetromino.createRandomTetromino();
            }
        }

        if (state.currentPieceType > 0) {
            currentPiece = Tetromino.createTetrominoByType(state.currentPieceType);
            currentPiece.setX(state.currentPieceX);
            currentPiece.setY(state.currentPieceY);
        } else {
            currentPiece = nextPieces[0];
            spawnPiece();
        }
    }

    private void spawnPiece() {
        currentPiece.setX(Board.WIDTH / 2 - 1);
        currentPiece.setY(0);
    }

    private void spawnNextPiece() {
        currentPiece = nextPieces[0];
        for (int i = 0; i < nextPieces.length - 1; i++) {
            nextPieces[i] = nextPieces[i + 1];
        }
        nextPieces[nextPieces.length - 1] = Tetromino.createRandomTetromino();
    }

    public boolean movePiece(int dx, int dy) {
        currentPiece.move(dx, dy);
        if (!board.isValidPosition(currentPiece)) {
            currentPiece.move(-dx, -dy);
            return false;
        }
        return true;
    }

    public void rotatePiece() {
        currentPiece.rotate();
        if (!board.isValidPosition(currentPiece)) {
            currentPiece.rotateBack();
        }
    }

    public void dropPiece() {
        while (movePiece(0, 1)) {
            score += 2;
        }
    }

    private void updateScore(int lines) {
        linesCleared += lines;
        
        int points = 0;
        switch (lines) {
            case 1: points = 100; break;
            case 2: points = 300; break;
            case 3: points = 500; break;
            case 4: points = 800; break;
        }
        score += points * level;

        if (score > highScore) {
            highScore = score;
        }
        
        int newLevel = (linesCleared / 10) + 1;
        if (newLevel != level) {
            level = newLevel;
            timer.setDelay(getSpeed());
        }
    }

    private int getSpeed() {
        int base = 500 - (level - 1) * 50;

        if ("EASY".equalsIgnoreCase(difficulty)) {
            base += 100;
        } else if ("HARD".equalsIgnoreCase(difficulty)) {
            base -= 100;
        }

        return Math.max(100, base);
    }

    public void setDifficulty(String difficulty) {
        this.difficulty = difficulty;
        if (timer != null) {
            timer.setDelay(getSpeed());
        }
    }

    public void togglePause() {
        isPaused = !isPaused;
        if (gamePanel != null) {
            gamePanel.updatePauseUI();
        }
    }

    class GamePanel extends JPanel {
        private final int BLOCK_SIZE = 30;
        private final int BOARD_WIDTH = Board.WIDTH * BLOCK_SIZE;
        private final int BOARD_HEIGHT = Board.HEIGHT * BLOCK_SIZE;
        private final int INFO_WIDTH = 200;

        private JButton pauseMenuButton;

        public GamePanel() {
            setPreferredSize(new Dimension(BOARD_WIDTH + INFO_WIDTH, BOARD_HEIGHT));
            setBackground(Color.BLACK);
            setFocusable(true);
            setLayout(null);

            pauseMenuButton = new JButton("Main Menu");
            pauseMenuButton.setFocusPainted(false);
            pauseMenuButton.setFont(new Font("Arial", Font.BOLD, 14));
            pauseMenuButton.setBackground(new Color(0, 120, 215));
            pauseMenuButton.setForeground(Color.WHITE);
            int btnWidth = 140;
            int btnHeight = 30;
            int btnX = (BOARD_WIDTH - btnWidth) / 2;
            int btnY = BOARD_HEIGHT / 2 + 40;
            pauseMenuButton.setBounds(btnX, btnY, btnWidth, btnHeight);
            pauseMenuButton.setVisible(false);
            pauseMenuButton.addActionListener(e -> {
                SwingUtilities.invokeLater(() -> {
                    MainMenu menu = new MainMenu();
                    menu.setVisible(true);
                });
                if (timer != null) {
                    timer.stop();
                }
                SwingUtilities.getWindowAncestor(GamePanel.this).dispose();
            });
            add(pauseMenuButton);

            addKeyListener(new KeyAdapter() {
                @Override
                public void keyPressed(KeyEvent e) {
                    if (gameOver) {
                        if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                            SwingUtilities.invokeLater(() -> {
                                TetrisGame newGame = new TetrisGame();
                                newGame.setDifficulty(difficulty);
                                newGame.setVisible(true);
                            });
                            SwingUtilities.getWindowAncestor(GamePanel.this).dispose();
                        } else if (e.getKeyCode() == KeyEvent.VK_ESCAPE) {
                            SwingUtilities.invokeLater(() -> {
                                MainMenu menu = new MainMenu();
                                menu.setVisible(true);
                            });
                            SwingUtilities.getWindowAncestor(GamePanel.this).dispose();
                        }
                        return;
                    }

                    switch (e.getKeyCode()) {
                        case KeyEvent.VK_LEFT:
                            movePiece(-1, 0);
                            break;
                        case KeyEvent.VK_RIGHT:
                            movePiece(1, 0);
                            break;
                        case KeyEvent.VK_DOWN:
                            movePiece(0, 1);
                            break;
                        case KeyEvent.VK_UP:
                            rotatePiece();
                            break;
                        case KeyEvent.VK_SPACE:
                            dropPiece();
                            break;
                        case KeyEvent.VK_P:
                            togglePause();
                            break;
                    }
                    repaint();
                }
            });
        }

        public void updatePauseUI() {
            if (isPaused) {
                pauseMenuButton.setVisible(true);
                pauseMenuButton.requestFocusInWindow();
            } else {
                pauseMenuButton.setVisible(false);
                requestFocusInWindow();
            }
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;

            drawBoard(g2d);
            
            if (!gameOver) {
                drawTetromino(g2d, currentPiece);
            }

            drawInfoPanel(g2d);

            if (gameOver) {
                drawGameOver(g2d);
            }

            if (isPaused) {
                drawPause(g2d);
            }
        }

        private void drawBoard(Graphics2D g) {
            int[][] grid = board.getGrid();
            
            for (int y = 0; y < Board.HEIGHT; y++) {
                for (int x = 0; x < Board.WIDTH; x++) {
                    if (grid[y][x] != 0) {
                        g.setColor(getColorFromValue(grid[y][x]));
                        g.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
                        g.setColor(Color.DARK_GRAY);
                        g.drawRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
                    }
                }
            }

            g.setColor(new Color(50, 50, 50));
            for (int i = 0; i <= Board.WIDTH; i++) {
                g.drawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, BOARD_HEIGHT);
            }
            for (int i = 0; i <= Board.HEIGHT; i++) {
                g.drawLine(0, i * BLOCK_SIZE, BOARD_WIDTH, i * BLOCK_SIZE);
            }
        }

        private void drawTetromino(Graphics2D g, Tetromino piece) {
            int[][] shape = piece.getShape();
            g.setColor(piece.getColor());

            for (int y = 0; y < shape.length; y++) {
                for (int x = 0; x < shape[y].length; x++) {
                    if (shape[y][x] != 0) {
                        int drawX = (piece.getX() + x) * BLOCK_SIZE;
                        int drawY = (piece.getY() + y) * BLOCK_SIZE;
                        g.fillRect(drawX, drawY, BLOCK_SIZE, BLOCK_SIZE);
                        g.setColor(Color.DARK_GRAY);
                        g.drawRect(drawX, drawY, BLOCK_SIZE, BLOCK_SIZE);
                        g.setColor(piece.getColor());
                    }
                }
            }
        }

        private void drawInfoPanel(Graphics2D g) {
            int startX = BOARD_WIDTH + 20;
            
            g.setColor(Color.WHITE);
            g.setFont(new Font("Arial", Font.BOLD, 18));
            g.drawString("TETRIS", startX, 30);

            g.setFont(new Font("Arial", Font.PLAIN, 14));
            g.drawString("Score: " + score, startX, 70);
            g.drawString("High Score: " + highScore, startX, 95);
            g.drawString("Level: " + level, startX, 120);
            g.drawString("Lines: " + linesCleared, startX, 145);
            g.drawString("Difficulty: " + difficulty, startX, 170);

            g.drawString("Next:", startX, 200);
            if (nextPieces != null) {
                int previewSize = 18;
                int previewSpacing = 50;

                for (int i = 0; i < nextPieces.length; i++) {
                    Tetromino preview = nextPieces[i];
                    if (preview == null) continue;

                    int[][] shape = preview.getShape();
                    g.setColor(preview.getColor());
                    int offsetY = 215 + i * previewSpacing;

                    for (int y = 0; y < shape.length; y++) {
                        for (int x = 0; x < shape[y].length; x++) {
                            if (shape[y][x] != 0) {
                                int drawX = startX + x * previewSize;
                                int drawY = offsetY + y * previewSize;
                                g.fillRect(drawX, drawY, previewSize, previewSize);
                                g.setColor(Color.DARK_GRAY);
                                g.drawRect(drawX, drawY, previewSize, previewSize);
                                g.setColor(preview.getColor());
                            }
                        }
                    }
                }
            }

            g.setColor(Color.LIGHT_GRAY);
            g.setFont(new Font("Arial", Font.PLAIN, 11));
            int controlsY = 440;
            g.drawString("Controls:", startX, controlsY);
            g.drawString("← →: Move", startX, controlsY + 20);
            g.drawString("↑: Rotate", startX, controlsY + 40);
            g.drawString("↓: Soft Drop", startX, controlsY + 60);
            g.drawString("Space: Hard Drop", startX, controlsY + 80);
            g.drawString("P: Pause", startX, controlsY + 100);
        }

        private void drawGameOver(Graphics2D g) {
            g.setColor(new Color(0, 0, 0, 180));
            g.fillRect(0, 0, BOARD_WIDTH, BOARD_HEIGHT);

            g.setColor(Color.RED);
            g.setFont(new Font("Arial", Font.BOLD, 32));
            String text = "GAME OVER";
            FontMetrics fm = g.getFontMetrics();
            int x = (BOARD_WIDTH - fm.stringWidth(text)) / 2;
            int centerY = BOARD_HEIGHT / 2;
            g.drawString(text, x, centerY - 50);

            g.setColor(Color.WHITE);
            g.setFont(new Font("Arial", Font.PLAIN, 16));
            fm = g.getFontMetrics();

            String finalScoreText = "Final Score: " + score;
            x = (BOARD_WIDTH - fm.stringWidth(finalScoreText)) / 2;
            g.drawString(finalScoreText, x, centerY - 5);

            String highScoreText = "High Score: " + highScore;
            x = (BOARD_WIDTH - fm.stringWidth(highScoreText)) / 2;
            g.drawString(highScoreText, x, centerY + 15);

            String hintText = "ENTER = Play Again    ESC = Main Menu";
            x = (BOARD_WIDTH - fm.stringWidth(hintText)) / 2;
            g.drawString(hintText, x, centerY + 45);

            // Record score into database-backed leaderboard with difficulty
            Leaderboard.getInstance().addScore(playerName, score, difficulty);
        }

        private void drawPause(Graphics2D g) {
            g.setColor(new Color(0, 0, 0, 150));
            g.fillRect(0, 0, BOARD_WIDTH, BOARD_HEIGHT);

            g.setColor(Color.YELLOW);
            g.setFont(new Font("Arial", Font.BOLD, 40));
            String text = "PAUSED";
            FontMetrics fm = g.getFontMetrics();
            int x = (BOARD_WIDTH - fm.stringWidth(text)) / 2;
            g.drawString(text, x, BOARD_HEIGHT / 2);
        }

        private Color getColorFromValue(int value) {
            Color[] colors = {
                null,
                new Color(0, 240, 240),
                new Color(240, 240, 0),
                new Color(160, 0, 240),
                new Color(240, 160, 0),
                new Color(0, 0, 240),
                new Color(0, 240, 0),
                new Color(240, 0, 0)
            };
            return value >= 0 && value < colors.length ? colors[value] : Color.GRAY;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginFrame login = new LoginFrame();
            login.setVisible(true);
        });
    }
}