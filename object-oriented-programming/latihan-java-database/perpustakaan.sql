DROP DATABASE IF EXISTS perpustakaan;

CREATE DATABASE perpustakaan DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;

USE `perpustakaan`;

CREATE TABLE `buku` ( 
    `id_buku` INT NOT NULL AUTO_INCREMENT , 
    `judul` VARCHAR(45) NOT NULL , 
    `pengarang` VARCHAR(45) NOT NULL , 
    PRIMARY KEY (`id_buku`)
);

INSERT INTO `buku` (`judul`, `pengarang`) 
VALUES ('Belajar Pemrograman Java dari Nol', 'Petani Kode'), ('Pemrograman Java Menggunakan Linux', 'Petani Kode');