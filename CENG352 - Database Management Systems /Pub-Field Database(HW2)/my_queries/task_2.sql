-- inserting 'author' values

insert into author(name)
select distinct
	f.field_value
from
	field f
where
	f.field_name = 'author';

-- inserting 'publication' values

insert into publication(pub_key, title, "year")
select
	f1.pub_key,
	f1.field_value,
	cast(f2.field_value as int)
from
	field f1,
	field f2
where
	f1.pub_key = f2.pub_key
	and f1.field_name = 'title'
	and f2.field_name = 'year';

-- inserting 'article' values

insert into article(pub_id, journal, "month", volume, "number" )
select
	p3.pub_id,
	temp_table4.journal ,
	temp_table4.month,
	temp_table4.volume,
	temp_table4.number
from
	"publication" p3,
	(select
		articles.id as id,
		temp_table3.journal as journal,
		temp_table3.month as month ,
		temp_table3.volume as volume,
		temp_table3.number as number
	from
		(select
			p2.pub_key as id
		from
			pub p2
		where
			p2.pub_type = 'article') as articles
	left join
		(select
			temp_table1.id as id,
			temp_table1.journal as journal,
			temp_table1.month as month ,
			temp_table2.volume as volume ,
			temp_table2.number as number
		from
			(select
				journal_table.id as id,
				journal_table.value as journal,
				month_table.value as month
			from
				(select
					p.pub_key as id,
					f.field_value as value
				from
					"publication" p,
					field f
				where
					p.pub_key = f.pub_key
					and f.field_name = 'journal') as journal_table
				full outer join
				(select
					p.pub_key as id,
					f.field_value as value
				from
					"publication" p,
					field f
				where
					p.pub_key = f.pub_key
					and f.field_name = 'month') as month_table
				on journal_table.id = month_table.id) as temp_table1
			full outer join
			(select
				volume_table.id as id,
				volume_table.value as volume,
				number_table.value as number
			from
				(select
					p.pub_key as id,
					f.field_value as value
				from
					"publication" p,
					field f
				where
					p.pub_key = f.pub_key
					and f.field_name = 'volume') as volume_table
				full outer join
				(select
					p.pub_key as id,
					f.field_value as value
				from
					"publication" p,
					field f
				where
					p.pub_key = f.pub_key
					and f.field_name = 'number') as number_table
				on volume_table.id = number_table.id) as temp_table2
			on temp_table1.id = temp_table2.id ) as temp_table3
	on articles.id = temp_table3.id) as temp_table4
where
	p3.pub_key = temp_table4.id;


-- inserting 'book' values

insert into book(pub_id, publisher, isbn)
select
    publisher_table.id as id,
    publisher_table.value as publisher_value,
    isbn_table.value as isbn_value
from
    (select
        p2.pub_id as id,
        f.field_value as value
    from
        field f,
        publication p2
    where
        f.field_name ='publisher'
        and f.pub_key in
            (select
                p.pub_key
            from
                pub p
            where
                p.pub_type = 'book')
        and f.pub_key = p2.pub_key) as publisher_table
left join
    (select
        p3.pub_id as id,
        max(f.field_value) as value
    from
        field f,
        publication p3
    where
        f.field_name ='isbn'
        and f.pub_key in
            (select
                p.pub_key
            from
                pub p
            where
                p.pub_type = 'book')
        and p3.pub_key = f.pub_key
    group by
        p3.pub_id) as isbn_table
on publisher_table.id = isbn_table.id;


-- inserting 'incollection' values

insert into incollection(pub_id, book_title, publisher, isbn)
select
    book_title_table.id as id,
    book_title_table.value as book_title_value,
    publisher_table.value as publisher_value,
    isbn_table.value as isbn_value
from
    (select
        p2.pub_id as id,
        f.field_value as value
    from
        field f,
        publication p2
    where
        f.field_name ='booktitle'
        and f.pub_key in
            (select
                p.pub_key
            from
                pub p
            where
                p.pub_type = 'incollection')
        and f.pub_key = p2.pub_key) as book_title_table
left join
    (select
        p2.pub_id as id,
        f.field_value as value
    from
        field f,
        publication p2
    where
        f.field_name ='publisher'
        and f.pub_key in
            (select
                p.pub_key
            from
                pub p
            where
                p.pub_type = 'incollection')
        and f.pub_key = p2.pub_key) as publisher_table
on book_title_table.id = publisher_table.id
left join
    (select
        p3.pub_id as id,
        f.field_value as value
    from
        field f,
        publication p3
    where
        f.field_name ='isbn'
        and f.pub_key in
            (select
                p.pub_key
            from
                pub p
            where
                p.pub_type = 'incollection')
        and p3.pub_key = f.pub_key) as isbn_table
on publisher_table.id = isbn_table.id;

-- inserting 'inproceedings' value

insert into inproceedings(pub_id, book_title, editor)
select
    book_title_table.id as id,
    book_title_table.value as book_title_value,
    editor_table.value as editor_value
from
    (select
        p2.pub_id as id,
        f.field_value as value
    from
        field f,
        publication p2
    where
        f.field_name ='booktitle'
        and f.pub_key in
            (select
                p.pub_key
            from
                pub p
            where
                p.pub_type = 'inproceedings')
        and f.pub_key = p2.pub_key) as book_title_table
left join
    (select
        p3.pub_id as id,
        f.field_value as value
    from
        field f,
        publication p3
    where
        f.field_name ='editor'
        and f.pub_key in
            (select
                p.pub_key
            from
                pub p
            where
                p.pub_type = 'inproceedings')
        and p3.pub_key = f.pub_key) as editor_table
on book_title_table.id = editor_table.id;

-- inserting 'authored' value

insert into authored(author_id, pub_id)
with pub_author_table as
    (select distinct
        f.pub_key as key,
        f.field_value as name
    from
        field f
    where
        f.field_name = 'author')
select
    a.author_id,
    p.pub_id
from
    publication p,
    author a,
    pub_author_table p2
where
    a.name = p2.name
    and p.pub_key = p2.key;





















































