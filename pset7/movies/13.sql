SELECT DISTINCT coactors.name FROM people AS kevin
JOIN stars AS kevin_stars ON kevin.id = kevin_stars.person_id
JOIN movies ON kevin_stars.movie_id = movies.id
JOIN stars AS coactors_stars ON movies.id = coactors_stars .movie_id
JOIN people AS coactors ON coactors_stars.person_id = coactors.id 
WHERE kevin.name = 'Kevin Bacon'
AND kevin.birth = 1958
AND coactors.name != 'Kevin Bacon';