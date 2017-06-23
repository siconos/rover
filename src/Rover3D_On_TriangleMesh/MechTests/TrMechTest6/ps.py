#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#com
#t, x, y, z = np.loadtxt('PVALUE.dat', usecols=(0, 1, 2, 3), unpack=True)

#wheels
t, w1, w2, w3, w4, w5, w6 = np.loadtxt('PVALUE.dat', usecols=(0, 10, 11, 15, 16, 20, 21), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

#ax.annotate('impact', xy=(0.99, 9),  xycoords='data',
#            xytext=(50, 30), textcoords='offset points',
#            arrowprops=dict(arrowstyle="->")
#            )

#wheels
ax.plot(t, w1, label='wheel FL')
ax.plot(t, w2, label='wheel FR')
ax.plot(t, w3, label='wheel ML')
ax.plot(t, w4, label='wheel BL')
ax.plot(t, w5, label='wheel MR')
ax.plot(t, w6, label='wheel BR')

plt.title(r'$R_{wheels}$ $Forces$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$R_{wheels}$ $Forces$ $[N]$')

ax.set_xlim([0, 150])

#ax.plot(t, x, label='x')
#ax.plot(t, y, label='y')
#ax.plot(t, z, label='z')

#plt.title(r'$R_{COM}$ $Forces$')
#plt.xlabel(r'$T [s]$')
#plt.ylabel(r'$R_{COM}$ $Forces$ $[N]$')

plt.legend(loc='lower right')

seq = [7, 4, 3, 4]
plt.axvline(x=10, color='black', dashes=seq)

plt.gca().yaxis.get_major_formatter().set_powerlimits((-1,1))

plt.show()
