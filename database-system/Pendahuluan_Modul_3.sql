-- Active: 1728911430420@@127.0.0.1@3306@neonest_gaming_shop
DROP DATABASE IF EXISTS neonest_gaming_shop;

CREATE DATABASE IF NOT EXISTS neonest_gaming_shop;

USE neonest_gaming_shop;

----------- KODE INSERT --------------


----------- KODE INSERT --------------

-- Q1
SELECT cu.cst_name
FROM customer cu
INNER JOIN membership me ON (cu.cst_id = me.customer_cst_id)  
WHERE me.mbr_points > 100 AND me.mbr_points < 115;

-- Q2
SELECT *
FROM `transaction`
WHERE tr_paymentMethod = 'Cash';

-- Q3
SELECT customer_cst_id, AVG(tr_totalBill) as average_bill
FROM `transaction`
GROUP BY customer_cst_id
HAVING AVG(tr_totalBill) > 5000000;

-- Q4
SELECT COUNT(tr_paymentMethod)
FROM `transaction`
WHERE tr_paymentMethod = 'Cash'
GROUP BY tr_paymentMethod;

-- Q5
SELECT cu.cst_name, cu.cst_phoneNumber, me.mbr_email, COUNT(*) as transaction_number
FROM customer cu
INNER JOIN membership me ON (cu.cst_id = me.customer_cst_id)
INNER JOIN `transaction` tr ON (cu.cst_id = tr.customer_cst_id)
GROUP BY cu.cst_id, me.mbr_email
ORDER BY COUNT(*) DESC
LIMIT 3;

-- Q6
SELECT customer_cst_id, AVG(tr_totalBill) as average_bill
FROM `transaction`
GROUP BY customer_cst_id
HAVING AVG(tr_totalBill) > (
    SELECT AVG(tr_totalBill)
    FROM `transaction`
)
ORDER BY AVG(tr_totalBill) DESC;

-- Q7
SELECT *
FROM employee
WHERE emp_id IN (
    SELECT e.emp_id
    FROM employee e
    INNER JOIN `transaction` tr ON (e.emp_id = tr.employee_emp_id)
    GROUP BY e.emp_id
    HAVING COUNT(*) = (
        SELECT MAX(transaction_count)
        FROM(
            SELECT COUNT(*) as transaction_count
            FROM `transaction`
            GROUP BY employee_emp_id
        ) as sq
    )
);

-- Q8
SELECT cu.cst_id, cu.cst_name, SUM(tr.tr_totalBill)
FROM customer cu
INNER JOIN `transaction` tr ON (cu.cst_id = tr.customer_cst_id)
GROUP BY tr.customer_cst_id, cu.cst_id
HAVING SUM(tr.tr_totalBill) > (
    SELECT AVG(tr_totalBill)
    FROM `transaction`
);

-- Q9
SELECT *
FROM customer
WHERE cst_id IN (
    SELECT customer_cst_id
    FROM `transaction`
    GROUP BY customer_cst_id
    HAVING COUNT(*) > 1
);

-- Q10
SELECT *
FROM item
WHERE item_id IN (
    SELECT i.item_id
    FROM item i
    LEFT JOIN transaction_item ti ON (i.item_id = ti.item_item_id)
    WHERE ti.item_amount is NULL
);