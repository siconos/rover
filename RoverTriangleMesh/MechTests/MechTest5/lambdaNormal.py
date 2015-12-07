#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#plane
#t, l1, l2, l3, l4, l5, l6 = np.loadtxt('LAMBDAS.dat', usecols=(0, 1, 4, 7, 10, 13, 16), unpack=True)

#sphere
t, y1, y2, y3, y4, y5, y6 = np.loadtxt('LAMBDAS.dat', usecols=(0, 19, 22, 25, 28, 31, 34), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, y1, label='Wheel FL')
ax.plot(t, y2, label='Wheel FR')
ax.plot(t, y3, label='Wheel ML')
ax.plot(t, y4, label='Wheel BL')
ax.plot(t, y5, label='Wheel MR')
ax.plot(t, y6, label='Wheel BR')

plt.title(r'$\lambda_{N}$ $for$ $each$ $wheel$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$\lambda_{N}$ $[Ns]$')

plt.legend(loc='upper right')

plt.show()

