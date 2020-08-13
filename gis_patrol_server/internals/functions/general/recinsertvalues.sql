create or replace function recinsertvalue(int8, int8, varchar, varchar) returns int8 as
$BODY$
declare
    idParameter alias for $1;
    idRecord alias for $2;
    p_value alias for $3;
    p_description alias for $4;

    id_p_v int8;
    idRes int8;
    idCategoryParam int8;
begin

    select into id_p_v pv.id from tbl_parameter_values pv inner join tbl_cat_params pcat on (pv.id_param_category = pcat.id) inner join tbl_parameters p on (pcat.id_parameter=p.id and p.id=idParameter) inner join tbl_io_communication_objects_references io on (pv.id_communication_object=io.id and io.id=idRecord);
    select into idCategoryParam pcat.id from tbl_cat_params pcat inner join tbl_parameters p on (pcat.id_parameter=p.id and p.id=idParameter) inner join tbl_communication_categories c on (pcat.id_category=c.id) inner join tbl_io_communication_objects_references io on (io.id_category=c.id and io.id=idRecord);
    if( idCategoryParam is null ) then
        raise exception 'Incorrect category/reference/parameter';
        return null;
    end if;
    if( id_p_v is not null ) then
        update tbl_parameter_values set finish_time=current_timestamp, is_actual=false where id=id_p_v;
    end if;
    idRes := getNextSeq('tbl_parameter_values', 'id');
    insert into tbl_parameter_values( id, id_communication_object, id_param_category, value, description, start_time, finish_time, insert_time, is_actual) values( idRes, idRecord, idCategoryParam, p_value, p_description, current_timestamp, null, current_timestamp, true );
    return idRes;
end
$BODY$
language 'plpgsql';
