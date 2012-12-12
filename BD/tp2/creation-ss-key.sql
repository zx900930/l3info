DROP TABLE pc;
DROP TABLE portables;
DROP TABLE imprimantes;
DROP TABLE produits;

CREATE TABLE produits(
constructeur char,
modele int,
type varchar2(10)
);

CREATE TABLE pc(
modele int,
vitesse float,
ram int,
hd float,
cd char(3),
prix float
);

CREATE TABLE portables(
modele int,
vitesse float,
ram int,
hd float,
ecran float,
prix float
);

CREATE TABLE imprimantes(
modele int,
couleur int,
type varchar2(10),
prix float
);



