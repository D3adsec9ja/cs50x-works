SELECT movies.title
FROM stars
INNER JOIN movies ON stars.movie_id = movies.id
INNER JOIN people ON stars.person_id = people.id
WHERE people.name IN ("Johnny Depp", "Helena Bonham Carter")
GROUP BY movies.title
HAVING count(movies.title) = 2;