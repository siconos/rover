#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, l1, l2, l3, l4, l5, l6 = np.loadtxt('LAMBDAS.dat', usecols=(0, 1, 4, 7, 10, 13, 16), unpack=True)

fig = plt.figure(1)

#ax = fig.add_subplot(111, autoscale_on=False, xlim=(5,100), ylim=(0.1,0.3))
ax = fig.add_subplot(111)

ax.annotate('impact', xy=(0.96, 1.6),  xycoords='data',
            xytext=(50, 30), textcoords='offset points',
            arrowprops=dict(arrowstyle="->")
            )

ax.plot(t, l1, label='Wheel FL')
ax.plot(t, l2, label='Wheel FR')
ax.plot(t, l3, label='Wheel ML')
ax.plot(t, l4, label='Wheel BL')
ax.plot(t, l5, label='Wheel MR')
ax.plot(t, l6, label='Wheel BR')

#ax.set_xlim([0, 5])
#ax.set_ylim([-0.2, 50])

#ax.set_xlim([0.8, 1.3])
#ax.set_ylim([-0.2, 50])

plt.title(r'$\lambda_{N}$ $for$ $each$ $wheel$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$\lambda_{N}$ $[Ns]$')

plt.legend(loc='upper right')

plt.show()

