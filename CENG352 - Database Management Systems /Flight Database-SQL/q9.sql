select  
	flights.tailNum as plane_tail_number, 
	avg(fr2.flight_distance / fr2.flight_time ) as avg_speed 
from 
	flight_reports fr2,
	((select 
		fr.plane_tail_number as tailNum
	from 
		flight_reports fr
	where 
		fr.is_cancelled = 0 
		and fr."month" = 1
		and fr."year" = 2016
		and (fr.weekday_id = 6
		or fr.weekday_id = 7))
	except(
	select 
		fr.plane_tail_number as tailNum
	from 
		flight_reports fr
	where 
		fr.is_cancelled = 0
		and fr."month" = 1
		and fr."year" = 2016
		and not(fr.weekday_id = 6
		or fr.weekday_id = 7))) as flights
where 
	fr2."month" = 1
	and fr2."year" = 2016
	and fr2.plane_tail_number = flights.tailNum
group by 
	flights.tailNum 
order by 
	avg_speed desc
	


	