select 
	distinct 
	BostonFlights.yearID as year,
	BostonFlights.airlineCode as airline_code,
	BostonFlights.boston_flight_count as boston_flight_count,
	((BostonFlights.boston_flight_count * 100.0) / TotalFlights.total_flight_count) as boston_flight_percentage
from 
	(select
		fr."year" as yearID,
		fr.airline_code as airlineCode, 
		count(*) as boston_flight_count
	from 
		flight_reports fr
	where 
		fr.is_cancelled = 0
		and fr.dest_city_name = 'Boston, MA'
	group by 
		fr."year",
		fr.airline_code) as BostonFlights,	
	(select
		fr."year" as yearID,
		fr.airline_code as airlineCode, 
		count(*) as total_flight_count
	from 
		flight_reports fr
	where 
		fr.is_cancelled = 0
	group by 
		fr."year",
		fr.airline_code) as TotalFlights
where 
	BostonFlights.airlineCode = TotalFlights.airlineCode
	and BostonFlights.yearID = TotalFlights.yearID
	and ((BostonFlights.boston_flight_count * 100.0) / TotalFlights.total_flight_count) > 1
order by 
	BostonFlights.yearID,
	BostonFlights.airlineCode 
	