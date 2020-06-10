create or replace function pInsertParameter (int4, int4, varchar, varchar, varchar, varchar, varchar) returns int4 as
$BODY$
declare
    idParamType alias for $1;
    idParamGroup alias for $2;
    parameter_code alias for $3;
    parameter_name alias for $4;
    parameter_title alias for $5;
    parameter_table_name alias for $6;
    parameter_column_name alias for $7;

    idParameter int4;
    cnt int4;
begin
    select pFindEqual(idParamType, parameter_code, parameter_name, parameter_title, parameter_table_name, parameter_column_name) into idParameter;
    if (idParameter is not null and idParameter > 0) then
        return idParameter;
    end if;
    select getNextSeq('tbl_parameters', 'id') into idParameter;
    insert into tbl_parameters (id, id_param_group, id_param_type, code, name, title, table_name, column_name, is_system) values (idParameter, idParamGroup, idParamType, parameter_code, parameter_name, parameter_title, parameter_table_name, parameter_column_name, false);
    if (not FOUND) then
        return -1;
    end if;

    return idParameter;

end
$BODY$
language 'plpgsql';
