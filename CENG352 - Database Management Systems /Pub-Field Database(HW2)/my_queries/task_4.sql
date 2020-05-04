-- creating ActiveAuthors table
create table ActiveAuthors
(
    name text
);

--inserting active authors to ActiveAuthors table
insert into ActiveAuthors(name)
select
    a2.name
from
    author a2,
    (select distinct
        a.author_id as author_id
    from
        authored a,
        publication p
    where
        a.pub_id = p.pub_id
        and p.year > 2017) as active_authors_ids
where
    a2.author_id = active_authors_ids.author_id ;

-- trigger

create or replace function add_to_active_authors()
  returns trigger AS
$func$
BEGIN
    if (new.pub_id in
        (
        select
            pub_id
        from
            publication
        where
            year > 2017
        )) then
    insert into activeauthors(name)
    select
        name
    from
        author
    where author.author_id = new.author_id
    and author.name not in (select name from activeauthors);
    end if;
    return new;
END
$func$
LANGUAGE plpgsql;

create trigger ActiveAuthorsTrigger
after insert
    on authored
for each row
execute procedure add_to_active_authors();