select distinct 
	planes1.plane as plane_tail_number,
	planes1.aCode as first_owner,
	planes2.aCode as second_owner
from 
	(select distinct 
		fr.airline_code as aCode,
		fr.plane_tail_number as plane,
		fr."year" as "year",
		fr."month" as "month",
		fr."day" as "day"
	from 
		flight_reports fr) as planes1, 
	(select distinct 
		fr.airline_code as aCode,
		fr.plane_tail_number as plane,
		fr."year" as "year",
		fr."month" as "month",
		fr."day" as "day"
	from 
		flight_reports fr) as planes2	
where 
	planes1.plane = planes2.plane
	and planes1.aCode <> planes2.aCode
	and 
	(planes1.year < planes2.year
	or (planes1.year = planes2.year 
		and planes1.month < planes2.month)
	or (planes1.year = planes2.year 
		and planes1.month = planes2.month
		and planes1.day < planes2.day))
order by 
	planes1.plane asc 
