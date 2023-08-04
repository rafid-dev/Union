## Mate/Stalemate detection
```
Elo difference: 90.2 +/- 34.6, LOS: 100.0 %, DrawRatio: 49.2 %
SPRT: llr 2.95 (100.3%), lbound -2.94, ubound 2.94 - H1 was accepted
```

## Repetition detection
```
Score of dev vs master: 1086 - 963 - 336  [0.526] 2385
...      dev playing White: 519 - 495 - 179  [0.510] 1193
...      dev playing Black: 567 - 468 - 157  [0.542] 1192
...      White vs Black: 987 - 1062 - 336  [0.484] 2385
Elo difference: 17.9 +/- 12.9, LOS: 99.7 %, DrawRatio: 14.1 %
SPRT: llr 2.97 (101.0%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

## Simple Bishop + Rook mobility
```
Score of dev vs master: 234 - 135 - 35  [0.623] 404
...      dev playing White: 97 - 88 - 17  [0.522] 202
...      dev playing Black: 137 - 47 - 18  [0.723] 202
...      White vs Black: 144 - 225 - 35  [0.400] 404
Elo difference: 86.9 +/- 33.4, LOS: 100.0 %, DrawRatio: 8.7 %
SPRT: llr 2.96 (100.4%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

## Simple Queen mobility
```
Score of dev vs master: 408 - 300 - 36  [0.573] 744
...      dev playing White: 174 - 177 - 19  [0.496] 370
...      dev playing Black: 234 - 123 - 17  [0.648] 374
...      White vs Black: 297 - 411 - 36  [0.423] 744
Elo difference: 50.8 +/- 24.6, LOS: 100.0 %, DrawRatio: 4.8 %
SPRT: llr 2.95 (100.1%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

## Capture move ordering
```
Score of dev vs master: 307 - 202 - 25  [0.598] 534
...      dev playing White: 52 - 195 - 18  [0.230] 265
...      dev playing Black: 255 - 7 - 7  [0.961] 269
...      White vs Black: 59 - 450 - 25  [0.134] 534
Elo difference: 69.2 +/- 29.3, LOS: 100.0 %, DrawRatio: 4.7 %
SPRT: llr 2.94 (100.0%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

## Fix location of time breaks
```
Score of dev vs master: 94 - 24 - 44 [0.716] 162
... dev playing White: 30 - 23 - 28 [0.543] 81
... dev playing Black: 64 - 1 - 16 [0.889] 81
... White vs Black: 31 - 87 - 44 [0.327] 162
Elo difference: 160.7 +/- 48.8, LOS: 100.0 %, DrawRatio: 27.2 %
SPRT: llr 2.97 (100.7%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

## Null Move Pruning
```
Score of dev vs master: 232 - 147 - 118  [0.586] 497
...      dev playing White: 133 - 58 - 58  [0.651] 249
...      dev playing Black: 99 - 89 - 60  [0.520] 248
...      White vs Black: 222 - 157 - 118  [0.565] 497
Elo difference: 60.0 +/- 27.0, LOS: 100.0 %, DrawRatio: 23.7 %
SPRT: llr 2.97 (100.8%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

## Dynamic Reduction to Null Move Pruning
```
Score of dev vs master: 293 - 202 - 121  [0.574] 616
...      dev playing White: 165 - 86 - 57  [0.628] 308
...      dev playing Black: 128 - 116 - 64  [0.519] 308
...      White vs Black: 281 - 214 - 121  [0.554] 616
Elo difference: 51.7 +/- 24.8, LOS: 100.0 %, DrawRatio: 19.6 %
SPRT: llr 2.96 (100.5%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

## Introduce killers in move ordering
```
Score of dev vs master: 107 - 25 - 26  [0.759] 158
...      dev playing White: 53 - 9 - 17  [0.778] 79
...      dev playing Black: 54 - 16 - 9  [0.741] 79
...      White vs Black: 69 - 63 - 26  [0.519] 158
Elo difference: 199.8 +/- 56.6, LOS: 100.0 %, DrawRatio: 16.5 %
SPRT: llr 2.98 (101.2%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

## Add optimal time
```
Score of dev vs master: 126 - 35 - 18 [0.754] 179
... dev playing White: 78 - 7 - 6 [0.890] 91
... dev playing Black: 48 - 28 - 12 [0.614] 88
... White vs Black: 106 - 55 - 18 [0.642] 179
Elo difference: 194.8 +/- 55.7, LOS: 100.0 %, DrawRatio: 10.1 %
SPRT: llr 2.95 (100.2%), lbound -2.94, ubound 2.94 - H1 was accepted
```

## Fix location of time break in iterative deepening 
```
Score of dev vs master: 145 - 49 - 16  [0.729] 210
...      dev playing White: 90 - 9 - 6  [0.886] 105
...      dev playing Black: 55 - 40 - 10  [0.571] 105
...      White vs Black: 130 - 64 - 16  [0.657] 210
Elo difference: 171.5 +/- 50.7, LOS: 100.0 %, DrawRatio: 7.6 %
SPRT: llr 2.96 (100.7%), lbound -2.94, ubound 2.94 - H1 was accepted
```

## (Change value >= bestValue to value > bestValue)
Honestly I have no idea but SPRT says it's a bug 
```
Score of dev vs master: 104 - 1 - 6  [0.964] 111
...      dev playing White: 53 - 0 - 2  [0.982] 55
...      dev playing Black: 51 - 1 - 4  [0.946] 56
...      White vs Black: 54 - 51 - 6  [0.514] 111
Elo difference: 570.9 +/- 174.3, LOS: 100.0 %, DrawRatio: 5.4 %
SPRT: llr 5.45 (185.2%), lbound -2.94, ubound 2.94 - H1 was accepted
```

## Add quiescence search
```
Score of dev vs master: 56 - 1 - 6  [0.937] 63
...      dev playing White: 29 - 1 - 2  [0.938] 32
...      dev playing Black: 27 - 0 - 4  [0.935] 31
...      White vs Black: 29 - 28 - 6  [0.508] 63
Elo difference: 467.5 +/- 171.2, LOS: 100.0 %, DrawRatio: 9.5 %
SPRT: llr 2.96 (100.5%), lbound -2.94, ubound 2.94 - H1 was accepted
```

## Fix qsearch and illegal move bug (don't check for checks bruh)
```
Score of dev vs master: 227 - 137 - 86  [0.600] 450
...      dev playing White: 118 - 64 - 43  [0.620] 225
...      dev playing Black: 109 - 73 - 43  [0.580] 225
...      White vs Black: 191 - 173 - 86  [0.520] 450
Elo difference: 70.4 +/- 29.4, LOS: 100.0 %, DrawRatio: 19.1 %
SPRT: llr 3 (102.0%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```