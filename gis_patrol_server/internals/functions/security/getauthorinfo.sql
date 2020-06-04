create or replace function getAuthorInfo() returns varchar as
$BODY$
declare
    info varchar;
    c_user varchar;
    r record;
begin

    info = NULL;
    select into c_user current_user;
    
    for r in 
        select 
            u.family_name,
            u.information,
            u.email
        from users u
        where 
            u.db_user = c_user
    loop
        info = r.family_name;
        info = info || E'\n';
        if(r.email is not null) then
            info = info || 'email: ' || r.email;
            info = info || E'\n';
        end if;

    end loop;       

    if (not FOUND or info isnull) then
        info = 'Нет информации об авторе';
    end if;

    return info;
end
$BODY$
language 'plpgsql';
