begin;
\i cat_user_params.sql
\i geography_type.sql
\i params.sql
\i parent_param.sql
\i tbl_id64.sql
\i tbl_io_params.sql
\i tbl_io_tables.sql
\i user_params.sql
commit;

begin;
update version_table set version='GIS Patrol  Server version 1.0.0', short_version='1.0.0';
commit;
