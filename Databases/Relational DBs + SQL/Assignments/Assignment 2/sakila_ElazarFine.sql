USE sakila;

-- Elazar Fine

-- 1
SELECT *
FROM actor
WHERE first_name = 'Alice';

-- 2
SELECT DISTINCT last_name
FROM actor;

-- 3
SELECT last_name, COUNT(*)
FROM actor
GROUP BY last_name;

-- 4
SELECT *
FROM film
WHERE film.language_id IN (SELECT language_id FROM language WHERE name = 'Italian');

-- 5
SELECT *
FROM film
WHERE film_id IN (SELECT film_id
                  FROM (SELECT category_id FROM category WHERE name = 'Comedy') AS cid
                           JOIN film_category ON cid.category_id = film_category.category_id);

-- 6
SELECT first_name, last_name
FROM actor
WHERE actor_id IN (SELECT actor_id
                   FROM film_actor
                            JOIN (SELECT film_id FROM film WHERE title = 'Citizen Shrek') AS cs
                                 ON film_actor.film_id = cs.film_id);

-- 7
SELECT title, COUNT(*) AS 'num of actors'
FROM (SELECT actor.actor_id, title
      FROM (actor JOIN film_actor ON actor.actor_id = film_actor.actor_id)
               JOIN film ON film.film_id = film_actor.film_id) AS actors_in_film
GROUP BY title
ORDER BY title;

-- 8
SELECT first_name, last_name
FROM actor
         JOIN (SELECT actor_id, COUNT(*) AS count
               FROM film_actor
               GROUP BY actor_id
               ORDER BY count DESC
               LIMIT 1) AS highest ON actor.actor_id = highest.actor_id;

-- 9
SELECT COUNT(actor_id)
FROM actor
WHERE actor_id NOT IN (SELECT actor_id FROM film_actor);

-- 10
SELECT *
FROM actor
WHERE actor_id NOT IN (SELECT actor_id FROM film_actor);

-- 11
SELECT AVG(length)
FROM film;

-- 12
SELECT (SELECT name FROM category WHERE lens.category_id = category.category_id) AS genre, AVG(length)
FROM (SELECT category_id, length
      FROM film_category
               JOIN film ON film.film_id = film_category.film_id) AS lens
GROUP BY category_id;

-- 13
SELECT name
FROM category
         JOIN (SELECT category_id, COUNT(*) AS count
               FROM film_category
               GROUP BY category_id
               HAVING count > 100) AS high ON high.category_id = category.category_id;

-- 14
SELECT *
FROM country
WHERE country_id IN (SELECT country_id FROM city WHERE city.city = 'London');

-- 15
SELECT (SELECT CONCAT(first_name, ' ', last_name)
        FROM staff
        WHERE store.manager_staff_id = staff.staff_id) AS manager,

       (SELECT (SELECT city FROM city WHERE address.city_id = city.city_id) AS cty
        FROM address
        WHERE store.address_id = address.address_id)   AS city
FROM store;

-- 16
SELECT last_name, SUM(amount) AS sum
FROM customer
         JOIN payment p ON customer.customer_id = p.customer_id
GROUP BY p.customer_id, last_name
ORDER BY last_name;

-- 17
SELECT *
FROM film
WHERE film_id IN (SELECT film_id
                  FROM inventory
                           JOIN (SELECT inventory_id, COUNT(*) AS count
                                 FROM rental
                                 GROUP BY inventory_id
                                 ORDER BY count DESC
                                 LIMIT 1) AS max
                                ON max.inventory_id = inventory.inventory_id);

-- 18
SELECT *
FROM film
WHERE film_id IN (SELECT film_id
                  FROM inventory
                           JOIN (SELECT DISTINCT inventory_id
                                 FROM rental
                                 WHERE return_date IS NULL) AS not_returned
                                ON not_returned.inventory_id = inventory.inventory_id);

-- 19


INSERT INTO rental
VALUES (default, NOW(), 4444, 222, NULL, 1, NOW());


INSERT INTO payment (customer_id, staff_id, rental_id, amount, payment_date, last_update)
VALUES (222,
        1,
        (SELECT rental_id FROM rental WHERE inventory_id = 4444 ORDER BY rental_id DESC LIMIT 1),
        0,
        NOW(),
        NOW());

-- 20

UPDATE payment
SET amount = 7.5
WHERE amount = 0.0
  AND customer_id = 222
  AND rental_id = (SELECT rental_id FROM rental WHERE inventory_id = 4444 ORDER BY rental_id DESC LIMIT 1)
  AND staff_id = 1
ORDER BY payment_date DESC
LIMIT 1;

-- 21

UPDATE rental
SET return_date = NOW()
WHERE inventory_id = 4444
  AND customer_id = 222
  AND staff_id = 1
ORDER BY return_date DESC
LIMIT 1;

select DISTINCT rental_id from rental;