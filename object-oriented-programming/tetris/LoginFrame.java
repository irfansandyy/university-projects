import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class LoginFrame extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private Color[] tetrominoColors = {
        new Color(0, 240, 240),
        new Color(240, 240, 0),
        new Color(160, 0, 240),
        new Color(240, 160, 0),
        new Color(0, 0, 240),
        new Color(0, 240, 0),
        new Color(240, 0, 0)
    };

    public LoginFrame() {
        setTitle("Tetris Login");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);

        initUI();

        pack();
        setLocationRelativeTo(null);
    }

    private void initUI() {
        JPanel mainPanel = new JPanel(new BorderLayout()) {
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
        mainPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

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
                    // T
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
                    // E
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
                    // T
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
                    // R
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
                    // I
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
                    // S
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

                int offsetX = 0;
                for (int letterIndex = 0; letterIndex < letters.length; letterIndex++) {
                    int[][] letter = letters[letterIndex];
                    Color letterColor = tetrominoColors[letterIndex % tetrominoColors.length];
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

        JPanel formPanel = new JPanel(new GridBagLayout());
        formPanel.setOpaque(false);
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(8, 8, 8, 8);
        gbc.fill = GridBagConstraints.HORIZONTAL;

        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);

        Color fieldBg = new Color(20, 20, 20, 220);
        Color fieldFg = Color.WHITE;
        usernameField.setBackground(fieldBg);
        usernameField.setForeground(fieldFg);
        usernameField.setCaretColor(Color.WHITE);
        passwordField.setBackground(fieldBg);
        passwordField.setForeground(fieldFg);
        passwordField.setCaretColor(Color.WHITE);

        JLabel userLabel = new JLabel("Username:");
        userLabel.setForeground(Color.WHITE);
        JLabel passLabel = new JLabel("Password:");
        passLabel.setForeground(Color.WHITE);

        JButton loginButton = new JButton("PLAY");
        loginButton.setFocusPainted(false);
        loginButton.setForeground(Color.WHITE);
        loginButton.setBackground(new Color(0, 120, 215));
        loginButton.setBorder(BorderFactory.createCompoundBorder(
            BorderFactory.createLineBorder(Color.WHITE),
            BorderFactory.createEmptyBorder(5, 20, 5, 20)
        ));
        loginButton.setFont(new Font("Arial", Font.BOLD, 14));
        loginButton.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));

        JButton registerButton = new JButton("Register");
        registerButton.setFocusPainted(false);
        registerButton.setForeground(Color.LIGHT_GRAY);
        registerButton.setContentAreaFilled(false);
        registerButton.setBorder(BorderFactory.createEmptyBorder(2, 2, 2, 2));
        registerButton.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 1;
        gbc.weightx = 1;
        gbc.anchor = GridBagConstraints.WEST;
        formPanel.add(userLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        formPanel.add(usernameField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.fill = GridBagConstraints.NONE;
        formPanel.add(passLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        formPanel.add(passwordField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.gridwidth = 1;
        gbc.weightx = 0;
        gbc.anchor = GridBagConstraints.CENTER;
        gbc.fill = GridBagConstraints.NONE;
        formPanel.add(loginButton, gbc);

        gbc.gridx = 0;
        gbc.gridy = 5;
        gbc.anchor = GridBagConstraints.CENTER;
        formPanel.add(registerButton, gbc);

        mainPanel.add(formPanel, BorderLayout.CENTER);

        JLabel hintLabel = new JLabel("Enter your account or register a new one", SwingConstants.CENTER);
        hintLabel.setForeground(Color.LIGHT_GRAY);
        hintLabel.setFont(new Font("Arial", Font.PLAIN, 11));
        mainPanel.add(hintLabel, BorderLayout.SOUTH);

        int boardWidth = Board.WIDTH * 30;
        int boardHeight = Board.HEIGHT * 30;
        int infoWidth = 200;
        int fullWidth = boardWidth + infoWidth;
        int fullHeight = boardHeight;
        mainPanel.setPreferredSize(new Dimension(fullWidth, fullHeight));

        setContentPane(mainPanel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                handleLogin();
            }
        });

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                SwingUtilities.invokeLater(() -> {
                    new RegisterFrame().setVisible(true);
                });
                dispose();
            }
        });

        KeyAdapter enterKeyAdapter = new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    handleLogin();
                }
            }
        };
        usernameField.addKeyListener(enterKeyAdapter);
        passwordField.addKeyListener(enterKeyAdapter);
    }

    private void handleLogin() {
        String username = usernameField.getText().trim();
        String password = new String(passwordField.getPassword());

        if (!username.isEmpty() && DatabaseManager.validateUser(username, password)) {
            System.setProperty("tetris.playerName", username);
            SwingUtilities.invokeLater(() -> {
                MainMenu menu = new MainMenu();
                menu.setVisible(true);
            });
            dispose();
        } else {
            JOptionPane.showMessageDialog(
                this,
                "Invalid username or password",
                "Login Failed",
                JOptionPane.ERROR_MESSAGE
            );
        }
    }
}