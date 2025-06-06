-- Active: 1728911430420@@127.0.0.1@3306@modul_2_library
DROP DATABASE IF EXISTS Modul_2_Library;
CREATE DATABASE IF NOT EXISTS Modul_2_Library;
USE Modul_2_Library;

CREATE TABLE genres(
    `id` CHAR(5) NOT NULL,
    genre_name VARCHAR(50) NOT NULL,
    `description` VARCHAR(255) NOT NULL,
    CONSTRAINT PK_genres PRIMARY KEY (`id`)
);

CREATE TABLE members(
    `id` CHAR(5) NOT NULL,
    `name` VARCHAR(50) NOT NULL,
    email VARCHAR(50) NOT NULL,
    gender CHAR(1) NOT NULL,
    `address` VARCHAR(100) NOT NULL,
    CONSTRAINT PK_members PRIMARY KEY (`id`)
);

CREATE TABLE positions (
    `id` CHAR(5) NOT NULL,
    position_name VARCHAR(50) NOT NULL,
    admin_access BOOLEAN NOT NULL,
    CONSTRAINT PK_positions PRIMARY KEY (`id`)
);

CREATE TABLE employees (
    `id` CHAR(5) NOT NULL,
    `name` VARCHAR(50) NOT NULL,
    email VARCHAR(50) NOT NULL,
    gender CHAR(1) NOT NULL,
    `address` VARCHAR(100) NOT NULL,
    position_id CHAR(5) NOT NULL,
    CONSTRAINT PK_employees PRIMARY KEY (`id`),
    CONSTRAINT FK_employees_positions 
    FOREIGN KEY (position_id) REFERENCES positions(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE books (
    `id` CHAR(5) NOT NULL,
    isbn CHAR(13) NOT NULL,
    title VARCHAR(100) NOT NULL,
    author_name VARCHAR(50) NOT NULL,
    year_published YEAR NOT NULL,
    synopsis VARCHAR(255) NOT NULL,
    stock INT NOT NULL,
    genre_id CHAR(5) NOT NULL,
    CONSTRAINT PK_books PRIMARY KEY (`id`),
    CONSTRAINT FK_books_genres
    FOREIGN KEY (genre_id) REFERENCES genres(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE phone_numbers (
    phone_number VARCHAR(13) NOT NULL,
    member_id CHAR(5) NOT NULL,
    employee_id CHAR(5) NOT NULL,
    CONSTRAINT PK_phone_numbers PRIMARY KEY (phone_number),
    CONSTRAINT FK_phone_members
    FOREIGN KEY (member_id) REFERENCES members(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT FK_phone_employees
    FOREIGN KEY (employee_id) REFERENCES employees(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE borrows (
    `id` CHAR(5) NOT NULL,
    borrow_date DATE NOT NULL,
    return_date DATE NULL,
    due_date DATE NOT NULL,
    fine DECIMAL(10, 2) NULL,
    member_id CHAR(5) NOT NULL,
    employee_id CHAR(5) NOT NULL,
    CONSTRAINT PK_borrows PRIMARY KEY (`id`),
    CONSTRAINT FK_borrows_members
    FOREIGN KEY (member_id) REFERENCES members(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT FK_borrows_employees
    FOREIGN KEY (employee_id) REFERENCES employees(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE books_borrows (
    book_id CHAR(5) NOT NULL,
    borrow_id CHAR(5) NOT NULL,
    CONSTRAINT PK_books_borrows PRIMARY KEY (book_id, borrow_id),
    CONSTRAINT FK_books_borrows_books
    FOREIGN KEY (book_id) REFERENCES books(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT FK_books_borrows_borrows
    FOREIGN KEY (borrow_id) REFERENCES borrows(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE
);

-- Q2
ALTER TABLE books
DROP author_name;

CREATE TABLE authors (
    `id` CHAR(5) NOT NULL,
    author_name VARCHAR(50) NOT NULL,
    nationality VARCHAR(30) NOT NULL,
    birthdate DATE NOT NULL,
    CONSTRAINT PK_authors PRIMARY KEY (`id`)
);

CREATE TABLE publishers (
    `id` CHAR(5) NOT NULL,
    `name` VARCHAR(50) NOT NULL,
    `address` VARCHAR(100) NOT NULL,
    country VARCHAR(30) NOT NULL,
    email VARCHAR(50) NOT NULL,
    CONSTRAINT PK_publishers PRIMARY KEY (`id`)
);

ALTER TABLE books
ADD author_id CHAR(5) NOT NULL,
ADD publisher_id CHAR(5) NOT NULL,
ADD CONSTRAINT FK_books_authors
FOREIGN KEY (author_id) REFERENCES authors(`id`)
ON DELETE CASCADE ON UPDATE CASCADE,
ADD CONSTRAINT FK_books_publishers
FOREIGN KEY (publisher_id) REFERENCES publishers(`id`)
ON DELETE CASCADE ON UPDATE CASCADE;

-- Q3
ALTER TABLE phone_numbers
DROP CONSTRAINT FK_phone_members,
DROP member_id;

ALTER TABLE borrows
DROP CONSTRAINT FK_borrows_members,
DROP member_id;

ALTER TABLE members
CHANGE `id` NIK CHAR(16) NOT NULL;

ALTER TABLE phone_numbers
ADD member_nik CHAR(16) NOT NULL,
ADD CONSTRAINT FK_phone_members 
FOREIGN KEY (member_nik) REFERENCES members(NIK)
ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE borrows
ADD member_nik CHAR(16) NOT NULL,
ADD CONSTRAINT FK_borrows_members
FOREIGN KEY (member_nik) REFERENCES members(NIK)
ON DELETE CASCADE ON UPDATE CASCADE;

-- Q4
DROP TABLE phone_numbers;

ALTER TABLE members
ADD phone_number VARCHAR(13) NOT NULL;

ALTER TABLE employees
ADD phone_number VARCHAR(13) NOT NULL AFTER gender;

-- Q5
INSERT INTO genres(`id`, genre_name, `description`) VALUES
('GR001', 'History', 'Books that examine specific events or eras, providing insight into the past and its impact on the present. Usually accompanied by in-depth historical data, analysis and narrative.'),
('GR002', 'Fiction', 'Imaginative stories created by writers, not based on real facts. This genre includes subgenres such as romance, fantasy, and adventure, with a focus on characters and storyline.'),
('GR003', 'Self-Development', 'Books that provide guidance to improve the quality of life or skills of the reader. Presents practical advice on topics such as motivation, time management, and personal problem solving.'),
('GR004', 'Biography', 'Tells a person\'s life in detail from birth to the end of his life or now. Compiled based on facts, this story describes the character\'s experiences, struggles and achievements.'),
('GR005', 'Reference', 'Books that function as complete reference sources, such as dictionaries, encyclopedias, or handbooks. Contains data, definitions or concepts that can be accessed as needed, without having to be read sequentially.');

INSERT INTO authors(`id`, author_name, nationality, birthdate) VALUES
('AU001', 'Michael Brown', 'American', '1990-3-30'),
('AU002', 'Andi Saputra', 'Indonesian', '1988-10-2'),
('AU003', 'Yuki Nakamura', 'Japanese', '1973-1-22'),
('AU004', 'Kim Min Joon', 'South Korean', '1982-4-18'),
('AU005', 'James Williams', 'British', '1962-12-4');

INSERT INTO publishers(`id`, `name`, `address`, country, email) VALUES
('PB001', 'Silver Oak Publishing', '1234 Elm Street', 'United States', 'silveroak1234@gmail.com'),
('PB002', 'Blue Sky Books', '9012 Pine Road', 'Japan', 'bluesky9012@gmail.com'),
('PB003', 'Green Leaf Press', '5678 Maple Avenue', 'Indonesia', 'greenleaf5678@gmail.com'),
('PB004', 'Golden Dragon Publishing', '3456 Bamboo Lane', 'China', 'goldendragon3456@gmail.com'),
('PB005', 'Red River Press', '7890 Cherry Blossom Drive', 'France', 'redriver7890@gmail.com');

INSERT INTO books(`id`, isbn, title, year_published, synopsis, stock, genre_id, author_id, publisher_id) VALUES
('BK001', '9780123456789', 'Jejak Peradaban: Kisah Perjalanan Sejarah Indonesia', '2010', 'Delving into Indonesian history, this book presents important events and influential figures who shaped the nation\'s civilization, bringing readers to understand the roots of Indonesian culture and identity.', 5, 'GR001', 'AU002', 'PB003'),
('BK002', '9781234567890', 'Small Steps, Big Changes: Building Positive Habits', '2005', 'Discover the power of small habits that have a big impact. This book provides practical strategies for building positive habits that can change lives and improve overall well-being.', 3, 'GR003', 'AU003', 'PB002'),
('BK003', '9782345678901', 'Complete Dictionary of Information Technology Terms', '2020', 'A complete guide to information technology terms, this book explains basic concepts to complex technical terms, making it a useful reference resource for students and professionals.', 7, 'GR005', 'AU001', 'PB001'),
('BK004', '9783456789012', 'Breaking Barriers: The Inspiring Story of Nelson Mandela', '2018', 'The extraordinary story of Nelson Mandela, a freedom fighter who overcame obstacles to fight for equality and justice. An inspiring journey of courage, sacrifice, and hope.', 2, 'GR004', 'AU005', 'PB001'),
('BK005', '9784567890123', 'Light at the End of the Road: A Story of Hope', '2024', 'In a journey full of challenges, a character finds the strength of hope and friendship. This novel invites readers to reflect on the meaning of life and the importance of believing in a better future.', 4, 'GR002', 'AU004', 'PB004');

INSERT INTO positions(`id`, position_name, admin_access) VALUES
('PS001', 'Librarian', TRUE),
('PS002', 'Cleaning', FALSE),
('PS003', 'Security', FALSE);

INSERT INTO employees(`id`, `name`, email, gender, phone_number, `address`, position_id) VALUES
('EM001', 'Andi Gading', 'andi@gmail.com', 'P', '081628492610', 'Jl. Merdeka No.10', 'PS001'),
('EM002', 'Budi Sitombing', 'budi@gmail.com', 'L', '085864927581', 'Jl. Sukun Raya No.25', 'PS003'),
('EM003', 'Jennifer Tina', 'tina@gmail.com', 'P', '089603471812', 'Jl.Pahlawan No.5', 'PS001'),
('EM004', 'Lili Sari', 'lili@gmail.com', 'P', '088385793136', 'Jl. Cendana No.8', 'PS002'),
('EM005', 'Alexander Agus', 'agus@gmail.com', 'L', '088273659814', 'Jl. Bunga No.12', 'PS001');

INSERT INTO members(NIK, `name`, email, gender, `address`, phone_number) VALUES
('3326162409040002', 'Citra Kirana', 'citra@gmail.com', 'P', 'Jl. Cinta No.45', '088374628921'),
('3525017006950028', 'Jasmine Neroli', 'jasmine@gmail.com', 'P', 'Jl. Melati No.9', '083285716164'),
('3525017006520020', 'Nico Parto', 'nico@gmail.com', 'L', 'Jl. Kenanga No.33', '089675329117'),
('3305040901072053', 'Teddy Widodo', 'teddy@gmail.com', 'L', 'Jl. Anggrek No.17', '085782306818'),
('3326161509700004', 'Beni Soeharti', 'beni@gmail.com', 'L', 'Jl. Raya No.56', '0812345678919');

INSERT INTO borrows(`id`, borrow_date, return_date, due_date, fine, member_nik, employee_id) VALUES
('BR001', '2024-5-6', '2024-5-20', '2024-5-20', NULL, '3326162409040002', 'EM004'),
('BR002', '2024-7-14', '2024-7-29', '2024-7-28', 5000.00, '3525017006950028', 'EM001'),
('BR003', '2024-9-22', '2024-10-8', '2024-10-6', 10000.00, '3525017006520020', 'EM003'),
('BR004', '2024-10-3', '2024-10-20', '2024-10-17', 15000.00, '3305040901072053', 'EM002'),
('BR005', '2024-11-2', NULL, '2024-11-16', NULL, '3326161509700004', 'EM005');

INSERT INTO books_borrows(book_id, borrow_id) VALUES
('BK001', 'BR001'),
('BK003', 'BR002'),
('BK001', 'BR002'),
('BK004', 'BR003'),
('BK005', 'BR004'),
('BK002', 'BR005');

-- Q6
DROP TABLE books_borrows;

DELETE FROM borrows WHERE 1=1; 

ALTER TABLE borrows
MODIFY `id` INT AUTO_INCREMENT NOT NULL;

CREATE TABLE books_borrows (
    book_id CHAR(5) NOT NULL,
    borrow_id INT NOT NULL,
    CONSTRAINT PK_books_borrows PRIMARY KEY (book_id, borrow_id),
    CONSTRAINT FK_books_borrows_books
    FOREIGN KEY (book_id) REFERENCES books(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT FK_books_borrows_borrows
    FOREIGN KEY (borrow_id) REFERENCES borrows(`id`)
    ON DELETE CASCADE ON UPDATE CASCADE
);

INSERT INTO borrows(borrow_date, return_date, due_date, fine, member_nik, employee_id) VALUES
('2024-5-6', '2024-5-20', '2024-5-20', NULL, '3326162409040002', 'EM004'),
('2024-7-14', '2024-7-29', '2024-7-28', 5000.00, '3525017006950028', 'EM001'),
('2024-9-22', '2024-10-8', '2024-10-6', 10000.00, '3525017006520020', 'EM003'),
('2024-10-3', '2024-10-20', '2024-10-17', 15000.00, '3305040901072053', 'EM002'),
('2024-11-2', NULL, '2024-11-16', NULL, '3326161509700004', 'EM005');

INSERT INTO books_borrows(book_id, borrow_id) VALUES
('BK001', 1),
('BK003', 2),
('BK001', 2),
('BK004', 3),
('BK005', 4),
('BK002', 5);

-- Q7
UPDATE borrows SET return_date = CURDATE() WHERE member_nik = '3326161509700004';

-- Q8
UPDATE borrows set fine = NULL WHERE member_nik IN ('3525017006520020', '3305040901072053');

-- Q9
INSERT INTO borrows(borrow_date, return_date, due_date, fine, member_nik, employee_id) VALUES
('2024-11-3', NULL, '2024-11-17', NULL, '3326161509700004', 'EM005');

UPDATE books SET stock = stock - 1 WHERE `id` = 'BK003';

INSERT INTO books_borrows(book_id, borrow_id) VALUES
('BK003', 6)

-- Q10
INSERT INTO employees(`id`, `name`, email, gender, phone_number, `address`, position_id) VALUES
('EM006', 'Aspas Gata', 'aspasgata@gmail.com', 'L', '0895323390308', 'Jl. Badut No.62', 'PS001');

-- Q11
UPDATE employees SET `name` = 'Andi Haki', gender = 'L', phone_number = '081628492611' WHERE `id` = 'EM001';

-- Q12
DELETE FROM members WHERE NIK = '3525017006950028';
DELETE FROM employees WHERE `id` = 'EM006';