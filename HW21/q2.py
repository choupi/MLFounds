x=[(1,0), (0,1), (0,-1), (-1,0), (0,2), (0,-2), (-2,0)]
y=[-1,-1,-1,1,1,1,1]

def t1((x1,x2)):
    return x2*x2-2*x1+3
def t2((x1,x2)):
    return x1*x1-2*x2-3

def g1((x1,x2)):
    return x1+x2-4.5
def g2((x1,x2)):
    return x1-x2-4.5
def g3((x1,x2)):
    return x1-4.5
def g4((x1,x2)):
    return x2-4.5
for i in xrange(len(x)):
    print y[i]*g3((t1(x[i]), t2(x[i])))
