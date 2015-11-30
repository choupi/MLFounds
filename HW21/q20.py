import numpy as np
from sklearn.svm import SVC
from sklearn.cross_validation import cross_val_score,ShuffleSplit
from sklearn.grid_search import GridSearchCV
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

estor = SVC(C=0.1, kernel='rbf')
cv=ShuffleSplit(len(y), 100, 1000)
clf=GridSearchCV(estimator=estor, cv=cv, param_grid=dict(gamma=[1,10,100,1000,10000]))
clf.fit(x,y)
print clf.grid_scores_
print clf.best_params_

#for d in [1,10,100,1000,10000]:
#    clf = SVC(C=0.1, kernel='rbf', gamma=d)
#    cv=ShuffleSplit(len(y), 100, 1000)
#    scores=cross_val_score(clf, x, y, cv=cv)
#    print d, scores
    #clf.fit(x,y)
    #print '========',d
    #print len(clf.support_)
    #print clf.support_
    #print clf.support_vectors_
    #print clf.dual_coef_
    #print clf.decision_function(x)
    #print sum(clf.dual_coef_[0])

#w=[0.0, 0.0]
#for i in xrange(len(clf.dual_coef_[0])):
#    w[0]+=clf.dual_coef_[0][i]*clf.support_vectors_[i][0]
#    w[1]+=clf.dual_coef_[0][i]*clf.support_vectors_[i][1]
#print w
#ww=w[0]*w[0] + w[1]*w[1]
#print ww, math.sqrt(ww)
