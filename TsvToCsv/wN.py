import pandas as pd
import os
import sys
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np


# inti : matplotlibの文字
mpl.rcParams['font.family'] = 'Hiragino Sans'

ALL = ["time", "glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "sar_r", "add_mag2_r", "tfl_r", "pect_r", "grac_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "quad_fem_r", "gem_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]

KEY = 'add_mag2_r'
R = 0.015

args = sys.argv
# IFILE = str(args[1])
fileF = "_import/2019_ResultsCMC_subject01_walk1_Actuation_force.tsv"
fileW = "_import/subject01_walk1_Actuation_speed.tsv"

# tsv = pd.read_table(IFILE, header=22, usecols=range(9))
lst1 = pd.read_table(fileF, header=22)
# lst1 = lst1[['glut_med2_r']]#.dropna().values.tolist() # nan削除と数値化
lst1 = lst1[[KEY]].values.tolist() # nan削除と数値化
lst1 = [x[0]*R for x in lst1] # numpy.ndarrayからlistに変換

lst2 = pd.read_table(fileW, header=22)
# lst2 = lst2[['glut_med2_r']]#.dropna().values.tolist() # nan削除と数値化
lst2 = lst2[[KEY]].values.tolist() # nan削除と数値化
lst2 = [(x[0])/(2*np.pi*R) *60 for x in lst2] # numpy.ndarrayからlistに変換
# print(lst2.values.tolist())


result = list(zip(lst1, lst2))
# print(result)
result.sort()
# print(result)

lst1, lst2 = zip(*result)

plt.plot(lst1, lst2, "-")
plt.xlabel('[Nm]')
plt.ylabel('[rpm]')
# plt.plot(lst1)
# plt.plot(lst2)
plt.show()

# plt.figure()

# plt.savefig('x.png')
# plt.close('all')