import pandas as pd
import os
import sys
import matplotlib.pyplot as plt
# subject01_walk1_Actuation_force.tsv
# vas_int_r

ALL = ["time", "glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "sar_r", "add_mag2_r", "tfl_r", "pect_r", "grac_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "quad_fem_r", "gem_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]

args = sys.argv
IFILE = str(args[1])
COL = str(args[2])

# tsv = pd.read_table(IFILE, header=22, usecols=range(9))
tsv = pd.read_table(IFILE, header=22, usecols=ALL)
print(tsv)
df = pd.DataFrame(tsv)
# df.T.to_csv( '_export/'+COL+'.csv', header=False, index=False)
plt.figure()
df.plot()
plt.savefig('x.png')
plt.close('all')