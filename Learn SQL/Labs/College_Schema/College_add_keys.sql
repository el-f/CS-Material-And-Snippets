use college;

alter table teachertable
add constraint teacherPK primary key (teacherID);

alter table departmentteacher
add constraint teacherFK foreign key (TID) references teachertable (teacherID);

alter table departmentteacher
add constraint departmentFK foreign key (DID) references departmenttable (departmentID);

alter table teachercourse
add constraint TCteacherFK foreign key (TID) references teachertable (teacherID);

alter table teachercourse
add constraint TCcourseFK foreign key (CID) references coursetable (courseID);

alter table degree 
add constraint DcourseFK foreign key (CID) references  coursetable (courseID);

alter table degree
add constraint DStudentFK foreign key (SID) references studenttable (studentID);

alter table evaluations
add constraint ETeacherFK foreign key (TID) references teachertable (teacherID);

alter table evaluations
add constraint EStudentFK foreign key (SID) references studenttable (studentID);

alter table prerequisites
add constraint PCourseFK foreign key (CID) references coursetable (courseID);

alter table prerequisites
add constraint PprerequisiteFK foreign key (PID) references coursetable (courseID);

alter table prerequisites
add constraint PPK primary key (CID, PID);