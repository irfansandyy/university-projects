USE Northwind;

SELECT orders.OrderDate, shippers.ShipperName
FROM orders JOIN shippers ON (orders.ShipperID = shippers.ShipperID)
WHERE orders.customerID = (SELECT CustomerID FROM customers WHERE ContactName = 'Thomas Hardy');

SELECT * 
FROM employees
WHERE month(BirthDate) = 1
ORDER BY FirstName ASC;

SELECT categories.CategoryName, COUNT(*) as CategoryCount
FROM categories JOIN products ON (categories.CategoryID = products.CategoryID)
GROUP BY categories.CategoryName;

SELECT *
FROM products
WHERE Price = (SELECT max(price) FROM products);

SELECT categories.CategoryName, AVG(Price) as AveragePrice
FROM categories JOIN products ON (categories.CategoryID = products.CategoryID)
GROUP BY categories.CategoryName;