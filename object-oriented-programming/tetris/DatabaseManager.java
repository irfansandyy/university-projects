import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseManager {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/tetris?serverTimezone=UTC&useSSL=false";
    private static final String DB_USER = "root";
    private static final String DB_PASS = "";

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        initialize();
    }

    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
    }

    private static void initialize() {
        try (Connection conn = getConnection(); Statement st = conn.createStatement()) {
            st.executeUpdate(
                "CREATE TABLE IF NOT EXISTS users (" +
                "id INT AUTO_INCREMENT PRIMARY KEY," +
                "username VARCHAR(100) UNIQUE NOT NULL," +
                "password VARCHAR(255) NOT NULL" +
                ")"
            );

            st.executeUpdate(
                "CREATE TABLE IF NOT EXISTS highscores (" +
                "id INT AUTO_INCREMENT PRIMARY KEY," +
                "username VARCHAR(100) NOT NULL," +
                "difficulty VARCHAR(20) NOT NULL," +
                "score INT NOT NULL," +
                "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP" +
                ")"
            );

            st.executeUpdate(
                "CREATE TABLE IF NOT EXISTS game_state (" +
                "username VARCHAR(100) PRIMARY KEY," +
                "difficulty VARCHAR(20) NOT NULL," +
                "score INT NOT NULL," +
                "level INT NOT NULL," +
                "lines_cleared INT NOT NULL," +
                "board TEXT NOT NULL," +
                "current_piece_type INT NOT NULL," +
                "current_piece_x INT NOT NULL," +
                "current_piece_y INT NOT NULL," +
                "next_pieces TEXT NOT NULL" +
                ")"
            );
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean validateUser(String username, String password) {
        if (username == null || username.trim().isEmpty() || password == null) {
            return false;
        }
        username = username.trim();
        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement("SELECT password FROM users WHERE username = ?")) {
            ps.setString(1, username);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    String stored = rs.getString(1);
                    return stored.equals(password);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public static boolean registerUser(String username, String password) {
        if (username == null || username.trim().isEmpty() || password == null) {
            return false;
        }
        username = username.trim();
        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement("INSERT INTO users(username, password) VALUES(?, ?)")) {
            ps.setString(1, username);
            ps.setString(2, password);
            ps.executeUpdate();
            return true;
        } catch (SQLException e) {
            if ("23000".equals(e.getSQLState())) {
                return false;
            }
            e.printStackTrace();
            return false;
        }
    }

    public static void addHighscore(String username, String difficulty, int score) {
        if (username == null || username.trim().isEmpty()) {
            username = "Player";
        }
        if (difficulty == null || difficulty.trim().isEmpty()) {
            difficulty = "MEDIUM";
        }
        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement(
                "INSERT INTO highscores(username, difficulty, score) VALUES(?,?,?)")) {
            ps.setString(1, username.trim());
            ps.setString(2, difficulty.toUpperCase());
            ps.setInt(3, score);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static int getHighestScore() {
        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement(
                 "SELECT MAX(score) FROM highscores")) {
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    public static List<Leaderboard.Entry> getTopHighscores(int limit) {
        List<Leaderboard.Entry> list = new ArrayList<>();
        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement(
                 "SELECT username, score, difficulty FROM highscores ORDER BY score DESC, created_at ASC LIMIT ?")) {
            ps.setInt(1, limit);
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    String user = rs.getString("username");
                    int score = rs.getInt("score");
                    String difficulty = rs.getString("difficulty");
                    list.add(new Leaderboard.Entry(user, score, difficulty));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    public static void saveGameState(String username, SavedGameState state) {
        if (username == null || username.trim().isEmpty() || state == null) {
            return;
        }
        username = username.trim();
        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement(
                 "REPLACE INTO game_state(" +
                     "username, difficulty, score, level, lines_cleared, board, " +
                     "current_piece_type, current_piece_x, current_piece_y, next_pieces" +
                 ") VALUES(?,?,?,?,?,?,?,?,?,?)")) {
            ps.setString(1, username);
            ps.setString(2, state.difficulty);
            ps.setInt(3, state.score);
            ps.setInt(4, state.level);
            ps.setInt(5, state.linesCleared);
            ps.setString(6, state.boardData);
            ps.setInt(7, state.currentPieceType);
            ps.setInt(8, state.currentPieceX);
            ps.setInt(9, state.currentPieceY);
            ps.setString(10, state.nextPiecesData);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static SavedGameState loadGameState(String username) {
        if (username == null || username.trim().isEmpty()) {
            return null;
        }
        username = username.trim();
        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement(
                 "SELECT difficulty, score, level, lines_cleared, board, " +
                     "current_piece_type, current_piece_x, current_piece_y, next_pieces " +
                 "FROM game_state WHERE username = ?")) {
            ps.setString(1, username);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    SavedGameState state = new SavedGameState();
                    state.username = username;
                    state.difficulty = rs.getString("difficulty");
                    state.score = rs.getInt("score");
                    state.level = rs.getInt("level");
                    state.linesCleared = rs.getInt("lines_cleared");
                    state.boardData = rs.getString("board");
                    state.currentPieceType = rs.getInt("current_piece_type");
                    state.currentPieceX = rs.getInt("current_piece_x");
                    state.currentPieceY = rs.getInt("current_piece_y");
                    state.nextPiecesData = rs.getString("next_pieces");
                    return state;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void deleteGameState(String username) {
        if (username == null || username.trim().isEmpty()) {
            return;
        }
        username = username.trim();
        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement("DELETE FROM game_state WHERE username = ?")) {
            ps.setString(1, username);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static class SavedGameState {
        public String username;
        public String difficulty;
        public int score;
        public int level;
        public int linesCleared;
        public String boardData;
        public int currentPieceType;
        public int currentPieceX;
        public int currentPieceY;
        public String nextPiecesData;
    }
}
