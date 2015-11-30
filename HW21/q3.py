import numpy as np
from sklearn.svm import SVC

x=np.array([(1,0), (0,1), (0,-1), (-1,0), (0,2), (0,-2), (-2,0)])
y=np.array([-1,-1,-1,1,1,1,1])

clf = SVC(C=1e10, kernel='poly', degree=2, gamma=1, coef0=1)
clf.fit(x,y)
print clf.support_
print clf.support_vectors_
print clf.dual_coef_
print sum(clf.dual_coef_[0])

print clf.decision_function(x)
