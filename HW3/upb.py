from math import exp
from math import log

def theta(a):
  return 1.0/(1+exp(-1.0*a))

def e(a):
  if a<0: return 1
  return 0

for i in xrange(-10,10):
  print e(i), theta(-1*i), max(0,1-i), max(0,-1*i), max(0,1-i)*max(0,1-i)
