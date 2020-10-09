-- Database generated with pgModeler (PostgreSQL Database Modeler).
-- pgModeler  version: 0.9.3-beta1
-- PostgreSQL version: 9.6
-- Project Site: pgmodeler.io
-- Model Author: ---

-- Database creation must be performed outside a multi lined SQL file. 
-- These commands were put in this file only as a convenience.
-- 
-- object: new_database | type: DATABASE --
-- DROP DATABASE IF EXISTS new_database;
CREATE DATABASE new_database;
-- ddl-end --


-- object: public.tbl_linear_part_vols | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_linear_part_vols CASCADE;
CREATE TABLE public.tbl_linear_part_vols (
	id bigserial NOT NULL,
	id_well bigint NOT NULL,
	vols_length float8 NOT NULL,
	sections_number integer,
	section_length float8 NOT NULL,
	id_regenerator bigint NOT NULL,
	vols_type varchar,
	CONSTRAINT tbl_linear_part_vols_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON COLUMN public.tbl_linear_part_vols.id_well IS E'Номер колодца кабеля сигнализации';
-- ddl-end --
COMMENT ON COLUMN public.tbl_linear_part_vols.sections_number IS E'Количество секций';
-- ddl-end --

-- object: public.tbl_well_shaft | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_well_shaft CASCADE;
CREATE TABLE public.tbl_well_shaft (
	id bigserial NOT NULL,
	longitude float8 NOT NULL,
	latitude float8 NOT NULL,
	altitude float8,
	srid integer NOT NULL,
	CONSTRAINT tbl_well_shaft_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: postgis | type: EXTENSION --
-- DROP EXTENSION IF EXISTS postgis CASCADE;
CREATE EXTENSION postgis
WITH SCHEMA public;
-- ddl-end --

-- object: public.tbl_regenerator | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_regenerator CASCADE;
CREATE TABLE public.tbl_regenerator (
	id bigserial NOT NULL,
	regenerator_type varchar NOT NULL,
	cable_mark varchar,
	longitude float8,
	latitude float8,
	srid integer,
	CONSTRAINT tbl_regenerator_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_stationary_part_vols | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_stationary_part_vols CASCADE;
CREATE TABLE public.tbl_stationary_part_vols (
	id bigserial NOT NULL,
	id_vols bigint NOT NULL,
	opt_crosses_purpose varchar,
	cross_type varchar NOT NULL,
	cross_place_number integer,
	vols_number integer NOT NULL,
	column_number integer NOT NULL,
	number_reflection integer,
	date_reflection date,
	periturbation_description varchar,
	id_object bigint NOT NULL,
	CONSTRAINT tbl_stationary_part_vols_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON COLUMN public.tbl_stationary_part_vols.opt_crosses_purpose IS E'Назначение оптических кроссов';
-- ddl-end --
COMMENT ON COLUMN public.tbl_stationary_part_vols.cross_type IS E'Тип оптического кросса';
-- ddl-end --
COMMENT ON COLUMN public.tbl_stationary_part_vols.cross_place_number IS E'Номер места на оптическом кроссе';
-- ddl-end --
COMMENT ON COLUMN public.tbl_stationary_part_vols.vols_number IS E'Номер оптоволокна';
-- ddl-end --
COMMENT ON COLUMN public.tbl_stationary_part_vols.column_number IS E'Номер шкафа места подключения';
-- ddl-end --
COMMENT ON COLUMN public.tbl_stationary_part_vols.number_reflection IS E'Номер рефлектограммы';
-- ddl-end --
COMMENT ON COLUMN public.tbl_stationary_part_vols.periturbation_description IS E'Описание неоднородностей';
-- ddl-end --

-- object: public.tbl_fire_security_alarm | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_fire_security_alarm CASCADE;
CREATE TABLE public.tbl_fire_security_alarm (
	id bigserial NOT NULL,
	id_device integer NOT NULL,
	device_model varchar NOT NULL,
	is_fire boolean NOT NULL DEFAULT true,
	id_building bigint NOT NULL,
	central_control varchar,
	cable_mark varchar,
	CONSTRAINT tbl_fire_alarm_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON COLUMN public.tbl_fire_security_alarm.id_device IS E'Номер датчика';
-- ddl-end --
COMMENT ON COLUMN public.tbl_fire_security_alarm.device_model IS E'Модель датчика';
-- ddl-end --
COMMENT ON COLUMN public.tbl_fire_security_alarm.is_fire IS E'Пожарная сигнализация (true) или охранная сигнализация (false).';
-- ddl-end --
COMMENT ON COLUMN public.tbl_fire_security_alarm.id_building IS E'Номер сооружения';
-- ddl-end --

-- object: public.tbl_object_building | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_object_building CASCADE;
CREATE TABLE public.tbl_object_building (
	id bigserial NOT NULL,
	name varchar NOT NULL,
	width float8 NOT NULL,
	height float8 NOT NULL,
	depth float8 NOT NULL,
	number_floors integer NOT NULL DEFAULT 1,
	longitude float8,
	latitude float8,
	srid integer,
	id_iss_object bigint NOT NULL,
	CONSTRAINT tbl_object_buildings_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_object_building IS E'Сооружения объекта';
-- ddl-end --
COMMENT ON COLUMN public.tbl_object_building.name IS E'Наименование';
-- ddl-end --
COMMENT ON COLUMN public.tbl_object_building.width IS E'Ширина';
-- ddl-end --
COMMENT ON COLUMN public.tbl_object_building.height IS E'Длина основания';
-- ddl-end --
COMMENT ON COLUMN public.tbl_object_building.depth IS E'высота';
-- ddl-end --
COMMENT ON COLUMN public.tbl_object_building.number_floors IS E'Этажность';
-- ddl-end --

-- object: public.tbl_rooms | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_rooms CASCADE;
CREATE TABLE public.tbl_rooms (

);
-- ddl-end --

-- object: id | type: COLUMN --
-- ALTER TABLE public.tbl_rooms DROP COLUMN IF EXISTS id CASCADE;
ALTER TABLE public.tbl_rooms ADD COLUMN id bigserial NOT NULL;
-- ddl-end --


-- object: id_floor_room | type: COLUMN --
-- ALTER TABLE public.tbl_rooms DROP COLUMN IF EXISTS id_floor_room CASCADE;
ALTER TABLE public.tbl_rooms ADD COLUMN id_floor_room integer NOT NULL;
-- ddl-end --

COMMENT ON COLUMN public.tbl_rooms.id_floor_room IS E'Номер помещения на этаже';
-- ddl-end --


-- object: floor_number | type: COLUMN --
-- ALTER TABLE public.tbl_rooms DROP COLUMN IF EXISTS floor_number CASCADE;
ALTER TABLE public.tbl_rooms ADD COLUMN floor_number integer NOT NULL DEFAULT 0;
-- ddl-end --

COMMENT ON COLUMN public.tbl_rooms.floor_number IS E'Номер этажа';
-- ddl-end --


-- object: id_building | type: COLUMN --
-- ALTER TABLE public.tbl_rooms DROP COLUMN IF EXISTS id_building CASCADE;
ALTER TABLE public.tbl_rooms ADD COLUMN id_building integer NOT NULL;
-- ddl-end --

COMMENT ON COLUMN public.tbl_rooms.id_building IS E'Номер здания';
-- ddl-end --



-- object: tbl_rooms_pk | type: CONSTRAINT --
-- ALTER TABLE public.tbl_rooms DROP CONSTRAINT IF EXISTS tbl_rooms_pk CASCADE;
ALTER TABLE public.tbl_rooms ADD CONSTRAINT tbl_rooms_pk PRIMARY KEY (id);
-- ddl-end --

COMMENT ON TABLE public.tbl_rooms IS E'Помещения сооружения';
-- ddl-end --

-- object: public.tbl_iss_objects | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_iss_objects CASCADE;
CREATE TABLE public.tbl_iss_objects (
	id bigserial NOT NULL,
	id_class_object integer NOT NULL,
	name varchar NOT NULL,
	short_name varchar,
	control_border geometry,
	post_address varchar NOT NULL,
	longitude float8,
	latitude float8,
	srid integer,
	CONSTRAINT tbl_iss_objects_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_iss_objects IS E'Объекты ИСС';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_objects.id IS E'Номер объекта';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_objects.id_class_object IS E'Учетный номер объекта';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_objects.name IS E'Полное название';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_objects.short_name IS E'Сокращенное название';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_objects.control_border IS E'Границы контрольной зоны';
-- ddl-end --

-- object: public.tbl_iss_object_adjucent_objects | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_iss_object_adjucent_objects CASCADE;
CREATE TABLE public.tbl_iss_object_adjucent_objects (
	id_iss_object bigint NOT NULL,
	id_iss_adjucent_object bigint NOT NULL,
	CONSTRAINT tbl_iss_object_adjucent_objects_pk PRIMARY KEY (id_iss_object,id_iss_adjucent_object)

);
-- ddl-end --

-- object: public.tbl_fire_alarm_room_device | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_fire_alarm_room_device CASCADE;
CREATE TABLE public.tbl_fire_alarm_room_device (
	id bigserial NOT NULL,
	device_name varchar,
	device_model varchar NOT NULL,
	id_room bigint,
	id_state bigint NOT NULL,
	CONSTRAINT tbl_fire_alarm_room_device_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON COLUMN public.tbl_fire_alarm_room_device.id_state IS E'Состояние устройства';
-- ddl-end --

-- object: public.tbl_iss_node | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_iss_node CASCADE;
CREATE TABLE public.tbl_iss_node (
	id bigserial NOT NULL,
	id_stat_number bigint NOT NULL,
	id_iss_object bigint NOT NULL,
	control_level smallint NOT NULL DEFAULT 3,
	state_number integer NOT NULL DEFAULT 0,
	special_user_category smallint NOT NULL DEFAULT 1,
	node_border geometry,
	CONSTRAINT tbl_iss_node_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_node.id_stat_number IS E'Учетный номер узла';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_node.control_level IS E'Уровень управления\n3й \n2й \n1й';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_node.state_number IS E'Количество обслуживающего персонала';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_node.special_user_category IS E'1я, 2я, 3я';
-- ddl-end --
COMMENT ON COLUMN public.tbl_iss_node.node_border IS E'Границы контролируемой зоны узла';
-- ddl-end --

-- object: public.tbl_ground_system | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_ground_system CASCADE;
CREATE TABLE public.tbl_ground_system (
	id bigserial NOT NULL,
	id_tread bigint,
	wire_mark varchar,
	resistance float8 NOT NULL DEFAULT 15,
	contour_type smallint NOT NULL DEFAULT 1,
	contour_number integer,
	id_floor integer NOT NULL,
	id_electrical_file integer,
	id_building bigint,
	CONSTRAINT tbl_ground_system_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_ground_system IS E'Система заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_ground_system.id_tread IS E'Номер шины заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_ground_system.wire_mark IS E'Марка провода';
-- ddl-end --
COMMENT ON COLUMN public.tbl_ground_system.resistance IS E'Сопротивление заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_ground_system.contour_type IS E'1 -- защитный \n2 -- рабочий';
-- ddl-end --
COMMENT ON COLUMN public.tbl_ground_system.contour_number IS E'Номер контура заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_ground_system.id_floor IS E'Номер этажа';
-- ddl-end --
COMMENT ON COLUMN public.tbl_ground_system.id_electrical_file IS E'Номер файла электропитания на этаже';
-- ddl-end --

-- object: public.tbl_electrical_systems | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_electrical_systems CASCADE;
CREATE TABLE public.tbl_electrical_systems (
	id bigserial NOT NULL,
	id_building bigint NOT NULL,
	name varchar NOT NULL,
	CONSTRAINT tbl_electrical_systems_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_electrical_shield | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_electrical_shield CASCADE;
CREATE TABLE public.tbl_electrical_shield (
	id bigserial NOT NULL,
	serial_number varchar NOT NULL,
	mark varchar,
	id_electrical_system bigint NOT NULL,
	CONSTRAINT tbl_electrical_shield_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_electrical_transform | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_electrical_transform CASCADE;
CREATE TABLE public.tbl_electrical_transform (
	id bigserial NOT NULL,
	serial_number varchar NOT NULL,
	mark varchar,
	id_electrical_system bigint NOT NULL,
	CONSTRAINT tbl_electrical_transform_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_electric_shield_transform | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_electric_shield_transform CASCADE;
CREATE TABLE public.tbl_electric_shield_transform (
	id bigserial NOT NULL,
	id_shield bigint NOT NULL,
	id_transformator bigint NOT NULL,
	CONSTRAINT tbl_electric_shield_transform_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: public.tbl_grounding_system | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_grounding_system CASCADE;
CREATE TABLE public.tbl_grounding_system (
	id bigserial NOT NULL,
	grounding_bar_mark varchar,
	grounding_cord varchar,
	grounding_resistance float8,
	grounding_type varchar,
	grounding_contour_number integer,
	id_floor integer,
	id_building bigint NOT NULL,
	CONSTRAINT tbl_grounding_system_pk PRIMARY KEY (id)

);
-- ddl-end --
COMMENT ON TABLE public.tbl_grounding_system IS E'Система заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_grounding_system.grounding_bar_mark IS E'Маркировка шины заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_grounding_system.grounding_cord IS E'Марка провода заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_grounding_system.grounding_resistance IS E'Сопротивление заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_grounding_system.grounding_contour_number IS E'Номер контура заземления';
-- ddl-end --
COMMENT ON COLUMN public.tbl_grounding_system.id_floor IS E'Номер этажа';
-- ddl-end --
COMMENT ON COLUMN public.tbl_grounding_system.id_building IS E'Номер строения';
-- ddl-end --

-- object: public.tbl_state_tko | type: TABLE --
-- DROP TABLE IF EXISTS public.tbl_state_tko CASCADE;
CREATE TABLE public.tbl_state_tko (
	id bigserial NOT NULL,
	name varchar NOT NULL,
	description varchar,
	CONSTRAINT tbl_state_tko_pk PRIMARY KEY (id)

);
-- ddl-end --

-- object: fk_well | type: CONSTRAINT --
-- ALTER TABLE public.tbl_linear_part_vols DROP CONSTRAINT IF EXISTS fk_well CASCADE;
ALTER TABLE public.tbl_linear_part_vols ADD CONSTRAINT fk_well FOREIGN KEY (id_well)
REFERENCES public.tbl_well_shaft (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_regenerator | type: CONSTRAINT --
-- ALTER TABLE public.tbl_linear_part_vols DROP CONSTRAINT IF EXISTS fk_regenerator CASCADE;
ALTER TABLE public.tbl_linear_part_vols ADD CONSTRAINT fk_regenerator FOREIGN KEY (id_regenerator)
REFERENCES public.tbl_regenerator (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_vols | type: CONSTRAINT --
-- ALTER TABLE public.tbl_stationary_part_vols DROP CONSTRAINT IF EXISTS fk_vols CASCADE;
ALTER TABLE public.tbl_stationary_part_vols ADD CONSTRAINT fk_vols FOREIGN KEY (id_vols)
REFERENCES public.tbl_linear_part_vols (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_object | type: CONSTRAINT --
-- ALTER TABLE public.tbl_stationary_part_vols DROP CONSTRAINT IF EXISTS fk_object CASCADE;
ALTER TABLE public.tbl_stationary_part_vols ADD CONSTRAINT fk_object FOREIGN KEY (id_object)
REFERENCES public.tbl_iss_objects (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_building | type: CONSTRAINT --
-- ALTER TABLE public.tbl_fire_security_alarm DROP CONSTRAINT IF EXISTS fk_building CASCADE;
ALTER TABLE public.tbl_fire_security_alarm ADD CONSTRAINT fk_building FOREIGN KEY (id_building)
REFERENCES public.tbl_object_building (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_object | type: CONSTRAINT --
-- ALTER TABLE public.tbl_object_building DROP CONSTRAINT IF EXISTS fk_object CASCADE;
ALTER TABLE public.tbl_object_building ADD CONSTRAINT fk_object FOREIGN KEY (id_iss_object)
REFERENCES public.tbl_iss_objects (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_object_buildings | type: CONSTRAINT --
-- ALTER TABLE public.tbl_rooms DROP CONSTRAINT IF EXISTS fk_object_buildings CASCADE;
ALTER TABLE public.tbl_rooms ADD CONSTRAINT fk_object_buildings FOREIGN KEY (id_building)
REFERENCES public.tbl_object_building (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_object | type: CONSTRAINT --
-- ALTER TABLE public.tbl_iss_object_adjucent_objects DROP CONSTRAINT IF EXISTS fk_object CASCADE;
ALTER TABLE public.tbl_iss_object_adjucent_objects ADD CONSTRAINT fk_object FOREIGN KEY (id_iss_object)
REFERENCES public.tbl_iss_objects (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_adjucent_object | type: CONSTRAINT --
-- ALTER TABLE public.tbl_iss_object_adjucent_objects DROP CONSTRAINT IF EXISTS fk_adjucent_object CASCADE;
ALTER TABLE public.tbl_iss_object_adjucent_objects ADD CONSTRAINT fk_adjucent_object FOREIGN KEY (id_iss_adjucent_object)
REFERENCES public.tbl_iss_objects (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_room | type: CONSTRAINT --
-- ALTER TABLE public.tbl_fire_alarm_room_device DROP CONSTRAINT IF EXISTS fk_room CASCADE;
ALTER TABLE public.tbl_fire_alarm_room_device ADD CONSTRAINT fk_room FOREIGN KEY (id_room)
REFERENCES public.tbl_rooms (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_state | type: CONSTRAINT --
-- ALTER TABLE public.tbl_fire_alarm_room_device DROP CONSTRAINT IF EXISTS fk_state CASCADE;
ALTER TABLE public.tbl_fire_alarm_room_device ADD CONSTRAINT fk_state FOREIGN KEY (id_state)
REFERENCES public.tbl_state_tko (id) MATCH FULL
ON DELETE RESTRICT ON UPDATE RESTRICT;
-- ddl-end --

-- object: fk_iss_node | type: CONSTRAINT --
-- ALTER TABLE public.tbl_iss_node DROP CONSTRAINT IF EXISTS fk_iss_node CASCADE;
ALTER TABLE public.tbl_iss_node ADD CONSTRAINT fk_iss_node FOREIGN KEY (id_iss_object)
REFERENCES public.tbl_iss_objects (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_building | type: CONSTRAINT --
-- ALTER TABLE public.tbl_ground_system DROP CONSTRAINT IF EXISTS fk_building CASCADE;
ALTER TABLE public.tbl_ground_system ADD CONSTRAINT fk_building FOREIGN KEY (id_building)
REFERENCES public.tbl_object_building (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_building | type: CONSTRAINT --
-- ALTER TABLE public.tbl_electrical_systems DROP CONSTRAINT IF EXISTS fk_building CASCADE;
ALTER TABLE public.tbl_electrical_systems ADD CONSTRAINT fk_building FOREIGN KEY (id_building)
REFERENCES public.tbl_object_building (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_electrical_system | type: CONSTRAINT --
-- ALTER TABLE public.tbl_electrical_shield DROP CONSTRAINT IF EXISTS fk_electrical_system CASCADE;
ALTER TABLE public.tbl_electrical_shield ADD CONSTRAINT fk_electrical_system FOREIGN KEY (id_electrical_system)
REFERENCES public.tbl_electrical_systems (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_electrical_system | type: CONSTRAINT --
-- ALTER TABLE public.tbl_electrical_transform DROP CONSTRAINT IF EXISTS fk_electrical_system CASCADE;
ALTER TABLE public.tbl_electrical_transform ADD CONSTRAINT fk_electrical_system FOREIGN KEY (id_electrical_system)
REFERENCES public.tbl_electrical_systems (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_shield | type: CONSTRAINT --
-- ALTER TABLE public.tbl_electric_shield_transform DROP CONSTRAINT IF EXISTS fk_shield CASCADE;
ALTER TABLE public.tbl_electric_shield_transform ADD CONSTRAINT fk_shield FOREIGN KEY (id_shield)
REFERENCES public.tbl_electrical_shield (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_transform | type: CONSTRAINT --
-- ALTER TABLE public.tbl_electric_shield_transform DROP CONSTRAINT IF EXISTS fk_transform CASCADE;
ALTER TABLE public.tbl_electric_shield_transform ADD CONSTRAINT fk_transform FOREIGN KEY (id_transformator)
REFERENCES public.tbl_electrical_transform (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: fk_building | type: CONSTRAINT --
-- ALTER TABLE public.tbl_grounding_system DROP CONSTRAINT IF EXISTS fk_building CASCADE;
ALTER TABLE public.tbl_grounding_system ADD CONSTRAINT fk_building FOREIGN KEY (id_building)
REFERENCES public.tbl_object_building (id) MATCH FULL
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --


