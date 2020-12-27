use college;

-- 1
select * from departmenttable
where departmentID in (select DID from facultydepartment where FName = 'Natural Sciences');

-- 2
select classHour, classDay, (select courseName from coursetable where CID = courseID)
from teachercourse
where TID in (select teacherID from teachertable where teacherFirstName = 'Yona' and teacherLastName = 'Haber');
 
-- 3
select studentFirstName, studentLastName, city
from studenttable
where studentID in (select SID from departmentstudent where DID in (select departmentID from departmenttable where departmentName = 'Mathematics'));
 
-- 4
select (select DID from departmentteacher where teacherID = TID), teacherFirstName, teacherLastName, teacherAddress
from teachertable
where teacherAddress = 'Tel - Aviv' or teacherAddress = 'Jerusalem';
 
-- 5
select departmentID, teacherFirstName, teacherLastName, teacherAddress
from (teachertable join departmentteacher on (teacherID = TID)) join departmenttable on (DID = departmentID)
where teacherAddress = 'Tel - Aviv' or teacherAddress = 'Jerusalem'
order by departmentName , teacherAddress;

-- 6
select studentFirstName, studentLastName
from studenttable
join (select * from evaluations where TID in 
		(select teacherID from teachertable where (teacherFirstName = 'Moshe' and teacherLastName = 'Levy'))
) as tt on (studentID = SID);

-- 7
select departmentName, count(TID)
from (select * from departmentteacher join departmenttable on (DID = departmentID)) as dd group by departmentName;

-- 8
select teacherFirstName, teacherLastName, teacherSalary
from teachertable
where teacherDegree = 'Dr' and teacherSalary > (select min(teacherSalary) as minp from teachertable where teacherDegree = 'Prof')
order by teacherSalary DESC;

-- 9
select courseName, (select courseName from coursetable where PID = courseID) as PName
from (prerequisites join coursetable as namedt on (CID = courseID))
order by courseName, PName ;