import itertools
import multiprocessing
import os
import re
import chess
import chess.engine
import logging

from pprint import pprint

import yaml

from str_tools import group_by_prefix

logging.basicConfig()
logging.getLogger().setLevel(logging.INFO)
from collections import Counter

versions = os.listdir("../versions")



debug = False
def play_a_game(_):
    print (_)
    board = chess.Board()
    moves = []

    try:
        while not board.is_game_over():
            engine = chess.engine.SimpleEngine.popen_uci(r"../prog")
            result = engine.play(board, chess.engine.Limit(time=200))#, info=chess.engine.INFO_ALL)
            board.push(result.move)
            pid = re.findall(r"(\d+)", str(engine))[0]
            os.system(f'kill {pid}')
            moves = (tuple([m.__repr__()[15:19] for m in board.move_stack]))

        print(f"{_} Game over. {board.result()} + FEN {board.starting_fen}")
        print (board)
        return board.result()

    except Exception as e:
        return str(e), moves, str(board)

if debug:
    outcome =[play_a_game(1)]
else:
    fights = list(itertools.permutations(versions, 2)) * 100

    _pool = multiprocessing.Pool(10)
    outcome = _pool.map(play_a_game, enumerate(fights)  )

outcome = list(Counter(outcome).items())


# Convert the tuples to strings for easier comparison
error_strings = list(([' '.join(map(str, error)) for error in outcome]))

# Use this function to group the error strings
grouped_errors = group_by_prefix(error_strings)

with open('result.yml', 'w') as yaml_file:
    yaml.dump(grouped_errors, yaml_file, default_flow_style=False)
pprint(grouped_errors)
os.system("killall prog")