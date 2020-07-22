begin;
alter table tbl_cat_params disable trigger all;

update tbl_cat_params set param_sort_order=param_sort_order+1 where id >= 57 and id<=62;

alter table tbl_cat_params enable trigger all;
commit;
