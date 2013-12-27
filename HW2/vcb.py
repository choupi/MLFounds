import math
import sys

N=int(sys.argv[1])
dvc=int(sys.argv[2])
e=float(sys.argv[3])

mm=math.log(4)+dvc*math.log(2*N)-e*e*N/8
print mm, math.exp(mm), 1-math.exp(mm)
print 1-4*math.pow(2*N,dvc)*math.exp(-1*e*e*N/8)

