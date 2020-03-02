select 
	ac.airline_name as airline_name,
	tmp3.yearID as year,
	tmp3.totalCount as total_num_flights,
	tmp4.totalCount as cancelled_flights
from
	airline_codes ac, 
	(select 
		tmp2.aCode as aCode,
		fr2.year as yearID,
		count(*) as totalCount
	from
		flight_reports fr2, 
		(select 
			tmp.aCode as aCode
		from 
			(select  
				totals.aCode as aCode,
				totals.year as yearID,
				avg(totals.total_num_flights) as avgNum
			from  
				(select 
					fr.airline_code as aCode,
					fr.year,
					count(*) as total_num_flights 
				from 
					flight_reports fr
				group by
					fr.airline_code, 
					fr."year",
					fr."month",
					fr."day" ) as totals
			group by 
				totals.aCode,
				totals.year
			having avg(totals.total_num_flights) > 2000) as tmp
		group by 
			tmp.aCode
		having 
			count(*) = 4) as tmp2
	where 
		fr2.airline_code = tmp2.aCode
	group by 
		tmp2.aCode,
		fr2.year) as tmp3,
	(select 
		tmp2.aCode as aCode,
		fr2.year as yearID,
		count(*) as totalCount
	from
		flight_reports fr2, 
		(select 
			tmp.aCode as aCode
		from 
			(select  
				totals.aCode as aCode,
				totals.year as yearID,
				avg(totals.total_num_flights) as avgNum
			from  
				(select 
					fr.airline_code as aCode,
					fr.year,
					count(*) as total_num_flights 
				from 
					flight_reports fr
				group by
					fr.airline_code, 
					fr."year",
					fr."month",
					fr."day" ) as totals
			group by 
				totals.aCode,
				totals.year
			having avg(totals.total_num_flights) > 2000) as tmp
		group by 
			tmp.aCode
		having 
			count(*) = 4) as tmp2
	where 
		fr2.airline_code = tmp2.aCode
		and fr2.is_cancelled = 1
	group by 
		tmp2.aCode,
		fr2.year) as tmp4
where 
	tmp3.aCode = tmp4.aCode
	and tmp3.yearID = tmp4.yearID
	and tmp3.aCode = ac.airline_code 
order by 
	ac.airline_name 
	

	

	