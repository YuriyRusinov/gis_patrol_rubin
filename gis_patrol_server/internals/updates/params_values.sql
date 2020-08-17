alter table tbl_parameter_values alter column value drop not null;
alter table tbl_cat_params disable trigger trgcatparaminsert;
update tbl_cat_params set is_mandatory = false where id=505;
alter table tbl_cat_params enable trigger trgcatparaminsert;
drop function if exists recinsertvalue(int8, int8, varchar, varchar);
