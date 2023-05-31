#1
select name
from pokemon
where type = 'Grass'
order by name;

#2
select name
from trainer
where hometown='Brown City' or hometown='Rainbow City'
order by name;

#3
select distinct type
from pokemon
order by type;

#4
select name
from city
where name like 'B%'
order by name;

#5
select hometown
from trainer
where name not like 'M%'
order by hometown;

#6
select nickname
from catchedpokemon
where level= (select max(level)
              from catchedpokemon)
order by nickname;

#7
SELECT name
FROM pokemon
WHERE name LIKE 'A%'
  OR name LIKE 'E%'
  OR name LIKE 'I%'
  OR name LIKE 'O%'
  OR name LIKE 'U%'
ORDER BY name;

#8
select avg(level) as AverageLevel
from catchedpokemon;

#9
select max(level)
from catchedpokemon
where owner_id=5;

#10
select distinct hometown
from trainer
order by hometown;

#11
SELECT t.name, cp.nickname
FROM Trainer t
JOIN CatchedPokemon cp ON t.id = cp.owner_id
  AND cp.nickname LIKE 'A%'
ORDER BY t.name;

#12
select t.name
from trainer t
join gym g on t.id = g.leader_id
join city c on g.city = c.name
and c.description='Amazon';

#13
SELECT cp.owner_id, COUNT(cp.owner_id) AS cnt
FROM CatchedPokemon cp
JOIN Pokemon p ON cp.pid = p.id
  AND p.type = 'Fire'
GROUP BY cp.owner_id
HAVING cnt = (SELECT MAX(cnt)
              FROM (SELECT COUNT(cp.owner_id) AS cnt
                    FROM CatchedPokemon cp
                    JOIN Pokemon p ON cp.pid = p.id
                      AND p.type = 'Fire'
                    GROUP BY cp.owner_id) sub);

#14

select distinct type
from pokemon
where id<10
order by id desc;

#15
select count(*)
from pokemon
where not type='Fire';

#16
select p.name
from pokemon p
join Evolution ev ON p.id = ev.before_id
and ev.before_id > ev.after_id
order by p.name;

#17
select avg(cp.level) as avgLevel
from catchedpokemon cp
join pokemon p on cp.pid = p.id
and p.type='Water';

#18
select cp.nickname
from catchedpokemon cp
join gym g on cp.owner_id=g.leader_id
where cp.level = (select max(cp.level)
                  from catchedpokemon cp, gym g
                  where cp.owner_id = g.leader_id);

#19
select t.name
from trainer t
join catchedpokemon c on t.id = c.owner_id
where t.hometown = 'Blue City'
group by t.name
having avg(level) = (select max(avglevel)
                     from (select avg(level) as avglevel
                           from trainer t
                           join catchedpokemon cp on t.id = cp.owner_id
                           where t.hometown= 'Blue City'
                           group by t.name) sub)
order by t.name;

#20
select p.name
from pokemon p
join catchedpokemon cp on p.id = cp.pid
where p.id in (select before_id from evolution)
and p.type = 'Electric'
and cp.owner_id in (select id
                    from trainer
                    group by hometown
                    having count(*) = 1);

#21
select t.name, sum(cp.level) as sumLevel
from trainer t
join gym g on t.id = g.leader_id
join catchedpokemon cp on g.leader_id=cp.owner_id
group by t.name
order by sumLevel desc;

#22
select hometown
from trainer
group by hometown
having count(*) = (select max(cnt)
                   from (select hometown, count(*) as cnt
                         from trainer
                         group by hometown) sub);

#23
select distinct p.name
from pokemon p
join (select cp.pid, count(distinct t.hometown) as cnt
      from catchedpokemon cp
      join trainer t on cp.owner_id = t.id
      and (t.hometown = 'Sangnok City'
          or t.hometown='Brown City')
      group by cp.pid) sub on p.id = sub.pid
and sub.cnt = 2
order by p.name;

#24
select t.name
from trainer t
join catchedpokemon cp on t.id = cp.owner_id
join pokemon p on cp.pid = p.id
and p.name like 'P%'
where t.hometown = 'Sangnok City'
order by t.name;

#25
select t.name as TrainerName, p.name as PokemonName
from trainer t
join catchedpokemon cp on t.id = cp.owner_id
join pokemon p on p.id = cp.pid
order by TrainerName, PokemonName;

#26
select p.name
from pokemon p
join evolution ev on p.id = ev.before_id
and ev.before_id not in (select after_id from evolution)
and ev.after_id not in (select before_id from evolution)
order by p.name;

#27
select cp.nickname
from catchedpokemon cp
join gym g on cp.owner_id=g.leader_id
and g.city = 'Sangnok City'
join pokemon p on cp.pid = p.id
and p.type='Water'
order by cp.nickname;

#28
select name
from trainer
where id in (select owner_id
             from catchedpokemon
             where pid in (select after_id from evolution)
             group by owner_id
             having count(*) >= 3)
order by name;

#29
select name
from pokemon
where id not in (select distinct pid from catchedpokemon)
order by name;

#30
select max(cp.level) as maxLevel
from catchedpokemon cp
join trainer t on cp.owner_id = t.id
group by t.hometown
order by maxLevel desc;

#31
select p1.id, p1.name as firstName, p2.name as secondName, p3.name as thirdName
from (select ev1.before_id as bid, ev1.after_id as aid1, ev2.after_id as aid2
      from evolution ev1, evolution ev2
      where ev1.after_id=ev2.before_id) sub
join pokemon p1 on sub.bid = p1.id
join pokemon p2 on sub.aid1 = p2.id
join pokemon p3 on sub.aid2 = p3.id
order by p1.id;
