create or replace function ioUpdate(int4, varchar, varchar, varchar, boolean, int8, int8, varchar) returns int4 as
$BODY$
declare

    idObject alias for $1;
    ioName alias for $2;
    ioDesc alias for $3;
    ioInfo alias for $4;
    isGlobal alias for $5;
    recordFillColor alias for $6;
    recordTextColor alias for $7;
    rIcon alias for $8;


begin

    if (idObject is null or idObject <= 0) then
        return -1;
    end if;
    
    update tbl_io_communication_objects_references set 
                            name = ioName, 
                            description = ioDesc, 
                            information = ioInfo, 
                            is_global = isGlobal,
                            record_fill_color = recordFillColor,
                            record_text_color = recordTextColor,
                            r_icon = rIcon
    where id=idObject;

    return idObject;

end
$BODY$
language 'plpgsql';
