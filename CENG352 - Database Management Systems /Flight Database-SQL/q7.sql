select 
	ac.airline_name,
	(cancelledFlights.cancelledCount * 100.0 / (totalFlights.totalCount)) as percentage
from 
	airline_codes ac, 
	(select 
		fr.airline_code as flightCode1,
		count(*) as cancelledCount
	from 	
		flight_reports fr
	where 
		fr.origin_city_name = 'Boston, MA'
		and fr.is_cancelled = 1
	group by 
		fr.airline_code) as cancelledFlights, 
	(select 
		fr.airline_code as flightCode2, 
		count(*) as totalCount
	from 	
		flight_reports fr
	where 
		fr.origin_city_name = 'Boston, MA'
	group by 
		fr.airline_code) as totalFlights
where 
	cancelledflights.flightCode1 = totalFlights.flightcode2
	and cancelledflights.flightCode1 = ac.airline_code 
	and (cancelledFlights.cancelledCount * 100.0 / (totalFlights.totalCount)) > 10
order by 
	percentage desc