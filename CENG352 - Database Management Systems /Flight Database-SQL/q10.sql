select 
	ac.airline_name,
	count(*) as flight_count
from
	airline_codes ac,
	flight_reports fr2, 
	((select
		fr.plane_tail_number,
		fr.airline_code 
	from 
		world_area_codes wac,
		flight_reports fr
	where 
		wac.wac_name = 'Texas' 
		and wac.wac_id = fr.dest_wac_id)
	except	
	(select
		fr.plane_tail_number,
		fr.airline_code 
	from 
		world_area_codes wac,
		flight_reports fr
	where 
		wac.wac_name <> 'Texas' 
		and wac.wac_id = fr.dest_wac_id)) as onlyTexas
where 
	onlyTexas.airline_code = ac.airline_code 
	and fr2.plane_tail_number = onlyTexas.plane_tail_number 
group by 
	ac.airline_name 
order by 
	ac.airline_name asc 