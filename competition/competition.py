import chess
import chess.engine
import logging
logging.basicConfig()
logging.getLogger().setLevel(logging.DEBUG)


board = chess.Board()
while not board.is_game_over():
    print (board)
    engine = chess.engine.SimpleEngine.popen_uci(r"../prog")
    result = engine.play(board, chess.engine.Limit(time=2000), info=chess.engine.INFO_ALL)
    board.push(result.move)

engine.quit()