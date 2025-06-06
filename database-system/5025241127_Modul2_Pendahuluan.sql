DROP DATABASE IF EXISTS 5025241127_Sandy_Modul2_Pendahuluan;
CREATE DATABASE 5025241127_Sandy_Modul2_Pendahuluan;
USE 5025241127_Sandy_Modul2_Pendahuluan;

CREATE TABLE Author(
    Author_ID CHAR(5) NOT NULL, -- DI DATASET PANJANGNYA 5
    Author_Name VARCHAR(100) NOT NULL, 
    Author_Nationality VARCHAR(100) NOT NULL,
    Author_BirthDate DATE NOT NULL,
    PRIMARY KEY (Author_ID)
);

CREATE TABLE Shelf(
    Shelf_ID CHAR(5) NOT NULL, -- DI DATASET PANJANGNYA 5 (CHAR(6) -> CHAR(5))
    Shelf_Capacity INT NOT NULL,
    Shelf_Floor INT NOT NULL,
    PRIMARY KEY (Shelf_ID)
);

CREATE TABLE Employee(
    Employee_ID CHAR(5) NOT NULL, -- DI DATASET PANJANGNYA 5 (CHAR(16) -> CHAR(5))
    Employee_Name VARCHAR(100) NOT NULL, 
    Employee_Email VARCHAR(100) NOT NULL,
    Employee_Phone VARCHAR(15) NOT NULL, -- DI DATASET KALO INT NANTI OVERFLOW (INT -> VARCHAR(15))
    PRIMARY KEY (Employee_ID)
);

CREATE TABLE `Member`(
    Member_ID CHAR(4) NOT NULL, -- DI DATASET PANJANGNYA 4 (CHAR(7) -> CHAR(4))
    Member_Name VARCHAR(100) NOT NULL,
    Member_Address VARCHAR(100) NULL, -- DI DATASET GAK DIPAKE (NOT NULL -> NULL)
    Member_PhoneNum INT NULL, -- DI DATASET GAK DIPAKE (NOT NULL -> NULL)
    Member_Email VARCHAR(100) NOT NULL,
    Member_Creation_Date DATE NOT NULL, -- DI DATASET CUMA ADA DATE (TIMESTAMP -> DATE)
    Member_Expired_Date DATE NOT NULL, -- DI DATASET CUMA ADA DATE (TIMESTAMP -> DATE)
    PRIMARY KEY (Member_ID)
);

CREATE TABLE Book(
    Book_ID CHAR(5) NOT NULL, -- DI DATASET PANJANGNYA 5 (CHAR(6) -> CHAR(5))
    Book_Title VARCHAR(50) NOT NULL, 
    Book_Author VARCHAR(100) NULL, -- DI DATASET PAKE TABEL BARU MANY TO MANY (NOT NULL -> NULL)
    Book_Genre VARCHAR(20) NOT NULL,
    Book_Release DATE NOT NULL,
    Book_Shelf_ID CHAR(5) NULL, -- DI DATASET PANJANGNYA 5 (CHAR(7) -> CHAR(5))
    PRIMARY KEY (Book_ID),
    FOREIGN KEY (Book_Shelf_ID) REFERENCES Shelf(Shelf_ID)
);

CREATE TABLE Loan(
    Loan_ID CHAR(4) NOT NULL, -- DI DATASET ADA CHARNYA (INT -> CHAR(4))
    Loan_Date DATE NOT NULL,
    Loan_Return_Date DATE NULL, -- DI DATASET ADA YANG NULL (NOT NULL -> NULL)
    Loan_Due_Date DATE NOT NULL,
    Loan_Fine INT NULL,
    Member_Member_ID CHAR(4) NOT NULL, -- DI DATASET PANJANGNYA 4 (CHAR(7) -> CHAR(4))
    Book_Book_ID CHAR(5) NOT NULL, -- DI DATASET PANJANGNYA 5 (CHAR(13) -> CHAR(5))
    PRIMARY KEY (Loan_ID),
    FOREIGN KEY (Member_Member_ID) REFERENCES `Member`(Member_ID),
    FOREIGN KEY (Book_Book_ID) REFERENCES Book(Book_ID)
);

CREATE TABLE Author_Book(
    Author_Author_ID CHAR(5) NOT NULL, -- DI DATASET PANJANGNYA 4 (INT -> CHAR(5))
    Book_Book_ID CHAR(5) NOT NULL, -- DI DATASET PANJANGNYA 5 (CHAR(7) -> CHAR(5))
    PRIMARY KEY (Author_Author_ID, Book_Book_ID),
    FOREIGN KEY (Author_Author_ID) REFERENCES Author(Author_ID),
    FOREIGN KEY (Book_Book_ID) REFERENCES Book(Book_ID)
);

-- DI PDM SEBENARNYA TIDAK ADA TAPI DI DATASET ADA
CREATE TABLE Publisher(
    Publisher_ID CHAR(5) NOT NULL,
    Publisher_Name VARCHAR(100) NOT NULL,
    Publisher_Address VARCHAR(100) NOT NULL,
    Publisher_Country VARCHAR(10) NOT NULL,
    Publisher_Email VARCHAR(100) NOT NULL,
    PRIMARY KEY (Publisher_ID)
);

INSERT INTO Author (Author_ID, Author_Name, Author_Nationality, Author_BirthDate) VALUES
('AU001', 'John Doe', 'American', '1970-05-12'),
('AU002', 'Jane Smith', 'British', '1985-07-24'),
('AU003', 'Robert Johnson', 'American', '1962-10-02'),
('AU004', 'Emily Zhang', 'Chinese', '1980-03-17'),
('AU005', 'Alice Nguyen', 'Vietnamese', '1992-11-29');

INSERT INTO Shelf (Shelf_ID, Shelf_Capacity, Shelf_Floor) VALUES
('SH001', 15, 1),
('SH002', 5, 1),
('SH003', 8, 2),
('SH004', 10, 2),
('SH005', 20, 3);

INSERT INTO Employee (Employee_ID, Employee_Name, Employee_Email, Employee_Phone) VALUES
('FT001', 'Sarah Connor', 'sarah@library.org', '1234567890'),
('FT002', 'Tom Watson', 'tom@library.org', '9876543210'),
('PT003', 'Nancy Drew', 'nancy@gmail.com', '5678901234'),
('PT004', 'James Bond', 'james@library.org', '4561237890'),
('FT005', 'Laura Croft', 'laura@library.org', '6789012345');

INSERT INTO `Member` (Member_ID, Member_Name, Member_Email, Member_Creation_Date, Member_Expired_Date) VALUES
('M001', 'Alice Peterson', 'alice@gmail.com', '2022-02-15', '2023-02-15'),
('M002', 'Bob Smith', 'bob@library.org', '2023-01-05', '2024-01-05'),
('M003', 'Charlie Brown', 'charlie@gmail.com', '2023-03-20', '2024-03-20'),
('M004', 'Diane Lewis', 'diane@library.org', '2023-11-01', '2024-11-01'),
('M005', 'Eve Johnson', 'eve@gmail.com', '2021-10-15', '2022-10-15');

INSERT INTO Book (Book_ID, Book_Title, Book_Genre, Book_Release, Book_Shelf_ID) VALUES
('BK001', 'The Great Adventure', 'Fiction', '2019-04-10', 'SH001'),
('BK002', 'The World of Science', 'Science', '2020-06-15', 'SH002'),
('BK003', 'American History Explained', 'History', '2018-02-20', 'SH003'),
('BK004', 'Understanding the Cosmos', 'Science', '2021-09-11', 'SH004'),
('BK005', 'Mystery of the Old Castle', 'Fiction', '2022-01-05', 'SH005');

INSERT INTO Loan (Loan_ID, Loan_Date, Loan_Return_Date, Loan_Due_Date, Loan_Fine, Member_Member_ID, Book_Book_ID) VALUES
('L001', '2023-01-10', '2023-01-20', '2023-01-15', 5000, 'M001', 'BK001'),
('L002', '2023-05-12', '2023-05-22', '2023-05-15', 20000, 'M002', 'BK002'),
('L003', '2023-08-15', '2023-08-25', '2023-08-18', 10000, 'M003', 'BK003'),
('L004', '2023-11-01', '2023-11-05', '2023-11-03', 15000, 'M004', 'BK004'),
('L005', '2023-12-10', NULL, '2023-12-17', NULL, 'M005', 'BK005');

INSERT INTO Author_Book (Author_Author_ID, Book_Book_ID) VALUES
('AU001', 'BK001'),
('AU002', 'BK002'),
('AU003', 'BK003'),
('AU004', 'BK004'),
('AU005', 'BK005');

INSERT INTO Publisher (Publisher_ID, Publisher_Name, Publisher_Address, Publisher_Country, Publisher_Email) VALUES
('PB001', 'Penguin Books', '123 Main St', 'USA', 'contact@penguin.com'),
('PB002', 'HarperCollins', '456 Oak Ave', 'UK', 'support@harpercollins.com'),
('PB003', 'Quanta Publishing', '789 Maple Rd', 'Australia', 'info@quanta.com'),
('PB004', 'Scholastic', '101 Pine Dr', 'Canada', 'inquiries@scholastic.com'),
('PB005', 'Random House', '202 Birch Ln', 'USA', 'service@randomhouse.com');

-- Query Problem 1
ALTER TABLE Book
ADD Book_Status VARCHAR(15) NOT NULL;

UPDATE Book SET Book_Status = "Available" WHERE 1=1;

-- Query Problem 2
ALTER TABLE Employee
ADD Employee_Status VARCHAR(15) NOT NULL;

UPDATE Employee SET Employee_Status = "full-time" WHERE Employee_ID LIKE "FT%";
UPDATE Employee SET Employee_Status = "part-time" WHERE Employee_ID LIKE "PT%";
SELECT * FROM Employee;

-- Query Problem 3
SELECT bo.Book_ID, bo.Book_Title, au.Author_Name, bo.Book_Genre, bo.Book_Release, bo.Book_Shelf_ID  
FROM Author_Book ab
INNER JOIN Author au ON (ab.Author_Author_ID = au.Author_ID)
INNER JOIN Book bo ON (ab.Book_Book_ID = bo.Book_ID)
WHERE au.Author_Nationality = "American";

-- Query Problem 4
UPDATE Loan SET Loan_Fine = 20000 WHERE Loan_Due_Date - Loan_Return_Date < -5;
SELECT * FROM LOAN;

-- Query Problem 5
SELECT * FROM `Member` WHERE YEAR(Member_Creation_Date) = 2023;

-- Query Problem 6
ALTER TABLE `Member`
ADD Member_Status VARCHAR(15) NOT NULL;

UPDATE `Member` SET Member_Status = "Active" WHERE 1=1;
UPDATE `Member` SET Member_Status = "Inactive" WHERE Member_Expired_Date < CURDATE();

-- Query Problem 7
SELECT au.Author_Name
FROM Author_Book ab
INNER JOIN Author au ON (ab.Author_Author_ID = au.Author_ID)
INNER JOIN Book bo ON (ab.Book_Book_ID = bo.Book_ID)
INNER JOIN Shelf sh ON (bo.Book_Shelf_ID = sh.Shelf_ID)
WHERE sh.Shelf_Capacity <= 10;

-- Query Problem 8
SELECT bo.Book_ID, bo.Book_Title, bo.Book_Genre, bo.Book_Release, bo.Book_Shelf_ID
FROM Book bo
INNER JOIN Loan lo ON (bo.Book_ID = lo.Book_Book_ID)
GROUP BY Book_ID
ORDER BY COUNT(*) DESC
LIMIT 3;

-- Query Problem 9
SELECT * FROM Employee WHERE Employee_Email LIKE "%@library.org";

-- Query Problem 10
SELECT bo.Book_ID, bo.Book_Title, bo.Book_Genre, bo.Book_Release, bo.Book_Shelf_ID
FROM Book bo
INNER JOIN Shelf sh ON (bo.Book_Shelf_ID = sh.Shelf_ID)
WHERE sh.Shelf_Floor = 2;