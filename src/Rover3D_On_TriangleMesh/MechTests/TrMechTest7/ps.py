#! /usr/bin/env python

# plotting rover q generalized coordinates.

import matplotlib
matplotlib.use('Qt4Agg')

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rc, rcParams

rc('text', usetex=True)

#wheels
t, w1, w2, w3, w4, w5, w6 = np.loadtxt('PVALUE.dat', usecols=(0, 10, 11, 15, 16, 20, 21), unpack=True)

fig = plt.figure(1)

ax = fig.add_subplot(111, autoscale_on=False, xlim=(0,200), ylim=(-10e-7,10e-7))

#wheels
ax.plot(t, w1, label='wheel FL')
ax.plot(t, w2, label='wheel FR')
ax.plot(t, w3, label='wheel ML')
ax.plot(t, w4, label='wheel BL')
ax.plot(t, w5, label='wheel MR')
ax.plot(t, w6, label='wheel BR')

plt.title(r'$R_{wheels}$ $Forces$')
plt.xlabel(r'$T [s]$')
plt.ylabel(r'$R_{wheels}$ $Forces$ $[N]$')

plt.gca().yaxis.get_major_formatter().set_powerlimits((-1,1))

plt.grid()

seq = [7, 4, 3, 4]

plt.axvline(x=20, color='black', dashes=seq)
plt.axvline(x=40, color='black', dashes=seq)
plt.axvline(x=80, color='black', dashes=seq)
plt.axvline(x=105.15, color='black', dashes=seq)
plt.axvline(x=150, color='black', dashes=seq)

plt.show()

