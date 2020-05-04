select
    a3.name,
    count(*) as collab_count
from
    author a3,
    (select distinct
        a.author_id as author_id ,
        a2.author_id as author2_id
    from authored a,
         authored a2
    where
        a.pub_id = a2.pub_id
        and a.author_id != a2.author_id) as authors_table
where
    a3.author_id = authors_table.author_id
group by
    a3.name
order by
    collab_count desc,
    a3.name
fetch first 1000 rows only;

--TODO : it executes nearly 24 sec, nested query may be separated table