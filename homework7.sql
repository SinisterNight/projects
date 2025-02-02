/* 
Question 1 
*/

SELECT Geo_QNAME, acs18_5yr_b15003024
    FROM b15003 AS outS
    WHERE acs18_5yr_b15003024 < ALL
    (
        SELECT AVG(acs18_5yr_b15003024)
        FROM b15003
        WHERE outS.Geo_STUSAB = Geo_STUSAB
        GROUP BY Geo_STUSAB
    )
    ORDER BY Geo_STUSAB, acs18_5yr_b15003024 DESC;
	

/* 
Question 2 
*/


SELECT Geo_QName, SUM(ACS18_5yr_B15003024::NUMERIC/ACS18_5yr_B15003001) AS ratios
    FROM b15003 AS outS
	GROUP BY Geo_STUSAB, Geo_QName
        HAVING SUM(ACS18_5yr_B15003024::NUMERIC/ACS18_5yr_B15003001) < ALL
		(
            SELECT SUM(ACS18_5yr_B15003024)::NUMERIC/SUM(ACS18_5yr_B15003001)
			FROM b15003
			WHERE outS.Geo_STUSAB = Geo_STUSAB
			GROUP BY Geo_STUSAB	
    )
    ORDER BY Geo_STUSAB;
			

/* 
Question 3 
*/

SELECT Geo_QNAME, acs18_5yr_b15003017
    FROM b15003 AS outS
    WHERE acs18_5yr_b15003017 > ALL
    (
        SELECT AVG(acs18_5yr_b15003017)
        FROM b15003
        WHERE outS.Geo_STUSAB = Geo_STUSAB
        GROUP BY Geo_STUSAB
    )
    ORDER BY Geo_STUSAB DESC, Geo_QNAME DESC;
	
/* 
Question 4 
*/

SELECT Geo_NAME AS countyName COUNT(Geo_NAME) AS theCount
FROM b15003
GROUP BY Geo_NAME
HAVING COUNT(Geo_NAME) > 1
ORDER BY Geo_NAME ASC;