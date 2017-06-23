#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, l1, l2, l3, l4 = np.loadtxt('LAMBDAS.dat', usecols=(0, 1, 4, 7, 10), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, l1, label='plane 1')
ax.plot(t, l2, label='plane 2')
ax.plot(t, l3, label='plane 3')
ax.plot(t, l4, label='plane 4')

#ax.set_xlim([0, 10])

plt.title(r'$\lambda_{N}$ $for$ $each$ $wheel$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$\lambda_{N}$ $[N]$')

plt.legend(loc='upper right')

seq = [7, 4, 3, 4]

plt.axvline(x=119.965, color='black', dashes=seq)
plt.axvline(x=200, color='black', dashes=seq)

plt.show()

