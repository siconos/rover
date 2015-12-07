#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, l1, l2, l3, l4, l5, l6 = np.loadtxt('LAMBDAS.dat', usecols=(0, 3, 6, 9, 12, 15, 18), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, l1, label='Wheel FL')
ax.plot(t, l2, label='Wheel FR')
ax.plot(t, l3, label='Wheel ML')
ax.plot(t, l4, label='Wheel BL')
ax.plot(t, l5, label='Wheel MR')
ax.plot(t, l6, label='Wheel BR')

ax.set_xlim([0.2, 90])

plt.title(r'$\lambda_{T_z}$ $for$ $each$ $wheel$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$\lambda_{T_z}$ $[\frac{N}{s}]$')

plt.legend(loc='center right')

seq = [7, 4, 3, 4]

plt.axvline(x=50, color='black', dashes=seq)

plt.gca().yaxis.get_major_formatter().set_powerlimits((-1,1))

plt.show()

