USE College;

INSERT INTO courseTable VALUES
(1,'English',3),
(2,'Visual Basic',4),
(3,'Statistics',4),
(4,'C++',3),
(5,'Operating Systems',6),
(6,'Boolean Algebra',6),
(7,'Data Base',4);

INSERT INTO studentTable VALUES
(12,'Goldfarb','Isaac','France','Jerusalem'),
(13,'Ofir','Moti','Italy','Haifa'),
(14,'Lazaar','Eti','Spain','Ashdod'),
(15,'Kochavi','Israel','Israel','Haifa'),
(16,'Levy','Shlomi','Israel','Tel Aviv'),
(17,'Klein','Tamar','Israel','Rechovot');

INSERT INTO teacherTable VALUES
(1,'Haber','Yona','Prof','5000','Jerusalem'),
(2,'Levy','Moshe','Dr','4000','Tel - Aviv'),
(3,'Cohen','Meir','Prof','6000','Ashdod'),
(4,'Ezra','Gidoon','Dr','6000','Tel - Aviv'),
(5,'Fogel','Shimon','Dr','4000','Rechovot');

INSERT INTO departmentTable VALUES
(21,'Biology'),
(22,'Chemistry'),
(23,'Computer Science'),
(24,'Mathematics'),
(25,'Physics');

INSERT INTO facultyTable VALUES
('Engineering'),
('Natural Sciences'),
('Exact Sciences');

INSERT INTO FacultyDepartment VALUES
(21,'Natural Sciences'),
(23,'Engineering'),
(24, 'Engineering'),
(25,'Exact Sciences');

INSERT INTO DepartmentCourse VALUES
(1,21),
(1,22),
(1,23),
(1,24),
(1,25),
(2,23),
(3,24),
(4,23),
(5,23),
(6,24);



INSERT INTO DepartmentTeacher VALUES
(1, 24),
(2, 23),
(3, 22),
(4, 25);

INSERT INTO DepartmentStudent VALUES
(12, 24),
(13, 23),
(14, 23),
(15, 22),
(16, 25),
(17, 21);

INSERT INTO degree VALUES
(1,15,'BA'),
(1,17,'BSc'),
(2,14,'BA'),
(3,16,'BSc'),
(4,13,'BSc'),
(6,12,'BA');

INSERT INTO prerequisites VALUES
(1,3),
(2,4),
(3,2),
(4,6),
(5,1),
(6,3);


INSERT INTO TeacherCourse VALUES
(1,1,'1200','Wed','Y','100'),
(2,3,'1400','Tue','Z','300'),
(3,2,'1500','Thu','X','200'),
(4,2,'1300','Mon','Y','200'),
(5,3,'1000','Fri','Z','300'),
(6,1,'1200','Sun','X','100');

INSERT INTO evaluations VALUES
(1,12,70),
(1,15,67),
(1,17,89),
(2,13,90),
(2,16,38),
(3,14,25); 

