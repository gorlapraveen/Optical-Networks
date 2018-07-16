#flow based RWA
from pulp import *
N=[1,2,3,4,5,6] #6 Nodes
W=[1,2,3] #3 Wavelenghts
S=[(1,3),(1,6),(2,5),(3,4),(4,1),(5,3),(5,6),(6,2)]
L=[(1,2),(2,3),(3,4),(4,5),(5,1),(3,6),(4,6),(5,6),\
(1,5),(5,4),(4,3),(3,2),(2,1),(6,3),(6,4),(6,5)] #bidirectional ring
P={}
P[((1,3),1)]=[(1,2),(2,3)]
P[((1,6),1)]=[(1,5),(5,6)]
P[((2,5),1)]=[(2,1),(1,5)]
P[((3,4),1)]=[(3,4)]
P[((4,1),1)]=[(4,5),(5,1)]
P[((5,3),1)]=[(5,4),(4,3)]
P[((5,6),1)]=[(5,6)]
P[((6,2),1)]=[(6,3),(3,2)]

a={} #unit link cost
for l in L:
	a[l]=1
F={} #1 fiber per link
for l in L:
	F[l]=1
t={} #1 lightpath for each s-d pair
t[(4,1)]=2
t[(6,2)]=1
t[(1,3)]=2
t[(5,3)]=3
t[(3,4)]=1
t[(2,5)]=2
t[(1,6)]=1
t[(5,6)]=1
prob=LpProblem('RWA_without_dedicated_protection',LpMinimize)
f=LpVariable.dicts('f',(P,W),0,None,LpInteger)
g=LpVariable.dicts('g',(P,W),0,None,LpInteger)
#objectives
prob += lpSum(a[l]*f[p][w] for l in L for w in W for p in P if P[p].count(l)>0)+lpSum(a[l]*g[p][w] for l in L for w in W for p in P) 
#constraints
for l in L:
 for w in W:
  prob += lpSum(f[p][w] for p in P if P[p].count(l)>0) + \
lpSum(g[p][w] for p in P ) <= F[l]
for s in S:
  prob += lpSum(f[p][w] for p in P if p[0]==s for w in W) == t[s]
prob.writeLP('RWA_without_dedicated_protection.lp')
prob.solve(GLPK())
print 'status:',LpStatus[prob.status]
print 'optimal cost:',value(prob.objective)
for p in P:
 for w in W:
  if value(f[p][w])>0:
    print 'f',p,w,':',value(f[p][w])
for p in P:
 for w in W:
   if value(g[p][w])>0:
    print 'g',p,w,':',value(g[p][w])

