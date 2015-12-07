#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#wheel's qdot
t, x = np.loadtxt('VELOCITY.dat', usecols=(0, 8), unpack=True)

#mass center qdot
#t, x, y, z = np.loadtxt('VELOCITY.dat', usecols=(0, 1, 2, 3), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

#wheel's qdot
ax.plot(t, x, label='x')
#ax.plot(t, y, label='y')
#ax.plot(t, z, label='z')

plt.title(r'$v_{FL}$ $velocity$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$v_{FL}$ $velocity$ $[\frac{rad}{s}]$')

plt.annotate('torque turn-on', xy=(50, 0), xytext=(40, 0.10),
            arrowprops=dict(facecolor='blue', shrink=0.05),
            )

#mass center qdot
#ax.plot(t, x, label='x')
#ax.plot(t, y, label='y')
#ax.plot(t, z, label='z')

#plt.title(r'$v_{COM}$ $velocity$')
#plt.xlabel(r'$T [s]$')
#plt.ylabel(r'$v_{COM}$ $velocity$ $[\frac{m}{s}]$')

plt.legend(loc='upper left')

plt.show()
