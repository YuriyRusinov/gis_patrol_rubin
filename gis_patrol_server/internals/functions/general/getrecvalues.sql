select f_safe_drop_type('h_rec_parameters_values');
create type h_rec_parameters_values as (id_parameter int8,
                                id_param_type int8,
                                id_param_group int8,
                                parameter_code varchar,
                                parameter_name varchar,
                                parameter_title varchar,
                                table_name varchar,
                                column_name varchar,
                                parameter_type_name varchar,
                                parameter_type_code varchar,
                                is_mandatory boolean,
                                is_read_only boolean,
                                param_sort_order integer,
                                id_ex int8,
                                id_param_ref int8,
                                ref_type_id int8,
                                ref_type_name varchar,
                                ref_type_code varchar,
                                parameter_value varchar,
                                parameter_description varchar,
                                start_time timestamptz,
                                finish_time timestamptz,
                                insert_time timestamptz,
                                is_actual boolean
                            );

create or replace function getRecParamValues(int8) returns setof h_rec_parameters_values as
$BODY$
declare
    idRecord alias for $1;

    query varchar;
    r h_rec_parameters_values%rowtype;
begin
    for r in
        select 
            p.id,
            ptt.id,
            p.id_param_group,
            p.code,
            p.name,
            p.title,
            p.table_name,
            p.column_name,
            ptt.name,
            ptt.code,
            pcat.is_mandatory,
            pcat.is_read_only,
            pcat.param_sort_order,
            pcat.id,
            p1.id as prefid,
            ptt1.id as ref_type_id,
            ptt1.name as ref_type_name,
            ptt1.code as ref_type_code,
            pval.value as parameter_value,
            pval.description as parameter_description,
            pval.start_time as start_time,
            pval.finish_time as finish_time,
            pval.insert_time as insert_time,
            pval.is_actual
        from
            tbl_parameters p inner join tbl_parameter_types ptt on (p.id_param_type = ptt.id)
            inner join tbl_cat_params as pcat on (pcat.id_parameter = p.id)
            left join tbl_parameter_values pval on (pval.id_param_category = pcat.id_category and pval.is_actual and (pval.finish_time is null or pval.finish_time >= current_timestamp ))
            inner join tbl_io_communication_objects_references io on (pval.id_communication_object=io.id and io.id=idRecord)
            left join tbl_parameters p1 on (p.column_name=p1.code and p.column_name is not null) left join tbl_parameter_types ptt1 on (p1.id_param_type=ptt1.id)
        loop
            return next r;
        end loop;

        return;

end
$BODY$
language 'plpgsql';
