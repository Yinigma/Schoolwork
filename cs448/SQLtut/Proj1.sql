REM Benjamin Denison
REM bdenison@purdue.edu

--Question 1
SELECT EmpName FROM Employee WHERE ZipCode IN (47906, 47907);

--Question 2
SELECT DISTINCT P.ProjName 
FROM Project P, ProjectManager M  
WHERE P.ProjId = M.ProjId;

--Question 3
SELECT ProjName 
FROM Project ORDER BY ProjName DESC;

--Question 4
SELECT U.UnivName, Count(E.EmpId) AS NumGradsWorking 
FROM University U LEFT JOIN Graduate G ON U.UnivId = G.UnivID 
JOIN Employee E ON G.EmpId = E.EmpId GROUP BY U.UnivName;

--Question 5
SELECT E.EmpName, D.DeptName, G.GradYear 
FROM Employee E LEFT JOIN Department D ON E.DeptId = D.DeptID 
LEFT JOIN Graduate G ON E.EmpId = G.EmpId;

--Question 6
SELECT E.EmpName 
FROM Employee E 
WHERE E.DeptId = 2 ORDER BY E.EmpName ASC;

--Question 7
SELECT E.EmpName 
FROM University U LEFT JOIN Graduate G ON U.UnivID = G.UnivID 
LEFT JOIN Employee E ON G.EmpID = E.EmpID 
WHERE G.GradYear > 2000 AND U.UnivName = 'Purdue';

--Question 8
SELECT E.Zipcode, Count(*) AS NumEmpsAtZip 
FROM Employee E 
GROUP BY E.ZipCode
ORDER BY E.ZipCode DESC;

--Question 9
SELECT E.EmpName 
FROM Employee E LEFT JOIN Graduate G ON E.EmpId = G.EmpId, 
	(SELECT Max(GradYear) AS MaxGrad
	FROM Graduate) Y
WHERE G.GradYear = Y.MaxGrad;

--Question 10
SELECT P.ProjName, E.EmpName
FROM Project P JOIN EmpProject EP ON P.ProjId = EP.ProjId
JOIN Employee E ON EP.EmpId = E.EmpId
ORDER BY P.ProjName ASC, E.EmpName ASC;



