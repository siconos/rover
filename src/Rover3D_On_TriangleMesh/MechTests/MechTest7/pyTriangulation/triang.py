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

        outMatr = []
        ind = []
        
        for t in tri:
        # t[0], t[1], t[2] are the points indexes of the triangle
        # each triangle is composed of four ref. points 0, 1, 2, 0 (we start at 0 
        # and go around until in 0 again)
    
            t_i = [t[0], t[1], t[2], t[0]]

            ind.append(t_i[0:3])
            
            # laying out the list with triangles coords

            outMatr.append(outMat[t[0]] + outMat[t[1]] + outMat[t[2]])

            # we access the x and z coords of each point in a triangle and plot them
           
            pylab.plot(x[t_i],z[t_i])
            
        pylab.plot(x,z,'o')
        pylab.show()

        # output VRML file writing - first the coords, then the vertices indices
        # file format should be changed with accordance to the rendering engine

        # writing outside of the current dir

        script_dir = os.path.dirname(os.path.abspath(__file__))
        script_dir = os.path.split(script_dir)
        file_out_dir = script_dir[0]

        file_name1 = file_out_dir + '/output.wrl'
        file_name2 = file_out_dir + '/SICout.txt'

        fout = open(file_name1, 'w+')

        # output file for SICONOS writing - only coords of vertices

        foutSIC = open(file_name2, 'w+')
        
        count = len(outMatr)    

        count = str(count)
        
        foutSIC.write(count + '\n')

        for j in outMatr:

            j = str(j)
            j = j.replace(j[0], '')
            j = j.replace(j[-1], '')
            j = j.replace(', ', ' ')
            j = j + ',' + '\n'
            foutSIC.write(j)

        # output file for VRML writing    

        #texture by material -> appearance Appearance {material diffusecolor[ 0 0 0.6]}    

        fout.write('#VRML V2.0 utf8 \n \n')
        fout.write('Shape { \n')
    
        #fout.write('\t appearance Appearance { \n\n')
        #fout.write('\t\t material Material { \n\n')
        #fout.write('\t\t diffuseColor 0.0 1.0 0.498 \n\n')
       
        fout.write('\t appearance DEF theTexture Appearance { \n\n')
        fout.write('\t\t texture ImageTexture { \n\n')
        fout.write('\t\t\t url [\"texture.png\"] \n\n')
       
        fout.write('\t\t } \n\n')
        fout.write('\t } \n\n')
        fout.write('\t geometry IndexedFaceSet { \n\n')
        fout.write('\t\t solid FALSE  \n\n')
        fout.write('\t\t coord Coordinate { \n')
        fout.write('\t\t point [ \n')
        
        for j in outMat:

            # divide by 100 to fit into VRML scale
            j[:] = [i/100 for i in j]
            # we swap elements x and z and change signs - for VRML
            j[0], j[2] = -j[2], -j[0]
            j = str(j)
            j = j.replace(j[0], '')
            j = j.replace(j[-1], '')
            j = j.replace(', ', ' ')
            j = j + '\n'
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


        print """

VRML output file written --> ../output.wrl
SICONOS output file written --> ../SICout.txt

        """

    else:

        print "No such file"

except IndexError:

    print "No file specified"

 




