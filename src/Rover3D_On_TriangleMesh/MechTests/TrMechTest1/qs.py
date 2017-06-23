#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#com
t, x, y, z = np.loadtxt('POSITION.dat', usecols=(0, 1, 2, 3), unpack=True)

#com velocity
t, vx, vy, vz = np.loadtxt('VELOCITY.dat', usecols=(0, 1, 2, 3), unpack=True)

#com reactions
t, px, py, pz = np.loadtxt('PVALUE.dat', usecols=(0, 1, 2, 3), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.tick_params(labelcolor='none', top='off', bottom='off', left='off', right='off')

ax1 = fig.add_subplot(311, autoscale_on=False, xlim=(0,2), ylim=(0,6))

ax1.annotate('impact', xy=(0.92, 0.609),  xycoords='data',
            xytext=(50, 30), textcoords='offset points',
            arrowprops=dict(arrowstyle="->")
            )

ax1.plot(t, x, label='x')
ax1.plot(t, y, label='y')
ax1.plot(t, z, label='z')

ax1.set_ylabel(r'$x_{COM}$ $coordinates$ $[m]$')

ax1.xaxis.set_ticklabels([])

ax1.grid()

ax2 = fig.add_subplot(312, autoscale_on=False, xlim=(0,2), ylim=(-4,1))

ax2.plot(t, vx, label='x')
ax2.plot(t, vy, label='y')
ax2.plot(t, vz, label='z')

ax2.set_ylabel(r'$x_{COM}$ $velocity$ $[\frac{m}{s}$]')

ax2.xaxis.set_ticklabels([])

ax2.grid()

ax3 = fig.add_subplot(313, autoscale_on=False, xlim=(0,2), ylim=(-5,233))

ax3.plot(t, px, label='x')
ax3.plot(t, py, label='y')
ax3.plot(t, pz, label='z')

ax3.set_ylabel(r'$R_{COM}$ $[Ns]$')

#for setting time in the big common subplot
ax.set_xlabel(r'$T [s]$')

ax3.grid()

plt.legend(loc='center right')

fig.tight_layout()

plt.show()

