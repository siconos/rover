#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#plane relation
#t, l1, l2, l3, l4, l5, l6 = np.loadtxt('LAMBDAS.dat', usecols=(0, 2, 5, 8, 11, 14, 17), unpack=True)

#sphere relation
t, l1, l2, l3, l4, l5, l6 = np.loadtxt('LAMBDAS.dat', usecols=(0, 20, 23, 26, 29, 32, 35), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, l1, label='Wheel FL')
ax.plot(t, l2, label='Wheel FR')
ax.plot(t, l3, label='Wheel ML')
ax.plot(t, l4, label='Wheel BL')
ax.plot(t, l5, label='Wheel MR')
ax.plot(t, l6, label='Wheel BR')

#for plane
#ax.set_xlim([10, 150])
#ax.set_ylim([-1, 1.7])

#for sphere
ax.set_xlim([52, 62])
#ax.set_ylim([-1, 7])

plt.title(r'$\lambda_{T_x}$ $for$ $each$ $wheel$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$\lambda_{T_x}$ $[\frac{N}{s}]$')

plt.legend(loc='lower right')

seq = [7, 4, 3, 4]
plt.axvline(x=10, color='black', dashes=seq)

plt.gca().yaxis.get_major_formatter().set_powerlimits((-1,1))

plt.show()

