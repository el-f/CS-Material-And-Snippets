-- 𝕔𝕠𝕕𝕖𝕨𝕒𝕣𝕤.𝕔𝕠𝕞/𝕜𝕒𝕥𝕒/5821ee33ec380124f1000013
-- deal with table with different formats and casing for the same column

-- Version 1 - clean the table before operating on it
with
    cleaned_prospects as (
        select
            lower(trim(split_part(full_name, ' ', 1))) as first_name,
            lower(trim(split_part(full_name, ' ', 2))) as last_name,
            credit_limit
        from prospects
        where (full_name like '% %' and full_name not like '% % %') or (full_name like '% % %' and full_name not like '%. % %' and lower(full_name) not like 'miss % %')
        union
        select
            lower(trim(split_part(full_name, ' ', 2))) as first_name,
            lower(trim(split_part(full_name, ' ', 3))) as last_name,
            credit_limit
        from prospects
        where full_name like '%. % %' or lower(full_name) like 'miss % %'
        union
        select
            lower(trim(split_part(full_name, ', ', 2))) as first_name,
            lower(trim(split_part(full_name, ', ', 1))) as last_name,
            credit_limit
        from prospects
        where full_name like '%, %'
    )
select
    c.first_name,
    c.last_name,
    c.credit_limit as old_limit,
    max(p.credit_limit) as new_limit
from customers as c
         left join cleaned_prospects as p
                   on lower(c.first_name) = p.first_name and
                      lower(c.last_name)  = p.last_name
where p.credit_limit > c.credit_limit
group by
    c.first_name,
    c.last_name,
    c.credit_limit
order by
    c.first_name,
    c.last_name


-- Version 2 - index the dirty table using the dirty column
create extension pg_trgm;
create index prospects_idx on prospects using gin(full_name gin_trgm_ops);

select c.first_name,
       c.last_name,
       c.credit_limit as old_limit,
       max(p.credit_limit) as new_limit
from customers c, prospects p
where p.full_name ilike '%' || c.first_name || '%'
  and p.full_name ilike '%' || c.last_name  || '%'
  and p.credit_limit > c.credit_limit
group by c.first_name, c.last_name, c.credit_limit
having max(p.credit_limit) > c.credit_limit
order by first_name, last_name;

