select 
	w.weekday_id,
	w.weekday_name,
	avg(fr.departure_delay + fr.arrival_delay) as avg_delay
from 
	flight_reports fr,
	weekdays w 
where 
	fr.origin_airport_id in 
		(select ai.airport_id 
	 	from 
			airport_ids ai
		where 
			ai.airport_desc like 'San Francisco, CA:%')
	and 
	fr.dest_airport_id in 
		(select ai2.airport_id 
	 	from 
			airport_ids ai2
		where 
			ai2.airport_desc like 'Boston, MA:%')
	and fr.weekday_id = w.weekday_id 
group by 
	w.weekday_id 
order by 
	avg(fr.departure_delay + fr.arrival_delay) asc
fetch first 1 row only