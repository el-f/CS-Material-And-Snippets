-- 𝕔𝕠𝕕𝕖𝕨𝕒𝕣𝕤.𝕔𝕠𝕞/𝕜𝕒𝕥𝕒/5818bde9559ff58bd90004a2
-- CTE + pairwise sorting + join

with top_pair as (
  select actor_a.actor_id id_a, actor_b.actor_id id_b
  from film_actor actor_a join film_actor actor_b 
    on  actor_a.film_id   = actor_b.film_id 
    and actor_a.actor_id  < actor_b.actor_id
  group by actor_a.actor_id, actor_b.actor_id
  order by count(*) desc
  limit 1)
select
  (select first_name || ' ' || last_name from actor where actor_id = top_pair.id_a) first_actor,
  (select first_name || ' ' || last_name from actor where actor_id = top_pair.id_b) second_actor,
  title
from top_pair
  join film_actor fa_a on id_a = fa_a.actor_id
  join film_actor fa_b on id_b = fa_b.actor_id
  join film f on fa_a.film_id = f.film_id and fa_b.film_id = f.film_id
