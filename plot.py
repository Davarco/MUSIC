import pylab as plt
import numpy as np

signal = np.genfromtxt("signal.txt", delimiter=',')
xval = signal[:, 0] 

plt.figure(0)
plt.xlabel("Time (seconds)")
plt.ylabel("Voltage (normalized to -1, 1)")
plt.plot(xval, signal[:, 1], label='Phone 1')
plt.plot(xval, signal[:, 2], label='Phone 2')
plt.plot(xval, signal[:, 3], label='Phone 3')
plt.plot(xval, signal[:, 4], label='Phone 4')
plt.legend(loc='upper left')

doa = np.genfromtxt("doa.txt", delimiter=',')
xval = doa[:, 0]

plt.figure(1)
plt.xlabel("Angle (degrees)")
plt.ylabel("Spatial Spectrum (db)")
plt.plot(xval, doa[:, 1])

plt.show()

"""
plt.figure(1)
plt.plot(xval, signal[:, 1])
plt.figure(2)
plt.plot(xval, signal[:, 2])
plt.figure(3)
plt.plot(xval, signal[:, 3])
plt.figure(4)
plt.plot(xval, signal[:, 4])
plt.show()
"""
