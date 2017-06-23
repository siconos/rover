#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#wheel's q
t, x = np.loadtxt('POSITION.dat', usecols=(0, 8), unpack=True)

#mass center q
#t, x, y, z = np.loadtxt('POSITION.dat', usecols=(0, 1, 2, 3), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

#wheel's q
ax.plot(t, x, label='x')
#ax.plot(t, y, label='y')
#ax.plot(t, z, label='z')

plt.title(r'$x_{FL}$ $displacement$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$x_{FL}$ $displacement$ $[rad]$')

plt.annotate('torque turn-on', xy=(50, 0), xytext=(40, 3),
            arrowprops=dict(facecolor='blue', shrink=0.05),
            )

#mass center q
#ax.plot(t, x, label='x')
#ax.plot(t, y, label='y')
#ax.plot(t, z, label='z')

#plt.title(r'$x_{COM}$ $displacement$')
#plt.xlabel(r'$T [s]$')
#plt.ylabel(r'$x_{COM}$ $displacement$ $[m]$')

plt.legend(loc='upper left')

plt.show()

