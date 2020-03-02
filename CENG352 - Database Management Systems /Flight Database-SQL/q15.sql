select 
	ai.airport_desc 
from 
	airport_ids ai,
	(select 
		outgoing_flights.origin_airport_id as airportIds ,
		(
			outgoing_flights.outNum + incoming_flights.inNum) as totalNum
	from
		(select 
			fr1.origin_airport_id,
			count(*) as outNum
		from 
			flight_reports fr1
		where
			fr1.is_cancelled = 0
		group by 
			origin_airport_id) as outgoing_flights,
		(select 
			fr2.dest_airport_id ,
			count(*) inNum
		from 
			flight_reports fr2
		where
			fr2.is_cancelled = 0
		group by 
			dest_airport_id) as incoming_flights
	where 
		incoming_flights.dest_airport_id = outgoing_flights.origin_airport_id  
	order by  
		totalNum desc
	fetch first 5 row only) as answers
where 
	ai.airport_id = answers.airportIds 
order by 
	ai.airport_desc asc
