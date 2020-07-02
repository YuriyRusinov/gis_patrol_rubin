create or replace function cUpdate(int8, varchar, varchar, varchar, int8, int8, boolean) returns int8 as
$BODY$
declare
    idCat alias for $1;
    cName alias for $2;
    cCode alias for $3;
    cDesc alias for $4;
    idType alias for $5;
    idChild alias for $6;
    isMain alias for $7;
    
    idCategory int8;
begin

    select cFindEqual(cName, cCode, cDesc, idType, idChild, isMain) into idCategory;
    if(idCategory is not null and idCategory > 0) then
        return idCategory;
    end if;
    
    update tbl_communication_categories
            set id_category_type=idType,
                id_child = idChild,
                is_main = isMain,
                name = cName,
                code = cCode,
                description = cDesc
            where id = idCat;
 
    if(not FOUND) then
        return -1;
    else
        idCategory := idCat;
    end if;
    
    return idCategory;
end
$BODY$
language 'plpgsql';
/*
--used in information exchange
create or replace function cInsertEx(varchar, varchar, varchar, int4, int4, boolean, varchar, boolean, int4, int4, int4) returns int4 as
$BODY$
declare
    cName alias for $1;
    cCode alias for $2;
    cDesc alias for $3;
    idType alias for $4;
    idChild alias for $5;
    isMain alias for $6;
    uniqueID alias for $7;
    isGlobal alias for $8;
    idState alias for $9;
    idChild2 alias for $10;
    idLifeCycle alias for $11;
    
    idCategory int4;
    ccc int4;
begin

    --select cFindEqual(cName, cCode, cDesc, idType, idChild, isMain) into idCategory;
    select id into idCategory from io_categories where unique_id = uniqueID;
    if(idCategory is not null and idCategory > 0) then
        --child category for indicators can be added after creation and synchronization of the category.
        --so, we must detect this case and add child2 category to existing category
        select id_child2 into ccc from io_categories where id = idCategory;
        if(ccc is null and idChild2 is not null) then
            update io_categories set id_child2 = idChild2 where id = idCategory;
        end if;

        return idCategory;
    end if;
    
    select getNextSeq('io_categories', 'id') into idCategory;

    insert into io_categories (id,
                               id_io_category_type,
                               id_child,
                               is_main,
                               name,
                               code,
                               description,
                               is_system,
                               unique_id,
                               is_global,
                               id_io_state,
                               id_child2,
                               id_life_cycle)
                       values (idCategory,
                               idType,
                               idChild,
                               isMain,
                               cName,
                               cCode,
                               cDesc,
                               false,
                               uniqueID,
                               isGlobal,
                               idState,
                               idChild2,
                               idLifeCycle);
    if(FOUND = FALSE) then
        return -1;
    end if;
    
    return idCategory;
end
$BODY$
language 'plpgsql';
*/
