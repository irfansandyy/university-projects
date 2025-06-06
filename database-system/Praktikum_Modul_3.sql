-- Active: 1728911430420@@127.0.0.1@3306@zoo
use zoo;
-- Q1
SELECT an.name as animal_name, att.name as attraction_name
FROM animals_attractions aa
INNER JOIN animals an ON (aa.animals_id = an.id)
INNER JOIN attractions att ON (aa.attractions_id = att.id)
WHERE HOUR(schedule_start) >= 9 AND HOUR(schedule_start) <= 15 AND HOUR(schedule_end) >= 9 AND HOUR(schedule_end) <= 15
GROUP BY an.id, att.name;

-- Q2
SELECT DISTINCT ty.species
FROM animals_attractions aa
INNER JOIN animals an ON (aa.animals_id = an.id)
INNER JOIN attractions att ON (aa.attractions_id = att.id)
INNER JOIN `types` ty ON (an.types_id = ty.id)
WHERE att.name = 'night spectacular';

-- Q3
SELECT *
FROM animals an
INNER JOIN `types` ty ON (an.types_id = ty.id)
WHERE an.id NOT IN (
    SELECT animals_id
    FROM animals_attractions
);

-- Q4
SELECT (
    SELECT COUNT(*)
    FROM employee
    WHERE certification is NOT NULL
)/(
    SELECT COUNT(*)
    FROM employee
)*100 as percentage_of_certified_employees;

-- Q5
SELECT an.id, an.name, SUM(att.price)
FROM animals_attractions aa
INNER JOIN animals an ON (aa.animals_id = an.id)
INNER JOIN attractions att ON (aa.attractions_id = att.id)
GROUP BY an.id
ORDER BY SUM(att.price) DESC;

-- Q6
SELECT *
FROM attractions
WHERE price = 0 AND `id` NOT IN (
    SELECT att.id
    FROM attractions_employee ae
    INNER JOIN attractions att ON (ae.attractions_id = att.id)
    INNER JOIN employee em ON (ae.employee_id = em.id)
    WHERE em.type = 'healthcare'
);

-- Q7
SELECT `name`, place, (
    CASE 
        WHEN `id` IN (
            SELECT att.id
            FROM attractions_employee ae
            INNER JOIN attractions att ON (ae.attractions_id = att.id)
            INNER JOIN employee em ON (ae.employee_id = em.id)
            WHERE em.certification is NOT NULL
        ) THEN 'YES' 
        ELSE 'NO' 
    END
    ) as has_certification
FROM attractions;


-- Q8
WITH LocationCounts AS (
    SELECT 
        a.name AS animal_name,
        att.place,
        COUNT(*) AS location_count,
        (COUNT(*) * 100.0 / (
            SELECT COUNT(*)
            FROM animals_attractions aa2
            WHERE aa2.animals_id = aa.animals_id
        )) AS percentage
    FROM animals a
    JOIN animals_attractions aa ON a.id = aa.animals_id
    JOIN attractions att ON aa.attractions_id = att.id
    WHERE a.id IN (SELECT DISTINCT animals_id FROM animals_attractions)
    GROUP BY a.name, att.place, aa.animals_id
)
SELECT 
    animal_name,
    MAX(CASE WHEN place = 'arctic dome' THEN percentage ELSE 0 END) as 'arctic dome',
    MAX(CASE WHEN place = 'aviary' THEN percentage ELSE 0 END) as 'aviary',
    MAX(CASE WHEN place = 'main stage' THEN percentage ELSE 0 END) as 'main stage'
    
FROM LocationCounts
GROUP BY animal_name
ORDER BY animal_name;


-- Q9
SELECT em.`id`, em.name, count(*) as attraction_count, (
    CASE 
        WHEN em.type = 'healthcare' THEN  COUNT(*)*30*19
        WHEN em.type = 'ranger' THEN COUNT(*)*30*25
        WHEN em.type = 'senior ranger' THEN COUNT(*)*30*35
        ELSE 0
    END 
) as salary
FROM attractions_employee ae
INNER JOIN employee em ON (ae.employee_id = em.id)
GROUP BY em.id, em.name;

-- Q10
SELECT *
FROM employee
WHERE `id` IN (
    SELECT em.id
    FROM animals_attractions aa
    INNER JOIN animals an ON (aa.animals_id = an.id)
    INNER JOIN `types` ty ON (an.types_id = ty.id)
    INNER JOIN attractions att ON (aa.attractions_id = att.id)
    INNER JOIN attractions_employee ae ON (att.id = ae.attractions_id)
    INNER JOIN employee em ON (ae.employee_id = em.id)
    WHERE ty.genus = 'seal'
);