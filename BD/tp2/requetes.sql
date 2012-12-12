/* -------------- requete 1 ------------- */

SELECT modele 
FROM produits
WHERE type = 'laptop';

/* -------------- requete 2 ------------- */

SELECT DISTINCT constructeur 
FROM produits;


/* -------------- requete 3 ------------- */

SELECT modele 
FROM produits
WHERE type = 'pc' OR type = 'laptop';

/* -------------- requete 4 ------------- */

SELECT modele 
FROM pc 
WHERE ram = 256;

/* -------------- requete 5 ------------- */

SELECT modele 
FROM pc
WHERE prix < 1100;

/* -------------- requete 6 ------------- */

SELECT modele 
FROM portables 
WHERE hd>=50 AND prix<=1400;

/* -------------- requete 7 ------------- */

SELECT modele 
FROM imprimantes 
WHERE couleur=1 AND type='laser';

/* -------------- requete 8 ------------- */

SELECT pr.modele 
FROM produits pr,portables po 
WHERE pr.modele=po.modele AND constructeur='D' AND ram>=256;

/* -------------- requete 9 ------------- */

(SELECT pr.modele 
FROM produits pr,pc 
WHERE pr.modele=pc.modele AND constructeur='D' AND ram>=256) 
UNION 
(SELECT pr.modele 
FROM produits pr,portables po 
WHERE pr.modele=po.modele AND constructeur='D' AND ram>=256);

/* -------------- requete 10 ------------- */

(SELECT modele 
 FROM pc 
 WHERE prix<1200) 
UNION 
(SELECT modele 
 FROM portables 
 WHERE prix<1200);

/* -------------- requete 11 ------------- */

(SELECT constructeur 
 FROM produits 
 WHERE type='pc') 
INTERSECT
(SELECT constructeur 
 FROM produits 
 WHERE type='printer');

SELECT DISTINCT p1.constructeur 
FROM produits p1, produits p2 
WHERE p1.constructeur = p2.constructeur 
      AND p1.type='pc' AND p2.type='printer';


/* -------------- requete 12 ------------- */

(SELECT constructeur 
 FROM produits 
 WHERE type='pc') 
INTERSECT 
(SELECT constructeur 
 FROM produits 
 WHERE type='printer')
INTERSECT 
(SELECT constructeur 
 FROM produits 
 WHERE type='laptop');

SELECT constructeur
FROM produits 
GROUP BY constructeur 
HAVING count(DISTINCT type)=(SELECT count(DISTINCT type) FROM produits);

SELECT DISTINCT p1.constructeur 
FROM produits p1, produits p2, produits p3 
WHERE p1.constructeur = p2.constructeur  
      AND p2.constructeur = p3.constructeur 
      AND p1.type='pc' AND p2.type='printer' AND p3.type='laptop';

/* -------------- requete 13 ------------- */
(SELECT constructeur 
 FROM produits 
 WHERE type='pc') 
MINUS 
(SELECT constructeur 
 FROM produits 
 WHERE type='printer')
MINUS
(SELECT constructeur 
 FROM produits 
 WHERE type='laptop');

/* -------------- requete 14 ------------- */
SELECT constructeur
FROM produits 
GROUP BY constructeur 
HAVING count(DISTINCT type)=1;

(
(SELECT constructeur 
 FROM produits 
 WHERE type='pc') 
MINUS 
(SELECT constructeur 
 FROM produits 
 WHERE type='printer')
MINUS
(SELECT constructeur 
 FROM produits 
 WHERE type='laptop')
)
UNION
(
(SELECT constructeur 
 FROM produits 
 WHERE type='printer') 
MINUS 
(SELECT constructeur 
 FROM produits 
 WHERE type='pc')
MINUS
(SELECT constructeur 
 FROM produits 
 WHERE type='laptop')
)
UNION
(
(SELECT constructeur 
 FROM produits 
 WHERE type='laptop') 
MINUS 
(SELECT constructeur 
 FROM produits 
 WHERE type='printer')
MINUS
(SELECT constructeur 
 FROM produits 
 WHERE type='pc')
);

/* -------------- requete 15 ------------- */

(SELECT constructeur 
 FROM produits p,pc
 WHERE p.modele=pc.modele AND ram>=1024 AND cd='56x')
INTERSECT
(SELECT constructeur 
 FROM produits p, portables po
 WHERE p.modele=po.modele AND ecran>15)
INTERSECT
(SELECT constructeur 
 FROM produits p,imprimantes i
 WHERE p.modele=i.modele AND prix<300);


/* -------------- requete 16 ------------- */
/*---- sol 1 : sans calcul du prix ----*/
(
(SELECT produits.constructeur
FROM (SELECT * FROM pc WHERE ram>=1024 AND (vitesse=3 OR vitesse=3.5) 
      AND Hd>=160 ) ordi,produits 
WHERE ordi.modele=produits.modele)
UNION
(SELECT constructeur
FROM (SELECT * FROM portables WHERE ram>=1024 AND (vitesse=3 OR vitesse=3.5) 
      AND Hd>=160 ) laptops,produits 
WHERE laptops.modele=produits.modele)
)
INTERSECT
(SELECT produits.constructeur
FROM (SELECT * FROM imprimantes WHERE couleur=1) impr,produits
WHERE impr.modele=produits.modele);

/*---- sol 2 ----*/
(SELECT ordi.constructeur, ordi.prix+impr.prix prix
FROM (SELECT * FROM produits p,pc WHERE p.modele=pc.modele AND ram>=1024 
      AND (vitesse=3 OR vitesse=3.5) AND Hd>=160 ) ordi, 
     (SELECT * FROM produits p,imprimantes i WHERE p.modele=i.modele 
      AND couleur=1) impr 
WHERE ordi.constructeur=impr.constructeur)
UNION
(SELECT ordi.constructeur, ordi.prix+impr.prix prix
FROM (SELECT * FROM produits p,portables po WHERE p.modele=po.modele 
      AND ram>=1024 AND (vitesse=3 OR vitesse=3.5) AND Hd>=160 ) ordi, 
     (SELECT * FROM produits p,imprimantes i WHERE p.modele=i.modele 
      AND couleur=1) impr 
WHERE ordi.constructeur=impr.constructeur);

/* -------------- requete 17 ------------- */

SELECT HD
FROM pc
GROUP BY HD
HAVING count(DISTINCT modele)>=2;

SELECT DISTINCT p1.HD
FROM pc p1, pc p2
WHERE p1.HD=p2.HD AND p1.modele <> p2.modele;

/* -------------- requete 18 ------------- */

SELECT DISTINCT ordi1.constructeur
FROM (SELECT constructeur,p.modele,vitesse FROM pc,produits p 
       WHERE pc.modele=p.modele AND vitesse>=3
      UNION 
      SELECT constructeur,p.modele,vitesse FROM portables po,produits p 
       WHERE po.modele=p.modele AND vitesse>=3) ordi1, 
     (SELECT constructeur,p.modele,vitesse FROM pc,produits p 
       WHERE pc.modele=p.modele AND vitesse>=3
      UNION 
      SELECT constructeur,p.modele,vitesse FROM portables po,produits p 
       WHERE po.modele=p.modele AND vitesse>=3) ordi2
WHERE ordi1.constructeur=ordi2.constructeur 
      AND ordi1.modele<>ordi2.modele;


/* -------------- requete 19 ------------- */

SELECT DISTINCT constructeur
FROM ((SELECT modele,vitesse FROM pc) 
      UNION (SELECT modele,vitesse FROM portables)) ordi, produits pr
WHERE ordi.modele=pr.modele 
      AND vitesse>=ALL((SELECT vitesse FROM pc) 
                       UNION (SELECT vitesse FROM portables));

SELECT constructeur 
FROM produits p, 
((SELECT DISTINCT modele FROM produits WHERE type='pc' OR type='laptop')
 MINUS
(SELECT DISTINCT ordi1.modele
 FROM ((SELECT modele,vitesse FROM pc ) 
       UNION (SELECT modele,vitesse FROM portables )) ordi1, 
      ((SELECT modele,vitesse FROM pc ) 
       UNION (SELECT modele,vitesse FROM portables )) ordi2
      WHERE ordi1.modele<>ordi2.modele 
            AND ordi1.vitesse<ordi2.vitesse)) rapide
WHERE p.modele=rapide.modele;

/* -------------- requete 20 ------------- */

SELECT constructeur
FROM produits
WHERE type='pc'
GROUP BY constructeur
HAVING count(DISTINCT modele)=3;

(SELECT DISTINCT p1.constructeur
FROM (SELECT modele,constructeur FROM produits WHERE type='pc') p1,  
     (SELECT modele,constructeur FROM produits WHERE type='pc') p2,  
     (SELECT modele,constructeur FROM produits WHERE type='pc') p3
WHERE p1.constructeur=p2.constructeur 
     AND p2.constructeur=p3.constructeur
     AND p1.modele<>p2.modele
     AND p1.modele<>p3.modele
     AND p2.modele<>p3.modele)
MINUS
(SELECT DISTINCT p1.constructeur
FROM (SELECT modele,constructeur FROM produits WHERE type='pc') p1,  
     (SELECT modele,constructeur FROM produits WHERE type='pc') p2,  
     (SELECT modele,constructeur FROM produits WHERE type='pc') p3,
     (SELECT modele,constructeur FROM produits WHERE type='pc') p4
WHERE p1.constructeur=p2.constructeur 
     AND p2.constructeur=p3.constructeur
     AND p3.constructeur=p4.constructeur
     AND p1.modele<>p2.modele
     AND p1.modele<>p3.modele
     AND p1.modele<>p4.modele
     AND p2.modele<>p3.modele
     AND p2.modele<>p4.modele
     AND p3.modele<>p4.modele); 

