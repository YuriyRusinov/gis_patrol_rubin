/*==============================================================*/
/* Table: maclabels                                             */
/*==============================================================*/
create or replace function checkForMaclabelType() returns int4 as
$BODY$
declare
    isExist int4;
begin

    select f_is_type_exist('maclabel') into isExist;
    if(isExist > 0) then
        return 1;
    end if;
    
    create type maclabel as(m1 int4, m2 int4);
    
    return 2;

end
$BODY$
language 'plpgsql';


select checkForMaclabelType();
drop table if exists maclabels;
create table if not exists maclabels (
   id                   SERIAL not null,
   name                 VARCHAR              not null,
   mac_value            MACLABEL             not null,
   constraint PK_MACLABELS primary key (id)
);

alter table if exists users
   add constraint FK_USERS_REFERENCE_MACLABEL foreign key (id_maclabel)
      references maclabels (id)
      on delete restrict on update restrict;

