select 
	ac.airport_code, 
	ac.airport_desc,
	count(*) as cancel_count
from 
	airport_codes ac, 
	flight_reports fr
where 
	fr.is_cancelled = 1
	and fr.cancellation_reason = 'D'
	and fr.origin_airport_code = ac.airport_code
group by 
	ac.airport_code 
order by 
	cancel_count desc,
	airport_code asc