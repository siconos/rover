#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#x component
t, yx1, yx2, yx3, yx4, yx5, yx6 = np.loadtxt('YDOTS.dat', usecols=(0, 2, 5, 8, 11, 14, 17), unpack=True)

#z component
yy1, yy2, yy3, yy4, yy5, yy6 = np.loadtxt('YDOTS.dat', usecols=(3, 6, 9, 12, 15, 18), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.tick_params(labelcolor='none', top='off', bottom='off', left='off', right='off')

ax1 = fig.add_subplot(211, autoscale_on=False, xlim=(1,40), ylim=(-0.01,0.01))

ax1.plot(t, yy1, label='1')
ax1.plot(t, yy2, label='2')
ax1.plot(t, yy3, label='3')
ax1.plot(t, yy4, label='4')
ax1.plot(t, yy5, label='5')
ax1.plot(t, yy6, label='6')

ax1.set_ylabel(r'$\dot{y}_{x}$ $[\frac{m}{s}]$')

ax1.xaxis.set_ticklabels([])

seq = [7, 4, 3, 4]

ax1.axvline(x=10, color='black', dashes=seq)

ax1.grid()

ax2 = fig.add_subplot(212, autoscale_on=False, xlim=(1,40), ylim=(-0.01,0.01))

ax2.plot(t, yx1, label='1')
ax2.plot(t, yx2, label='2')
ax2.plot(t, yx3, label='3')
ax2.plot(t, yx4, label='4')
ax2.plot(t, yx5, label='5')
ax2.plot(t, yx6, label='6')

ax2.set_ylabel(r'$\dot{y}_{y}$ $[\frac{m}{s}]$')

seq = [7, 4, 3, 4]

ax2.axvline(x=10, color='black', dashes=seq)

ax2.grid()

ax.set_xlabel(r'$T [s]$')

fig.tight_layout()

plt.show()

