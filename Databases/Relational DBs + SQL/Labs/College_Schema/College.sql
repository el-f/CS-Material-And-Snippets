
-- create schema College;

USE College;

CREATE TABLE courseTable
(courseID INT NOT NULL,
courseName VARCHAR(50),
credits INT,
PRIMARY KEY (courseID)) 
ENGINE = InnoDB; 

CREATE TABLE studentTable
(studentID INT NOT NULL,
studentLastName VARCHAR(50),
studentFirstName VARCHAR(50),
birthPlace  VARCHAR(50),
city VARCHAR(50),
PRIMARY KEY (studentID))
ENGINE = InnoDB; 


CREATE TABLE facultyTable
(facultyName VARCHAR(50) NOT NULL,
PRIMARY KEY (facultyName))
ENGINE = InnoDB; 


CREATE TABLE departmentTable
(departmentID INT NOT NULL,
departmentName VARCHAR(50),
PRIMARY KEY (departmentID))
ENGINE = InnoDB; 


CREATE TABLE teacherTable
(teacherID INT NOT NULL,
teacherLastName VARCHAR(50),
teacherFirstName VARCHAR(50),
teacherDegree VARCHAR(50),
teacherSalary VARCHAR(50),
teacherAddress VARCHAR(50))
ENGINE = InnoDB;
 

CREATE TABLE FacultyDepartment  
(DID INT NOT NULL,
FName VARCHAR(50) NOT NULL,
PRIMARY KEY (DID, FName),
FOREIGN KEY (FName) REFERENCES facultyTable(facultyName),
FOREIGN KEY (DID) REFERENCES departmentTable(departmentID))
ENGINE = InnoDB; 


CREATE TABLE DepartmentCourse
(CID INT NOT NULL,
DID INT NOT NULL,
PRIMARY KEY (CID, DID),
FOREIGN KEY (CID) REFERENCES courseTable(courseID),
FOREIGN KEY (DID) REFERENCES departmentTable(departmentID))
ENGINE = InnoDB; 

CREATE TABLE DepartmentStudent
(SID INT NOT NULL,
DID INT NOT NULL,
PRIMARY KEY (SID, DID),
FOREIGN KEY (SID) REFERENCES studentTable(studentID),
FOREIGN KEY (DID) REFERENCES departmentTable(departmentID))
ENGINE = InnoDB; 


CREATE TABLE DepartmentTeacher
(TID INT NOT NULL,
DID INT NOT NULL,
PRIMARY KEY (TID, DID))
ENGINE = InnoDB; 


CREATE TABLE degree
(CID INT NOT NULL,
SID INT NOT NULL,
grade VARCHAR(50))
ENGINE = InnoDB; 


CREATE TABLE TeacherCourse
(CID INT NOT NULL,
TID INT NOT NULL,
classHour	VARCHAR(50),
classDay	VARCHAR(50),
building 	VARCHAR(50),
room		VARCHAR(50))
ENGINE = InnoDB; 


CREATE TABLE evaluations 
(TID INT NOT NULL,
SID INT NOT NULL,
score INT)
ENGINE = InnoDB; 


CREATE TABLE prerequisites
(CID INT NOT NULL,
PID INT NOT NULL)
ENGINE = InnoDB; 


