#flow based RWA
from pulp import *
N=[1,2,3,4,5] #5 Nodes
W=[1,2] #2 Wavelenghts
S=[(1,3),(2,4),(3,1),(3,5),(4,2),(4,5),(5,3),(5,4)]
L=[(1,2),(2,3),(3,4),(4,5),(5,1),(1,4),(2,4),\
(1,5),(5,4),(4,3),(3,2),(2,1),(4,1),(4,2)] #bidirectional ring
a={} #unit link cost
for l in L:
	a[l]=1
F={} #1 fiber per link
for l in L:
	F[l]=1
t={} #1 lightpath for each s-d pair
for s in S:
	t[s]=1
P={}
P[((1,3),1)]=[(1,2),(2,3)]
P[((1,3),2)]=[(1,4),(4,3)]
P[((2,4),1)]=[(2,4)]
P[((2,4),2)]=[(2,1),(1,4)]
P[((3,1),1)]=[(3,2),(2,1)]
P[((3,1),2)]=[(3,4),(4,1)]
P[((3,5),1)]=[(3,4),(4,5)]
P[((3,5),2)]=[(3,2),(2,1),(1,5)]
P[((4,2),1)]=[(4,2)]
P[((4,2),2)]=[(4,3),(3,2)]
P[((4,5),1)]=[(4,5)]
P[((4,5),2)]=[(4,1),(1,5)]
P[((5,3),1)]=[(5,4),(4,3)]
P[((5,3),2)]=[(5,1),(1,2),(2,3)]
P[((5,4),1)]=[(5,4)]
P[((5,4),2)]=[(5,1),(1,4)]

prob=LpProblem('flow based RWA',LpMinimize)
f=LpVariable.dicts('f',(P,W),0,None,LpInteger)
#objectives
prob += lpSum(a[l]*f[p][w] for l in L for w in W for p in P if P[p].count(l)>0)
#constraints
for l in L:
 for w in W:
  prob += lpSum(f[p][w] for p in P if P[p].count(l)>0) <= F[l]
for s in S:
  prob += lpSum(f[p][w] for w in W for p in P if p[0]==s) == t[s]
prob.writeLP('Flow based_RWA.lp')
prob.solve(GLPK())
print 'Status:',LpStatus[prob.status]
print 'Optimal cost:',value(prob.objective)
for p in P:
 for w in W:
   if value(f[p][w])>0:
      print 'f',p,w,':',value(f[p][w])



