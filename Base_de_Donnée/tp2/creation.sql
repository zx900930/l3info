DROP TABLE pc;
DROP TABLE portables;
DROP TABLE imprimantes;
DROP TABLE produits;

CREATE TABLE produits(
constructeur char NOT NULL,
modele int NOT NULL,
type varchar2(10) NOT NULL,
PRIMARY KEY (modele),
CHECK (type='pc' or type='laptop' or type='printer')
);

CREATE TABLE pc(
modele int NOT NULL,
vitesse float NOT NULL,
ram int NOT NULL,
hd float NOT NULL,
cd char(3) NOT NULL,
prix float NOT NULL,
PRIMARY KEY (modele),
FOREIGN KEY (modele) REFERENCES produits (modele),
CHECK (cd='48x' or cd='56x')
);

CREATE TABLE portables(
modele int NOT NULL,
vitesse float NOT NULL,
ram int NOT NULL,
hd float NOT NULL,
ecran float NOT NULL,
prix float NOT NULL,
PRIMARY KEY (modele),
FOREIGN KEY (modele) REFERENCES produits (modele)
);

CREATE TABLE imprimantes(
modele int NOT NULL,
couleur int NOT NULL,
type varchar2(10) NOT NULL,
prix float NOT NULL,
PRIMARY KEY (modele),
FOREIGN KEY (modele) REFERENCES produits (modele),
CHECK (couleur=0 or couleur=1),
CHECK (type='ink-jet' or type='laser' or type='dry')
);

SELECT * FROM tab;

DESCRIBE produits;
DESCRIBE pc;
DESCRIBE portables;
DESCRIBE imprimantes;

