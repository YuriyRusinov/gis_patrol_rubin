drop function if exists pinsertparameter ( integer, integer, character varying, character varying, character varying, character varying, character varying);
drop function if exists pupdate(   integer, integer, integer, character varying, character varying, character varying, character varying, character varying) ;
drop function if exists pdelete(integer);
drop function if exists pGetParamGroups(integer);
drop function if exists pGetParametersList(integer);
drop function if exists pGetParamGroup(integer);
drop function if exists cGetCategory(int4);
drop function if exists cGetParentCategory(int4);
drop function if exists pFindEqual(int4, varchar, varchar, varchar, varchar, varchar);
begin;
\i ../functions/parameters/pfindequal.sql
\i ../functions/parameters/pinsert.sql
\i ../functions/parameters/pgetgroup.sql
\i ../functions/parameters/pgetparameter.sql
\i ../functions/parameters/pgetparameterslist.sql
\i ../functions/categories/cgetcategoryparams.sql
\i ../functions/categories/cgetcategory.sql
commit;
