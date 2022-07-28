-- growth rate per month
select date_trunc('month', created_at)::date as date,
       count(*),
       round((100 * (count(*) - lag(count(*), 1) over (order by date_trunc('month', created_at)))::float / lag(count(*), 1) over (order by date_trunc('month', created_at)))::numeric, 1) || '%' as percent_growth
from posts
group by date_trunc('month', created_at)
order by date_trunc('month', created_at)