begin;
\i ./functions/init_data/param_types.sql
\i ./functions/init_data/category_types.sql
\i ./functions/init_data/param_groups.sql
\i ./functions/init_data/parameters.sql
\i ./functions/init_data/categories.sql
\i ./functions/init_data/cat_params.sql
commit;

begin;
\i ./functions/init_data/maclabels.sql
\i ./functions/init_data/users.sql
\i ./functions/init_data/io_objects.sql
commit;
