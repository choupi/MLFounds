from math import exp

def duE(u, v):
  return exp(u)+v*exp(u*v)+2*u-2*v-3

def dvE(u, v):
  return 2*exp(2*v)+u*exp(u*v)-2*u+4*v-2

def E(u, v):
  return exp(u)+exp(2*v)+exp(v*u)+u*u-2*u*v+2*v*v-3*u-2*v

u=0
v=0
eta=0.01
print duE(u,v), dvE(u,v)
for i in xrange(1,6):
  ue=eta*duE(u,v)
  ve=eta*dvE(u,v)
  u=u-ue
  v=v-ve
  print 'de', ue, ve
  print u, v
print E(u,v)
