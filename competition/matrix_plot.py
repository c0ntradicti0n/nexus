import yaml
from more_itertools import partition

with open("stats.yml", 'r') as stream:
    outcome = yaml.safe_load(stream)

errors, full_games = partition(lambda x: "error" not in x[2], outcome)

full_games = list(full_games)
errors = list(errors)
import pandas as pd
versions = list(sorted(set([x[0] for x in full_games])))
df = pd.DataFrame(columns=versions, index=versions)
df.fillna(0, inplace=True)

for game in full_games:
    white = game[0]
    black = game[1]
    win, loose = game[2]
    df.at[white, black] += eval(win)

import matplotlib.pyplot as plt

f = plt.figure(figsize=(19, 15))
plt.matshow(df, fignum=f.number)
plt.xticks(range(df.select_dtypes(['number']).shape[1]), df.select_dtypes(['number']).columns, fontsize=14, rotation=45)
plt.yticks(range(df.select_dtypes(['number']).shape[1]), df.select_dtypes(['number']).columns, fontsize=14)
cb = plt.colorbar()
cb.ax.tick_params(labelsize=14)
plt.title('Correlation Matrix', fontsize=16);
plt.savefig("matrix.png")