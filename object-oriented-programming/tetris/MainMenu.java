import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class MainMenu extends JFrame {

    private String[] menuItems = {"Resume", "New Game", "Difficulty", "Leaderboard", "Quit"};
    private int selectedIndex = 0;
    private JLabel[] menuLabels;
    private String[] difficulties = {"EASY", "MEDIUM", "HARD"};
    private int difficultyIndex = 1;

    private JPanel mainPanel;
    private JPanel centerWrapper;
    private JPanel leaderboardPanel;
    private JLabel hint;
    private boolean showingLeaderboard = false;

    public MainMenu() {
        setTitle("Tetris Main Menu");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);

        initUI();

        pack();
        setLocationRelativeTo(null);
    }

    private void initUI() {
        mainPanel = new JPanel(new BorderLayout()) {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2d = (Graphics2D) g;
                GradientPaint gp = new GradientPaint(0, 0, new Color(10, 10, 10), 0, getHeight(), new Color(30, 30, 30));
                g2d.setPaint(gp);
                g2d.fillRect(0, 0, getWidth(), getHeight());
            }
        };
        mainPanel.setOpaque(false);
        mainPanel.setBorder(BorderFactory.createEmptyBorder(20, 40, 20, 40));

        JPanel logoPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2d = (Graphics2D) g;
                g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

                int blockSize = 9;
                int gap = 1;
                int lettersCount = 6;
                int letterWidthBlocks = 6;
                int letterHeightBlocks = 8;
                int spacingBlocks = 1;

                int totalBlocksWidth = lettersCount * letterWidthBlocks + (lettersCount - 1) * spacingBlocks;
                int totalPixelWidth = totalBlocksWidth * (blockSize + gap);
                int totalPixelHeight = letterHeightBlocks * (blockSize + gap);
                int startX = (getWidth() - totalPixelWidth) / 2;
                int startY = (getHeight() - totalPixelHeight) / 2;

                int[][][] letters = {
                    {
                        {1,1,1,1,1,1},
                        {1,1,1,1,1,1},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0}
                    },
                    {
                        {1,1,1,1,1,1},
                        {1,1,0,0,0,0},
                        {1,1,0,0,0,0},
                        {1,1,1,1,1,1},
                        {1,1,1,1,1,1},
                        {1,1,0,0,0,0},
                        {1,1,0,0,0,0},
                        {1,1,1,1,1,1}
                    },
                    {
                        {1,1,1,1,1,1},
                        {1,1,1,1,1,1},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0}
                    },
                    {
                        {1,1,1,1,1,0},
                        {1,1,0,0,0,1},
                        {1,1,0,0,0,1},
                        {1,1,1,1,1,0},
                        {1,1,1,1,0,0},
                        {1,1,0,1,1,0},
                        {1,1,0,0,1,1},
                        {1,1,0,0,0,1}
                    },
                    {
                        {1,1,1,1,1,1},
                        {0,1,1,1,1,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,0,1,1,0,0},
                        {0,1,1,1,1,0},
                        {1,1,1,1,1,1}
                    },
                    {
                        {0,1,1,1,1,0},
                        {1,1,0,0,0,1},
                        {1,1,0,0,0,0},
                        {0,1,1,1,1,0},
                        {0,1,1,1,1,1},
                        {0,0,0,0,1,1},
                        {1,0,0,0,1,1},
                        {0,1,1,1,1,0}
                    }
                };

                Color[] colors = {
                    new Color(0, 240, 240),
                    new Color(240, 240, 0),
                    new Color(160, 0, 240),
                    new Color(240, 160, 0),
                    new Color(0, 0, 240),
                    new Color(240, 0, 0)
                };

                int offsetX = 0;
                for (int letterIndex = 0; letterIndex < letters.length; letterIndex++) {
                    int[][] letter = letters[letterIndex];
                    Color letterColor = colors[letterIndex % colors.length];
                    for (int y = 0; y < letterHeightBlocks; y++) {
                        for (int x = 0; x < letterWidthBlocks; x++) {
                            if (letter[y][x] == 1) {
                                int px = startX + (offsetX + x) * (blockSize + gap);
                                int py = startY + y * (blockSize + gap);
                                g2d.setColor(letterColor);
                                g2d.fillRect(px, py, blockSize, blockSize);
                                g2d.setColor(Color.DARK_GRAY);
                                g2d.drawRect(px, py, blockSize, blockSize);
                            }
                        }
                    }
                    offsetX += letterWidthBlocks + spacingBlocks;
                }
            }
        };
        logoPanel.setBackground(new Color(0, 0, 0, 0));
        logoPanel.setPreferredSize(new Dimension(0, 90));
        mainPanel.add(logoPanel, BorderLayout.NORTH);

        centerWrapper = new JPanel();
        centerWrapper.setOpaque(false);
        centerWrapper.setLayout(new GridBagLayout());

        JPanel centerPanel = new JPanel();
        centerPanel.setOpaque(false);
        centerPanel.setLayout(new BoxLayout(centerPanel, BoxLayout.Y_AXIS));

        menuLabels = new JLabel[menuItems.length];
        for (int i = 0; i < menuItems.length; i++) {
            JLabel label = new JLabel();
            label.setForeground(Color.LIGHT_GRAY);
            label.setFont(new Font("Arial", Font.PLAIN, 18));
            label.setAlignmentX(Component.CENTER_ALIGNMENT);
            menuLabels[i] = label;
            centerPanel.add(label);
            centerPanel.add(Box.createVerticalStrut(10));
        }

        updateMenuLabels();

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.anchor = GridBagConstraints.CENTER;
        centerWrapper.add(centerPanel, gbc);

        mainPanel.add(centerWrapper, BorderLayout.CENTER);

        hint = new JLabel("Use ↑/↓ to move, ←/→ to change difficulty, Enter to select", SwingConstants.CENTER);
        hint.setForeground(Color.DARK_GRAY);
        hint.setFont(new Font("Arial", Font.PLAIN, 11));
        mainPanel.add(hint, BorderLayout.SOUTH);

        int boardWidth = Board.WIDTH * 30;
        int boardHeight = Board.HEIGHT * 30;
        int infoWidth = 200;
        int fullWidth = boardWidth + infoWidth;
        int fullHeight = boardHeight;
        mainPanel.setPreferredSize(new Dimension(fullWidth, fullHeight));

        setContentPane(mainPanel);

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (showingLeaderboard) {
                    if (e.getKeyCode() == KeyEvent.VK_ESCAPE || e.getKeyCode() == KeyEvent.VK_ENTER) {
                        hideLeaderboard();
                    }
                    return;
                }
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_UP:
                        selectedIndex = (selectedIndex - 1 + menuItems.length) % menuItems.length;
                        updateMenuLabels();
                        break;
                    case KeyEvent.VK_DOWN:
                        selectedIndex = (selectedIndex + 1) % menuItems.length;
                        updateMenuLabels();
                        break;
                    case KeyEvent.VK_LEFT:
                        if (menuItems[selectedIndex].equals("Difficulty")) {
                            difficultyIndex = (difficultyIndex - 1 + difficulties.length) % difficulties.length;
                            updateMenuLabels();
                        }
                        break;
                    case KeyEvent.VK_RIGHT:
                        if (menuItems[selectedIndex].equals("Difficulty")) {
                            difficultyIndex = (difficultyIndex + 1) % difficulties.length;
                            updateMenuLabels();
                        }
                        break;
                    case KeyEvent.VK_ENTER:
                        handleSelection();
                        break;
                }
            }
        });

        setFocusable(true);
        requestFocusInWindow();
    }

    private void updateMenuLabels() {
        for (int i = 0; i < menuItems.length; i++) {
            String text = menuItems[i];
            if ("Difficulty".equals(text)) {
                text = "Difficulty: " + difficulties[difficultyIndex];
            }
            if (i == selectedIndex) {
                menuLabels[i].setText("> " + text + " <");
                menuLabels[i].setForeground(Color.WHITE);
                menuLabels[i].setFont(new Font("Arial", Font.BOLD, 20));
            } else {
                menuLabels[i].setText(text);
                menuLabels[i].setForeground(Color.LIGHT_GRAY);
                menuLabels[i].setFont(new Font("Arial", Font.PLAIN, 18));
            }
        }
    }

    private void handleSelection() {
        String selected = menuItems[selectedIndex];
        if ("New Game".equals(selected)) {
            startNewGame();
        } else if ("Resume".equals(selected)) {
            String playerName = System.getProperty("tetris.playerName");
            DatabaseManager.SavedGameState state = DatabaseManager.loadGameState(playerName);
            if (state == null) {
                JOptionPane.showMessageDialog(this, "No saved game found.", "Resume", JOptionPane.INFORMATION_MESSAGE);
            } else {
                SwingUtilities.invokeLater(() -> {
                    TetrisGame game = new TetrisGame(state);
                    game.setVisible(true);
                });
                dispose();
            }
        } else if ("Leaderboard".equals(selected)) {
            showLeaderboard();
        } else if ("Quit".equals(selected)) {
            System.exit(0);
        }
    }

    private void showLeaderboard() {
        java.util.List<Leaderboard.Entry> entries = Leaderboard.getInstance().getEntries();
        if (entries.isEmpty()) {
            JOptionPane.showMessageDialog(this, "No scores yet.", "Leaderboard", JOptionPane.INFORMATION_MESSAGE);
            return;
        }
        showingLeaderboard = true;

        leaderboardPanel = new JPanel(new BorderLayout());
        leaderboardPanel.setOpaque(false);

        JPanel inner = new JPanel(new BorderLayout());
        inner.setBackground(Color.BLACK);
        inner.setBorder(BorderFactory.createEmptyBorder(30, 60, 30, 60));

        JLabel title = new JLabel("LEADERBOARD", SwingConstants.CENTER);
        title.setForeground(Color.WHITE);
        title.setFont(new Font("Arial", Font.BOLD, 26));
        JPanel titleWrapper = new JPanel(new BorderLayout());
        titleWrapper.setOpaque(false);
        titleWrapper.setBorder(BorderFactory.createEmptyBorder(0, 0, 20, 0));
        titleWrapper.add(title, BorderLayout.CENTER);
        inner.add(titleWrapper, BorderLayout.NORTH);

        JPanel listPanel = new JPanel();
        listPanel.setOpaque(false);
        listPanel.setLayout(new BoxLayout(listPanel, BoxLayout.Y_AXIS));

        int rank = 1;
        for (Leaderboard.Entry e : entries) {
            String line = String.format("%d. %s - %d (%s)", rank, e.name, e.score, e.difficulty);
            JLabel lbl = new JLabel(line, SwingConstants.LEFT);
            lbl.setForeground(Color.WHITE);
            lbl.setFont(new Font("Arial", Font.PLAIN, 18));
            lbl.setAlignmentX(Component.LEFT_ALIGNMENT);
            listPanel.add(lbl);
            listPanel.add(Box.createVerticalStrut(10));
            rank++;
        }

        JScrollPane scrollPane = new JScrollPane(listPanel);
        scrollPane.setBorder(null);
        scrollPane.getViewport().setBackground(Color.BLACK);
        inner.add(scrollPane, BorderLayout.CENTER);

        leaderboardPanel.add(inner, BorderLayout.CENTER);

        hint.setText("Press ESC or Enter to return to menu");

        mainPanel.remove(centerWrapper);
        mainPanel.add(leaderboardPanel, BorderLayout.CENTER);
        mainPanel.revalidate();
        mainPanel.repaint();
    }

    private void hideLeaderboard() {
        if (!showingLeaderboard) return;
        showingLeaderboard = false;
        mainPanel.remove(leaderboardPanel);
        mainPanel.add(centerWrapper, BorderLayout.CENTER);
        hint.setText("Use ↑/↓ to move, ←/→ to change difficulty, Enter to select");
        mainPanel.revalidate();
        mainPanel.repaint();
    }

    private void startNewGame() {
        String difficulty = difficulties[difficultyIndex];
        String playerName = System.getProperty("tetris.playerName");
        DatabaseManager.deleteGameState(playerName);
        SwingUtilities.invokeLater(() -> {
            TetrisGame game = new TetrisGame();
            game.setDifficulty(difficulty);
            game.setVisible(true);
        });
        dispose();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MainMenu menu = new MainMenu();
            menu.setVisible(true);
        });
    }
}

