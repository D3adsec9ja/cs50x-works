--SQL query to list names of the top 5 longest songs, within descending order of length.
SELECT name

FROM songs

ORDER BY duration_ms DESC

LIMIT 5;