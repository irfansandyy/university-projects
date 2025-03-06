SELECT *
FROM customers
WHERE customers.`CustomerID` IN 
(SELECT `CustomerID` FROM orders);

