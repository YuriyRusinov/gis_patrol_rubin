create or replace function gis_patrol_version() returns varchar as
$BODY$
declare
    ver varchar;
begin
    
    select version into ver from version_table;

    if(ver isnull) then
        raise warning 'Incorrect version of GIS PATROL SERVER!';
    end if;
    
    return ver;
    
end
$BODY$
language 'plpgsql' security definer;

create or replace function gis_patrol_version1() returns varchar as
$BODY$
declare
    ver varchar;
begin
    
    select short_version into ver from version_table;

    if(ver isnull) then
        raise warning 'Incorrect version of GIS PATROL SERVER!';
    end if;
    
    return ver;
    
end
$BODY$
language 'plpgsql' security definer;

create or replace function setgis_patrol_version(varchar, varchar) returns int4 as
$BODY$
declare
    ver alias for $1;
    shortVer alias for $2;
begin
    
    perform f_safe_drop_table('version_table');

    create table version_table(version varchar, short_version varchar);

    insert into version_table(version, short_version) values(ver, shortVer);

    return 1;

end
$BODY$
language 'plpgsql' security definer;
