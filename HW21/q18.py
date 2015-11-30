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

yy=[]
xx=[]
with open(sys.argv[2], 'r') as in_file:
    for l in in_file:
        ll=l.split()
        if float(ll[0])==0: yy.append(1)
        else: yy.append(-1)
        xx.append([float(i) for i in ll[1:]])
yy=np.array(yy)
xx=np.array(xx)

for d in [0.001, 0.01, 0.1, 1, 10]:
    clf = SVC(C=d, kernel='rbf', gamma=100)
    clf.fit(x,y)
    print '========',d
    print len(clf.support_)
    #print clf.support_
    #print clf.support_vectors_
    print clf.dual_coef_
    print clf.intercept_
    #r=clf.decision_function(clf.support_vectors_)
    #for i in xrange(len(clf.support_)):
    #    if math.fabs(clf.dual_coef_[0][i])<d: print clf.dual_coef_[0][i], r[i]
    print sum(clf.dual_coef_[0])
    print clf.score(xx, yy)

#w=[0.0, 0.0]
#for i in xrange(len(clf.dual_coef_[0])):
#    w[0]+=clf.dual_coef_[0][i]*clf.support_vectors_[i][0]
#    w[1]+=clf.dual_coef_[0][i]*clf.support_vectors_[i][1]
#print w
#ww=w[0]*w[0] + w[1]*w[1]
#print ww, math.sqrt(ww)
