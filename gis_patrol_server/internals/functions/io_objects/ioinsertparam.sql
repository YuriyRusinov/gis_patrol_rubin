create or replace function ioInsertParameter(int8, int8, varchar, timestamptz, timestamptz, varchar) returns int8 as
$BODY$
declare
    idObject alias for $1;
    idParam alias for $2;
    pValue alias for $3;
    pStartTime alias for $4;
    pStopTime alias for $5;
    pDesc alias for $6;

    idCategory int8;
    idCatParam int8;

    idParamValue int8;
begin

    select id_category into idCategory from tbl_io_communication_objects_references where id=idObject;
    if( idCategory is null ) then
        raise warning 'Document does not exist!';
        return -1;
    end if;

    select id into idCatParam from tbl_cat_params cp where cp.id_category=idCategory and cp.id_parameter = idParam;
    select getNextSeq('tbl_parameter_values', 'id') into idParamValue;
    insert into tbl_parameter_values(id, id_communication_object, id_param_category, value, description, start_time, finish_time)
    values (idParamValue, idObject, idCatParam, pValue, pDesc, pStartTime, pStopTime);

    return idParamValue;
end
$BODY$
language 'plpgsql';
