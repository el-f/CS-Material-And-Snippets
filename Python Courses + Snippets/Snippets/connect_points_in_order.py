def connect_the_dots(paper):
    Y    = paper.find("\n")+1
    lst  = list(paper)
    pts  = {c: i for i,c in enumerate(paper) if c.isalpha() }
    chrs = sorted(pts)

    for i in range(len(pts)-1):
        a,b = sorted((pts[chrs[i]], pts[chrs[i+1]]))
        (x,y),(u,v) = divmod(a,Y), divmod(b,Y)
        dx, dy = Y * ( (u>x)-(u<x) ), (v>y)-(v<y)

        for j in range(a,b+1,dx+dy): lst[j]='*'

    return ''.join(lst)