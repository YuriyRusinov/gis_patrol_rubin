-- Database generated with pgModeler (PostgreSQL Database Modeler).
-- pgModeler  version: 0.9.3-alpha1
-- PostgreSQL version: 9.6
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

-- object: public.tbl_communication_categories | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_communication_categories CASCADE;
CREATE TABLE public.tbl_communication_categories (
	id serial NOT NULL,
	id_category_type integer NOT NULL,
	id_child int4,
	is_main bool NOT NULL DEFAULT true,
	name varchar NOT NULL,
	code varchar NOT NULL,
	description varchar,
	is_system bool NOT NULL DEFAULT false,
	CONSTRAINT tbl_communication_categories_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON COLUMN public.tbl_communication_categories.id_child IS E'Категория может содержать справочник, и дочерняя категория описывает подчиненную таблицу';
-- ddl-end --

-- object: public.tbl_communication_objects_references_id_seq | type: SEQUENCE --
-- DROP SEQUENCE IF EXISTS public.tbl_communication_objects_references_id_seq CASCADE;
CREATE SEQUENCE public.tbl_communication_objects_references_id_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START WITH 1
	CACHE 1
	NO CYCLE
	OWNED BY NONE;
-- ddl-end --
ALTER SEQUENCE public.tbl_communication_objects_references_id_seq OWNER TO postgres;
-- ddl-end --

-- object: public.tbl_io_communication_objects_references | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_io_communication_objects_references CASCADE;
CREATE TABLE public.tbl_io_communication_objects_references (
	id integer NOT NULL DEFAULT nextval('public.tbl_communication_objects_references_id_seq'::regclass),
	id_author int4 NOT NULL,
	id_category integer NOT NULL,
	name varchar NOT NULL,
	description varchar,
	table_name varchar(256),
	information text NOT NULL,
	is_system boolean NOT NULL DEFAULT false,
	insert_time timestamptz NOT NULL DEFAULT current_timestamp,
	is_global boolean NOT NULL DEFAULT false,
	record_fill_color int8,
	record_text_color int8,
	ref_table_name varchar(256),
	r_icon varchar,
	uuid_t uuid NOT NULL DEFAULT uuid_generate_v1(),
	CONSTRAINT tbl_communications_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_io_communication_objects_references IS E'Таблица содержит перечень контейнеров информационных объектов, относящихся к ресурсам связи';
-- ddl-end --
COMMENT ON COLUMN public.tbl_io_communication_objects_references.ref_table_name IS E'Если таблица наследуется от таблицы другого информационного объекта, то здесь приводится название базовой таблицы';
-- ddl-end --
COMMENT ON COLUMN public.tbl_io_communication_objects_references.r_icon IS E'Иконка для отображения';
-- ddl-end --
COMMENT ON COLUMN public.tbl_io_communication_objects_references.uuid_t IS E'Уникальный идентификатор';
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

-- object: public.tbl_parameters | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_parameters CASCADE;
CREATE TABLE public.tbl_parameters (
	id serial NOT NULL,
	id_param_type integer,
	code varchar(256) NOT NULL,
	name varchar NOT NULL,
	title varchar NOT NULL,
	table_name varchar(256),
	column_name varchar(256),
	is_system bool NOT NULL DEFAULT false,
	CONSTRAINT tbl_communication_parameters_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_parameter_types | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_parameter_types CASCADE;
CREATE TABLE public.tbl_parameter_types (
	id serial NOT NULL,
	id_param_view integer NOT NULL,
	name character varying NOT NULL,
	code character varying NOT NULL,
	CONSTRAINT tbl_communication_parameter_types_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_cat_params | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_cat_params CASCADE;
CREATE TABLE public.tbl_cat_params (
	id serial NOT NULL,
	id_category integer NOT NULL,
	id_parameter integer NOT NULL,
	default_value varchar,
	is_mandatory bool NOT NULL DEFAULT false,
	is_read_only bool NOT NULL DEFAULT false,
	param_sort_order integer NOT NULL DEFAULT 0,
	CONSTRAINT tbl_cat_params_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON COLUMN public.tbl_cat_params.is_mandatory IS E'Определяет, является ли поле обязательным для заполнения';
-- ddl-end --

-- object: public.tbl_category_type | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_category_type CASCADE;
CREATE TABLE public.tbl_category_type (
	id serial NOT NULL,
	name varchar NOT NULL,
	description varchar,
	CONSTRAINT tbl_category_type_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_category_type IS E'Справочник типов категорий.\n- справочник;\n- журнал;\n- документ;\n- формуляр;\n- сообщение;\n- шаблон документа.\nРяд других.';
-- ddl-end --

-- object: public.tbl_parameter_values | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_parameter_values CASCADE;
CREATE TABLE public.tbl_parameter_values (
	id serial NOT NULL,
	id_communication_object integer,
	id_cat_param integer NOT NULL,
	value varchar NOT NULL,
	description varchar,
	start_time timestamptz NOT NULL DEFAULT current_timestamp,
	finish_time timestamptz,
	is_actual boolean NOT NULL DEFAULT true,
	CONSTRAINT tbl_parameter_values_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_parameter_values IS E'Таблица содержит значения параметров, в случае изменения значения, прежняя величина остается в таблице, но для нее устанавливается время окончания и поле is_actual становится равным false';
-- ddl-end --

-- object: public.users | type: TABLE --
-- DROP TABLE IF EXISTS public.users CASCADE;
CREATE TABLE public.users (
	id serial NOT NULL,
	id_maclabel smallint NOT NULL DEFAULT 1,
	firstname varchar NOT NULL,
	surname varchar,
	lastname varchar NOT NULL,
	insert_time timestamptz NOT NULL DEFAULT current_timestamp,
	family_name varchar NOT NULL,
	information text,
	email varchar,
	db_user varchar NOT NULL,
	CONSTRAINT users_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_param_views | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_param_views CASCADE;
CREATE TABLE public.tbl_param_views (
	id serial NOT NULL,
	name varchar NOT NULL,
	CONSTRAINT param_views_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_param_views IS E'Таблица содержит перечень элементов управления, при помощи которых должны отображаться атрибуты различных типов.\nТак, например, атрибуты типа элемент справочника должны отображаться при помощи элемента управления выпадающий список и т.д.';
-- ddl-end --

-- object: fk_category_ref | type: CONSTRAINT --
-- ALTER TABLE public.tbl_communication_categories DROP CONSTRAINT IF EXISTS fk_category_ref CASCADE;
ALTER TABLE public.tbl_communication_categories ADD CONSTRAINT fk_category_ref FOREIGN KEY (id_child)
REFERENCES public.tbl_communication_categories (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: category_type_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_communication_categories DROP CONSTRAINT IF EXISTS category_type_fk CASCADE;
ALTER TABLE public.tbl_communication_categories ADD CONSTRAINT category_type_fk FOREIGN KEY (id_category_type)
REFERENCES public.tbl_category_type (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;
-- ddl-end --

-- object: category_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_io_communication_objects_references DROP CONSTRAINT IF EXISTS category_fk CASCADE;
ALTER TABLE public.tbl_io_communication_objects_references ADD CONSTRAINT category_fk FOREIGN KEY (id_category)
REFERENCES public.tbl_communication_categories (id) MATCH FULL
ON DELETE RESTRICT ON UPDATE RESTRICT;
-- ddl-end --

-- object: fk_author | type: CONSTRAINT --
-- ALTER TABLE public.tbl_io_communication_objects_references DROP CONSTRAINT IF EXISTS fk_author CASCADE;
ALTER TABLE public.tbl_io_communication_objects_references ADD CONSTRAINT fk_author FOREIGN KEY (id_author)
REFERENCES public.users (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_param_type | type: CONSTRAINT --
-- ALTER TABLE public.tbl_parameters DROP CONSTRAINT IF EXISTS fk_param_type CASCADE;
ALTER TABLE public.tbl_parameters ADD CONSTRAINT fk_param_type FOREIGN KEY (id_param_type)
REFERENCES public.tbl_parameter_types (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: ft_par_types_views | type: CONSTRAINT --
-- ALTER TABLE public.tbl_parameter_types DROP CONSTRAINT IF EXISTS ft_par_types_views CASCADE;
ALTER TABLE public.tbl_parameter_types ADD CONSTRAINT ft_par_types_views FOREIGN KEY (id_param_view)
REFERENCES public.tbl_param_views (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: category_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_cat_params DROP CONSTRAINT IF EXISTS category_fk CASCADE;
ALTER TABLE public.tbl_cat_params ADD CONSTRAINT category_fk FOREIGN KEY (id_category)
REFERENCES public.tbl_communication_categories (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;
-- ddl-end --

-- object: param_fk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_cat_params DROP CONSTRAINT IF EXISTS param_fk CASCADE;
ALTER TABLE public.tbl_cat_params ADD CONSTRAINT param_fk FOREIGN KEY (id_parameter)
REFERENCES public.tbl_parameters (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;
-- ddl-end --

-- object: fk_communication_object | type: CONSTRAINT --
-- ALTER TABLE public.tbl_parameter_values DROP CONSTRAINT IF EXISTS fk_communication_object CASCADE;
ALTER TABLE public.tbl_parameter_values ADD CONSTRAINT fk_communication_object FOREIGN KEY (id_communication_object)
REFERENCES public.tbl_io_communication_objects_references (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_cat_param | type: CONSTRAINT --
-- ALTER TABLE public.tbl_parameter_values DROP CONSTRAINT IF EXISTS fk_cat_param CASCADE;
ALTER TABLE public.tbl_parameter_values ADD CONSTRAINT fk_cat_param FOREIGN KEY (id_cat_param)
REFERENCES public.tbl_cat_params (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --


