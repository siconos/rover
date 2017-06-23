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

ax1 = fig.add_subplot(311, autoscale_on=False, xlim=(1,22), ylim=(0,7))

ax1.plot(t, x, label='x')
ax1.plot(t, y, label='y')
ax1.plot(t, z, label='z')

ax1.set_ylabel(r'$x_{COM}$ $coordinates$ $[m]$')

ax1.xaxis.set_ticklabels([])

ax1.grid()

seq = [7, 4, 3, 4]

ax1.axvline(x=10, color='black', dashes=seq)

ax2 = fig.add_subplot(312, autoscale_on=False, xlim=(1,22), ylim=(-0.9,0.4))

ax2.plot(t, vx, label='x')
ax2.plot(t, vy, label='y')
ax2.plot(t, vz, label='z')

ax2.set_ylabel(r'$x_{COM}$ $velocity$ $[\frac{m}{s}$]')

ax2.xaxis.set_ticklabels([])

ax2.grid()

seq = [7, 4, 3, 4]

ax2.axvline(x=10, color='black', dashes=seq)

ax3 = fig.add_subplot(313, autoscale_on=False, xlim=(1,22), ylim=(-4,23))

ax3.plot(t, px, label='x')
ax3.plot(t, py, label='y')
ax3.plot(t, pz, label='z')

ax3.set_ylabel(r'$R_{COM}$ $[Ns]$')

#for setting time in the big common subplot
ax.set_xlabel(r'$T [s]$')

ax3.grid()

seq = [7, 4, 3, 4]

ax3.axvline(x=10, color='black', dashes=seq)

fig.tight_layout()

plt.show()

