-- CREATE SCHEMA lab8;

------


USE lab8;

CREATE TABLE table1
(ID INT,
 name VARCHAR(30),
 birthdate DATE); 
 
CREATE TABLE table2
(ID INT,
 name VARCHAR(30),
 birthdate DATE);
 
-- CREATE TABLE table3
-- (ID INT,
-- name VARCHAR(30),
--  birthdate DATE);
 
 ALTER TABLE table2
 ADD CONSTRAINT pk2 PRIMARY KEY (ID);
 
 ------
 
 use lab8;

INSERT INTO table2 (ID, name, birthdate)
VALUES (456, 'hi', '1996-09-06'),
	   (248, 'nobody', '2004-06-01'),
	   (534, 'newname', NULL);
	   
------

USE lab8;

DELETE FROM table2
WHERE YEAR(birthdate) = 2004;

------

use lab8;

INSERT INTO table1 
VALUES (234, 'nobody', '1939-12-21');

UPDATE table1
SET name = 'newname'
WHERE ID = 123;

INSERT INTO table1 (name)
VALUES ('banana');

SELECT * 
FROM table1;

INSERT INTO table2 (name)
VALUES ('banana');

SELECT * 
FROM table2;

------

USE lab8;

CREATE TABLE table4
(CoolID INT NOT NULL auto_increment,
 Fruit VARCHAR(25),
 PRIMARY KEY (CoolID)
 );
 
 
 INSERT INTO table4 (Fruit)
 VALUES ('banana'), ('apple'), ('orange'), ('peach');
 
 SELECT * from table4;
 
 INSERT INTO table4 (CoolID, Fruit)
 VALUES (79,'strawberry');
 
 INSERT INTO table4 (Fruit)
 VALUES ('plum');
 
 -----
 
 USE lab8;

CREATE TABLE table40
(CoolID INT NOT NULL auto_increment,
 Fruit VARCHAR(25),
 PRIMARY KEY (CoolID)
 ) Engine = InnoDB;
 
 
 INSERT INTO table40 (Fruit)
 VALUES ('banana'), ('apple'), ('orange'), ('peach');
 
 -- SELECT * from table4;
 
 -- Foreign keys require use of InnoDB engine for all tables
 
 INSERT INTO table40 (CoolID, Fruit)
 VALUES (79,'strawberry');
 
 INSERT INTO table40 (Fruit)
 VALUES ('plum');
 
 CREATE TABLE table70
(CoolID INT NOT NULL auto_increment,
 Fruit VARCHAR(25),
 PRIMARY KEY (CoolID),
 FOREIGN KEY (CoolID)
		REFERENCES table40 (CoolID)
 ) engine = InnoDB;
 
 INSERT INTO table70 (CoolID, fruit)   -- works fine because 1 is a key in table40
 VALUES (1, 'lemon');
 
 INSERT INTO table70 (CoolID, fruit)   -- fails because violates foreign key constraint
 VALUES (6, 'clementine')
 
 
	   