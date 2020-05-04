with author_ids_table as
(select
    a.author_id as id,
    count(*) as number
from
     authored a
group by
    a.author_id
having
    count(*) > 149 and count(*) < 200)
select
    a3.name as author_name,
    a2.number as pub_count
from
    author_ids_table a2,
    author a3
where
    a3.author_id = a2.id
order by
    pub_count,
    author_name asc;

-- TODO: common table expression to task_3_temp.sql
