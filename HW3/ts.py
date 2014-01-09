from math import exp
from numpy import matrix
from numpy import linalg

def duE(u, v):
  return exp(u)+v*exp(u*v)+2*u-2*v-3

def dduE(u, v):
  return exp(u)+v*v*exp(u*v)+2

def dvE(u, v):
  return 2*exp(2*v)+u*exp(u*v)-2*u+4*v-2

def ddvE(u, v):
  return 4*exp(2*v)+u*u*exp(u*v)+4

def duvE(u, v):
  return u*v*exp(u*v)-2

def E(u, v):
  return exp(u)+exp(2*v)+exp(v*u)+u*u-2*u*v+2*v*v-3*u-2*v

def HessianMatrix(u, v):
  return matrix([[dduE(u,v), duvE(u,v)], [duvE(u,v), ddvE(u,v)]])

u=0
v=0
eta=0.01
print dduE(u,v)/2, ddvE(u,v)/2, duvE(u,v), duE(u,v), dvE(u,v), E(u,v)
#print linalg.inv(HessianMatrix(u, v))
for i in xrange(1,6):
  invH=linalg.inv(HessianMatrix(u, v))
  uv=matrix([[duE(u,v)],[dvE(u,v)]])
  ND=invH*uv
  u=u-ND[0,0]
  v=v-ND[1,0]
  print u, v
print E(u,v)
