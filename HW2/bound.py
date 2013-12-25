import sys
import math

def mH(N, dvc):
    return math.pow(N, dvc)

def VCbound(N, dvc, delta):
    return math.sqrt(8*(math.log(4)+dvc*math.log(2*N)-math.log(delta))/N)

# Rademacher Penalty Bound
def RPbound(N, dvc, delta):
    return math.sqrt(2*(math.log(2*N)+dvc*math.log(N))/N) + \
           math.sqrt(2*math.log(1/delta)/N) + 1.0/N

# Parrondo & Van den Broek
def PVBbound(N, dvc, delta, e):
    return math.sqrt((2*e+math.log(6)+dvc*math.log(2*N)-math.log(delta))/N)

def Dbound(N, dvc, delta, e):
    return math.sqrt((4*e*(1+e)+math.log(4)+2*dvc*math.log(N)-math.log(delta))/(2*N))

N=int(sys.argv[1])
dvc=int(sys.argv[2])
delta=float(sys.argv[3])

evc=VCbound(N, dvc, delta)
erp=RPbound(N, dvc, delta)
print evc
print erp
epvb=min(evc, erp)
for i in xrange(1,10): 
    epvb=PVBbound(N, dvc, delta, epvb)
print epvb

ed=min(evc, erp, epvb)
for i in xrange(1,10): 
    ed=Dbound(N, dvc, delta, ed)
print ed

