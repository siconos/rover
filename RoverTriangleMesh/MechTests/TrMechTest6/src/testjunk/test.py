#! /usr/bin/env python

# run the code as ./test.py sample.txt from the current directory
# in the current directory there should be a sample.txt file
# with the coords of points in the cloud.
# output file isn't written until the plot window is closed 

import matplotlib.delaunay as triang
import pylab
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

        for line in f: 
                       
            intList = [float(i) for i in line.split()]

            # list of three-element lists with coords

            outMat.append(intList);

        f.close()

        # triangulation

        x = []
        z = []

        for i in outMat:

            x.append(i[0])
            z.append(i[2])

        x = numpy.array(x)    
        z = numpy.array(z)

        cens,edg,tri,neig = triang.delaunay(x,z)

        ind = []

        for t in tri:
        # t[0], t[1], t[2] are the points indexes of the triangle
        # each triangle is composed of four ref. points 0, 1, 2, 0 (we start at 0 
        # and go around until in 0 again)
    
            t_i = [t[0], t[1], t[2], t[0]]

            ind.append(t_i[0:3])
            
            # we access the x and y coords of each point in a triangle and plot them
            
            pylab.plot(x[t_i],z[t_i])
            
        pylab.plot(x,z,'o')
        pylab.show()

        # output VRML file writing - first the coords, then the vertices indices
        # file format should be changed with accordance to the rendering engine

        fout = open('output.wrl', 'w+')

        # output file for SICONOS writing - only coords of vertices

        foutSIC = open('SICout.txt', 'w+')

        fout.write('#VRML V2.0 utf8 \n \n')
        fout.write('Shape { \n')
        fout.write('\t appearance Appearance { \n\n')
        fout.write('\t\t material Material { \n\n')
        fout.write('\t\t\t diffuseColor 0.0 1.0 0.498 \n\n')
        fout.write('\t\t } \n\n')
        fout.write('\t } \n\n')
        fout.write('\t geometry IndexedFaceSet { \n\n')
        fout.write('\t\t solid FALSE  \n\n')
        fout.write('\t\t coord Coordinate { \n')
        fout.write('\t\t point [ \n')
        
        for j in outMat:

            j = str(j)
            j = j.replace(j[0], '')
            j = j.replace(j[-1], '')
            j = j.replace(', ', ' ')
            j = j + '\n'
            foutSIC.write(j)
            fout.write('\t\t\t' + j)

        fout.write('\t\t    ] \n')
        fout.write('\t\t } \n\n')
        fout.write('\t\t coordIndex [ \n')

        for j in ind:

            j = str(j)
            j = j.replace(j[0], '')
            j = j.replace(j[-1], '')
            j = j.replace(', ', ' ')
            j = j + ' -1' + '\n'
            fout.write('\t\t\t' + j)

        fout.write('\t\t    ] \n\n')
        fout.write('\t } \n') 
        fout.write('} \n')

        fout.close()
        foutSIC.close()

        script_dir = os.path.dirname(os.path.abspath(__file__))

        print script_dir
        
        print """

        VRML output file written --> output.wrl
        SICONOS output file written --> SICout.txt

        """

    else:

        print "No such file"

except IndexError:

    print "No file specified"

 
