select
    temp_table.field_name
from
    (select
        count(distinct pub_type) as distinct_counts
    from
        pub) as distinct_pubs,
    (select
        pub_field_table.field_name,
        count(*) as cnt
    from
        (select distinct
            p.pub_type as pub_type,
            f.field_name as field_name
        from
            pub p,
            field f
        where
            p.pub_key = f.pub_key
        group by
            p.pub_type,
            f.field_name
        order by
            p.pub_type,
            f.field_name) as pub_field_table
    group by
        pub_field_table.field_name) as temp_table
where
    temp_table.cnt = distinct_pubs.distinct_counts
;
	-- results are sorted alphabetically according to their pub_type first, then their field name.  