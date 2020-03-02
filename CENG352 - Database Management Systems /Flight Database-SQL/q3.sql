select 
	tmp.plane as plane_tail_number,
	tmp.yearID as year,
	avg(tmp.dailyFlightCount) as daily_avg
from 
	(select 
		fr.plane_tail_number as plane,
		fr."year" as yearID, 
		count(*) as dailyFlightCount
	from 
		flight_reports fr
	where 
		fr.is_cancelled = 0
	group by
		plane_tail_number, 
		fr."day",
		fr."month",
		fr."year") as tmp
group by 
	tmp.plane,
	tmp.yearID
having 
	avg(tmp.dailyFlightCount) > 5
order by 
	tmp.plane,
	tmp.yearID