create table eleve(num_e int, nom varchar2(20), prenom varchar2(20), adresse varchar2(100), date_naiss date, statut varchar2(10));
alter table  eleve add primary key (num_e);

create table assiste (num_e int, date_s date, heure_s date , nb_fautes int, num_cd int);
alter table assiste add primary key (num_e, heure_s, date_s);

create table seance (date_s date, heure_s date, num_serie int, num_cd int);
alter table seance add primary key (heure_s, date_s);

create table examen (date_session date, nb_presents int);
alter table examen add primary key (date_session);

create table present (num_e int, date_session date, nb_fautes int);
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

/*

create or replace trigger T1
after insert or update on present
for each row
declare faute int;

begin
	select nb_fautes into faute from present where num_e = :new.num_e;
	if(faute <= 5) then DBMS_OUTPUT.PUT_LINE('Permis obtenu');
	end if;
end T1;

.
run
*/


/* Trigger de mise à jour du nombre de présent dans la table examen
 * lors d'une insertion dans la table present */
create or replace trigger present_insert
after insert or update or delete on present
for each row
begin
	if inserting then
		update examen set nb_presents = 1+nb_presents where date_session = :new.date_session;
	elsif updating then
		update examen set nb_presents = nb_presents - 1 where date_session = :old.date_session;
		update examen set nb_presents = nb_presents where date_session = :new.date_session;
	elsif deleting then
		update examen set nb_presents = nb_presents - 1 where date_session = :old.date_session;
	end if;
end present_insert;




/* Trigger de mise à jour du nombre de présent dans la table examen
 * lors d'une insertion dans la table present */
create or replace trigger miseajour 
after insert on present
declare
cursor c is select count(num_e), date_session from present group by date_session;
wdate_session varchar2(20);	
nbp varchar2(1);
begin
	open c;
	loop
	fetch c into nbp, wdate_session;
	exit when c%NOTFOUND;
	if nbp < 8 then
		update examen set nb_presents = nbp where date_session = wdate_session;
	else
		DBMS_OUTPUT.PUT_LINE('Le nombre doit pas dépasser 8');
	end if;

end loop;
close c;
end;
	
.
run

