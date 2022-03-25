USE vac_operation;

/***********************************************
 ****************** QUERIES ********************
 ***********************************************/


/*************** SELECT QUERIES ***************/


# amount of people in each phase
SELECT phases_complete, COUNT(*) AS amount_of_people
FROM citizen
GROUP BY phases_complete
ORDER BY phases_complete;

# show all citizens who missed their appointments
SELECT date, first_name, last_name, phone_num
FROM appointment,
     citizen
WHERE date < DATE(NOW())
  AND citizen.citizen_id = appointment.citizen_id;

# show amount of vaccines in each district
SELECT district, COUNT(barcode) AS vaccines_total_amount
FROM dose
         JOIN supply s ON dose.supply_id = s.supply_id
         JOIN clinic c2 ON s.clinic_id = c2.clinic_id
WHERE barcode NOT IN (SELECT dose_barcode FROM vaccination)
GROUP BY district;

# show amount of workers in each clinic ordered by descending seniority
SELECT clinic_name,
       COUNT(worker.worker_id) AS workers_count,
       AVG(worker.seniority)   AS average_seniority_in_years
FROM worker
         JOIN clinic c
              ON worker.clinic_id = c.clinic_id
GROUP BY c.clinic_id
ORDER BY average_seniority_in_years DESC;

# show all clinics and their supplies ordered by expiry date
SELECT (SELECT clinic.clinic_name
        FROM clinic
        WHERE clinic_id = supplies.clinic_id)           AS clinic,
       (SELECT CONCAT(company, ' - ', vaccine_name)
        FROM vaccine
        WHERE vaccine.vaccine_id = supplies.vaccine_id) AS vaccine,
       amount,
       expiry_date
FROM ((SELECT clinic_id, vaccine_id, COUNT(barcode) AS amount, expiry_date
       FROM supply
                JOIN dose d ON supply.supply_id = d.supply_id
       WHERE barcode NOT IN (SELECT dose_barcode FROM vaccination)
       GROUP BY clinic_id
      ) AS supplies
         JOIN clinic ON supplies.clinic_id = clinic.clinic_id)
ORDER BY expiry_date;

# show citizens in the max risk group who did not
# complete the first phase and not don't have an appointment
SELECT first_name, last_name, phone_num, email
FROM citizen
WHERE phases_complete = 0
  AND citizen_id NOT IN (SELECT citizen_id
                         FROM appointment)
  AND risk_group = 'max';

# show how many vaccinated in each age group
SELECT CONCAT(FLOOR(age / 10) * 10, '-',
              FLOOR((age + 10) / 10) * 10) AS age_group,
       COUNT(*)                            AS amount_vaccinated
FROM citizen
WHERE phases_complete = 2
GROUP BY FLOOR(age / 10) * 10
ORDER BY age;

# show a specific citizen how much time is left until his appointment
SELECT DATEDIFF(appointment.date, NOW()) AS days_left
FROM appointment
WHERE appointment.citizen_id = 696200479
ORDER BY appointment.date
LIMIT 1;

# show citizen and worker details + appointment date for people who are max
# risk group who are scheduled with a worker with less than 5 years seniority
SELECT c.citizen_id,
       c.first_name,
       c.last_name,
       w.worker_id,
       w.first_name,
       w.last_name,
       w.seniority,
       appointment.date
FROM (appointment JOIN citizen c ON c.citizen_id = appointment.citizen_id)
         JOIN worker w ON w.worker_id = appointment.worker_id
WHERE c.risk_group = 'Max'
  AND w.seniority < 5;


# show clinics who have more appointments than total vaccine amount
# or don't any supplies but do have appointments
SELECT *
FROM (SELECT clinic.clinic_id,
             clinic.clinic_name,
             (SELECT COUNT(barcode)
              FROM dose
              WHERE dose.supply_id = supply.supply_id) AS vaccines_total,
             COUNT(appointment_id)                     AS appointments
      FROM (clinic JOIN appointment ap ON clinic.clinic_id = ap.clinic_id)
               JOIN supply ON supply.clinic_id = clinic.clinic_id
      GROUP BY clinic.clinic_id) AS all_clinics
WHERE appointments > vaccines_total
UNION
(SELECT clinic_id,
        clinic_name,
        (SELECT COUNT(clinic_id) FROM supply WHERE clinic.clinic_id = supply.clinic_id),
        (SELECT COUNT(clinic_id) FROM appointment WHERE clinic.clinic_id = appointment.clinic_id)
 FROM clinic
 WHERE clinic_id NOT IN (SELECT clinic_id FROM supply)
   AND clinic_id IN (SELECT clinic_id AS cid FROM appointment)
);

# show workers who have no appointments in a specific
# time range. order by ascending seniority
SELECT *
FROM worker
WHERE worker_id NOT IN (
    SELECT appointment.worker_id
    FROM appointment
    WHERE appointment.worker_id = worker.worker_id
      AND appointment.date BETWEEN NOW() AND DATE_ADD(NOW(), INTERVAL 1 MONTH))
ORDER BY worker.seniority;

# show schedule for a specific worker in the next month
SELECT *
FROM appointment
WHERE worker_id = 248490510
  AND appointment.date BETWEEN NOW() AND DATE_ADD(NOW(), INTERVAL 1 MONTH)
ORDER BY appointment.date;

/*************** UPDATE/INSERT/DELETE QUERIES ***************/

# remove un-administered expired supplies
DELETE
FROM dose
WHERE supply_id IN (SELECT supply_id
                    FROM supply
                    WHERE expiry_date < DATE(NOW()))
  AND barcode NOT IN (SELECT dose_barcode
                      FROM vaccination);

# move supplies from most supplied clinic to the least
# supplied (nested format to work with complex set/where)
UPDATE supply
SET supply.clinic_id = (SELECT cid
                        FROM (SELECT clinic_id AS cid
                              FROM (SELECT c.clinic_id, COUNT(barcode) AS cnt
                                    FROM supply
                                             JOIN dose d ON supply.supply_id = d.supply_id
                                             JOIN clinic c ON c.clinic_id = supply.clinic_id
                                    GROUP BY c.clinic_id
                                    ORDER BY cnt

                                    LIMIT 1) AS min_inner) AS min)

WHERE supply.supply_id = (SELECT sid
                          FROM (SELECT supply_id AS sid
                                FROM (SELECT d2.supply_id, COUNT(barcode) AS cnt
                                      FROM supply
                                               JOIN dose d2 ON supply.supply_id = d2.supply_id
                                               JOIN clinic c2 ON c2.clinic_id = supply.clinic_id
                                      GROUP BY c2.clinic_id
                                      ORDER BY cnt DESC
                                      LIMIT 1) AS max_inner) AS max);


# replace worker in appointments in a specific day
CALL replace_worker_in_specific_date(
        460223128,
        998843053,
        DATE(DATE_ADD(NOW(), INTERVAL 21 DAY))
    );

# add supplies to all clinics with less than 1000 total vaccines
CALL add_to_low_supply_clinics();


