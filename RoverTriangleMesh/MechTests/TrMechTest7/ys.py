#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#z component
t, y1, y2, y3, y4, y5, y6 = np.loadtxt('Y.dat', usecols=(0, 1, 4, 7, 10, 13, 16), unpack=True)

#y component
yd1, yd2, yd3, yd4, yd5, yd6 = np.loadtxt('YDOTS.dat', usecols=(1, 4, 7, 10, 13, 16), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.tick_params(labelcolor='none', top='off', bottom='off', left='off', right='off')

ax1 = fig.add_subplot(211, autoscale_on=False, xlim=(0,40), ylim=(-2,4))

ax1.annotate('impact', xy=(0.88, 0.23),  xycoords='data',
            xytext=(50, 30), textcoords='offset points',
            arrowprops=dict(arrowstyle="->")
            )

ax1.plot(t, y1, label='1')
ax1.plot(t, y2, label='2')
ax1.plot(t, y3, label='3')
ax1.plot(t, y4, label='4')
ax1.plot(t, y5, label='5')
ax1.plot(t, y6, label='6')

ax1.set_ylabel(r'$y_{z}$ $[m]$')

ax1.xaxis.set_ticklabels([])

ax1.grid()

ax2 = fig.add_subplot(212, autoscale_on=False, xlim=(0,40), ylim=(-4,1))

ax2.plot(t, yd1, label='1')
ax2.plot(t, yd2, label='2')
ax2.plot(t, yd3, label='3')
ax2.plot(t, yd4, label='4')
ax2.plot(t, yd5, label='5')
ax2.plot(t, yd6, label='6')

ax2.set_ylabel(r'$\dot{y}_{z}$ $[\frac{m}{s}]$')

ax2.grid()

ax.set_xlabel(r'$T [s]$')

fig.tight_layout()

plt.show()

