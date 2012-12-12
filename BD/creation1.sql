create table eleve(num_e int, nom varchar2(20), prenom varchar2(20), adresse varchar2(100), date_naiss varchar2(12), statut varchar2(10));
alter table  eleve add primary key (num_e);

create table assiste (num_e int, date_s varchar2(20), heure_s varchar2(20), nb_fautes int, num_cd int);
alter table assiste add primary key (num_e, heure_s, date_s);

create table seance (date_s varchar2(20), heure_s varchar2(20), num_serie int, num_cd int);
alter table seance add primary key (heure_s, date_s);

create table examen (date_session varchar2(20), nb_presents int);
alter table examen add primary key (date_session);

create table present (num_e int, date_session varchar2(20), nb_fautes int);
alter table present add primary key (num_e);


create table cd (num_cd int, editeur varchar2(20));
alter table cd add primary key (num_cd);


create table serie (num_serie int, num_cd int);
alter table serie add primary key (num_serie, num_cd);


create table question (intitule varchar2(50), reponse int, difficulte int, theme varchar2(30));
alter table question add primary key (intitule);


create table estcomposee( num_serie int, num_cd int, intitule varchar2(50), ordre int);
 alter table estcomposee add primary key (num_serie, num_cd,intitule);

 alter table assiste add foreign key (num_e) references eleve (num_e);
 alter table present add foreign key (num_e) references eleve (num_e);




