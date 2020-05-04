create index pub_pub_type on pub using btree(pub_type);

create index pub_pub_key on pub using btree(pub_key);

create index field_pub_key on field using btree(pub_key);

create index field_field_name on field using btree(field_name);