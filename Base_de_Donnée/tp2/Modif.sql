ALTER TABLE produits MODIFY constructeur NOT NULL;
ALTER TABLE produits MODIFY modele NOT NULL;
ALTER TABLE produits MODIFY type NOT NULL;

ALTER TABLE pc MODIFY modele NOT NULL; 
ALTER TABLE pc MODIFY vitesse NOT NULL;
ALTER TABLE pc MODIFY ram NOT NULL;
ALTER TABLE pc MODIFY hd NOT NULL;
ALTER TABLE pc MODIFY cd NOT NULL;
ALTER TABLE pc MODIFY prix NOT NULL;

ALTER TABLE portables MODIFY modele NOT NULL;
ALTER TABLE portables MODIFY vitesse NOT NULL;
ALTER TABLE portables MODIFY ram NOT NULL;
ALTER TABLE portables MODIFY hd NOT NULL;
ALTER TABLE portables MODIFY ecran NOT NULL;
ALTER TABLE portables MODIFY prix NOT NULL;

ALTER TABLE imprimantes MODIFY modele NOT NULL;
ALTER TABLE imprimantes MODIFY couleur NOT NULL;
ALTER TABLE imprimantes MODIFY type NOT NULL;
ALTER TABLE imprimantes MODIFY prix NOT NULL;

ALTER TABLE produits ADD PRIMARY KEY (modele);
ALTER TABLE pc ADD PRIMARY KEY (modele);
ALTER TABLE portables ADD PRIMARY KEY (modele);
ALTER TABLE imprimantes ADD PRIMARY KEY (modele);

ALTER TABLE pc ADD FOREIGN KEY (modele) REFERENCES produits (modele);
ALTER TABLE portables ADD FOREIGN KEY (modele) REFERENCES produits (modele);
ALTER TABLE imprimantes ADD FOREIGN KEY (modele) REFERENCES produits (modele);

ALTER TABLE produits ADD CHECK (type='pc' or type='laptop' or type='printer');
ALTER TABLE pc ADD CHECK (cd='48x' or cd='56x');
ALTER TABLE imprimantes ADD CHECK (couleur=0 or couleur=1);
ALTER TABLE imprimantes ADD CHECK (type='ink-jet' or type='laser' or type='dry');

DESCRIBE produits;
DESCRIBE pc;
DESCRIBE portables;
DESCRIBE imprimantes;

