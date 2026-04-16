  tester git:(main) ./test.sh

42 Philosophers Tester  2026/04/16
Iterations: 10

Mandatory tests (eval sheet)            [0]

Normal tests                            [1]
Hardcore tests (a lot)                  [2]

Exit Tester                             [ESC]



Please choose:2

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
1       Fail    [x]     612 1 died
2       Fail    [x]     611 3 died
3       Pass    [✓]     simulation ended
4       Pass    [✓]     simulation ended
5       Fail    [x]     612 1 died
6       Pass    [✓]     simulation ended
7       Fail    [x]     611 3 died
8       Fail    [x]     611 1 died
9       Pass    [✓]     simulation ended
10      Fail    [x]     611 1 died
        40 % correct
____________________________________________
        199 610 200 200 10
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
Testing uneven numbers (overkill) - they shouldn't die

        5 610 200 100 10
1       Pass    [✓]     simulation ended
2       Fail    [x]     611 3 died
3       Pass    [✓]     simulation ended
4       Fail    [x]     816 2 died
5       Fail    [x]     611 1 died
6       Fail    [x]     611 3 died
7       Fail    [x]     611 3 died
8       Pass    [✓]     simulation ended
9       Fail    [x]     611 3 died
10      Pass    [✓]     simulation ended
        40 % correct
____________________________________________
        5 601 200 200 10
1       Fail    [x]     603 3 died
2       Fail    [x]     602 1 died
3       Fail    [x]     603 1 died
4       Fail    [x]     603 1 died
5       Fail    [x]     603 3 died
6       Fail    [x]     603 3 died
7       Fail    [x]     602 3 died
8       Fail    [x]     602 3 died
9       Fail    [x]     602 1 died
10      Fail    [x]     603 3 died
        0 % correct
____________________________________________
        31 610 200 100 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Pass    [✓]     simulation ended
4       Fail    [x]     813 28 died
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Pass    [✓]     simulation ended
8       Fail    [x]     611 29 died
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        80 % correct
____________________________________________
        31 610 200 200 10
1       Fail    [x]     612 29 died
2       Fail    [x]     612 1 died
3       Fail    [x]     611 29 died
4       Pass    [✓]     simulation ended
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Pass    [✓]     simulation ended
8       Fail    [x]     611 29 died
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        60 % correct
____________________________________________
        31 605 200 200 10
1       Fail    [x]     606 29 died
2       Pass    [✓]     simulation ended
3       Fail    [x]     607 29 died
4       Fail    [x]     609 29 died
5       Fail    [x]     606 1 died
6       Fail    [x]     607 29 died
7       Fail    [x]     607 29 died
8       Fail    [x]     608 29 died
9       Fail    [x]     606 29 died
10      Fail    [x]     606 29 died
        10 % correct
____________________________________________
        31 601 200 200 10
1       Fail    [x]     602 1 died
2       Fail    [x]     602 29 died
3       Fail    [x]     602 1 died
4       Fail    [x]     602 29 died
5       Fail    [x]     602 1 died
6       Fail    [x]     602 29 died
7       Fail    [x]     604 29 died
8       Fail    [x]     603 29 died
9       Fail    [x]     602 1 died
10      Fail    [x]     602 1 died
        0 % correct
____________________________________________
        131 610 200 100 10
1       Fail    [x]     611 1 died
2       Pass    [✓]     simulation ended
3       Fail    [x]     612 129 died
4       Fail    [x]     611 1 died
5       Pass    [✓]     simulation ended
6       Fail    [x]     612 129 died
7       Fail    [x]     613 129 died
8       Pass    [✓]     simulation ended
9       Pass    [✓]     simulation ended
10      Fail    [x]     611 1 died
        40 % correct
____________________________________________
        131 610 200 200 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Pass    [✓]     simulation ended
4       Fail    [x]     614 129 died
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Fail    [x]     612 129 died
8       Fail    [x]     611 1 died
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        70 % correct
____________________________________________
        131 605 200 200 10
1       Fail    [x]     608 129 died
2       Fail    [x]     607 129 died
3       Fail    [x]     608 129 died
4       Fail    [x]     607 129 died
5       Fail    [x]     607 129 died
6       Fail    [x]     607 129 died
7       Fail    [x]     608 129 died
8       Fail    [x]     606 1 died
9       Fail    [x]     606 1 died
10      Fail    [x]     606 129 died
        0 % correct
____________________________________________
        131 601 200 200 10
1       Fail    [x]     604 129 died
2       Fail    [x]     604 129 died
3       Fail    [x]     603 129 died
4       Fail    [x]     803 128 died
5       Fail    [x]     604 129 died
6       Fail    [x]     604 129 died
7       Fail    [x]     603 129 died
8       Fail    [x]     603 129 died
9       Fail    [x]     603 1 died
10      Fail    [x]     603 129 died
        0 % correct
____________________________________________
        199 610 200 100 10
1       Pass    [✓]     simulation ended
2       Pass    [✓]     simulation ended
3       Pass    [✓]     simulation ended
4       Fail    [x]     613 197 died
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Pass    [✓]     simulation ended
8       Fail    [x]     612 197 died
9       Pass    [✓]     simulation ended
10      Fail    [x]     611 1 died
        70 % correct
____________________________________________
        199 610 200 200 10
1       Fail    [x]     613 197 died
2       Pass    [✓]     simulation ended
3       Pass    [✓]     simulation ended
4       Pass    [✓]     simulation ended
5       Pass    [✓]     simulation ended
6       Pass    [✓]     simulation ended
7       Pass    [✓]     simulation ended
8       Fail    [x]     611 1 died
9       Pass    [✓]     simulation ended
10      Pass    [✓]     simulation ended
        80 % correct
____________________________________________
        199 605 200 200 10
1       Fail    [x]     609 197 died
2       Fail    [x]     608 197 died
3       Fail    [x]     609 197 died
4       Fail    [x]     606 1 died
5       Pass    [✓]     simulation ended
6       Fail    [x]     609 197 died
7       Pass    [✓]     simulation ended
8       Pass    [✓]     simulation ended
9       Fail    [x]     608 197 died
10      Pass    [✓]     simulation ended
        40 % correct
____________________________________________
        199 601 200 200 10
1       Fail    [x]     605 197 died
2       Fail    [x]     604 197 died
3       Fail    [x]     605 197 died
4       Fail    [x]     604 197 died
5       Fail    [x]     604 197 died
6       Fail    [x]     604 197 died
7       Fail    [x]     603 197 died
8       Fail    [x]     604 197 died
9       Fail    [x]     604 197 died
10      Fail    [x]     604 197 died
        0 % correct
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
1       Fail    [x]     617 2 died
2       Fail    [x]     412 3 died
3       Fail    [x]     411 1 died
4       Fail    [x]     411 1 died
5       Fail    [x]     411 1 died
6       Fail    [x]     411 3 died
7       Fail    [x]     613 2 died
8       Fail    [x]     412 3 died
9       Fail    [x]     614 2 died
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
Testing even numbers (overkill) - they shouldn't die
        50 410 200 100 10
1       Fail    [x]     1021 6 died
2       Fail    [x]     612 2 died
3       Fail    [x]     817 41 died
4       Fail    [x]     1023 4 died
5       Fail    [x]     1223 31 died
6       Fail    [x]     1220 29 died
7       Fail    [x]     1224 33 died
8       Fail    [x]     613 40 died
9       Fail    [x]     1018 16 died
10      Fail    [x]     3461 40 died
        0 % correct
____________________________________________
        50 410 200 200 10
1       Fail    [x]     411 3 died
2       Fail    [x]     411 3 died
3       Fail    [x]     411 1 died
4       Fail    [x]     412 15 died
5       Fail    [x]     411 1 died
6       Fail    [x]     411 1 died
7       Fail    [x]     411 1 died
8       Fail    [x]     411 1 died
9       Fail    [x]     411 1 died
10      Fail    [x]     411 1 died
        0 % correct
____________________________________________
        50 405 200 200 10
1       Fail    [x]     406 1 died
2       Fail    [x]     406 1 died
3       Fail    [x]     407 1 died
4       Fail    [x]     406 1 died
5       Fail    [x]     406 1 died
6       Fail    [x]     406 1 died
7       Fail    [x]     407 1 died
8       Pass    [✓]     406 17 is thinking
9       Fail    [x]     406 1 died
10      Fail    [x]     406 1 died
        10 % correct
____________________________________________
        50 401 200 200 10
1       Fail    [x]     402 1 died
2       Fail    [x]     402 1 died
3       Fail    [x]     402 1 died
4       Fail    [x]     402 1 died
5       Fail    [x]     404 1 died
6       Fail    [x]     402 1 died
7       Fail    [x]     403 1 died
8       Fail    [x]     402 1 died
9       Fail    [x]     403 1 died
10      Fail    [x]     402 1 died
        0 % correct
____________________________________________
        130 410 200 100 10
1       Fail    [x]     613 28 died
2       Fail    [x]     411 19 died
3       Fail    [x]     818 9 died
4       Fail    [x]     1224 45 died
5       Fail    [x]     612 2 died
6       Fail    [x]     816 51 died
7       Fail    [x]     411 35 died
8       Fail    [x]     411 5 died
9       Pass    [✓]     411 18 is sleeping
10      Fail    [x]     411 1 died
        10 % correct
____________________________________________
        130 410 200 200 10
1       Fail    [x]     412 1 died
2       Fail    [x]     411 11 died
3       Fail    [x]     411 1 died
4       Pass    [✓]     411 43 has taken a fork
5       Fail    [x]     411 1 died
6       Fail    [x]     411 1 died
7       Fail    [x]     411 1 died
8       Fail    [x]     411 1 died
9       Fail    [x]     412 1 died
10      Fail    [x]     412 1 died
        10 % correct
____________________________________________
        130 405 200 200 10
1       Pass    [✓]     407 39 has taken a fork
2       Fail    [x]     407 1 died
3       Fail    [x]     406 1 died
4       Pass    [✓]     408 92 is sleeping
5       Pass    [✓]     406 69 is thinking
6       Fail    [x]     406 1 died
7       Pass    [✓]     406 17 is eating
8       Fail    [x]     406 1 died
9       Fail    [x]     406 1 died
10      Fail    [x]     406 1 died
        40 % correct
____________________________________________
        130 401 200 200 10
1       Fail    [x]     403 1 died
2       Fail    [x]     402 1 died
3       Fail    [x]     402 1 died
4       Fail    [x]     402 1 died
5       Fail    [x]     402 1 died
6       Fail    [x]     402 1 died
7       Fail    [x]     402 1 died
8       Fail    [x]     402 1 died
9       Fail    [x]     402 1 died
10      Fail    [x]     402 1 died
        0 % correct
____________________________________________
        198 410 200 100 10
1       Fail    [x]     1017 26 died
2       Fail    [x]     411 47 died
3       Fail    [x]     817 7 died
4       Fail    [x]     818 3 died
5       Fail    [x]     818 3 died
6       Fail    [x]     818 5 died
7       Fail    [x]     615 138 died
8       Fail    [x]     412 1 died
9       Fail    [x]     816 5 died
10      Fail    [x]     614 146 died
        0 % correct
____________________________________________
        198 410 200 200 10
1       Fail    [x]     411 1 died
2       Fail    [x]     412 1 died
3       Fail    [x]     411 1 died
4       Fail    [x]     411 1 died
5       Fail    [x]     411 1 died
6       Pass    [✓]     413 59 has taken a fork
7       Fail    [x]     411 1 died
8       Fail    [x]     411 1 died
9       Fail    [x]     412 1 died
10      Fail    [x]     411 1 died
        10 % correct
____________________________________________
        198 405 200 200 10
1       Fail    [x]     407 1 died
2       Fail    [x]     407 1 died
3       Fail    [x]     406 1 died
4       Pass    [✓]     407 123 is thinking
5       Fail    [x]     406 1 died
6       Fail    [x]     406 1 died
7       Fail    [x]     407 1 died
8       Fail    [x]     406 1 died
9       Fail    [x]     406 1 died
10      Fail    [x]     406 1 died
        10 % correct
____________________________________________
        198 401 200 200 10
1       Fail    [x]     402 1 died
2       Pass    [✓]     402 25 is thinking
3       Fail    [x]     402 1 died
4       Pass    [✓]     403 157 is thinking
5       Fail    [x]     403 1 died
6       Fail    [x]     402 1 died
7       Fail    [x]     402 1 died
8       Fail    [x]     402 1 died
9       Pass    [✓]     402 169 has taken a fork
10      Fail    [x]     402 1 died
        30 % correct
____________________________________________
Testing uneven numbers - one should die
        4 310 200 100 10
1       Pass    [✓]     311 1 died
2       Pass    [✓]     311 1 died
3       Pass    [✓]     312 1 died
4       Pass    [✓]     311 1 died
5       Pass    [✓]     312 1 died
6       Pass    [✓]     311 1 died
7       Pass    [✓]     311 1 died
8       Pass    [✓]     311 1 died
9       Pass    [✓]     311 1 died
10      Pass    [✓]     311 1 died
        100 % correct
____________________________________________
        1 800 200 100 10
1       Pass    [✓]     801 1 died
2       Pass    [✓]     801 1 died
3       Pass    [✓]     802 1 died
4       Pass    [✓]     801 1 died
5       Pass    [✓]     801 1 died
6       Pass    [✓]     801 1 died
7       Pass    [✓]     801 1 died
8       Pass    [✓]     801 1 died
9       Pass    [✓]     802 1 died
10      Pass    [✓]     802 1 died
        100 % correct
____________________________________________
Testing uneven numbers - one should die
        3 596 200 200 10
1       Pass    [✓]     598 3 died
2       Pass    [✓]     597 1 died
3       Pass    [✓]     598 1 died
4       Pass    [✓]     597 1 died
5       Pass    [✓]     597 3 died
6       Pass    [✓]     598 1 died
7       Pass    [✓]     597 3 died
8       Pass    [✓]     598 1 died
9       Pass    [✓]     598 3 died
10      Pass    [✓]     597 1 died
        100 % correct
____________________________________________
        3 599 200 200 10
1       Pass    [✓]     600 1 died
2       Pass    [✓]     600 3 died
3       Pass    [✓]     600 1 died
4       Pass    [✓]     600 3 died
5       Pass    [✓]     600 1 died
6       Pass    [✓]     600 1 died
7       Pass    [✓]     601 1 died
8       Pass    [✓]     601 1 died
9       Pass    [✓]     600 1 died
10      Pass    [✓]     600 1 died
        100 % correct
____________________________________________
        3 600 200 200 10
1       Pass    [✓]     601 3 died
2       Pass    [✓]     602 1 died
3       Pass    [✓]     601 3 died
4       Pass    [✓]     601 3 died
5       Pass    [✓]     601 1 died
6       Pass    [✓]     601 3 died
7       Pass    [✓]     602 3 died
8       Pass    [✓]     602 1 died
9       Pass    [✓]     602 3 died
10      Pass    [✓]     602 3 died
        100 % correct
____________________________________________
        31 596 200 200 10
1       Pass    [✓]     597 1 died
2       Pass    [✓]     597 29 died
3       Pass    [✓]     597 29 died
4       Pass    [✓]     597 29 died
5       Pass    [✓]     597 1 died
6       Pass    [✓]     597 1 died
7       Pass    [✓]     597 29 died
8       Pass    [✓]     599 29 died
9       Pass    [✓]     597 29 died
10      Pass    [✓]     597 29 died
        100 % correct
____________________________________________
        31 599 200 200 10
1       Pass    [✓]     600 29 died
2       Pass    [✓]     600 1 died
3       Pass    [✓]     600 29 died
4       Pass    [✓]     601 29 died
5       Pass    [✓]     600 1 died
6       Pass    [✓]     600 29 died
7       Pass    [✓]     600 1 died
8       Pass    [✓]     601 29 died
9       Pass    [✓]     600 1 died
10      Pass    [✓]     602 29 died
        100 % correct
____________________________________________
        31 600 200 200 10
1       Pass    [✓]     601 1 died
2       Pass    [✓]     602 29 died
3       Pass    [✓]     601 29 died
4       Pass    [✓]     601 29 died
5       Pass    [✓]     602 29 died
6       Pass    [✓]     602 29 died
7       Pass    [✓]     602 29 died
8       Pass    [✓]     601 29 died
9       Pass    [✓]     601 29 died
10      Pass    [✓]     601 29 died
        100 % correct
____________________________________________
        131 596 200 200 10
1       Pass    [✓]     599 129 died
2       Pass    [✓]     599 129 died
3       Pass    [✓]     598 129 died
4       Pass    [✓]     598 129 died
5       Pass    [✓]     599 129 died
6       Pass    [✓]     598 129 died
7       Pass    [✓]     598 129 died
8       Pass    [✓]     599 129 died
9       Pass    [✓]     598 129 died
10      Pass    [✓]     599 129 died
        100 % correct
____________________________________________
        131 599 200 200 10
1       Pass    [✓]     600 1 died
2       Pass    [✓]     601 129 died
3       Pass    [✓]     601 129 died
4       Pass    [✓]     600 1 died
5       Pass    [✓]     602 129 died
6       Pass    [✓]     601 129 died
7       Pass    [✓]     602 129 died
8       Pass    [✓]     600 1 died
9       Pass    [✓]     601 129 died
10      Pass    [✓]     601 1 died
        100 % correct
____________________________________________
        131 600 200 200 10
1       Pass    [✓]     604 129 died
2       Pass    [✓]     603 1 died
3       Pass    [✓]     602 129 died
4       Pass    [✓]     601 1 died
5       Pass    [✓]     601 1 died
6       Pass    [✓]     606 129 died
7       Pass    [✓]     602 1 died
8       Pass    [✓]     603 129 died
9       Pass    [✓]     603 129 died
10      Pass    [✓]     602 129 died
        100 % correct
____________________________________________
        199 596 200 200 10
1       Pass    [✓]     599 197 died
2       Pass    [✓]     600 197 died
3       Pass    [✓]     599 197 died
4       Pass    [✓]     599 197 died
5       Pass    [✓]     599 197 died
6       Pass    [✓]     600 197 died
7       Pass    [✓]     599 197 died
8       Pass    [✓]     597 1 died
9       Pass    [✓]     598 1 died
10      Pass    [✓]     599 197 died
        100 % correct
____________________________________________
        199 599 200 200 10
1       Pass    [✓]     602 197 died
2       Pass    [✓]     601 1 died
3       Pass    [✓]     602 197 died
4       Pass    [✓]     603 197 died
5       Pass    [✓]     603 197 died
6       Pass    [✓]     602 197 died
7       Pass    [✓]     603 197 died
8       Pass    [✓]     602 197 died
9       Pass    [✓]     603 197 died
10      Pass    [✓]     601 1 died
        100 % correct
____________________________________________
        199 600 200 200 10
1       Pass    [✓]     602 197 died
2       Pass    [✓]     604 197 died
3       Pass    [✓]     604 197 died
4       Pass    [✓]     603 197 died
5       Pass    [✓]     601 1 died
6       Pass    [✓]     603 197 died
7       Pass    [✓]     603 197 died
8       Pass    [✓]     603 197 died
9       Pass    [✓]     603 197 died
10      Pass    [✓]     601 1 died
        100 % correct
____________________________________________
Testing even numbers - one should die
        3 599 200 200 10
1       Pass    [✓]     600 1 died
2       Pass    [✓]     600 1 died
3       Pass    [✓]     601 1 died
4       Pass    [✓]     600 3 died
5       Pass    [✓]     600 3 died
6       Pass    [✓]     601 1 died
7       Pass    [✓]     601 1 died
8       Pass    [✓]     600 3 died
9       Pass    [✓]     600 3 died
10      Pass    [✓]     600 1 died
        100 % correct
____________________________________________
        31 599 200 200 10
1       Pass    [✓]     600 29 died
2       Pass    [✓]     601 29 died
3       Pass    [✓]     601 29 died
4       Pass    [✓]     600 29 died
5       Pass    [✓]     601 29 died
6       Pass    [✓]     601 29 died
7       Pass    [✓]     601 29 died
8       Pass    [✓]     600 1 died
9       Pass    [✓]     600 29 died
10      Pass    [✓]     602 29 died
        100 % correct
____________________________________________
        131 596 200 200 10
1       Pass    [✓]     599 129 died
2       Pass    [✓]     597 1 died
3       Pass    [✓]     598 129 died
4       Pass    [✓]     600 129 died
5       Pass    [✓]     598 129 died
6       Pass    [✓]     598 129 died
7       Pass    [✓]     598 129 died
8       Pass    [✓]     598 129 died
9       Pass    [✓]     597 1 died
10      Pass    [✓]     597 1 died
        100 % correct
____________________________________________
Testing even numbers - one should die
        4 310 200 100 10
1       Pass    [✓]     311 1 died
2       Pass    [✓]     312 1 died
3       Pass    [✓]     311 1 died
4       Pass    [✓]     311 1 died
5       Pass    [✓]     311 1 died
6       Pass    [✓]     311 1 died
7       Pass    [✓]     312 1 died
8       Pass    [✓]     311 1 died
9       Pass    [✓]     311 1 died
10      Pass    [✓]     311 1 died
        100 % correct
____________________________________________
        50 396 200 200 10
1       Pass    [✓]     397 1 died
2       Pass    [✓]     397 1 died
3       Pass    [✓]     397 1 died
4       Pass    [✓]     397 1 died
5       Pass    [✓]     398 1 died
6       Pass    [✓]     397 1 died
7       Pass    [✓]     398 1 died
8       Pass    [✓]     397 1 died
9       Pass    [✓]     398 1 died
10      Pass    [✓]     397 1 died
        100 % correct
____________________________________________
        50 399 200 200 10
1       Pass    [✓]     400 1 died
2       Pass    [✓]     400 1 died
3       Pass    [✓]     400 1 died
4       Pass    [✓]     400 1 died
5       Pass    [✓]     400 1 died
6       Pass    [✓]     401 1 died
7       Pass    [✓]     400 1 died
8       Pass    [✓]     400 1 died
9       Pass    [✓]     400 1 died
10      Pass    [✓]     401 1 died
        100 % correct
____________________________________________
        50 400 200 200 10
1       Pass    [✓]     401 1 died
2       Pass    [✓]     401 1 died
3       Pass    [✓]     401 1 died
4       Pass    [✓]     401 1 died
5       Pass    [✓]     401 1 died
6       Pass    [✓]     401 1 died
7       Pass    [✓]     401 1 died
8       Pass    [✓]     401 1 died
9       Pass    [✓]     401 1 died
10      Pass    [✓]     402 1 died
        100 % correct
____________________________________________
        130 396 200 200 10
1       Pass    [✓]     398 1 died
2       Pass    [✓]     398 1 died
3       Pass    [✓]     397 1 died
4       Pass    [✓]     398 1 died
5       Pass    [✓]     397 1 died
6       Pass    [✓]     397 1 died
7       Pass    [✓]     397 1 died
8       Pass    [✓]     397 1 died
9       Pass    [✓]     398 1 died
10      Pass    [✓]     397 1 died
        100 % correct
____________________________________________
        130 399 200 200 10
1       Pass    [✓]     400 1 died
2       Pass    [✓]     401 1 died
3       Pass    [✓]     400 1 died
4       Pass    [✓]     400 1 died
5       Pass    [✓]     401 1 died
6       Pass    [✓]     401 1 died
7       Pass    [✓]     400 1 died
8       Pass    [✓]     401 1 died
9       Pass    [✓]     400 1 died
10      Pass    [✓]     400 1 died
        100 % correct
____________________________________________
        130 400 200 200 10
1       Pass    [✓]     409 17 died
2       Pass    [✓]     401 1 died
3       Pass    [✓]     401 1 died
4       Pass    [✓]     401 1 died
5       Pass    [✓]     401 1 died
6       Pass    [✓]     402 1 died
7       Pass    [✓]     401 1 died
8       Pass    [✓]     401 1 died
9       Pass    [✓]     401 1 died
10      Pass    [✓]     402 1 died
        100 % correct
____________________________________________
        198 396 200 200 10
1       Pass    [✓]     397 1 died
2       Pass    [✓]     397 1 died
3       Pass    [✓]     398 1 died
4       Pass    [✓]     397 1 died
5       Pass    [✓]     397 1 died
6       Pass    [✓]     398 1 died
7       Pass    [✓]     397 1 died
8       Pass    [✓]     397 1 died
9       Pass    [✓]     397 1 died
10      Pass    [✓]     398 1 died
        100 % correct
____________________________________________
        198 399 200 200 10
1       Pass    [✓]     400 1 died
2       Pass    [✓]     400 1 died
3       Pass    [✓]     400 1 died
4       Pass    [✓]     400 1 died
5       Pass    [✓]     402 1 died
6       Pass    [✓]     400 1 died
7       Pass    [✓]     400 1 died
8       Pass    [✓]     400 1 died
9       Pass    [✓]     400 1 died
10      Pass    [✓]     401 1 died
        100 % correct
____________________________________________
        198 400 200 200 10
1       Pass    [✓]     401 1 died
2       Pass    [✓]     401 1 died
3       Pass    [✓]     401 1 died
4       Pass    [✓]     401 1 died
5       Pass    [✓]     401 1 died
6       Pass    [✓]     402 1 died
7       Pass    [✓]     402 1 died
8       Pass    [✓]     401 1 died
9       Pass    [✓]     401 1 died
10      Pass    [✓]     402 1 died
        100 % correct
____________________________________________

RESULT: passed: 385     failed: 215
./test.sh: line 350: [: 64.1667: integer expression expected
./test.sh: line 352: [: 64.1667: integer expression expected
        64.1667 % correct
____________________________________________
➜  tester git:(main) ✗ ./test.sh

42 Philosophers Tester  2026/04/16
Iterations: 10

Mandatory tests (eval sheet)            [0]

Normal tests                            [1]
Hardcore tests (a lot)                  [2]

Exit Tester                             [ESC]


