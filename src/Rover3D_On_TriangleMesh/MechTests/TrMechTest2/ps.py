#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, x, y, z = np.loadtxt('PVALUE.dat', usecols=(0, 1, 2, 3), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111, autoscale_on=False, xlim=(0,5), ylim=(-5,220))

ax.annotate('impact', xy=(0.99, 9),  xycoords='data',
            xytext=(50, 30), textcoords='offset points',
            arrowprops=dict(arrowstyle="->")
            )

ax.plot(t, x, label='x')
ax.plot(t, y, label='y')
ax.plot(t, z, label='z')

plt.title(r'$R_{COM}$ $Forces$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$R_{COM}$ $Forces$ $[N]$')

plt.legend(loc='upper right')

plt.show()

