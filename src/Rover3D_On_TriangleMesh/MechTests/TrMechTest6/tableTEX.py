#! /usr/bin/env python

# run the code as ./test.py sample.txt from the current directory
# in the current directory there should be a sample.txt file
# with the coords of points in the cloud.
# output file isn't written until the plot window is closed 

import numpy
import os
import sys

try:

    if os.path.exists(sys.argv[1]):

        try:

            f = open(sys.argv[1], 'r')
        
        except IOError:

            print 'Can\'t open', sys.argv[1]

        outMat = []    

        firstRow = int(sys.argv[2])

        for line in f: 
                       
            intList = [float(i) for i in line.split()]

            # list of three-element lists with coords

            outMat.append(intList);

        f.close()

        #outMat truncation

        outMat[0:firstRow] = []
        
        file_name = 'yourTab.tex'

        fout = open(file_name, 'w+')
        
        #tex file writing

        fout.write('\\begin{tabular}{ l | c | c | c | c | c | r }\n')
       
        for row in outMat:
            
            time = row[0]
            row = row[1::3]
            row.insert(0, time)
            row = str(row)
            row = row.replace(' ', ' & ')                
            row = row.replace(',', ' ')                
            row = row.replace(row[0], '')
            row = row.replace(row[-1], '')                
            row = row + ' \\\\' + '\n'
            fout.write(row)

        fout.write('\\end{tabular}\n')

        fout.close()

except IndexError:

    print "No file specified"

 




