-- Database generated with pgModeler (PostgreSQL Database Modeler).
-- pgModeler  version: 0.9.3-alpha1
-- PostgreSQL version: 9.6
-- Project Site: pgmodeler.io
-- Model Author: ---


-- Database creation must be done outside a multicommand file.
-- These commands were put in this file only as a convenience.
-- -- object: main_db | type: DATABASE --
-- -- DROP DATABASE IF EXISTS main_db;
-- CREATE DATABASE main_db
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

-- object: public.tbl_communication_types | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_communication_types CASCADE;
CREATE TABLE public.tbl_communication_types (
	id integer NOT NULL DEFAULT nextval('public.tbl_communication_types_id_seq'::regclass),
	name_en character varying NOT NULL,
	name_ru character varying NOT NULL,
	description_en character varying,
	description_ru character varying,
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
	description character varying,
	id_type integer NOT NULL,
	geo_location public.geometry,
	address text NOT NULL,
	CONSTRAINT tbl_communications_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_func_equipment | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_func_equipment CASCADE;
CREATE TABLE public.tbl_func_equipment (
	id serial NOT NULL,
	func_name_ru varchar,
	func_name_en varchar,
	description_ru varchar,
	description_en varchar,
	CONSTRAINT tbl_func_equipment_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.many_tbl_func_equipment_has_many_tbl_communications | type: TABLE --
-- DROP TABLE IF EXISTS public.many_tbl_func_equipment_has_many_tbl_communications CASCADE;
CREATE TABLE public.many_tbl_func_equipment_has_many_tbl_communications (
	id_tbl_func_equipment integer NOT NULL,
	id_tbl_communication_objects integer NOT NULL,
	id serial NOT NULL,
	CONSTRAINT many_tbl_func_equipment_has_many_tbl_communications_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: tbl_func_equipment_fk | type: CONSTRAINT --
-- ALTER TABLE public.many_tbl_func_equipment_has_many_tbl_communications DROP CONSTRAINT IF EXISTS tbl_func_equipment_fk CASCADE;
ALTER TABLE public.many_tbl_func_equipment_has_many_tbl_communications ADD CONSTRAINT tbl_func_equipment_fk FOREIGN KEY (id_tbl_func_equipment)
REFERENCES public.tbl_func_equipment (id) MATCH FULL
ON DELETE RESTRICT ON UPDATE CASCADE;
-- ddl-end --

-- object: tbl_communication_objects_fk | type: CONSTRAINT --
-- ALTER TABLE public.many_tbl_func_equipment_has_many_tbl_communications DROP CONSTRAINT IF EXISTS tbl_communication_objects_fk CASCADE;
ALTER TABLE public.many_tbl_func_equipment_has_many_tbl_communications ADD CONSTRAINT tbl_communication_objects_fk FOREIGN KEY (id_tbl_communication_objects)
REFERENCES public.tbl_communication_objects (id) MATCH FULL
ON DELETE RESTRICT ON UPDATE CASCADE;
-- ddl-end --

-- object: public.tbl_protective_cabinets | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_protective_cabinets CASCADE;
CREATE TABLE public.tbl_protective_cabinets (
	id serial NOT NULL,
	name varchar NOT NULL,
	CONSTRAINT tbl_protective_cabinets_pk PRIMARY KEY (id)

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
REFERENCES public.tbl_communication_types (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: grant_bc0d3a519e | type: PERMISSION --
GRANT CREATE,USAGE
   ON SCHEMA public
   TO postgres;
-- ddl-end --

-- object: grant_8710c8d154 | type: PERMISSION --
GRANT CREATE,USAGE
   ON SCHEMA public
   TO PUBLIC;
-- ddl-end --


