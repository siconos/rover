#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#mass center
#t, x, y, z = np.loadtxt('PVALUE.dat', usecols=(0, 1, 2, 3), unpack=True)

#wheels
t, w1, w2, w3, w4, w5, w6 = np.loadtxt('PVALUE.dat', usecols=(0, 10, 11, 15, 16, 20, 21), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

#mass center
#ax.plot(t, x, label='x')
#ax.plot(t, y, label='y')
#ax.plot(t, z, label='z')

#plt.title(r'$R_{COM}$')
#plt.xlabel(r'$T [s]$')
#plt.ylabel(r'$R_{COM}$')

#wheels
ax.plot(t, w1, label='wheel FL')
ax.plot(t, w2, label='wheel FR')
ax.plot(t, w3, label='wheel ML')
ax.plot(t, w4, label='wheel BL')
ax.plot(t, w5, label='wheel MR')
ax.plot(t, w6, label='wheel BR')

plt.title(r'$R_{wheels}$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$R_{wheels}$')

plt.legend(loc='lower left')

#seq = [7, 4, 3, 4]

#plt.axvline(x=119.965, color='black', dashes=seq)
#plt.axvline(x=200, color='black', dashes=seq)

plt.show()

