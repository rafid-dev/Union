cutechess-cli -engine cmd="./Union.exe" stderr="./tests/error.txt" name="dev" proto="uci" -engine cmd="./binaries/Union.exe" name="master" proto="uci" -each tc=inf/6+0.06 -openings file=./pgns/8moves_v3.pgn order=sequential  -games 2 -rounds 10000 -repeat 2 -maxmoves 200 -sprt elo0=0 elo1=10   alpha=0.05 beta=0.05 -concurrency 6 -ratinginterval 10 -pgnout "./pgns/test.pgn"