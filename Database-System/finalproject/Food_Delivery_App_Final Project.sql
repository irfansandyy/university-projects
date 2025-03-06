DROP DATABASE IF EXISTS FoodDelivery

CREATE DATABASE IF NOT EXISTS FoodDelivery;

USe FoodDelivery;

-- DDL 1
CREATE TABLE Customer (
    CustomerID char(10)  NOT NULL,
    Name varchar(255)  NOT NULL,
    Gender char(1)  NULL,
    Email varchar(255)  NOT NULL,
    Phone varchar(15)  NOT NULL,
    MembershipStartDate datetime  NULL,
    MembershipEndDate datetime  NULL,
    Balance decimal(15,2)  NOT NULL,
    Status varchar(255)  NOT NULL,
    Points int  NOT NULL,
    CONSTRAINT Customer_pk PRIMARY KEY (CustomerID)
);

CREATE TABLE CustomerAddress (
    AddressID char(10)  NOT NULL,
    Province varchar(255)  NOT NULL,
    City varchar(255)  NOT NULL,
    PostalCode char(5)  NOT NULL,
    Address varchar(255)  NOT NULL,
    Location varchar(255)  NOT NULL,
    CustomerID char(10)  NOT NULL,
    CONSTRAINT CustomerAddress_pk PRIMARY KEY (AddressID)
);

CREATE TABLE Driver (
    DriverID char(10)  NOT NULL,
    Name varchar(255)  NOT NULL,
    Gender char(1)  NULL,
    Email varchar(255)  NOT NULL,
    Phone varchar(15)  NOT NULL,
    LicensePlate varchar(10)  NOT NULL,
    VehicleType varchar(255)  NOT NULL,
    Rating decimal(3,2)  NULL,
    Status varchar(255)  NOT NULL,
    Location varchar(255)  NOT NULL,
    CONSTRAINT Driver_pk PRIMARY KEY (DriverID)
);

CREATE TABLE FoodMenu (
    FoodID char(10)  NOT NULL,
    Name varchar(255)  NOT NULL,
    Description varchar(255)  NOT NULL,
    Category varchar(100)  NOT NULL,
    Price decimal(10,2)  NOT NULL,
    Available boolean  NOT NULL,
    RestaurantID char(10)  NOT NULL,
    CONSTRAINT FoodMenu_pk PRIMARY KEY (FoodID)
);

CREATE TABLE FoodOrder (
    FoodID char(10)  NOT NULL,
    OrderID char(10)  NOT NULL,
    Quantity int  NOT NULL,
    SubTotal decimal(10,2)  NOT NULL,
    Notes varchar(255)  NULL,
    CONSTRAINT FoodOrder_pk PRIMARY KEY (FoodID,OrderID)
);

CREATE TABLE OrderAddress (
    AddressID char(10)  NOT NULL,
    Province varchar(255)  NOT NULL,
    City varchar(255)  NOT NULL,
    PostalCode char(5)  NOT NULL,
    Address varchar(255)  NOT NULL,
    Location varchar(255)  NOT NULL,
    OrderID char(10)  NOT NULL,
    CONSTRAINT OrderAddress_pk PRIMARY KEY (AddressID)
);

CREATE TABLE Orders (
    OrderID char(10)  NOT NULL,
    OrderTime datetime  NOT NULL,
    DeliveredTime datetime  NULL,
    TotalPrice decimal(10,2)  NOT NULL,
    PaymentMethod varchar(255)  NOT NULL,
    Notes varchar(255)  NULL,
    Status varchar(255)  NOT NULL,
    DriverID char(10)  NOT NULL,
    CustomerID char(10)  NOT NULL,
    CONSTRAINT Orders_pk PRIMARY KEY (OrderID)
);

CREATE TABLE Restaurant (
    RestaurantID char(10)  NOT NULL,
    Name varchar(255)  NOT NULL,
    Email varchar(255)  NOT NULL,
    Phone varchar(15)  NOT NULL,
    OpeningTime time  NOT NULL,
    ClosingTime time  NOT NULL,
    Rating decimal(3,2)  NULL,
    Status varchar(255)  NOT NULL,
    CONSTRAINT Restaurant_pk PRIMARY KEY (RestaurantID)
);

CREATE TABLE RestaurantAddress (
    AddressID char(10)  NOT NULL,
    Province varchar(255)  NOT NULL,
    City varchar(255)  NOT NULL,
    PostalCode char(5)  NOT NULL,
    Address varchar(255)  NOT NULL,
    Location varchar(255)  NOT NULL,
    RestaurantID char(10)  NOT NULL,
    CONSTRAINT RestaurantAddress_pk PRIMARY KEY (AddressID)
);

CREATE TABLE Reviews (
    ReviewID char(10)  NOT NULL,
    ReviewTime datetime  NOT NULL,
    RestaurantRating decimal(3,2)  NULL,
    DriverRating decimal(3,2)  NULL,
    Comment varchar(255)  NULL,
    OrderID char(10)  NOT NULL,
    CONSTRAINT Reviews_pk PRIMARY KEY (ReviewID)
);

ALTER TABLE OrderAddress ADD CONSTRAINT OrderAddress_Orders FOREIGN KEY OrderAddress_Orders (OrderID)
REFERENCES Orders (OrderID);

ALTER TABLE CustomerAddress ADD CONSTRAINT CustomerAddress_Customer FOREIGN KEY CustomerAddress_Customer (CustomerID)
REFERENCES Customer (CustomerID);

ALTER TABLE FoodMenu ADD CONSTRAINT FoodMenu_Restaurant FOREIGN KEY FoodMenu_Restaurant (RestaurantID)
REFERENCES Restaurant (RestaurantID);

ALTER TABLE FoodOrder ADD CONSTRAINT FoodOrder_FoodMenu FOREIGN KEY FoodOrder_FoodMenu (FoodID)
REFERENCES FoodMenu (FoodID),
ADD CONSTRAINT FoodOrder_Orders FOREIGN KEY FoodOrder_Orders (OrderID)
REFERENCES Orders (OrderID);

ALTER TABLE Orders 
ADD CONSTRAINT Orders_Customer FOREIGN KEY Orders_Customer (CustomerID) 
REFERENCES Customer (CustomerID),
ADD CONSTRAINT Orders_Driver FOREIGN KEY Orders_Driver (DriverID)
REFERENCES Driver (DriverID);

ALTER TABLE RestaurantAddress ADD CONSTRAINT RestaurantAddress_Restaurant FOREIGN KEY RestaurantAddress_Restaurant (RestaurantID)
REFERENCES Restaurant (RestaurantID);

ALTER TABLE Reviews ADD CONSTRAINT Reviews_Orders FOREIGN KEY Reviews_Orders (OrderID)
REFERENCES Orders (OrderID);

-- DDL 2
ALTER TABLE Customer
DROP COLUMN MembershipStartDate,
DROP COLUMN MembershipEndDate,
DROP COLUMN Points;

-- DDL 3
ALTER TABLE FoodMenu
ADD COLUMN isHalal BOOLEAN NOT NULL;

-- DDL 4
ALTER TABLE Driver 
ADD IsPartner BOOLEAN NULL,
DROP COLUMN Location;

-- DDL 5
ALTER TABLE CustomerAddress
DROP CONSTRAINT CustomerAddress_Customer;

DROP TABLE CustomerAddress;

-- DDL 6
ALTER TABLE Driver
DROP COLUMN VehicleType;

-- DDL 7
ALTER TABLE RestaurantAddress
DROP COLUMN Province,
DROP COLUMN City,
DROP COLUMN PostalCode;

ALTER TABLE OrderAddress
DROP COLUMN Province,
DROP COLUMN City,
DROP COLUMN PostalCode;

-- DML 1
INSERT INTO Customer (CustomerID, Name, Gender, Email, Phone, Balance, Status) VALUES
('C000000001', 'Budi Santoso', 'M', 'budi.s@email.com', '+6281234567890', 75.00, 'Active'),
('C000000002', 'Dewi Lestari', 'F', 'dewi.l@email.com', '+6281345678901', 120.25, 'Active'),
('C000000003', 'Agus Wijaya', 'M', 'agus.w@email.com', '+6287812345678', 30.50, 'Inactive'),
('C000000004', 'Siti Rahayu', 'F', 'siti.r@email.com', '+6281567890123', 180.00, 'Active'),
('C000000005', 'Joko Prasetyo', 'M', 'joko.p@email.com', '+6282198765432', 5.75, 'Suspended'),
('C000000006', 'Rina Melati', 'F', 'rina.m@email.com', '+6281122334455', 90.00, 'Active'),
('C000000007', 'Andi Saputra', 'M', 'andi.s@email.com', '+6281987654321', 200.50, 'Active'),
('C000000008', 'Fitri Indah', 'F', 'fitri.i@email.com', '+6287711223344', 45.25, 'Inactive'),
('C000000009', 'Rizki Pratama', 'M', 'rizki.p@email.com', '+6281234567890', 15.00, 'Suspended'),
('C000000010', 'Dian Permata', 'F', 'dian.p@email.com', '+6285298765432', 0.00, 'Active');

INSERT INTO Driver (DriverID, Name, Gender, Email, Phone, LicensePlate, Rating, Status, IsPartner) VALUES
('D000000001', 'Eko Sudrajat', 'M', 'eko.s@email.com', '+6281211223344', 'B 1234 ABC', 4.60, 'Available', TRUE),
('D000000002', 'Wati Handayani', 'F', 'wati.h@email.com', '+6281355667788', 'D 4321 CBA', 4.70, 'Busy', FALSE),
('D000000003', 'Fajar Kurniawan', 'M', 'fajar.k@email.com', '+6287722334455', 'A 3678 XYZ', 4.30, 'Offline', TRUE),
('D000000004', 'Indah Permatasari', 'F', 'indah.p@email.com', '+6281599001122', 'B 1876 QWE', 4.80, 'Available', TRUE),
('D000000005', 'Guntur Pratama', 'M', 'guntur.p@email.com', '+6282144556677', 'E 2468 MNO', 4.00, 'Inactive', FALSE),
('D000000006', 'Hesti Wijaya', 'F', 'hesti.w@email.com', '+6281277889900', 'F 1357 LJK', 4.90, 'Available', TRUE),
('D000000007', 'Irfan Santoso', 'M', 'irfan.s@email.com', '+6281322334455', 'B 4642 UIO', 4.20, 'Busy', FALSE),
('D000000008', 'Kartika Putri', 'F', 'kartika.p@email.com', '+6287812345678', 'D 2531 TRE', 4.70, 'Offline', TRUE),
('D000000009', 'Lukman Hakim', 'M', 'lukman.h@email.com', '+6281543210987', 'A 3876 YUI', 4.40, 'Available', TRUE),
('D000000010', 'Maya Sari', 'F', 'maya.s@email.com', '+6282165432109', 'B 3692 QAZ', 4.10, 'Inactive', FALSE);

INSERT INTO Restaurant (RestaurantID, Name, Email, Phone, OpeningTime, ClosingTime, Rating, Status) VALUES
('R000000001', 'Noodle House', 'noodles@email.com', '+622112345678', '10:00:00', '22:00:00', 4.30, 'Open'),
('R000000002', 'Fried Chicken Joint', 'chicken@email.com', '+622198765432', '11:00:00', '23:00:00', 4.60, 'Open'),
('R000000003', 'Indian Bistro', 'indian@email.com', '+622155512345', '12:00:00', '21:00:00', 4.40, 'Closed'),
('R000000004', 'Vegan Cafe', 'vegan@email.com', '+622178901234', '09:00:00', '20:00:00', 4.80, 'Open'),
('R000000005', 'Steakhouse', 'steak@email.com', '+622132165498', '17:00:00', '23:59:00', 4.90, 'Permanently Closed'),
('R000000006', 'Bakery', 'bakery@email.com', '+622187654321', '07:00:00', '18:00:00', 4.70, 'Open'),
('R000000007', 'Seafood Grill', 'seafood@email.com', '+622123456789', '11:00:00', '22:00:00', 4.50, 'Open'),
('R000000008', 'Korean BBQ', 'koreanbbq@email.com', '+622165432109', '16:00:00', '23:00:00', 4.60, 'Open'),
('R000000009', 'Ice Cream Parlor', 'icecream@email.com', '+622143210987', '12:00:00', '21:00:00', 4.40, 'Closed'),
('R000000010', 'Salad Bar', 'salad@email.com', '+622109876543', '10:00:00', '20:00:00', 4.20, 'Open');

INSERT INTO RestaurantAddress (AddressID, Address, Location, RestaurantID) VALUES
('RA00000001', 'Jl. Merdeka No. 10', '-6.1754, 106.8272', 'R000000001'),
('RA00000002', 'Jl. Sudirman No. 25', '-6.2088, 106.8456', 'R000000002'),
('RA00000003', 'Jl. Thamrin No. 15', '-6.2297, 106.7595', 'R000000003'),
('RA00000004', 'Jl. Gatot Subroto No. 5', '-6.1604, 106.8839', 'R000000004'),
('RA00000005', 'Jl. Rasuna Said No. 12', '-6.2615, 106.8106', 'R000000005'),
('RA00000006', 'Jl. Asia Afrika No. 8', '-6.1938, 106.7885', 'R000000006'),
('RA00000007', 'Jl. Diponegoro No. 30', '-6.1775, 106.9058', 'R000000007'),
('RA00000008', 'Jl. Kebon Sirih No. 22', '-6.2446, 106.8650', 'R000000008'),
('RA00000009', 'Jl. Senayan No. 18', '-6.3001, 106.8275', 'R000000009'),
('RA00000010', 'Jl. Cikini Raya No. 40', '-6.1462, 106.8053', 'R000000010');

INSERT INTO FoodMenu (FoodID, Name, Description, Category, Price, Available, RestaurantID, isHalal) VALUES
('F000000001', 'Spaghetti Bolognese', 'Spaghetti with meat sauce', 'Pasta', 10.00, TRUE, 'R000000001', TRUE),
('F000000002', 'Fried Chicken', 'Crispy fried chicken', 'Chicken', 8.00, TRUE, 'R000000002', FALSE),
('F000000003', 'Chicken Curry', 'Indian chicken curry', 'Indian', 12.00, FALSE, 'R000000003', FALSE),
('F000000004', 'Vegan Burger', 'Plant-based burger', 'Vegan', 9.50, TRUE, 'R000000004', TRUE),
('F000000005', 'Ribeye Steak', 'Grilled ribeye steak', 'Steak', 25.00, TRUE, 'R000000005', FALSE),
('F000000006', 'Chocolate Croissant', 'Buttery chocolate-filled pastry', 'Pastry', 3.50, TRUE, 'R000000006', TRUE),
('F000000007', 'Grilled Salmon', 'Grilled salmon with lemon butter sauce', 'Seafood', 18.00, TRUE, 'R000000007', FALSE),
('F000000008', 'Bulgogi', 'Korean marinated beef', 'Korean', 15.00, TRUE, 'R000000008', TRUE),
('F000000009', 'Vanilla Ice Cream', 'Classic vanilla ice cream', 'Dessert', 4.00, FALSE, 'R000000009', TRUE),
('F000000010', 'Caesar Salad', 'Romaine lettuce with Caesar dressing', 'Salad', 7.50, TRUE, 'R000000010', TRUE);

INSERT INTO Orders (OrderID, OrderTime, DeliveredTime, TotalPrice, PaymentMethod, Notes, Status, DriverID, CustomerID) VALUES
('O000000001', '2023-11-22 13:00:00', '2023-11-22 13:30:00', 18.00, 'Credit Card', 'Extra sauce', 'Delivered', 'D000000001', 'C000000001'),
('O000000002', '2023-11-22 19:15:00', '2023-11-22 19:45:00', 8.00, 'Cash', NULL, 'Delivered', 'D000000002', 'C000000002'),
('O000000003', '2023-11-23 20:00:00', NULL, 12.00, 'E-Wallet', 'No onions', 'Preparing', 'D000000003', 'C000000003'),
('O000000004', '2023-11-23 14:30:00', '2023-11-23 15:00:00', 19.00, 'Credit Card', NULL, 'Delivered', 'D000000004', 'C000000004'),
('O000000005', '2023-11-24 12:45:00', NULL, 25.00, 'E-Wallet', 'Well-done', 'Confirmed', 'D000000005', 'C000000005'),
('O000000006', '2023-11-24 10:30:00', '2023-11-24 11:00:00', 7.00, 'Cash', 'Extra butter', 'Delivered', 'D000000006', 'C000000006'),
('O000000007', '2023-11-25 18:45:00', NULL, 36.00, 'Credit Card', NULL, 'Preparing', 'D000000007', 'C000000007'),
('O000000008', '2023-11-25 17:20:00', '2023-11-25 17:50:00', 15.00, 'E-Wallet', 'Spicy', 'Delivered', 'D000000008', 'C000000008'),
('O000000009', '2023-11-26 13:15:00', NULL, 8.00, 'Cash', 'Add sprinkles', 'Driver in Restaurant', 'D000000009', 'C000000009'),
('O000000010', '2023-11-26 11:00:00', '2023-11-26 11:30:00', 15.00, 'Credit Card', 'No dressing', 'Delivered', 'D000000010', 'C000000010');

INSERT INTO FoodOrder (FoodID, OrderID, Quantity, SubTotal, Notes) VALUES
('F000000001', 'O000000001', 2, 20.00, 'Extra sauce'),
('F000000002', 'O000000002', 1, 8.00, NULL),
('F000000003', 'O000000003', 1, 12.00, 'No onions'),
('F000000004', 'O000000004', 2, 19.00, NULL),
('F000000005', 'O000000005', 1, 25.00, 'Well-done'),
('F000000006', 'O000000006', 2, 7.00, 'Extra butter'),
('F000000007', 'O000000007', 2, 36.00, NULL),
('F000000008', 'O000000008', 1, 15.00, 'Spicy'),
('F000000009', 'O000000009', 2, 8.00, 'Add sprinkles'),
('F000000010', 'O000000010', 2, 15.00, 'No dressing');

INSERT INTO OrderAddress (AddressID, Address, Location, OrderID) VALUES
('OA00000001', 'Jl. Merdeka Barat No. 5', '-6.1754, 106.8272', 'O000000001'),
('OA00000002', 'Jl. Sudirman No. 10', '-6.2088, 106.8456', 'O000000002'),
('OA00000003', 'Jl. MH Thamrin No. 20', '-6.2297, 106.7595', 'O000000003'),
('OA00000004', 'Jl. Gatot Subroto No. 8', '-6.1604, 106.8839', 'O000000004'),
('OA00000005', 'Jl. HR Rasuna Said No. 15', '-6.2615, 106.8106', 'O000000005'),
('OA00000006', 'Jl. Asia Afrika No. 3', '-6.1938, 106.7885', 'O000000006'),
('OA00000007', 'Jl. Diponegoro No. 25', '-6.1775, 106.9058', 'O000000007'),
('OA00000008', 'Jl. Kebayoran Baru No. 12', '-6.2446, 106.8650', 'O000000008'),
('OA00000009', 'Jl. Casablanca No. 9', '-6.3001, 106.8275', 'O000000009'),
('OA00000010', 'Jl. Kemang Raya No. 33', '-6.1462, 106.8053', 'O000000010');

INSERT INTO Reviews (ReviewID, ReviewTime, RestaurantRating, DriverRating, Comment, OrderID) VALUES
('RV00000001', '2023-11-22 13:45:00', 4.50, 4.80, 'Great pasta, quick delivery', 'O000000001'),
('RV00000002', '2023-11-22 20:00:00', 4.00, 4.20, 'Chicken was good, delivery on time', 'O000000002'),
('RV00000003', '2023-11-23 15:15:00', 4.70, 4.50, 'Delicious vegan burger, friendly driver', 'O000000004'),
('RV00000004', '2023-11-24 11:15:00', 4.60, 4.90, 'Tasty croissant, fast delivery', 'O000000006'),
('RV00000005', '2023-11-25 18:00:00', 4.80, 4.70, 'Excellent Korean BBQ, driver was polite', 'O000000008'),
('RV00000006', '2023-11-26 11:45:00', 4.20, 4.00, 'Salad was fresh, but driver was a bit late', 'O000000010'),
('RV00000007', '2023-11-27 14:20:00', 3.50, 3.00, 'Food was cold, delivery took too long', 'O000000003'),
('RV00000008', '2023-11-28 19:55:00', 5.00, 5.00, 'Best steak I have ever had!', 'O000000005'),
('RV00000009', '2023-11-29 12:30:00', 4.00, 3.80, 'Ice cream was melted, but driver was apologetic', 'O000000009'),
('RV00000010', '2023-11-30 21:10:00', 4.30, 4.50, 'Good seafood, will order again', 'O000000007');

-- DML 2
INSERT INTO Orders (OrderID, OrderTime, DeliveredTime, TotalPrice, PaymentMethod, Notes, Status, DriverID, CustomerID) VALUES
('O000000011', '2023-11-22 13:00:00', NULL, 20.00, 'Credit Card', 'Extra sauce', 'Confirmed', 'D000000001', 'C000000001');

INSERT INTO OrderAddress (AddressID, Address, Location, OrderID) VALUES
('OA00000011', 'Jl. Merdeka Barat No. 5', '-6.1754, 106.8272', 'O000000011');

INSERT INTO FoodOrder (FoodID, OrderID, Quantity, SubTotal, Notes) VALUES
('F000000001', 'O000000011', 2, 20.00, 'Extra sauce');

UPDATE Orders
SET DeliveredTime = '2023-11-22 13:30:00', Status = 'Delivered'
WHERE OrderID = 'O000000011';

-- DML 3
DELETE FROM Reviews
WHERE ReviewID = 'RV00000007';

-- DML 4
UPDATE Restaurant
SET Status = 'Closed'
WHERE RestaurantID = 'R000000003';

UPDATE FoodMenu
SET Available = FALSE
WHERE FoodID = 'F000000003';

-- DML 5
UPDATE FoodMenu
SET Price = Price * 0.80
WHERE RestaurantID IN ('R000000001', 'R000000004', 'R000000008');

-- DML 6
INSERT INTO Orders (OrderID, OrderTime, DeliveredTime, TotalPrice, PaymentMethod, Notes, Status, DriverID, CustomerID) VALUES
('O000000012', '2023-12-03 10:00:00', NULL, 3.50, 'Cash', 'Please include napkins', 'Confirmed', 'D000000004', 'C000000003'); 

INSERT INTO OrderAddress (AddressID, Address, Location, OrderID) VALUES
('OA00000012', 'Jl. Thamrin No. 10', '-6.2297, 106.7595', 'O000000012');

INSERT INTO FoodOrder (FoodID, OrderID, Quantity, SubTotal, Notes) VALUES
('F000000006', 'O000000012', 1, 3.50, 'Please include napkins');

UPDATE FoodMenu
SET Available = FALSE
WHERE FoodID = 'F000000006';

UPDATE Orders
SET Status = 'Cancelled'
WHERE OrderID = 'O000000012';

-- Query 1
SELECT cu.CustomerID, cu.Name
FROM Customer cu
JOIN Orders ord ON cu.CustomerID = ord.CustomerID
WHERE ord.Notes LIKE '%spicy%';

-- Query 2
SELECT CustomerID, Name
FROM Customer
WHERE CustomerID NOT IN (
    SELECT DISTINCT ord.CustomerID
    FROM Orders ord
    JOIN FoodOrder fo ON ord.OrderID = fo.OrderID
    JOIN FoodMenu fm ON fo.FoodID = fm.FoodID
    WHERE fm.RestaurantID = 'R000000008'
);

-- Query 3
SELECT r.RestaurantID, r.Name, COUNT(o.OrderID) AS OrderCount
FROM Restaurant r
LEFT JOIN FoodMenu fm ON r.RestaurantID = fm.RestaurantID
LEFT JOIN FoodOrder fo ON fm.FoodID = fo.FoodID
LEFT JOIN Orders o ON fo.OrderID = o.OrderID
GROUP BY r.RestaurantID, r.Name
ORDER BY OrderCount DESC
LIMIT 1;

-- Query 4
SELECT r.RestaurantID, r.Name, AVG(r.Rating) AS AverageRating
FROM Restaurant r
GROUP BY r.RestaurantID, r.Name
HAVING AVG(r.Rating) > (SELECT AVG(Rating) FROM Restaurant);

-- Query 5
SELECT c.CustomerID, c.Name, SUM(o.TotalPrice) AS TotalSpent
FROM Customer c
JOIN Orders o ON c.CustomerID = o.CustomerID
GROUP BY c.CustomerID, c.Name
ORDER BY TotalSpent DESC
LIMIT 3;

-- Query 6
SELECT d.DriverID, d.Name, COUNT(o.OrderID) AS TotalOrdersDelivered
FROM Driver d
JOIN Orders o ON d.DriverID = o.DriverID
WHERE o.Status = 'Delivered'
GROUP BY d.DriverID, d.Name
ORDER BY TotalOrdersDelivered DESC
LIMIT 1;

-- Query 7
SELECT fm.Name AS FoodName, r.Name AS RestaurantName, fm.Price
FROM FoodMenu fm
JOIN Restaurant r ON fm.RestaurantID = r.RestaurantID
WHERE fm.Price < (SELECT AVG(Price) FROM FoodMenu)
ORDER BY fm.Price ASC;

-- Live Query
SELECT *
FROM (
    SELECT r.RestaurantID, r.Name, COUNT(o.OrderID) AS OrderCount
    FROM Restaurant r
    LEFT JOIN FoodMenu fm ON r.RestaurantID = fm.RestaurantID
    LEFT JOIN FoodOrder fo ON fm.FoodID = fo.FoodID
    LEFT JOIN Orders o ON fo.OrderID = o.OrderID
    GROUP BY r.RestaurantID, r.Name
) as RestaurantOrderCount
WHERE OrderCount = (
    SELECT COUNT(o.OrderID) AS OrderCount
    FROM Restaurant r
    LEFT JOIN FoodMenu fm ON r.RestaurantID = fm.RestaurantID
    LEFT JOIN FoodOrder fo ON fm.FoodID = fo.FoodID
    LEFT JOIN Orders o ON fo.OrderID = o.OrderID
    GROUP BY r.RestaurantID, r.Name
    ORDER BY OrderCount DESC
    LIMIT 1
);