import chess
import chess.engine
import logging
logging.basicConfig()
logging.getLogger().setLevel(logging.DEBUG)

engine = chess.engine.SimpleEngine.popen_uci(r"../prog")

board = chess.Board()
while not board.is_game_over():
    print (board)
    result = engine.play(board, chess.engine.Limit(time=20), info=chess.engine.INFO_ALL)
    board.push(result.move)

engine.quit()