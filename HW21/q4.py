x=[(1,0), (0,1), (0,-1), (-1,0), (0,2), (0,-2), (-2,0)]
y=[-1,-1,-1,1,1,1,1]

def g1((x1,x2)):
    return (8*x2*x2-16*x2+6*x1*x1-15)/9.0
def g2((x1,x2)):
    return (8*x2*x2-16*x2+6*x1*x1+15)/9.0
def g3((x1,x2)):
    return (8*x1*x1-16*x1+6*x2*x2-15)/9.0
def g4((x1,x2)):
    return (8*x1*x1-16*x1+6*x2*x2+15)/9.0
for i in xrange(len(x)):
    print g3(x[i])
