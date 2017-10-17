REM CS 448 PSO
REM SQL Materials

--Basic Select From Where query
--1: Find all Students that are seniors (i.e. class standing is 'SR')
SELECT *
FROM Student S
WHERE S.standing = 'SR';

--Select From Where with multiple predicates in WHERE
--2: Find all Departments where the department budget is between 500000 and 1500000
SELECT *
FROM Dept D
WHERE D.budget >= 500000 AND D.budget <= 1500000;

--Projection of specific attributes
--3: Find the names of all faculty and the department ID they are in
SELECT F.fname, F.deptid
FROM Faculty F;

--Basic joins
--4: Find the name of all employees and the ID of the department they work in
SELECT E.ename, W.did
FROM Emp E, Works W
WHERE E.eid = W.eid;

--Same query with no projection, to show that joined table is all columns of joined tables
SELECT *
FROM Emp E, Works W
WHERE E.eid = W.eid;

--ANSI syntax
SELECT E.ename, W.did
FROM Emp E JOIN Works W ON E.eid = W.eid;

--Natural join option
SELECT E.ename, W.did
FROM Emp E NATURAL JOIN Works W;

--Chaining joins
--5: Find the name of all employees and the name of the department they work in
SELECT E.ename, D.dname
FROM Emp E JOIN Works W ON E.eid = W.eid JOIN Dept D ON W.did = D.did;

--Ordering results
--6: Find the names of salaries of all employees, sorted by salary in ascending order
SELECT E.ename, E.salary
FROM Emp E
ORDER BY E.salary ASC;

--Descending order?
SELECT E.ename, E.salary
FROM Emp E
ORDER BY E.salary DESC;

--Ordering by multiple columns
--7: Find the names, class standing, and age of all students - ordered first by class standing in descending order
--and then by age in ascending order
SELECT S.sname, S.standing, S.age
FROM Student S
ORDER BY S.standing DESC, S.age ASC;

--Aggregate functions without grouping
--8: Find the number of employees that work in department 2
SELECT Count(*)
FROM Emp E JOIN Works W ON E.eid = W.eid
WHERE W.did = 2;

--Aliasing of the count(*) field
SELECT Count(*) AS NumEmps
FROM Emp E JOIN Works W ON E.eid = W.eid
WHERE W.did = 2;

--9: Find the total budget for all departments combined
SELECT Sum(D.Budget) AS TotalBudget
FROM Dept D;

--Basic grouping and aggregation over grouping
--10: Find the name of each department and the average salary of all employees in that department
--Start with the full join of tables to get all the information we need
SELECT D.did, D.dname, E.salary
FROM Emp E JOIN Works W ON E.eid = W.eid JOIN Dept D ON W.did = D.did;

--We're going to use grouping to get each department out of the joined tables
SELECT D.did FROM Emp E JOIN Works W ON E.eid = W.eid JOIN Dept D ON W.did = D.did GROUP BY D.did;sn

--Add the name - all projected columns must be present in GROUP BY
SELECT D.did, D.dname FROM Emp E JOIN Works W ON E.eid = W.eid JOIN Dept D ON W.did = D.did GROUP BY D.did, D.dname;

--Now to put the joined tables to use - getting the average salary
SELECT D.did, D.dname, AVG(E.salary) AS AvgDeptSalary FROM Emp E JOIN Works W ON E.eid = W.eid JOIN Dept D ON W.did = D.did GROUP BY D.did, D.dname;

--How to get rid of the department ID field? Use subquery
SELECT dname, AvgDeptSalary
FROM (	SELECT D.did, D.dname, AVG(E.salary) AS AvgDeptSalary
		FROM Emp E JOIN Works W ON E.eid = W.eid JOIN Dept D ON W.did = D.did
		GROUP BY D.did, D.dname);
		
--Can also order by - say the Dept ID - note where we place the ORDER BY clause,
--since Dept.did is not visible in the outermost query. Also ASC is the default ordering option
SELECT dname, AvgDeptSalary
FROM (	SELECT D.did, D.dname, AVG(E.salary) AS AvgDeptSalary
		FROM Emp E JOIN Works W ON E.eid = W.eid JOIN Dept D ON W.did = D.did
		GROUP BY D.did, D.dname
		ORDER BY D.did);
		
--HAVING clause - like WHERE, but filter results after a GROUP BY
--11:Find the suppliers that supply more than 2 different parts and show how many parts they offer
SELECT S.sid, S.sname, Count(*) AS NumParts
FROM Suppliers S JOIN Catalog C ON S.sid = C.sid
GROUP BY S.sid, S.sname
HAVING Count(*) > 2;

--Comparing with aggregate value - use inline views
--12:Find the name and budget of departments that have the largest budget out of all departments.
--If there are ties, report all departments
SELECT D.dname, D.budget
FROM Dept D,
	(	SELECT Max(budget) AS MaxDeptBudget
		FROM Dept) M
WHERE D.budget = M.MaxDeptBudget;
