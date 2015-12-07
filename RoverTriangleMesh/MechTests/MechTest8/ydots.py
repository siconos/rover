#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#y component
t, y1, y2, y3, y4 = np.loadtxt('YDOTS.dat', usecols=(0, 1, 4, 7, 10), unpack=True)

#x component
#t, y1, y2, y3, y4 = np.loadtxt('YDOTS.dat', usecols=(0, 2, 5, 8, 11), unpack=True)

#z component
#t, y1, y2, y3, y4 = np.loadtxt('YDOTS.dat', usecols=(0, 3, 6, 9, 12), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, y1, label='plane 1')
ax.plot(t, y2, label='plane 2')
ax.plot(t, y3, label='plane 3')
ax.plot(t, y4, label='plane 4')

#ax.set_xlim([0, 250])

#y component
plt.title(r'$\dot{y}_{N}$ $for$ $each$ $wheel$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$\dot{y}_{N}$ $[\frac{m}{s}]$')
plt.legend(loc='lower right')

#x component
#plt.title(r'$\dot{y}_{T_x}$ $for$ $each$ $wheel$')
#plt.xlabel(r'$T [s]$')
#plt.ylabel(r'$\dot{y}_{T_x}$ $[\frac{m}{s}]$')
#plt.legend(loc='lower right')

#z component
#plt.title(r'$\dot{y}_{T_z}$ $for$ $each$ $wheel$')
#plt.xlabel(r'$T [s]$')
#plt.ylabel(r'$\dot{y}_{T_z}$ $[\frac{m}{s}]$')
#plt.legend(loc='upper right')

seq = [7, 4, 3, 4]

plt.axvline(x=119.965, color='black', dashes=seq)
plt.axvline(x=200, color='black', dashes=seq)

plt.show()
