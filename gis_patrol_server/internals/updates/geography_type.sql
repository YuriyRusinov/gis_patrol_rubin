begin;
insert into tbl_param_views (id, name) values (17, 'ГИС-объект (geography)');
insert into tbl_parameter_types (id, id_param_view, name, code) values (29, 17, 'ГИС-объект (geography)', 'GEOGRAPHY');
commit;
