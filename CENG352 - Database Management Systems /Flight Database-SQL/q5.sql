select 
	concat(cast(fr.day as varchar), '/', cast(fr.month as varchar), '/', cast(fr.year as varchar)) as flight_date,
	fr.plane_tail_number,
	fr.arrival_time as flight1_arrival_time,
	fr2.departure_time as flight2_departure_time,
	fr.origin_city_name ,
	fr.dest_city_name as stop_city_name,
	fr2.dest_city_name,
	(fr.flight_time + fr.taxi_out_time + fr2.taxi_in_time + fr2.flight_time) as total_time,
	(fr.flight_distance + fr2.flight_distance) as total_distance
from 
	flight_reports fr,
	flight_reports fr2 
where 
	fr.origin_city_name = 'Seattle, WA'
	and fr.dest_city_name <> 'Boston, MA'
	and fr.dest_airport_code = fr2.origin_airport_code
	and fr2.dest_city_name = 'Boston, MA'
	and fr.is_cancelled = 0
	and fr2.is_cancelled = 0
	and fr."year" = fr2."year" 
	and fr."day" = fr2."day" 
	and fr."month" = fr2."month" 
	and fr.arrival_time < fr2.departure_time
	and fr.plane_tail_number = fr2.plane_tail_number 
order by
	total_time,
	total_distance,
	plane_tail_number,
	stop_city_name