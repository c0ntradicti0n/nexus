import yaml
from more_itertools import partition
import matplotlib.pyplot as plt
import pandas as pd

with open("stats.yml", 'r') as stream:
    outcome = yaml.safe_load(stream)

errors, full_games = partition(lambda x: "error" not in x[2], outcome)

full_games = list(full_games)
errors = list(errors)
versions = list(sorted(set([x[0] for x in full_games])))


def plot_stat(versions, stat):
    df = pd.DataFrame(columns=versions, index=versions)
    df.fillna(0, inplace=True)
    for row in stat:
        white = row[0]
        black = row[1]
        win, loose = row[2]
        df.at[white, black] += eval(win)

    f = plt.figure(figsize=(19, 15))
    plt.matshow(df, fignum=f.number)
    plt.xticks(range(df.select_dtypes(['number']).shape[1]), df.select_dtypes(['number']).columns, fontsize=14,
               rotation=45)
    plt.yticks(range(df.select_dtypes(['number']).shape[1]), df.select_dtypes(['number']).columns, fontsize=14)
    cb = plt.colorbar()
    cb.ax.tick_params(labelsize=14)
    plt.title('Wining Prob', fontsize=16);
    plt.savefig("matrix_as_white.png")

    df = pd.DataFrame(columns=versions, index=versions)
    df.fillna(0, inplace=True)
    for row in stat:
        white = row[0]
        black = row[1]
        win, loose = row[2]
        df.at[white, black] += eval(loose)

    f = plt.figure(figsize=(19, 15))
    plt.matshow(df, fignum=f.number)
    plt.xticks(range(df.select_dtypes(['number']).shape[1]), df.select_dtypes(['number']).columns, fontsize=14,
               rotation=45)
    plt.yticks(range(df.select_dtypes(['number']).shape[1]), df.select_dtypes(['number']).columns, fontsize=14)
    cb = plt.colorbar()
    cb.ax.tick_params(labelsize=14)
    plt.title('Wining Prob', fontsize=16);
    plt.savefig("matrix_as_black.png")


plot_stat(versions=versions, stat=full_games)