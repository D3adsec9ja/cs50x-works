
-- SQL query that returning the average energy of songs by Drake.

SELECT
    avg(energy)

FROM
    songs

WHERE
    artist_id = (
        SELECT
            id
        FROM
            artists
        WHERE
            name == "Drake"
    )