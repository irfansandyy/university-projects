-- Active: 1728911430420@@127.0.0.1@3306@fullnorthwind
SELECT cu.custId, cu.companyName, cu.contactName, cu.contactTitle, cu.fax
FROM customer cu
WHERE cu.fax is NOT NULL
ORDER BY cu.custId ASC; 

SELECT e.employeeId, CONCAT(e.firstName, e.lastName), e.title, e.hireDate
FROM employee e
ORDER BY e.hireDate DESC
LIMIT 5;

SELECT *
FROM orderdetail o