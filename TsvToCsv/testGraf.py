# References: 
# https://matplotlib.org/gallery/lines_bars_and_markers/markevery_demo.html#sphx-glr-gallery-lines-bars-and-markers-markevery-demo-py

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

import pandas as pd
import os
import sys

# define a list of markevery cases to plot
# cases = [None,
#          8,
#          (30, 8),
#          [16, 24, 30], [0, -1],
#          slice(100, 200, 3),
#          0.1, 0.3, 1.5,
#          (0.0, 0.1), (0.45, 0.1)]

H = ["time", "glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "sar_r", "add_mag2_r", "tfl_r", "pect_r", "grac_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "quad_fem_r", "gem_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]
h = ["time", "glut_med2_r", "add_mag2_r", "glut_max2_r", "iliacus_r", "rect_fem_r", "vas_int_r", "med_gas_r", "tib_ant_r"]
# H = ["time", "glut_med2_r", "add_mag2_r", "glut_max2_r", "iliacus_r", "rect_fem_r", "vas_int_r", "med_gas_r", "tib_ant_r"]

# define the figure size and grid layout properties
# figsize = (12, 5)
figsize = (12, 10)
cols = 4
rows = len(H) // cols + 1
# rows = 2


def trim_axs(axs, N):
    """
    Reduce *axs* to *N* Axes. All further Axes are removed from the figure.
    """
    axs = axs.flat
    for ax in axs[N:]:
        ax.remove()
    return axs[:N]


args = sys.argv
IFILE = str(args[1])
HEADER = 22

# tsv = pd.read_table(IFILE, header=22, usecols=range(9))
tsv = pd.read_table(IFILE, header=HEADER, usecols=H)
df = pd.DataFrame(tsv)
a_df = df.T.values

fig1, axs = plt.subplots(rows, cols, figsize=figsize, constrained_layout=True)
axs = trim_axs(axs, len(H))
i = 1
# for ax, case in zip(axs, cases):
#     ax.set_title('%s' % H[i])
#     # ax.plot(x, y, 'o', ls='-', ms=4, markevery=case)
#     ax.plot(a_df[0], a_df[i], 'o', ls='-', ms=4, markevery=case, color="orange")
#     if(i < 8):
#         i += 1
for ax in axs:
    ax.set_title('%s' % H[i])
    # if(H[i] in h):
    #     ax.set_title('%s' % H[i], color="tomato")
    # else:
    #     ax.set_title('%s' % H[i])

    # ax.plot(x, y, 'o', ls='-', ms=4, markevery=case)
    # ax.plot(a_df[0], a_df[i], ls='-', color="orchid")
    if(H[i] in h):
        ax.plot(a_df[0], a_df[i], ls='-', color="orchid")
    else:
        ax.plot(a_df[0], a_df[i], ls='-', color="orange")

    i += 1
    if(i > len(H)-1):
        break

plt.savefig(IFILE + '.png')
plt.close('all')