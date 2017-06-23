#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, ln1, ln2, ln3, ln4, ln5, ln6 = np.loadtxt('LAMBDAS.dat', usecols=(0, 1, 4, 7, 10, 13, 16), unpack=True)

lx1, lx2, lx3, lx4, lx5, lx6 = np.loadtxt('LAMBDAS.dat', usecols=(3, 6, 9, 12, 15, 18), unpack=True)

lz1, lz2, lz3, lz4, lz5, lz6 = np.loadtxt('LAMBDAS.dat', usecols=(2, 5, 8, 11, 14, 17), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.tick_params(labelcolor='none', top='off', bottom='off', left='off', right='off')

ax1 = fig.add_subplot(311, autoscale_on=False, xlim=(1,40), ylim=(0.1,0.0))

ax1.plot(t, ln1, label='1')
ax1.plot(t, ln2, label='2')
ax1.plot(t, ln3, label='3')
ax1.plot(t, ln4, label='4')
ax1.plot(t, ln5, label='5')
ax1.plot(t, ln6, label='6')

ax1.set_ylabel(r'$\lambda_{z}$ $[Ns]$')

ax1.xaxis.set_ticklabels([])

ax1.grid()

seq = [7, 4, 3, 4]

ax1.axvline(x=10, color='black', dashes=seq)

ax2 = fig.add_subplot(312, autoscale_on=False, xlim=(1,40), ylim=(-0.025,0.025))

ax2.plot(t, lz1, label='1')
ax2.plot(t, lz2, label='2')
ax2.plot(t, lz3, label='3')
ax2.plot(t, lz4, label='4')
ax2.plot(t, lz5, label='5')
ax2.plot(t, lz6, label='6')

ax2.set_ylabel(r'$\lambda_{x}$ $[Ns]$')

ax2.xaxis.set_ticklabels([])

ax2.grid()

seq = [7, 4, 3, 4]

ax2.axvline(x=10, color='black', dashes=seq)

ax3 = fig.add_subplot(313, autoscale_on=False, xlim=(1,40), ylim=(-0.01,0.01))

ax3.plot(t, lx1, label='1')
ax3.plot(t, lx2, label='2')
ax3.plot(t, lx3, label='3')
ax3.plot(t, lx4, label='4')
ax3.plot(t, lx5, label='5')
ax3.plot(t, lx6, label='6')

ax3.set_ylabel(r'$\lambda_{y}$ $[Ns]$')

#for setting time in the big common subplot
ax.set_xlabel(r'$T [s]$')

ax3.grid()

seq = [7, 4, 3, 4]

ax3.axvline(x=10, color='black', dashes=seq)

fig.tight_layout()

plt.show()

