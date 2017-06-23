#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, y1, y2, y3, y4, y5, y6 = np.loadtxt('Y.dat', usecols=(0, 1, 4, 7, 10, 13, 16), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, y1, label='Wheel FL')
ax.plot(t, y2, label='Wheel FR')
ax.plot(t, y3, label='Wheel ML')
ax.plot(t, y4, label='Wheel BL')
ax.plot(t, y5, label='Wheel MR')
ax.plot(t, y6, label='Wheel BR')

ax.set_xlim([0, 400])

plt.title(r'$\\y_{N}$ $for$ $each$ $wheel$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$\\y_{N}$ $[m]$')

plt.legend(loc='lower left')

seq = [7, 4, 3, 4]

plt.axvline(x=50, color='black', dashes=seq)
plt.axvline(x=100, color='black', dashes=seq)
plt.axvline(x=150, color='black', dashes=seq)
plt.axvline(x=220, color='black', dashes=seq)
plt.axvline(x=300, color='black', dashes=seq)

plt.gca().yaxis.get_major_formatter().set_powerlimits((-1,1))

plt.show()
