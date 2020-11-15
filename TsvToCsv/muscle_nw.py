import pandas as pd
import numpy as np
import os
import sys
import matplotlib.pyplot as plt
import copy

Afp = 0.07665082 #[N/palse]
M   = 10000      #[-]モータ分解能
dt  = 0.02       #[s]制御周期 50 [Hz]
r   = 0.015      #[m]プーリ半径
D   = 0.03       #[m]プーリ直径
g   = 9.81       #[m/s**2]重力加速度

def DiffList(lst1, lst2):
    i = 0
    lst = []
    for em in lst1:
        lst.append(em - lst2[i])
        i += 1
    return lst


# ALL = ["time", "glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "sar_r", "add_mag2_r", "tfl_r", "pect_r", "grac_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "quad_fem_r", "gem_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]
# ALL = ["time", "glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]
ALL = ["time", "glut_med2_r", "glut_max2_r", "iliacus_r", "rect_fem_r", "vas_int_r", "med_gas_r", "tib_ant_r"]
# ALL = ["glut_med2_l","bifemlh_l","add_long_l","glut_max2_l","iliacus_l","rect_fem_l","vas_int_l","med_gas_l","tib_ant_l"]

args = sys.argv
IFILE = str(args[1])

# サンプリングデータの読み込み
# lst = pd.read_table(IFILE, header=22)
# lst = pd.read_table(IFILE)

diffLst = []
i = 0
for label in ALL:
    ''' データの読み込み '''
    lst = pd.read_table(IFILE, header=22)
    # lst = pd.read_table(IFILE, header=0)
    lst = lst[[label]].values.tolist() # nan削除と数値化
    lst = [x[0] for x in lst] # numpy.ndarrayからlistに変換

    # lstより1フレーム進めたリスト
    _lst = copy.copy(lst)
    # _lst.pop(0)
    del _lst[:2]
    _lst.append(_lst[len(_lst) -1])





    # lstの差分を求める(⊿F [N]を求める)
    dF = DiffList(_lst, lst)

    # 最小二乗法で求めたAfpを元に, [N]の変化時に必要な回転数を求める
    w_state = [(2*np.pi*((df/Afp)/M))/dt for df in dF]

    # イナーシャを求める
    I_state = [(f*D)/(4*g) for f in lst]

    # 加速トルクを求める
    Tacc = []
    for i in range(len(lst) -1):
        Tacc.append((I_state[i]*2*np.pi*w_state[i])/(60))

    # 把持トルク?を求める
    T = [f*r for f in lst]

    diffLst.append(max(dF))
    print(label, ",", diffLst[i])
    print('[Nm],', diffLst[i]*r)
    print('[rpm],', max(w))
    print('max[Nm],', max(lst)*r)
    i += 1

print("最大の差分は,", max(diffLst))