#List each pair of actors that have worked together.
with cte_actor_pairs as 
(
SELECT fa1.actor_id as actor_1, fa2.actor_id as actor_2, fa1.film_id 
FROM sakila.film_actor fa1
join sakila.film_actor fa2
on fa1.actor_id <> fa2.actor_id 
and fa1.film_id = fa2.film_id
where fa1.actor_id < fa2.actor_id
)
select * from cte_actor_pairs
join actor 
on cte_actor_pairs.actor_1 = actor.actor_id
;


# 2.-For each film, list actor that has acted in more films
drop table if exists sakila.temp_cte;
create temporary table sakila.temp_cte 
with cte__ as 
(
SELECT *, count(*) over(partition by actor_id) as counts_
 FROM sakila.film_actor
 )
 
 select film_id, actor_id, 
 rank() over(partition by film_id order by counts_ desc) as ranks_
 from 
 cte__;
 
 select * from 
  sakila.temp_cte  where ranks_ = 1;
