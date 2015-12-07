#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, y1,  y2, y3, y4 = np.loadtxt('Y.dat', usecols=(0, 1, 4, 7, 10), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, y1, label='plane 1')
ax.plot(t, y2, label='plane 2')
ax.plot(t, y3, label='plane 3')
ax.plot(t, y4, label='plane 4')

#ax.set_xlim([0, 250])

plt.title(r'$\\y_{N}$ $for$ $each$ $wheel$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$\\y_{N}$ $[m]$')

plt.legend(loc='center right')

seq = [7, 4, 3, 4]

plt.axvline(x=119.965, color='black', dashes=seq)
plt.axvline(x=200, color='black', dashes=seq)

plt.show()

