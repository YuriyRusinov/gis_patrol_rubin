--\encoding win1251

begin;
--\i ./functions/misc/f_create_lang.sql
\i ./functions/misc/setmactonull.sql
\i ./functions/misc/f_is_type_exist.sql
\i ./functions/misc/f_safe_drop_type.sql
\i ./functions/general/generateuid.sql
\i ./functions/general/createtriggeruidex.sql
commit;

\i ./functions/contribs/readd_contribs.sql


begin;
\i ./schema/all_tables.sql
create extension if not exists postgis;
create extension if not exists postgis_sfcgal; 
create extension if not exists postgis_topology;
create extension if not exists fuzzystrmatch;
create extension if not exists postgis_tiger_geocoder;
create extension if not exists address_standardizer;
create extension if not exists address_standardizer_data_us;
create view v_spatial_ref_sys as select srid as id, proj4text, srtext from spatial_ref_sys order by 1;
\i ./schema/maclabel.sql
commit;

--\encoding win1251

begin;

\i ./functions/readd_functions.sql

commit;
--in readd_commands use encoding utf8 - so, set cp1251 back
--\encoding win1251

--alter table io_objects rename to tbl_io_objects;
--alter sequence io_objects_id_seq rename to tbl_io_objects_id_seq;
--alter table attrs_values rename to tbl_attrs_values;
--alter table rec_attrs_values rename to tbl_rec_attrs_values;
begin;

\i ./functions/security/readd_security.sql

commit;

