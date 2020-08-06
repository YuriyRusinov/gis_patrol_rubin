alter table tbl_io_communication_objects_references disable trigger trgioinsert;
update tbl_io_communication_objects_references set is_system = false where id>=301;
alter table tbl_io_communication_objects_references enable trigger trgioinsert;
