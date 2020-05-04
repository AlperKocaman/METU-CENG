-- In task_3_1, author_id column is included in both group by and where clauses. 

create index author_id_index on author using btree(author_id);

-- in task_3_5, pub_id column of authored table is present in the where column of subquery. Also, name column of author table is exist in group by.

create index authored_pub_id_index on authored using btree(pub_id);

create index author_name_index on author using btree(name);