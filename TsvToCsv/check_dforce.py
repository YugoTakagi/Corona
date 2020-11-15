import pandas as pd
import os
import sys
import matplotlib.pyplot as plt
import copy


def DiffList(lst1, lst2):
    i = 0
    lst = []
    for em in lst1:
        lst.append(em - lst2[i])
        i += 1
    return lst


# ALL = ["time", "glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "sar_r", "add_mag2_r", "tfl_r", "pect_r", "grac_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "quad_fem_r", "gem_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]
# ALL = ["time", "glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]
ALL = ["glut_med2_l","bifemlh_l","add_long_l","glut_max2_l","iliacus_l","rect_fem_l","vas_int_l","med_gas_l","tib_ant_l"]

args = sys.argv
IFILE = str(args[1])

# サンプリングデータの読み込み
# lst = pd.read_table(IFILE, header=22)
# lst = pd.read_table(IFILE)

diffLst = []
i = 0
for label in ALL:
    # lst = pd.read_table(IFILE, header=22)
    lst = pd.read_table(IFILE, header=0)
    lst = lst[[label]].values.tolist() # nan削除と数値化
    lst = [x[0] for x in lst] # numpy.ndarrayからlistに変換

    # lstより1フレーム進めたリスト
    _lst = copy.copy(lst)
    _lst.pop(0)
    # del _lst[:7]
    _lst.append(_lst[len(_lst) -1])

    # lstの差分を求める
    ans = DiffList(_lst, lst)
    diffLst.append(max(ans))
    print(label, ",", diffLst[i])
    i += 1

print("最大の差分は,", max(diffLst))