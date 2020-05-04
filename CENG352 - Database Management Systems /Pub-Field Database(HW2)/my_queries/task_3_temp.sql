-- This is a common table expression in question 3.1. I used it to store author_ids whose publication count is between 150 and 200.

with author_ids_table as
(select
    a.author_id as id,
    count(*) as number
from
     authored a
group by
    a.author_id
having
    count(*) > 149 and count(*) < 200);

-- In order not to compute same number of publication by year table, I created a temporary table(for task_3_4)
create temporary table temp_years_table
(
    year int,
    number_of_pubs int
);

drop table temp_years_table;

