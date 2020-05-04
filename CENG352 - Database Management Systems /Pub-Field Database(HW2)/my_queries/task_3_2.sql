select
    a3.name as author_name,
    ieee_authors.pub_count as pub_count
from
    author a3 ,
    (select
        a2.author_id as author_id,
        count(*) as pub_count
    from
        authored a2,
        (select
            a.pub_id as id
        from
            article a
        where
            a.journal LIKE 'IEEE%') as ieee_related_table
    where
        a2.pub_id = ieee_related_table.id
    group by
        a2.author_id
    order by
        pub_count desc
    fetch first 100 row only) as ieee_authors
where
    a3.author_id = ieee_authors.author_id
order by
    pub_count desc,
    author_name asc
fetch first 50 row only;

-- TODO: check 100 is true or make join inside