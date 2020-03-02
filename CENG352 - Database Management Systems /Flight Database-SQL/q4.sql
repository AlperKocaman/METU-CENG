select 
	ac.airline_name 
from
	airline_codes ac, 
	((select
		BostonFlights.aCode as aCode
	from
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'Boston, MA'
			and (fr."year" = 2018 
				or fr."year" = 2019)) as BostonFlights,
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'New York, NY'
			and (fr."year" = 2018 
				or fr."year" = 2019)) as NewYorkFlights,
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'Portland, ME'
			and (fr."year" = 2018 
				or fr."year" = 2019)) as PortlandFlights,
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'Washington, DC'
			and (fr."year" = 2018 
				or fr."year" = 2019)) as WashingtonFlights,
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'Philadelphia, PA'
			and (fr."year" = 2018 
				or fr."year" = 2019)) as PhiladelphiaFlights
	where 
		BostonFlights.aCode = NewYorkFlights.aCode
		and BostonFlights.aCode = PortlandFlights.aCode
		and BostonFlights.aCode = WashingtonFlights.aCode
		and BostonFlights.aCode = PhiladelphiaFlights.aCode)
	except 
	(select
		BostonFlights.aCode
	from
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'Boston, MA'
			and (fr."year" = 2016 
				or fr."year" = 2017)) as BostonFlights,
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'New York, NY'
			and (fr."year" = 2016 
				or fr."year" = 2017)) as NewYorkFlights,
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'Portland, ME'
			and (fr."year" = 2016 
				or fr."year" = 2017)) as PortlandFlights,
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'Washington, DC'
			and (fr."year" = 2016 
				or fr."year" = 2017)) as WashingtonFlights,
		(select distinct 
			fr.airline_code as aCode,
			fr.year
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 0
			and fr.dest_city_name = 'Philadelphia, PA'
			and (fr."year" = 2016 
				or fr."year" = 2017)) as PhiladelphiaFlights
	where 
		BostonFlights.aCode = NewYorkFlights.aCode
		and BostonFlights.aCode = PortlandFlights.aCode
		and BostonFlights.aCode = WashingtonFlights.aCode
		and BostonFlights.aCode = PhiladelphiaFlights.aCode)) as tmp2
where 
	tmp2.aCode = ac.airline_code 
order by
	ac.airline_name asc
	
	
	
	
	