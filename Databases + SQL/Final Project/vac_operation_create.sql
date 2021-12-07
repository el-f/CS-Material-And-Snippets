CREATE SCHEMA vac_operation;

USE vac_operation;

/***********************************************
 **************** CREATE TABLES ****************
 ***********************************************/

CREATE TABLE vaccine
(
    vaccine_id   INT         NOT NULL,
    vaccine_name VARCHAR(50) NOT NULL,
    company      VARCHAR(50) NOT NULL,

    PRIMARY KEY (vaccine_id)
) ENGINE = InnoDB;


CREATE TABLE clinic
(
    clinic_id   INT         NOT NULL AUTO_INCREMENT,
    clinic_name VARCHAR(50) NOT NULL UNIQUE,
    phone_num   VARCHAR(50) NOT NULL,
    email       VARCHAR(50) NOT NULL UNIQUE,
    street      VARCHAR(50) NOT NULL,
    house_num   INT         NOT NULL,
    district    VARCHAR(50) NOT NULL,

    PRIMARY KEY (clinic_id),
    UNIQUE (street, house_num, district)
) ENGINE = InnoDB;

CREATE TABLE supply
(
    supply_id   INT  NOT NULL AUTO_INCREMENT,
    clinic_id   INT,
    vaccine_id  INT  NOT NULL,
    expiry_date DATE NOT NULL,

    PRIMARY KEY (supply_id),
    FOREIGN KEY (vaccine_id) REFERENCES vaccine (vaccine_id)
        ON DELETE NO ACTION
        ON UPDATE CASCADE,
    FOREIGN KEY (clinic_id) REFERENCES clinic (clinic_id)
        ON DELETE NO ACTION
        ON UPDATE CASCADE
) ENGINE = InnoDB;

CREATE TABLE dose
(
    barcode   INT NOT NULL AUTO_INCREMENT,
    supply_id INT NOT NULL,
    PRIMARY KEY (barcode),
    FOREIGN KEY (supply_id) REFERENCES supply (supply_id)
        ON UPDATE CASCADE
        ON DELETE NO ACTION
) ENGINE = InnoDB;

CREATE TABLE worker
(
    worker_id       INT         NOT NULL,
    first_name      VARCHAR(50) NOT NULL,
    last_name       VARCHAR(50) NOT NULL,
    phone_num       VARCHAR(20) NOT NULL UNIQUE,
    medical_license INT         NOT NULL UNIQUE,
    seniority       INT         NOT NULL,
    clinic_id       INT,

    PRIMARY KEY (worker_id),
    FOREIGN KEY (clinic_id) REFERENCES clinic (clinic_id)
        ON DELETE SET NULL
        ON UPDATE CASCADE
) ENGINE = InnoDB;

CREATE TABLE citizen
(
    citizen_id      INT         NOT NULL,
    first_name      VARCHAR(50) NOT NULL,
    last_name       VARCHAR(50) NOT NULL,
    phone_num       VARCHAR(20) NOT NULL,
    age             INT         NOT NULL,
    weight          INT         NOT NULL,
    email           VARCHAR(50),
    district        VARCHAR(50) NOT NULL,
    phases_complete INT         NOT NULL DEFAULT 0,
    risk_group      ENUM ('Max', 'High', 'Regular') AS (CASE
                                                            WHEN (age >= 85 OR weight >= 120)
                                                                OR (age >= 75 AND weight >= 110) THEN 'max'
                                                            WHEN (age >= 70 OR weight >= 100)
                                                                OR (age >= 65 AND weight >= 90) THEN 'high'
                                                            ELSE 'regular' END ),

    CONSTRAINT weight_constraint CHECK ( 0 < weight AND weight < 500 ),
    CONSTRAINT age_constraint CHECK ( age >= 0 ),
    CONSTRAINT phase_constraint CHECK ( 0 <= phases_complete AND phases_complete <= 2 ),

    PRIMARY KEY (citizen_id)
) ENGINE = InnoDB;

CREATE TABLE appointment
(
    appointment_id INT      NOT NULL AUTO_INCREMENT,
    clinic_id      INT      NOT NULL,
    citizen_id     INT,
    worker_id      INT,
    date           DATETIME NOT NULL,

    PRIMARY KEY (appointment_id),
    FOREIGN KEY (clinic_id) REFERENCES clinic (clinic_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (citizen_id) REFERENCES citizen (citizen_id)
        ON UPDATE CASCADE
        ON DELETE SET NULL,
    FOREIGN KEY (worker_id) REFERENCES worker (worker_id)
        ON UPDATE CASCADE
        ON DELETE SET NULL
) ENGINE = InnoDB;


CREATE TABLE vaccination
(
    worker_id    INT      NOT NULL,
    citizen_id   INT      NOT NULL,
    dose_barcode INT      NOT NULL UNIQUE,
    date         DATETIME NOT NULL,
    phase        INT      NOT NULL,

    PRIMARY KEY (worker_id, citizen_id, phase),
    FOREIGN KEY (worker_id) REFERENCES worker (worker_id)
        ON DELETE NO ACTION
        ON UPDATE CASCADE,
    FOREIGN KEY (citizen_id) REFERENCES citizen (citizen_id)
        ON DELETE NO ACTION
        ON UPDATE CASCADE,
    FOREIGN KEY (dose_barcode) REFERENCES dose (barcode)
        ON DELETE NO ACTION
        ON UPDATE CASCADE
) ENGINE = InnoDB;

/******************************************
 **************** TRIGGERS ****************
 ******************************************/

CREATE TRIGGER update_phase_for_citizen_after_vac
    AFTER INSERT
    ON vaccination
    FOR EACH ROW
    UPDATE citizen
    SET phases_complete = phases_complete + 1
    WHERE citizen_id = new.citizen_id;

DROP TRIGGER IF EXISTS make_appointment_for_next_phase;
-- make appointment for next phase in 21 days
DELIMITER $$
CREATE TRIGGER make_appointment_for_next_phase
    BEFORE INSERT
    ON vaccination
    FOR EACH ROW
mafnp_trigger:
BEGIN
    DECLARE citizen_chosen_clinic INT;

    SELECT clinic_id
    INTO citizen_chosen_clinic
    FROM appointment
    WHERE citizen_id = new.citizen_id
    LIMIT 1;


    /* make sure we have a clinic for the citizen
     in case he vaccinated without an appointment */
    IF citizen_chosen_clinic IS NULL THEN
        SET citizen_chosen_clinic = (
            SELECT clinic_id
            FROM clinic
            WHERE clinic.district IN
                  (SELECT citizen.district
                   FROM citizen
                   WHERE citizen.citizen_id = new.citizen_id)
            LIMIT 1
        );

        # choose random worker from that clinic instead of the current clinic worker,
        # otherwise the worker-clinic-integrity will break
        CALL get_random_worker_from_clinic_id(
                citizen_chosen_clinic,
                @rand_worker_id
            );

        INSERT INTO appointment
            VALUE (DEFAULT, citizen_chosen_clinic, new.citizen_id, (SELECT @rand_worker_id),
                   DATE_ADD(new.date, INTERVAL 21 DAY));

        LEAVE mafnp_trigger;

    END IF;

    INSERT INTO appointment
        VALUE (DEFAULT, citizen_chosen_clinic, new.citizen_id, new.worker_id, DATE_ADD(new.date, INTERVAL 21 DAY));
END $$
DELIMITER ;


DELIMITER $$
CREATE TRIGGER delete_fulfilled_appointment
    AFTER INSERT
    ON vaccination
    FOR EACH ROW
BEGIN
    /* takes cares of edge cases of vaccination
       in a different date or vaccination without appointment */
    IF (SELECT COUNT(appointment_id) AS aid
        FROM appointment
        WHERE appointment.citizen_id = new.citizen_id) > 1
    THEN
        DELETE
        FROM appointment
        WHERE appointment_id IN (
            SELECT aid
            FROM ( /* this weird format helps avoiding errors */
                     SELECT appointment_id AS aid
                     FROM appointment
                     WHERE appointment.citizen_id = new.citizen_id
                     ORDER BY appointment.date
                     LIMIT 1
                 ) AS a);
    END IF;
END $$
DELIMITER ;


DELIMITER $$
CREATE TRIGGER worker_clinic_integrity
    BEFORE INSERT
    ON appointment
    FOR EACH ROW
wci_trigger:
BEGIN
    DECLARE worker_clinic_integrity_error VARCHAR(255);
    DECLARE worker_clinic INT;

    SELECT clinic_id
    INTO worker_clinic
    FROM worker
    WHERE worker_id = new.worker_id;

    CALL get_random_worker_from_clinic_id(
            new.clinic_id,
            @rand_worker_id
        );

    /* if worker is null we choose a random valid
    worker from the user's chosen clinic and return */
    IF new.worker_id IS NULL THEN
        SET new.worker_id = (SELECT @rand_worker_id);
        LEAVE wci_trigger;
    END IF;

    SET worker_clinic_integrity_error = CONCAT('worker #',
                                               new.worker_id,
                                               ' is not in clinic #',
                                               new.clinic_id);

    /*  if worker is not assigned to a clinic
        assign him to the appointment clinic */
    IF worker_clinic IS NULL THEN
        SET worker_clinic = new.clinic_id;

        UPDATE worker
        SET clinic_id = worker_clinic
        WHERE worker_id = new.worker_id;
    END IF;

    IF new.clinic_id != worker_clinic THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = worker_clinic_integrity_error;
    END IF;

END $$
DELIMITER ;

/************************************************
 ****************** PROCEDURES ******************
 ************************************************/
DELIMITER $$
CREATE PROCEDURE get_random_worker_from_clinic_id(IN _clinic INT, OUT rand_worker_id INT)
BEGIN
    SELECT worker_id
    INTO rand_worker_id
    FROM (SELECT worker_id FROM worker WHERE clinic_id = _clinic) AS r1
             JOIN
         (SELECT CEIL(RAND() * (SELECT MAX(worker_id)
                                FROM (SELECT worker_id
                                      FROM worker
                                      WHERE clinic_id = _clinic) AS filtered)) AS id
         ) AS r2
    WHERE r1.worker_id >= r2.id
    ORDER BY r1.worker_id
    LIMIT 1;
END $$
DELIMITER ;

DELIMITER $$
CREATE PROCEDURE add_doses_to_supply(IN _amount_ INT, IN _supply_id_ INT)
BEGIN
    DECLARE i INT;
    SET i = 0;
    WHILE i < _amount_
        DO
            INSERT INTO dose VALUE (DEFAULT, _supply_id_);
            SET i = i + 1;
        END WHILE;
END $$
DELIMITER ;


CREATE PROCEDURE replace_worker_in_specific_date(IN _old_worker_id_ INT, IN _new_worker_id_ INT, IN _date_ DATE)
UPDATE appointment
SET appointment.worker_id = _new_worker_id_
WHERE appointment.worker_id = _old_worker_id_
  AND DATE(appointment.date) = _date_;

DELIMITER $$
CREATE PROCEDURE add_to_low_supply_clinics()
BEGIN
    DECLARE current_clinic INT;
    DECLARE current_supply INT;

    DROP TABLE IF EXISTS lows;
    CREATE TEMPORARY TABLE lows
    (
        _clinic_id_ INT
    );

    /* collect all low supply clinic IDs */
    INSERT INTO lows (_clinic_id_)
    SELECT cid
    FROM (SELECT c.clinic_id AS cid, COUNT(*) AS amount
          FROM supply
                   JOIN dose d ON supply.supply_id = d.supply_id
                   JOIN clinic c ON c.clinic_id = supply.clinic_id
          GROUP BY c.clinic_id
         ) AS min_inner
    WHERE amount < 1000;

    /* for each low supply clinic, add a 1000 doses supply */
    WHILE (SELECT COUNT(*) FROM lows) > 0
        DO
            SET current_clinic = (SELECT * FROM lows LIMIT 1);

            INSERT INTO supply VALUE (DEFAULT,
                                      current_clinic,
                                      1,
                                      DATE_ADD(DATE(NOW()), INTERVAL 1 MONTH));

            SELECT LAST_INSERT_ID() INTO current_supply;

            CALL add_doses_to_supply(1000, current_supply);

            DELETE FROM lows WHERE _clinic_id_ = current_clinic;

        END WHILE;
END $$
DELIMITER ;


/***********************************************
 ****************** SECURITY *******************
 ***********************************************/

CREATE USER 'city_manager'
    IDENTIFIED WITH caching_sha2_password BY 'cm_password'
    PASSWORD EXPIRE INTERVAL 180 DAY;

CREATE USER 'district_manager'
    IDENTIFIED WITH caching_sha2_password BY 'dm_password'
    PASSWORD EXPIRE INTERVAL 180 DAY;

CREATE USER 'regular_user'
    IDENTIFIED WITH caching_sha2_password BY 'hunter2'
    PASSWORD EXPIRE INTERVAL 180 DAY;

CREATE USER 'worker'
    IDENTIFIED WITH caching_sha2_password BY 'VeryStrongPassword'
    PASSWORD EXPIRE INTERVAL 180 DAY;


/******** city manager ********/
GRANT INSERT, DELETE, SELECT, UPDATE ON vac_operation.* TO 'city_manager';

/******** district manager ********/
CREATE VIEW district_view_citizen AS
SELECT *
FROM citizen
WHERE district = 'Merkaz';

CREATE VIEW district_view_clinic AS
SELECT *
FROM clinic
WHERE district = 'Merkaz';

CREATE VIEW district_view_worker AS
SELECT *
FROM clinic
WHERE district = 'Merkaz';

GRANT INSERT, DELETE, SELECT, UPDATE ON appointment TO 'district_manager';
GRANT SELECT, UPDATE ON district_view_citizen TO 'district_manager';
GRANT INSERT, DELETE, SELECT, UPDATE ON district_view_clinic TO 'district_manager';
GRANT INSERT, DELETE, SELECT, UPDATE ON dose TO 'district_manager';
GRANT INSERT, DELETE, SELECT, UPDATE ON supply TO 'district_manager';
GRANT INSERT, DELETE, SELECT, UPDATE ON vaccination TO 'district_manager';
GRANT SELECT ON vaccine TO 'district_manager';
GRANT INSERT, DELETE, SELECT, UPDATE ON district_view_worker TO 'district_manager';

/******** regular user ********/
CREATE VIEW user_view_appointment AS
SELECT *
FROM appointment
WHERE citizen_id = 123456789;

CREATE VIEW user_view_citizen AS
SELECT *
FROM citizen
WHERE citizen_id = 123456789;

CREATE VIEW user_view_clinic AS
SELECT *
FROM clinic
WHERE district IN (SELECT district
                   FROM citizen
                   WHERE citizen_id = 123456789);

CREATE VIEW user_view_vaccination AS
SELECT *
FROM vaccination
WHERE citizen_id = 123456789;


GRANT INSERT ON appointment TO 'regular_user';
GRANT SELECT, UPDATE (clinic_id, worker_id, date), DELETE ON user_view_appointment TO 'regular_user';
GRANT SELECT, UPDATE ON user_view_citizen TO 'regular_user';
GRANT SELECT ON user_view_clinic TO 'regular_user';
GRANT SELECT ON user_view_vaccination TO 'regular_user';

/******** worker ********/
CREATE VIEW worker_view_appointment AS
SELECT *
FROM appointment
WHERE worker_id = 123456789;

CREATE VIEW worker_view_citizen AS
SELECT *
FROM citizen
WHERE citizen_id IN (SELECT citizen_id FROM vaccination WHERE worker_id = 123456789)
   OR citizen_id IN (SELECT citizen_id FROM appointment WHERE worker_id = 123456789);

CREATE VIEW worker_view_supply AS
SELECT *
FROM supply
WHERE clinic_id IN (SELECT clinic_id
                    FROM worker
                    WHERE worker_id = 123456789);

CREATE VIEW worker_view_vaccination AS
SELECT *
FROM vaccination
WHERE worker_id = 123456789;

CREATE VIEW worker_view_worker AS
SELECT first_name, last_name, phone_num, clinic_id
FROM worker
WHERE clinic_id IN (SELECT clinic_id
                    FROM worker
                    WHERE worker_id = 123456789);

GRANT ALL ON worker_view_appointment TO 'worker';
GRANT INSERT ON appointment TO 'worker';
GRANT SELECT ON worker_view_citizen TO 'worker';
GRANT SELECT ON clinic TO 'worker';
GRANT SELECT ON dose TO 'worker';
GRANT SELECT ON worker_view_supply TO 'worker';
GRANT SELECT, UPDATE ON worker_view_vaccination TO 'worker';
GRANT INSERT ON vaccination TO 'worker';
GRANT SELECT ON vaccine TO 'worker';
GRANT SELECT ON worker_view_worker TO 'worker';
