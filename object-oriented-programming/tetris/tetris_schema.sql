CREATE DATABASE IF NOT EXISTS tetris CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE tetris;

CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(100) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS highscores (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(100) NOT NULL,
    difficulty VARCHAR(20) NOT NULL,
    score INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS game_state (
    username VARCHAR(100) PRIMARY KEY,
    difficulty VARCHAR(20) NOT NULL,
    score INT NOT NULL,
    level INT NOT NULL,
    lines_cleared INT NOT NULL,
    board TEXT NOT NULL,
    current_piece_type INT NOT NULL,
    current_piece_x INT NOT NULL,
    current_piece_y INT NOT NULL,
    next_pieces TEXT NOT NULL
);
