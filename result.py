# -*- coding: utf-8 -*-

#this program aims to read a file of page ranks and sort them for plotting the graph

#importting required
import operator

#opening the page rank file
file = "Page_Rank_rg.txt"
with open(file) as f:
	content = f.readlines()

#lines in the file
print(len(content))

#creating a dictionary where key is the node_id and value is the page rank of the node
index = {}

for i in content[:]:
	i = i.split()
	print(i)
	index[i[0]] = float(i[1])
	print(index[i[0]])

for i in range(1,20):
	print(index[str(i)],i)

#sorting based on key values of dictionary
sorted_x = sorted(index.items(), key=operator.itemgetter(1))
#reverse the sorted list (descending)
sorted_x.reverse()

#testing sorted_x
for i in range(20):
	print(sorted_x[(i)],i)

#writing the sorted_x to a file
file_s = "Page_Rank_Sorted_rg.txt"
f = open(file_s,"w")
for i in range(len(sorted_x)):
	f.write(str(sorted_x[i][0]))
	f.write(" ")
	f.write(str(sorted_x[i][1]*100))
	f.write("\n")
f.close()
	
#plotting the graph using matplot and networkx
import networkx as nx
import matplotlib.pyplot as plt

#creating an empty directed graph
G = nx.DiGraph()
content = []
#reading the top n nodes
with open("Page_Rank_Sorted_rg.txt",'r') as f:
	content = f.readlines()

vertices = []
pr = []

for i in content:
	x = i.split(' ')
	x[0] = x[0].strip('\n').strip('\r')
	x[1] = x[1].strip('\n').strip('\r')
	vertices.append(int(x[0]))
	pr.append(float(x[1]))

G.add_nodes_from(vertices[:20])
#reading the edges and adding to graph if both nodes occur in top k page_rank
with open("rg.txt",'r') as g:
	content = g.readlines()
for i in content:
	x = i.split(' ')
	x[0] = x[0].strip('\n').strip('\r')
	x[1] = x[1].strip('\n').strip('\r')
	if(int(x[0]) in vertices[:100] and int(x[1]) in vertices[:100]):
		G.add_edge(int(x[0]), int(x[1]))
#using random layout
pos = nx.random_layout(G)
#plotting with arrows and labels
pr = [pr[node] * 10000 for node in G.nodes()]
nx.draw(G,pos,with_labels=True,arrows=True,node_size = pr)
plt.draw()
#display the plot
plt.show()

"""
import pylab

pylab.figure(1,figsize=(20,20))
pylab.xlim(0,1)
pylab.ylim(0,1)
nx.draw(G,pos,font_size=8)
#nx.draw(G,pos,font_size=10)
pylab.show()

"""
