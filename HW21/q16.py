import numpy as np
from sklearn.svm import SVC
import sys
import math

yy=[]
x=[]
with open(sys.argv[1], 'r') as in_file:
    for l in in_file:
        ll=l.split()
        yy.append(int(float(ll[0])))
        x.append([float(i) for i in ll[1:]])

x=np.array(x)
for d in [0,2,4,6,8]:
    y=[]
    for i in yy:
        if i==d: y.append(1)
        else: y.append(-1)
    y=np.array(y)
    
    clf = SVC(C=0.01, kernel='poly', degree=2, gamma=1, coef0=1)
    clf.fit(x,y)
    #print clf.support_
    #print clf.support_vectors_
    #print clf.dual_coef_
    #print clf.decision_function(x)
    #print sum(clf.dual_coef_[0])
    sa=sum([clf.dual_coef_[0][i]*y[clf.support_[i]] for i in xrange(len(clf.dual_coef_[0]))])
    print d, clf.score(x,y), sa

