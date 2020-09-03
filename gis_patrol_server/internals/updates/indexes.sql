alter table tbl_io_communication_objects_references disable trigger trgioinsert;
update tbl_io_communication_objects_references set table_name='tbl_parameter_values' where id=90;
alter table tbl_io_communication_objects_references enable trigger trgioinsert;

-- object: i_param_code | type: INDEX --
DROP INDEX IF EXISTS public.i_param_code CASCADE;
CREATE INDEX i_param_code ON public.tbl_parameters
       USING btree
       (
         code
       );
-- ddl-end --

-- object: i_param_cat | type: INDEX --
DROP INDEX IF EXISTS public.i_param_cat CASCADE;
CREATE UNIQUE INDEX i_param_cat ON public.tbl_cat_params
       USING btree
       (
         id_category,
         id_parameter
       );
-- ddl-end --

-- object: i_p_category | type: INDEX --
DROP INDEX IF EXISTS public.i_p_category CASCADE;
CREATE INDEX i_p_category ON public.tbl_cat_params
       USING btree
       (
         id_category
       );
-- ddl-end --

-- object: "I_cat_code" | type: INDEX --
DROP INDEX IF EXISTS public."I_cat_code" CASCADE;
CREATE UNIQUE INDEX "I_cat_code" ON public.tbl_communication_categories
       USING btree
       (
         code
       );
-- ddl-end --

-- object: i_io_table | type: INDEX --
DROP INDEX IF EXISTS public.i_io_table CASCADE;
CREATE UNIQUE INDEX i_io_table ON public.tbl_io_communication_objects_references
       USING btree
       (
         table_name
       );
-- ddl-end --

-- object: i_author | type: INDEX --
DROP INDEX IF EXISTS public.i_author CASCADE;
CREATE INDEX i_author ON public.tbl_io_communication_objects_references
       USING btree
       (
         id_author
       );
-- ddl-end --

-- object: i_category | type: INDEX --
DROP INDEX IF EXISTS public.i_category CASCADE;
CREATE INDEX i_category ON public.tbl_io_communication_objects_references
       USING btree
       (
         id_category
       );
-- ddl-end --
