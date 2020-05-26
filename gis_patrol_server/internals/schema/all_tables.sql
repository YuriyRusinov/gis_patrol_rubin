-- Database generated with pgModeler (PostgreSQL Database Modeler).
-- pgModeler  version: 0.9.3-alpha1
-- PostgreSQL version: 12.0
-- Project Site: pgmodeler.io
-- Model Author: ---


-- Database creation must be done outside a multicommand file.
-- These commands were put in this file only as a convenience.
-- -- object: main_db0 | type: DATABASE --
-- -- DROP DATABASE IF EXISTS main_db0;
-- CREATE DATABASE main_db0
-- 	ENCODING = 'UTF8'
-- 	LC_COLLATE = 'en_US.utf8'
-- 	LC_CTYPE = 'en_US.utf8'
-- 	TABLESPACE = pg_default;
-- -- ddl-end --
-- 

-- object: postgis | type: EXTENSION --
-- DROP EXTENSION IF EXISTS postgis CASCADE;
CREATE EXTENSION postgis
WITH SCHEMA public;
-- ddl-end --
COMMENT ON EXTENSION postgis IS E'PostGIS geometry, geography, and raster spatial types and functions';
-- ddl-end --

-- object: public.tbl_communication_types_id_seq | type: SEQUENCE --
-- DROP SEQUENCE IF EXISTS public.tbl_communication_types_id_seq CASCADE;
CREATE SEQUENCE public.tbl_communication_types_id_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START WITH 1
	CACHE 1
	NO CYCLE
	OWNED BY NONE;
-- ddl-end --
ALTER SEQUENCE public.tbl_communication_types_id_seq OWNER TO postgres;
-- ddl-end --

-- object: public.tbl_communication_categories | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_communication_categories CASCADE;
CREATE TABLE public.tbl_communication_categories (
	id integer NOT NULL DEFAULT nextval('public.tbl_communication_types_id_seq'::regclass),
	name_en character varying NOT NULL,
	name_ru character varying NOT NULL,
	description_en text,
	description_ru text,
	code varchar NOT NULL,
	CONSTRAINT tbl_communication_types_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_communications_id_seq | type: SEQUENCE --
-- DROP SEQUENCE IF EXISTS public.tbl_communications_id_seq CASCADE;
CREATE SEQUENCE public.tbl_communications_id_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START WITH 1
	CACHE 1
	NO CYCLE
	OWNED BY NONE;
-- ddl-end --
ALTER SEQUENCE public.tbl_communications_id_seq OWNER TO postgres;
-- ddl-end --

-- object: public.tbl_communication_objects | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_communication_objects CASCADE;
CREATE TABLE public.tbl_communication_objects (
	id integer NOT NULL DEFAULT nextval('public.tbl_communications_id_seq'::regclass),
	id_parent integer,
	name character varying NOT NULL,
	description text,
	id_type integer NOT NULL,
	address text NOT NULL,
	geo_location geometry,
	CONSTRAINT tbl_communications_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_communication_objects IS E'Таблица содержит перечень ресурсов связи, данные ресурсы могут быть как самостоятельными структурами, так и частью более крупных ресурсов.';
-- ddl-end --

-- object: public.tbl_func_equipment_id_seq | type: SEQUENCE --
-- DROP SEQUENCE IF EXISTS public.tbl_func_equipment_id_seq CASCADE;
CREATE SEQUENCE public.tbl_func_equipment_id_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START WITH 1
	CACHE 1
	NO CYCLE
	OWNED BY NONE;
-- ddl-end --
ALTER SEQUENCE public.tbl_func_equipment_id_seq OWNER TO postgres;
-- ddl-end --

-- object: public.tbl_func_equipment | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_func_equipment CASCADE;
CREATE TABLE public.tbl_func_equipment (
	id integer NOT NULL DEFAULT nextval('public.tbl_func_equipment_id_seq'::regclass),
	func_name_ru character varying,
	func_name_en character varying,
	description text,
	CONSTRAINT tbl_func_equipment_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.many_tbl_func_equipment_has_many_tbl_communications_id_seq | type: SEQUENCE --
-- DROP SEQUENCE IF EXISTS public.many_tbl_func_equipment_has_many_tbl_communications_id_seq CASCADE;
CREATE SEQUENCE public.many_tbl_func_equipment_has_many_tbl_communications_id_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START WITH 1
	CACHE 1
	NO CYCLE
	OWNED BY NONE;
-- ddl-end --
ALTER SEQUENCE public.many_tbl_func_equipment_has_many_tbl_communications_id_seq OWNER TO postgres;
-- ddl-end --

-- object: public.tbl_func_equipment_communications | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_func_equipment_communications CASCADE;
CREATE TABLE public.tbl_func_equipment_communications (
	id serial NOT NULL,
	id_tbl_func_equipment integer NOT NULL,
	id_tbl_communication_objects integer NOT NULL,
	CONSTRAINT tbl_func_equipment_communications_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_protective_cabinets_id_seq | type: SEQUENCE --
-- DROP SEQUENCE IF EXISTS public.tbl_protective_cabinets_id_seq CASCADE;
CREATE SEQUENCE public.tbl_protective_cabinets_id_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START WITH 1
	CACHE 1
	NO CYCLE
	OWNED BY NONE;
-- ddl-end --
ALTER SEQUENCE public.tbl_protective_cabinets_id_seq OWNER TO postgres;
-- ddl-end --

-- object: public.tbl_protective_cabinets | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_protective_cabinets CASCADE;
CREATE TABLE public.tbl_protective_cabinets (
	id integer NOT NULL DEFAULT nextval('public.tbl_protective_cabinets_id_seq'::regclass),
	name character varying NOT NULL,
	CONSTRAINT tbl_protective_cabinets_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.maclabel | type: TYPE --
-- DROP TYPE IF EXISTS public.maclabel CASCADE;
CREATE TYPE public.maclabel AS
(
  m1 integer,
  m2 integer
);
-- ddl-end --

-- object: public.maclabels_id_seq | type: SEQUENCE --
-- DROP SEQUENCE IF EXISTS public.maclabels_id_seq CASCADE;
CREATE SEQUENCE public.maclabels_id_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START WITH 1
	CACHE 1
	NO CYCLE
	OWNED BY NONE;
-- ddl-end --
ALTER SEQUENCE public.maclabels_id_seq OWNER TO postgres;
-- ddl-end --

-- object: public.h_get_last_error | type: TYPE --
-- DROP TYPE IF EXISTS public.h_get_last_error CASCADE;
CREATE TYPE public.h_get_last_error AS
(
  error_sqlstate character(5),
  error_name character varying,
  error_message character varying,
  error_group integer,
  error_group_name character varying,
  error_data character varying
);
-- ddl-end --

-- object: public.version_table | type: TABLE --
-- DROP TABLE IF EXISTS public.version_table CASCADE;
CREATE TABLE public.version_table (
	version character varying,
	short_version character varying
);
-- ddl-end --

-- object: public.tbl_communication_parameters | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_communication_parameters CASCADE;
CREATE TABLE public.tbl_communication_parameters (
	id serial NOT NULL,
	name_en varchar,
	name_ru varchar,
	description text,
	CONSTRAINT tbl_communication_parameters_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_communication_parameter_types | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_communication_parameter_types CASCADE;
CREATE TABLE public.tbl_communication_parameter_types (
	id serial NOT NULL,
	name character varying NOT NULL,
	code character varying NOT NULL,
	id_tbl_communication_parameters integer,
	CONSTRAINT tbl_communication_parameter_types_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: tbl_communication_parameters_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_communication_parameter_types DROP CONSTRAINT IF EXISTS tbl_communication_parameters_fk CASCADE;
ALTER TABLE public.tbl_communication_parameter_types ADD CONSTRAINT tbl_communication_parameters_fk FOREIGN KEY (id_tbl_communication_parameters)
REFERENCES public.tbl_communication_parameters (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;
-- ddl-end --

-- object: tbl_communication_parameter_types_uq | type: CONSTRAINT --
-- ALTER TABLE public.tbl_communication_parameter_types DROP CONSTRAINT IF EXISTS tbl_communication_parameter_types_uq CASCADE;
ALTER TABLE public.tbl_communication_parameter_types ADD CONSTRAINT tbl_communication_parameter_types_uq UNIQUE (id_tbl_communication_parameters);
-- ddl-end --

-- object: public.tbl_param_values | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_param_values CASCADE;
CREATE TABLE public.tbl_param_values (
	id bigserial NOT NULL,
	id_communication_object integer NOT NULL,
	id_category_param integer NOT NULL,
	value varchar NOT NULL,
	CONSTRAINT tbl_param_values_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_cat_params | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_cat_params CASCADE;
CREATE TABLE public.tbl_cat_params (
	id serial NOT NULL,
	id_communication_category integer NOT NULL,
	id_param integer NOT NULL,
	default_value varchar,
	CONSTRAINT tbl_cat_params_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: fk_id_parent | type: CONSTRAINT --
-- ALTER TABLE public.tbl_communication_objects DROP CONSTRAINT IF EXISTS fk_id_parent CASCADE;
ALTER TABLE public.tbl_communication_objects ADD CONSTRAINT fk_id_parent FOREIGN KEY (id_parent)
REFERENCES public.tbl_communication_objects (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: tbl_communications_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_communication_objects DROP CONSTRAINT IF EXISTS tbl_communications_fk CASCADE;
ALTER TABLE public.tbl_communication_objects ADD CONSTRAINT tbl_communications_fk FOREIGN KEY (id_type)
REFERENCES public.tbl_communication_categories (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: func_equipment_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_func_equipment_communications DROP CONSTRAINT IF EXISTS func_equipment_fk CASCADE;
ALTER TABLE public.tbl_func_equipment_communications ADD CONSTRAINT func_equipment_fk FOREIGN KEY (id_tbl_func_equipment)
REFERENCES public.tbl_func_equipment (id) MATCH FULL
ON DELETE RESTRICT ON UPDATE CASCADE;
-- ddl-end --

-- object: communication_objects_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_func_equipment_communications DROP CONSTRAINT IF EXISTS communication_objects_fk CASCADE;
ALTER TABLE public.tbl_func_equipment_communications ADD CONSTRAINT communication_objects_fk FOREIGN KEY (id_tbl_communication_objects)
REFERENCES public.tbl_communication_objects (id) MATCH FULL
ON DELETE RESTRICT ON UPDATE CASCADE;
-- ddl-end --

-- object: communication_object_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_param_values DROP CONSTRAINT IF EXISTS communication_object_fk CASCADE;
ALTER TABLE public.tbl_param_values ADD CONSTRAINT communication_object_fk FOREIGN KEY (id_communication_object)
REFERENCES public.tbl_communication_objects (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: category_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_cat_params DROP CONSTRAINT IF EXISTS category_fk CASCADE;
ALTER TABLE public.tbl_cat_params ADD CONSTRAINT category_fk FOREIGN KEY (id_communication_category)
REFERENCES public.tbl_communication_categories (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;
-- ddl-end --

-- object: param_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_cat_params DROP CONSTRAINT IF EXISTS param_fk CASCADE;
ALTER TABLE public.tbl_cat_params ADD CONSTRAINT param_fk FOREIGN KEY (id_param)
REFERENCES public.tbl_communication_parameters (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;
-- ddl-end --


