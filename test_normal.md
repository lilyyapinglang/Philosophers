 tester git:(main) ✗ ./test.sh

42 Philosophers Tester  2026/04/16
Iterations: 10

Mandatory tests (eval sheet)            [0]

Normal tests                            [1]
Hardcore tests (a lot)                  [2]

Exit Tester                             [ESC]



Please choose:1

42 Philosophers Tester  2026/04/16
Iterations: 10

All tests                               [0]

Uneven numbers that shouldn't die       [1]
Even numbers that shouldn't die         [2]
All numbers that shouldn't die          [3]

Uneven numbers that should die          [4]
Even numbers that should die            [5]
All numbers that should die             [6]

Own tests                               [7]
Exit Tester                             [ESC]



Please choose:0
Testing uneven numbers - they shouldn't die

        5 800 200 200 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Pass    [✓]     simulation ended
4       Pass    [✓]     simulation ended
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Pass    [✓]     simulation ended
8       Pass    [✓]     simulation ended
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        100 % correct
____________________________________________
        5 610 200 200 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Fail    [x]     611 3 died
4       Pass    [✓]     simulation ended
5       Pass    [✓]     simulation ended
6       Fail    [x]     612 3 died
7       Pass    [✓]     simulation ended
8       Pass    [✓]     simulation ended
9       Fail    [x]     612 3 died
10      Fail    [x]     611 1 died
        60 % correct
____________________________________________
        199 610 200 200 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Fail    [x]     611 1 died
4       Pass    [✓]     simulation ended
5       Fail    [x]     613 197 died
6       Pass    [✓]     simulation ended
7       Pass    [✓]     613 128 is thinking
8       Pass    [✓]     simulation ended
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        80 % correct
____________________________________________
Testing even numbers - they shouldn't die
        4 410 200 100 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Pass    [✓]     simulation ended
4       Pass    [✓]     simulation ended
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Pass    [✓]     simulation ended
8       Pass    [✓]     simulation ended
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        100 % correct
____________________________________________
        4 410 200 200 10
1       Fail    [x]     412 1 died
2       Fail    [x]     411 1 died
3       Fail    [x]     411 1 died
4       Fail    [x]     411 1 died
5       Fail    [x]     411 1 died
6       Fail    [x]     411 1 died
7       Fail    [x]     412 1 died
8       Fail    [x]     412 1 died
9       Fail    [x]     411 1 died
10      Fail    [x]     412 1 died
        0 % correct
____________________________________________
        198 610 200 200 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Pass    [✓]     simulation ended
4       Pass    [✓]     simulation ended
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Pass    [✓]     simulation ended
8       Pass    [✓]     simulation ended
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        100 % correct
____________________________________________
        198 800 200 200 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Pass    [✓]     simulation ended
4       Pass    [✓]     simulation ended
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Pass    [✓]     simulation ended
8       Pass    [✓]     simulation ended
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        100 % correct
____________________________________________
Testing uneven numbers - one should die
        4 310 200 100 10
1       Pass    [✓]     311 1 died
2       Pass    [✓]     311 1 died
3       Pass    [✓]     311 1 died
4       Pass    [✓]     312 1 died
5       Pass    [✓]     311 1 died
6       Pass    [✓]     312 1 died
7       Pass    [✓]     311 1 died
8       Pass    [✓]     311 1 died
9       Pass    [✓]     311 1 died
10      Pass    [✓]     311 1 died
        100 % correct
____________________________________________
        1 800 200 100 10
1       Pass    [✓]     801 1 died
2       Pass    [✓]     801 1 died
3       Pass    [✓]     801 1 died
4       Pass    [✓]     801 1 died
5       Pass    [✓]     801 1 died
6       Pass    [✓]     801 1 died
7       Pass    [✓]     801 1 died
8       Pass    [✓]     801 1 died
9       Pass    [✓]     801 1 died
10      Pass    [✓]     802 1 died
        100 % correct
____________________________________________
Testing even numbers - one should die
        3 599 200 200 10
1       Pass    [✓]     600 1 died
2       Pass    [✓]     601 1 died
3       Pass    [✓]     600 3 died
4       Pass    [✓]     601 3 died
5       Pass    [✓]     600 3 died
6       Pass    [✓]     600 3 died
7       Pass    [✓]     600 1 died
8       Pass    [✓]     600 1 died
9       Pass    [✓]     601 1 died
10      Pass    [✓]     601 1 died
        100 % correct
____________________________________________
        31 599 200 200 10
1       Pass    [✓]     600 29 died
2       Pass    [✓]     600 29 died
3       Pass    [✓]     600 29 died
4       Pass    [✓]     601 29 died
5       Pass    [✓]     600 29 died
6       Pass    [✓]     600 29 died
7       Pass    [✓]     601 1 died
8       Pass    [✓]     600 29 died
9       Pass    [✓]     600 1 died
10      Pass    [✓]     600 29 died
        100 % correct
____________________________________________
        131 596 200 200 10
1       Pass    [✓]     598 129 died
2       Pass    [✓]     599 129 died
3       Pass    [✓]     597 1 died
4       Pass    [✓]     598 129 died
5       Pass    [✓]     598 129 died
6       Pass    [✓]     598 129 died
7       Pass    [✓]     598 129 died
8       Pass    [✓]     598 129 died
9       Pass    [✓]     598 1 died
10      Pass    [✓]     599 129 died
        100 % correct
____________________________________________

RESULT: passed: 104     failed: 16
./test.sh: line 350: [: 86.6667: integer expression expected
./test.sh: line 352: [: 86.6667: integer expression expected
        86.6667 % correct