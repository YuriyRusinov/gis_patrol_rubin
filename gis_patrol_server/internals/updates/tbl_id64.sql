alter table tbl_category_type alter column id type int8;
alter table tbl_communication_categories alter column id type int8;
alter table tbl_communication_categories alter column id_category_type type int8;
alter table tbl_communication_categories alter column id_child type int8;
alter table tbl_io_communication_objects_references alter column id type int8;
alter table tbl_io_communication_objects_references alter column id_author type int8;
alter table tbl_io_communication_objects_references alter column id_category type int8;
alter table users alter column id type int8;
alter table users alter column id_maclabel type int8;
alter table tbl_parameter_values alter column id type int8;
alter table tbl_parameter_values alter column id_communication_object type int8;
alter table tbl_cat_params alter column id type int8;
alter table tbl_cat_params alter column id_category type int8;
alter table tbl_cat_params alter column id_parameter type int8;
alter table tbl_parameters alter column id type int8;
alter table tbl_parameters alter column id_param_type type int8;
alter table tbl_parameters alter column id_param_group type int8;
alter table tbl_parameters_groups alter column id type int8;
alter table tbl_parameters_groups alter column id_parent type int8;
alter table tbl_parameter_types alter column id type int8;
alter table tbl_parameter_types alter column id_param_view type int8;
alter table tbl_param_views alter column id type int8;
alter table maclabels alter column id type int8;