"""Utilities to post-process Rover simulations outputs
"""
import shutil
import os
import scitools.filetable as ft
import matplotlib.pyplot as plt


ref_files_path = os.path.join('..', 'wrl_files')
rover_model = os.path.join(ref_files_path, 'RoverModel.wrl')
rover_anim = os.path.join(ref_files_path, 'RoverAnimation.wrl')


def build_complete_vrml(datafile, resultfile):
    """Concatenate RoverModel, Animation and datafile into resultfile.
    """
    assert datafile is not resultfile
    filelist = [rover_model, datafile, rover_anim]
    with open(resultfile, 'wb') as outfile:
        for filename in filelist:
            with open(filename, 'rb') as readfile:
                shutil.copyfileobj(readfile, outfile)



def plot_rover(filename):

    s = open(filename)
    table = ft.read(s)
    time = table[:, 0]
    q = table[:, 1:22]
    velo = table[:, 22:25]
    y = table[:, 25:31]
    lamb = table[:, 31]

    plt.subplot(2, 1, 1)
    plt.plot(time, q[:, 0:3], 'o-')
    plt.subplot(2, 1, 2)
    plt.plot(time, y[:, 0:3], 'o-')
    plt.show()



# RoverPlane simu
build_complete_vrml('data.wrl', 'run.wrl')
plot_rover('RoverPlane.dat')

