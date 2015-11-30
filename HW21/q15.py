import numpy as np
from sklearn.svm import SVC
import sys
import math

y=[]
x=[]
with open(sys.argv[1], 'r') as in_file:
    for l in in_file:
        ll=l.split()
        if float(ll[0])==0: y.append(1)
        else: y.append(-1)
        x.append([float(i) for i in ll[1:]])
y=np.array(y)
x=np.array(x)

clf = SVC(C=0.01, kernel='linear')
clf.fit(x,y)
print clf.support_
print clf.support_vectors_
print clf.dual_coef_
print clf.decision_function(x)
print sum(clf.dual_coef_[0])

w=[0.0, 0.0]
for i in xrange(len(clf.dual_coef_[0])):
    w[0]+=clf.dual_coef_[0][i]*clf.support_vectors_[i][0]
    w[1]+=clf.dual_coef_[0][i]*clf.support_vectors_[i][1]
print w
ww=w[0]*w[0] + w[1]*w[1]
print ww, math.sqrt(ww)
