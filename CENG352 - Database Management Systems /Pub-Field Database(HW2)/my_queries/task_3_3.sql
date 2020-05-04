 select
    a4.name,
    desired_authors.pub_count
from
     author a4,
    (with communications as
    (select
        a.pub_id as id
    from
         article a
    where
        a.journal = 'IEEE Trans. Wireless Communications'),
    letters as
    (select
        a.pub_id as id
    from
         article a
    where
        a.journal = 'IEEE Wireless Commun. Letters')
    select
        a2.author_id as id,
        count(*) as pub_count
    from
        authored a2,
        communications c
    where
        a2.pub_id = c.id
        and a2.author_id not in
        (
            select
                a3.author_id
            from
                authored a3,
                letters l
            where
                a3.pub_id = l.id
        )
    group by
        a2.author_id
    having
        count(*) > 9) as desired_authors
where a4.author_id = desired_authors.id
order by
    pub_count desc,
    name asc;

--TODO : handle temp tables issue