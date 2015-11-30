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

ty=[]
tx=[]
with open(sys.argv[2], 'r') as in_file:
    for l in in_file:
        ll=l.split()
        if float(ll[0])==0: ty.append(1)
        else: ty.append(-1)
        tx.append([float(i) for i in ll[1:]])
ty=np.array(ty)
tx=np.array(tx)
for d in [1,10,100,1000,10000]:
    clf = SVC(C=0.1, kernel='rbf', gamma=d)
    clf.fit(x,y)
    print '========',d
    print len(clf.support_)
    print clf.support_
    print clf.support_vectors_
    print clf.dual_coef_
    print clf.decision_function(x)
    print sum(clf.dual_coef_[0])
    print clf.score(tx,ty)

#w=[0.0, 0.0]
#for i in xrange(len(clf.dual_coef_[0])):
#    w[0]+=clf.dual_coef_[0][i]*clf.support_vectors_[i][0]
#    w[1]+=clf.dual_coef_[0][i]*clf.support_vectors_[i][1]
#print w
#ww=w[0]*w[0] + w[1]*w[1]
#print ww, math.sqrt(ww)
