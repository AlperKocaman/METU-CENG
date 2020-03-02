select 
	answer.year as year,
	w2.weekday_name ,
	cr.reason_desc as reason,
	answer.maxNumber as number_of_cancellations
from 
	weekdays w2,
	cancellation_reasons cr, 
	(select 
		tmp2.year as year,
		tmp2.weekday as weekday,
		tmp3.reason as reason,
		tmp2.maxNumber as maxNumber
	from 
		(select
			tmp.yearID as year,
			tmp.weekday as weekday ,
			max(tmp.numberOfCancellation) as maxNumber	
		from 
			(select 
				fr."year" as yearID,
				fr.weekday_id as weekday,
				fr.cancellation_reason as reason, 
				count(fr.cancellation_reason) numberOfCancellation
			from 
				flight_reports fr
			where 
				fr.is_cancelled = 1
			group by 
				fr."year",
				fr.weekday_id,
				fr.cancellation_reason) as tmp
		group by
			tmp.yearID,
			tmp.weekday) as tmp2,
		(select 
			fr."year" as yearID,
			fr.weekday_id as weekday,
			fr.cancellation_reason as reason, 
			count(fr.cancellation_reason) numberOfCancellation
		from 
			flight_reports fr
		where 
			fr.is_cancelled = 1
		group by 
			fr."year",
			fr.weekday_id,
			fr.cancellation_reason) as tmp3
	where 
		tmp2.year = tmp3.yearID
		and tmp2.weekday = tmp3.weekday
		and tmp2.maxNumber = tmp3.numberOfCancellation) as answer
where 
	cr.reason_code = answer.reason 
	and w2.weekday_id = answer.weekday
order by 
	answer.year asc,
	w2.weekday_id asc
	