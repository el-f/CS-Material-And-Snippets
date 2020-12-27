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
