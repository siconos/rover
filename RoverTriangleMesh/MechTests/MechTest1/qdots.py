#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, x, y, z = np.loadtxt('VELOCITY.dat', usecols=(0, 1, 2, 3), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, x, label='x')
ax.plot(t, y, label='y')
ax.plot(t, z, label='z')

plt.title(r'$x_{COM}$ $velocity$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$x_{COM}$ $velocity$ $[\frac{m}{s}$]')

plt.legend(loc='center right')

plt.show()

