-- Database generated with pgModeler (PostgreSQL Database Modeler).
-- pgModeler  version: 0.9.3-alpha1
-- PostgreSQL version: 9.6
-- Project Site: pgmodeler.io
-- Model Author: ---


-- Database creation must be done outside a multicommand file.
-- These commands were put in this file only as a convenience.
-- -- object: new_database | type: DATABASE --
-- -- DROP DATABASE IF EXISTS new_database;
-- CREATE DATABASE new_database;
-- -- ddl-end --
-- 

-- object: postgis | type: EXTENSION --
-- DROP EXTENSION IF EXISTS postgis CASCADE;
CREATE EXTENSION postgis
WITH SCHEMA public;
-- ddl-end --

-- object: public.tbl_communication_types | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_communication_types CASCADE;
CREATE TABLE public.tbl_communication_types (
	id serial NOT NULL,
	name_en varchar NOT NULL,
	name_ru varchar NOT NULL,
	description_en varchar,
	description_ru varchar,
	CONSTRAINT tbl_communication_types_pk PRIMARY KEY (id)

);
-- ddl-end --
ALTER TABLE public.tbl_communication_types OWNER TO postgres;
-- ddl-end --

-- object: public.tbl_communications | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_communications CASCADE;
CREATE TABLE public.tbl_communications (
	id serial NOT NULL,
	id_parent integer,
	name varchar NOT NULL,
	description varchar,
	id_type integer NOT NULL,
	geo_location geometry,
	CONSTRAINT tbl_communications_pk PRIMARY KEY (id)

);
-- ddl-end --
ALTER TABLE public.tbl_communications OWNER TO postgres;
-- ddl-end --

-- object: fk_id_parent | type: CONSTRAINT --
-- ALTER TABLE public.tbl_communications DROP CONSTRAINT IF EXISTS fk_id_parent CASCADE;
ALTER TABLE public.tbl_communications ADD CONSTRAINT fk_id_parent FOREIGN KEY (id_parent)
REFERENCES public.tbl_communications (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: tbl_communications_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_communications DROP CONSTRAINT IF EXISTS tbl_communications_fk CASCADE;
ALTER TABLE public.tbl_communications ADD CONSTRAINT tbl_communications_fk FOREIGN KEY (id_type)
REFERENCES public.tbl_communication_types (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --


