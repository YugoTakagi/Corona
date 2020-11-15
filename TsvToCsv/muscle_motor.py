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


# cp  = 0.64       #[rpm/rpm]コントローラが作る最初のステップ
cp  = 1       #[rpm/rpm]コントローラが作る最初のステップ
''' 分割してみる '''
cut = 2#分割


# subject01_walk1_Actuation_force.tsv
# label = ["glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "sar_r", "add_mag2_r", "tfl_r", "pect_r", "grac_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "quad_fem_r", "gem_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]

# ALL = ["time", "glut_med1_r", "glut_med2_r", "glut_med3_r", "bifemlh_r", "bifemsh_r", "glut_max1_r", "glut_max2_r", "glut_max3_r", "iliacus_r", "psoas_r", "peri_r", "rect_fem_r", "vas_int_r", "med_gas_r", "soleus_r", "tib_post_r", "tib_ant_r"]

# 2019_ResultsCMC_subject01_walk1_Actuation_force.tsv
label = ["glut_med2_r", "add_mag2_r", "glut_max2_r", "iliacus_r", "rect_fem_r", "vas_int_r", "med_gas_r", "tib_ant_r"]

# kaneko.tsv
# label = ["glut_med2_l","bifemlh_l","add_long_l","glut_max2_l","iliacus_l","rect_fem_l","vas_int_l","med_gas_l","tib_ant_l"]


args = sys.argv
filename = str(args[1])

''' データの読み込み(データフレームの作成) '''
df = pd.read_table(filename, header=22)
# df = pd.read_table(filename, header=0)



''' plotの設定 '''
plt.figure()
# ax1 = plt.subplot(1,2,1)
# ax2 = plt.subplot(1,2,2)
# ax = [plt.subplot(5,5,x) for x in np.arange(1,26)]
ax = [plt.subplot(2,4,x) for x in np.arange(1,9)]



''' dtに近いインデックスを捕まえる '''
t = df["time"].values

flow = [0]
time_buffer = 0.0
for i in range(len(t) - 1):
    _dt = t[i + 1] - t[i]

    time_buffer += _dt
    if time_buffer <= dt:
        continue
    else:
        flow.append(i)
        time_buffer = 0.0



''' muscleごとの処理を始める '''
x = 0
for muscle_name in label:
    f = df[muscle_name].values

    f_lst       = []
    f_buffer    = f[0]
    delta_f_lst = []

    T_lst       = []
    TI_lst      = []
    Tu_lst      = []
    rpm_lst     = []
    rps_lst     = []


    # dtごとの筋力を近似的に求める
    for i in range(len(flow) - 1):
        f_lst.append(f_buffer)

        # dt [s]間に変化した df [N]を近似的に取り出す
        _delta_f = f[flow[i + 1]] - f[flow[i]]
        _delta_t = t[flow[i + 1]] - t[flow[i]]

        dA = _delta_f / _delta_t
        delta_f = dA * dt

        f_buffer += delta_f



    for i in range(len(f_lst) - 1):
        # 最小二乗法で求めたAfpを元に, [N]の変化時に必要な回転数を求める
        fs = f_lst[i] / cut
        fn = f_lst[i + 1] / cut
        delta_f = fn - fs
        delta_f_lst.append(delta_f)

        delta_palse = delta_f/Afp # dt間で出力するパルス
        """ cp倍 """
        delta_palse *= cp


        rps = (2*np.pi * (delta_palse/M)) / dt #[rad/s]
        rpm = (30/np.pi) * rps #[rpm]
        rps_lst.append(rps)
        rpm_lst.append(rpm)


        # イナーシャを求める
        I_state = ((fs+(delta_f)/(2)) * D**2) / (4 * g)


        # イナーシャ分のトルクを求める
        if (i - 1 == 0):
            T_acc = 0.0
        TI = I_state * ((rps_lst[i] - rps_lst[i-1]) / dt)
        TI = TI if (TI > 0) else 0.0
        TI_lst.append(TI)


        # 要求されるトルクを求める
        T = fs*r
        T_lst.append(T)

        Tu = T + TI
        Tu_lst.append(Tu)   
        

    # print(muscle_name, ",")
    # print('max [N]', max(delat_f_lst))
    # print('max [Nm],', max(T_lst))
    # print('max [rpm],', max(rpm_lst))

    # plt.plot([0.02*x for x in range(len(f_lst))], f_lst, '.-', label='f, '+muscle_name)
    # plt.plot(delat_f_lst, label='delta_f, '+muscle_name)
    # plt.plot([0.02*x for x in range(len(rpm_lst))], T_lst, '.-',label='T_lst, '+muscle_name)
    # plt.plot([0.02*x for x in range(len(rpm_lst))], Tu_lst, '.-',label='Tu, '+muscle_name)
    # ax2.plot([0.02*x for x in range(len(rpm_lst))], T_val, '.-',label='T_val, '+muscle_name)
    # plt.plot([0.02*x for x in range(len(rpm_lst))], rpm_lst, '.-', label='rpm, '+muscle_name)

    # ax[x].bar(range(len(rpm_lst)), delta_f_lst, label='delta_f, '+muscle_name)
    # ax[x].bar(range(len(rpm_lst)), rpm_lst, label='rpm, '+muscle_name)


    ax[x].bar(range(len(T_lst)), T_lst, label='T, '+muscle_name)
    ax[x].bar(range(len(T_lst)), TI_lst, bottom=T_lst, label='TI, '+muscle_name)


    ax[x].legend()
    x += 1


    # plt.bar(range(len(T)), T_lst, label='T_lst, '+muscle_name)
    # plt.bar(range(len(T_acc_lst)), T_acc_lst, bottom = T_lst, label='T_acc, '+muscle_name)
    # plt.legend()
    # plt.show()

# # ax2.legend()
plt.legend()
plt.show()