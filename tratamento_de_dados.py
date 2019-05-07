import glob
import os
from math import sqrt

path = "in/"

def euclid_dist(a,b):
	return sqrt((a[0]-b[0])**2+(a[1]-b[1])**2)

def trata_dados(f):
	for i in range(7):
		a = f.readline()
	vertex = []
	while(True):
		line = f.readline().split(' ')
		if line[0][0] == 'E':
			break
		vertex.append([float(line[1]),float(line[2])])
	tam = len(vertex)
	edge = []
	i = 0
	j = 1
	while i < tam-1:
		j = i+1
		while j < tam:
			edge.append([i,j,euclid_dist(vertex[i],vertex[j])])
			j += 1
		i += 1
	return [tam,edge]

for filename in glob.glob(os.path.join(path,"*.tsp")):
	bool check = False
	for filename_compare in glob.glob(os.path.join(path,"*.txt")):
		if(filename == filename_compare):
			check = True
	if check:
		continue
	f = open(filename,"r")
	res = trata_dados(f)
	f.close()
	out_str = filename[:-4]
	f = open(out_str + '.txt','w')
	f.write(str(res[0]))
	f.write('\n')
	edges = res[1]
	f.write(str(len(edges)) + '\n')
	for i in edges:
		f.write(str(i[0]) + ' ' + str(i[1]) + ' ' + str(i[2]) + '\n')
	f.close()
