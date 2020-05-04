select
    max_author_table.year,
    a2.name,
    max_author_table.max_value as count
from
    author a2,
    (select
        author_year_table.year as year,
        max(total) as max_value
    from
        (select
            p.year as year,
            count(*) as total
        from
            publication p,
            authored a
        where
            a.pub_id = p.pub_id
            and p.year < 1991
            and p.year >1939
        group by
            a.author_id,
            p.year) as author_year_table
    group by
        author_year_table.year
    order by
        year) as max_author_table,
    (select
        a.author_id as author_id,
        p.year as year,
        count(*) as total
    from
        publication p,
        authored a
    where
        a.pub_id = p.pub_id
        and p.year < 1991
        and p.year >1939
    group by
        a.author_id,
        p.year) as author_year
where
    a2.author_id = author_year.author_id
    and author_year.total = max_author_table.max_value
    and author_year.year = max_author_table.year
order by
    year,
    a2.name
;