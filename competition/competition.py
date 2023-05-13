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

debug = os.environ.get("DEBUG", False)


def play_a_game(_):
    i, (white, black) = _
    board = chess.Board()
    moves = []

    white_to_move = None
    try:
        while not board.is_game_over():
            white_to_move = board.turn
            if white_to_move:
                engine = chess.engine.SimpleEngine.popen_uci(f"../versions/{white}/prog")
            else:
                engine = chess.engine.SimpleEngine.popen_uci(f"../versions/{black}/prog")
            result = engine.play(board, chess.engine.Limit(time=200))
            board.push(result.move)
            pid = re.findall(r"(\d+)", str(engine))[0]
            os.system(f'kill {pid}')
            fen = board.fen()
            moves = list([m.__repr__()[15:19] for m in board.move_stack])

        res = white, black, board.result().split("-"), f"{(white, black)} >>> {board.result()} >>> {fen} >>> {i}"
        print(board)
        print(res)
        return res

    except Exception as e:
        return white, black, f"error made by '{white if white_to_move else black}'", str(e), moves, str(board)


if debug:
    outcome = [play_a_game((0, [versions[0], versions[1]]))]
else:
    fights = list(itertools.permutations(versions, 2)) * 15
    print(len(fights))

    _pool = multiprocessing.Pool(10)
    outcome = _pool.map(play_a_game, enumerate(fights))



with open('stats.yml', 'w') as yaml_file:
    yaml.dump([list(t) for t in outcome], yaml_file, default_flow_style=False)

outcome = list(Counter(outcome).items())

# Convert the tuples to strings for easier comparison
error_strings = list(([' '.join(map(str, error)) for error in outcome]))

# Use this function to group the error strings
grouped_errors = group_by_prefix(error_strings)

with open('result.yml', 'w') as yaml_file:
    yaml.dump(grouped_errors, yaml_file, default_flow_style=False)
pprint(grouped_errors)
os.system("killall prog")
