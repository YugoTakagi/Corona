import pandas as pd
import os
import sys
# subject01_walk1_Actuation_force.tsv
# vas_int_r

args = sys.argv
IFILE = str(args[1])
COL = str(args[2])

tsv = pd.read_table(IFILE, header=22, usecols=[COL])
df = pd.DataFrame(tsv)
df.T.to_csv( '_export/'+COL+'.csv', header=False, index=False)
