use college;

-- a
select studentFirstName, studentLastName, city
from studenttable;

-- b
-- create view
create view cities as (
select studentFirstName, studentLastName, city
from studenttable
);

-- c
select * from cities;

-- d
insert into studenttable value (18, 'Israel', 'Israeli', 'Russia', 'Ramat-Gan');

-- e
select * from cities;

-- f
update cities
set city = 'Rohovot'
where city = 'Rechovot';

-- g
select * from cities;

-- h
select studentFirstName, studentLastName, city
from studenttable;

-- i
update cities
set studentLastName = 'Klein'
where studentLastName = 'Klain';

-- j
select * from cities;

-- k
-- would not work since we would need default values for the other columns
-- insert into cities (studentFirstName, studentLastName, city)
-- values  ('Momo', 'Maman', 'Tel-Aviv');

-- l
create view degrees as (
select teacherID, teacherFirstName, teacherLastName, teacherDegree
from teachertable
);

select * from degrees;

-- m
insert into degrees	(teacherID, teacherFirstName, teacherLastName, teacherDegree)
values (100,'Simon','Pah','Prof');

select * from teachertable;

-- n
create view teacherDepartments as (select * from
 departmentteacher join teachertable on (departmentteacher.TID = teachertable.teacherID)
	 join departmenttable on (departmenttable.departmentID = departmentteacher.DID)
);

select * from teacherDepartments;

-- o
-- not gonna work because of join



