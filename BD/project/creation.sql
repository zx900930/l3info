DROP TABLE EMP;
DROP TABLE DEPT;

CREATE TABLE EMP(
ENO int NOT NULL,
ENOM varchar2(20),
PROF varchar2(20),
DATEEMB date,
SAL int,
COMM int,
DNO int,
PRIMARY KEY (ENO),
FOREIGN KEY (DNO) REFERENCES DEPT (DNO),
);

CREATE TABLE DEPT(
DNO int NOT NULL,
DNOM varchar2(20),
DIR int,
VILLE varchar2(20),
PRIMARY KEY (DNO),
);

SELECT * FROM tab;

DESCRIBE EMP;
DESCRIBE DEPT;
