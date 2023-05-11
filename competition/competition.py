import multiprocessing
import os
import re
import chess
import chess.engine
import logging

from pprint import pprint

import yaml

logging.basicConfig()
logging.getLogger().setLevel(logging.INFO)
from collections import Counter, defaultdict

debug = False
def play_a_game(_):
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
    _pool = multiprocessing.Pool(10)
    outcome = _pool.map(play_a_game, range(0, 1000))

outcome = list(Counter(outcome).items())


# Convert the tuples to strings for easier comparison
error_strings = list(([' '.join(map(str, error)) for error in outcome]))

def group_by_prefix(errors):
    # Base case: if there's only one error, just return it
    if len(errors) <= 1:
        return errors

    # Split each error into words
    split_errors = [error.split(' ') for error in errors]

    # Find the longest common prefix of all errors
    common_prefix = []
    for words in zip(*split_errors):
        if len(set(words)) == 1:
            common_prefix.append(words[0])
        else:
            break

    # Group the remaining parts of the errors by their next word
    groups = defaultdict(list)
    for error in split_errors:
        # If the error is longer than the common prefix, add it to the appropriate group
        if len(error) > len(common_prefix):
            groups[error[len(common_prefix)]].append(' '.join(error))

    # Now recursively group each group of errors
    for key in groups:
        groups[key] = group_by_prefix(groups[key])

    # Finally, return a dictionary with the common prefix and the groups
    return {'prefix': ' '.join(common_prefix), 'groups': dict(groups)}

# Use this function to group the error strings
grouped_errors = group_by_prefix(error_strings)

with open('result.yml', 'w') as yaml_file:
    yaml.dump(grouped_errors, yaml_file, default_flow_style=False)
pprint(grouped_errors)
os.system("killall prog")