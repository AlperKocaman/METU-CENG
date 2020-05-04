-- In order not to compute same number of publication by year table, I created a temporary table(for task_3_4)
create temporary table temp_years_table
(
    year int,
    number_of_pubs int
);

insert into temp_years_table(year, number_of_pubs)
select
    p.year as year,
    count(*) as number
from
   publication p
Where
    p.year > 1939
group by
    p.year;

select
    concat(cast(answer_table.year as varchar), '-' ,cast(answer_table.max_year as varchar)) as decade,
    answer_table.total
from
    (select
        t.year as year,
        sum(t2.number_of_pubs) as total,
        (min(t2.year) +10)  as max_year
    from
        temp_years_table t,
        temp_years_table t2
    where
        t.year +10 > t2.year
        and t.year <= t2.year
    group by
        t.year,
        t.number_of_pubs
    order by
        t.year) as answer_table
;

drop table temp_years_table;

-- TODO : correct or ask " problem / maybe concatenating with '\"' solves problem