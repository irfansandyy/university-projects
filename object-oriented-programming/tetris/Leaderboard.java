import java.util.List;

public class Leaderboard {
    private static Leaderboard instance;

    public static class Entry {
        public final String name;
        public final int score;
        public final String difficulty;

        public Entry(String name, int score, String difficulty) {
            this.name = name;
            this.score = score;
            this.difficulty = difficulty;
        }
    }

    private Leaderboard() {
    }

    public static Leaderboard getInstance() {
        if (instance == null) {
            instance = new Leaderboard();
        }
        return instance;
    }

    public synchronized void addScore(String name, int score) {
        addScore(name, score, "MEDIUM");
    }

    public synchronized void addScore(String name, int score, String difficulty) {
        DatabaseManager.addHighscore(name, difficulty, score);
    }

    public synchronized int getHighestScore() {
        return DatabaseManager.getHighestScore();
    }

    public synchronized List<Entry> getEntries() {
        return DatabaseManager.getTopHighscores(10);
    }
}
