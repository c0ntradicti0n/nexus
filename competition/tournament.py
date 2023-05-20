import itertools
import multiprocessing
import os
import re
import traceback

import chess
import chess.engine
import logging

from pprint import pprint

import yaml

from str_tools import group_by_prefix

logging.basicConfig()
logging.getLogger().setLevel(logging.INFO)
from collections import Counter

versions = os.listdir("versions")

debug = os.environ.get("DEBUG", False)
moves = [] #"d2d4 d7d5 b1c3 g8f6 e2e3 b8c6 g1f3 e7e6 f1b5 a7a6 b5c6 b7c6 f3e5 h7h6 e5c6 d8d7 c6e5 d7d8 e1g1 f8d6 e5c6 d8d7 c6e5 d6e5 d4e5 f6g4 d1g4 f7f5 e5f6".split() #"d2d4 d7d5 b1c3 g8f6 g1f3 b8c6 e2e3 e7e6 f1b5 a7a6 b5c6 b7c6 f3e5 a6a5 e5c6 d8d7 c6e5 d7d8 e1g1".split()

def play_a_game(_):
    global moves
    i, (white, black) = _
    board = chess.Board()
    for m in moves:
        board.push_san(m)
    if debug:
        print(board)

    white_to_move = None
    try:
        fen = board.fen()
        while not board.is_game_over():
            white_to_move = board.turn
            if white_to_move:
                print ("white to move")
                engine = chess.engine.SimpleEngine.popen_uci(f"versions/{white}/prog")
            else:
                print ("black to move")

                engine = chess.engine.SimpleEngine.popen_uci(f"versions/{black}/prog")
            result = engine.play(board, chess.engine.Limit(time=20000), info=chess.engine.INFO_ALL)
            board.push(result.move)
            pid = re.findall(r"(\d+)", str(engine))[0]
            os.system(f'kill {pid}')
            fen = board.fen()
            moves = list([m.__repr__()[15:19] for m in board.move_stack])
            if debug:
                print(fen)


        res = white, black, board.result().split("-"), f">>> {board.result()} >>> {fen} >>> {i}"
        print(board)
        print(res)
        return res

    except Exception as e:
        traceback.print_exc()
        print(())
        print(board)
        return white, black, f"error made by '{white if white_to_move else black}'", str(e), moves, str(board)


if debug:
    os.system("rm log.txt log.*.txt")
    outcome = [play_a_game((0, [versions[1], versions[2]]))]
else:
    fights = list(itertools.permutations(versions, 2)) * 300
    print(len(fights))

    _pool = multiprocessing.Pool(10)
    outcome = _pool.map(play_a_game, enumerate(fights))



with open('stats.yml', 'w') as yaml_file:
    yaml.dump([list(t) for t in outcome], yaml_file, default_flow_style=False)

outcome = [str(o) for o in outcome]
outcome = list(Counter(outcome).items())

# Convert the tuples to strings for easier comparison
error_strings = list(([' '.join(map(str, error)) for error in outcome]))

# Use this function to group the error strings
grouped_errors = group_by_prefix(error_strings)

with open('result.yml', 'w') as yaml_file:
    yaml.dump(grouped_errors, yaml_file, default_flow_style=False)
pprint(grouped_errors)
os.system("killall prog")
