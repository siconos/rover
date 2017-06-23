#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

t, l1 = np.loadtxt('LAMBDAS.dat', usecols=(0, 3), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111)

ax.plot(t, l1, label='Wheel FL')

plt.legend(loc='upper right')

seq = [7, 4, 3, 4]

plt.axvline(x=119.965, color='black', dashes=seq)
plt.axvline(x=200, color='black', dashes=seq)

plt.show()

