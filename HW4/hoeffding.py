import math

N=10000
#M=math.pow(2,N)
lM=N/math.log(2)
e=0.01
hb=math.log(2)+lM-2*e*e*N
print lM
print hb
#print math.exp(hb)
