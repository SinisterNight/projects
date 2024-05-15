SELECT pid, pname
FROM tblProducts
WHERE city = 'Dallas';

SELECT o.ordno, o.cid, c.cname
FROM tblOrders o
INNER JOIN tblCustomers c
    ON o.cid = c.cid
WHERE c.city = 'Dallas';

SELECT p.pid
FROM tblProducts p
INNER JOIN tblOrderItems oi
    ON p.pid = oi.pid
INNER JOIN tblOrders o
    ON oi.ordno = o.ordno
INNER JOIN tblCustomers c
    ON o.cid = c.cid
WHERE c.cname = 'ACME' AND c.city = 'Duluth';

SELECT o.ordno, a.aid
FROM tblOrders o
INNER JOIN tblAgents a
    ON o.aid = a.aid
WHERE a.aname = 'agent Smith';