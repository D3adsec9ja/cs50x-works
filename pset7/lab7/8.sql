  -- SQL query that lists the names of the songs that featuring other artists.


SELECT

    name

FROM

    songs

WHERE

    name LIKE "%feat.%"