def simplify(poly):
    import re
    d = {}
    for x in re.findall(r"[+-]?[^+-]+", poly):
        m = re.findall(r"[a-z]+", x)[0]
        k = x.replace(m, '')
        m = "".join(sorted(m))
        k = int(k if re.match(r"[+-]?\d", k) else k + "1")
        d[m] = d.get(m, 0) + k
    d = {m: k for m, k in d.items() if k}
    d = sorted(d.items(), key=lambda x: (len(x[0]), x[0]))
    d = [''.join(['-' if k < 0 else '+', str('' if abs(k) == 1 else abs(k)), m]) for m, k in d]
    return ''.join(d).lstrip('+')


def simplify_v2(poly):
    # I'm feeling verbose today
    
    # get 3 parts (even if non-existent) of each term: (+/-, coefficient, variables)
    import re
    matches = re.findall(r'([+\-]?)(\d*)([a-z]+)', poly)
    
    # get the int equivalent of coefficient (including sign) and the sorted variables (for later comparison)
    expanded = [[int(i[0] + (i[1] if i[1] != "" else "1")), ''.join(sorted(i[2]))] for i in matches]
    
    # get the unique variables from above list. Sort them first by length, then alphabetically
    variables = sorted(list(set(i[1] for i in expanded)), key=lambda x: (len(x), x))
    
    # get the sum of coefficients (located in expanded) for each variable
    coefficients = {v:sum(i[0] for i in expanded if i[1] == v) for v in variables}
    
    # clean-up: join them with + signs, remove '1' coefficients, and change '+-' to '-'
    return '+'.join(str(coefficients[v]) + v for v in variables if coefficients[v] != 0).replace('1','').replace('+-','-')