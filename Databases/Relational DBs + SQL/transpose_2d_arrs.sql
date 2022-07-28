select array(
    select array(
            select matrix[a][b]
            from (select generate_subscripts(matrix, 1) a)_)
    from (select generate_subscripts(matrix, 2) b)__) matrix
from matrices