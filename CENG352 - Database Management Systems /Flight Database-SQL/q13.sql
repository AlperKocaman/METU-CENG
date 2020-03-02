select 
	ac.airline_name,
	monday.mondayCount as monday_flights,
	sunday.sundayCount as sunday_flights
from 
	airline_codes ac, 
	(select 
		fr.airline_code as airlineCode,
		count(*) as mondayCount
	from 
		flight_reports fr
	where
		fr.is_cancelled = 0
	group by 
		fr.airline_code, 
		fr.weekday_id 
	having 
		fr.weekday_id = 1) as monday ,
	(select 
		fr.airline_code as airlineCode,
		count(*) as sundayCount
	from 
		flight_reports fr
	where
		fr.is_cancelled = 0
	group by 
		fr.airline_code, 
		fr.weekday_id 
	having 
		fr.weekday_id = 7) as sunday
where 
	ac.airline_code = monday.airlineCode
	and ac.airline_code = sunday.airlineCode
order by 
	ac.airline_name asc