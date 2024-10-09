#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

long double prob_list[10];
long double front = 0.530125;
long double back = 0.469875;
int idx_list[40], idx = -1, st;

struct cell {
    int num;
    long double prob = 0.0;
};

cell arr[35];

void SetList()
{
    prob_list[0] = 4 * pow(front, 3) * pow(back, 1); // 도
    prob_list[1] = 6 * pow(front, 2) * pow(back, 2); // 개
    prob_list[2] = 4 * pow(front, 1) * pow(back, 3); // 걸
    prob_list[3] = pow(back, 4); // 윷
    prob_list[4] = pow(front, 4); // 모
    
    for (int i = 0; i <= 21; i++)
        idx_list[++idx] = i;
    
    idx_list[++idx] = 101;
    idx_list[++idx] = 102;
    idx_list[++idx] = 104;
    idx_list[++idx] = 105;
    idx_list[++idx] = 201;
    idx_list[++idx] = 202;
    idx_list[++idx] = 203;
    idx_list[++idx] = 204;
    idx_list[++idx] = 205;
}

void SetArr()
{
    for (int i = 0; i <= 25; i++)
    {
        arr[i].num = 0;
        arr[i].prob = 0.0;
    }
}

// 도, 개, 걸, 윷, 모의 갯수를 인자로 입력
// 확률을 반환
long double calc(int Do, int Gae, int Gul, int Yut, int Mo)
{
    return pow(prob_list[0], Do) * pow(prob_list[1], Gae) * pow(prob_list[2], Gul) * pow(prob_list[3], Yut) * pow(prob_list[4], Mo);
}

// 현재 위치과 이동수(e.g. 도=1, 개=2, etc.)을 인자로 입력
// 도착지점의 위치를 반환
int move(int cur, int moves)
{
    if (cur == 6)
    {
        if (moves == 3)
            return 203;
        else
            return 100 + moves;
    }

    else if (cur == 11)
    {
        return 200 + moves;
    }

    else if (cur >= 100 && cur < 200)
    {
        if (cur + moves == 103)
            return 203;
        else if (cur + moves > 105)
        {
            return (cur + moves - 90);
        }
        else
            return cur + moves;
    }

    else if (cur >= 200)
    {
        if (cur + moves > 205)
        {
            return (cur + moves) - 185;
        }
        else
            return (cur + moves);
    }

    else
        return cur + moves;
}

void DFS(int cur, int Do, int Gae, int Gul, int Yut, int Mo, int cnt, bool is_prev)
{
    if (cur > 21 && cur < 100)
    {
        //printf("%d %d %d %d %d %d %d\n", cur, Do, gae, gul, yut, mo, cnt);
        arr[cnt].num++;
        arr[cnt].prob += calc(Do, Gae, Gul, Yut, Mo);
        return;
    }
    
    if (is_prev)
        cnt--;
        
    cnt++;
    
    DFS(move(cur, 1), Do + 1, Gae, Gul, Yut, Mo, cnt, false);
    DFS(move(cur, 2), Do, Gae + 1, Gul, Yut, Mo, cnt, false);
    DFS(move(cur, 3), Do, Gae, Gul + 1, Yut, Mo, cnt, false);
    DFS(move(cur, 4), Do, Gae, Gul, Yut + 1, Mo, cnt, true);
    DFS(move(cur, 5), Do, Gae, Gul, Yut, Mo + 1, cnt, true);
    return;
}

int main()
{
    int i, j, k;
    int pos, moves, ans_num = -1, ans_sum = 0;
    long double ans_prob;
    
    SetList();
    
    printf("Please input a position: ");
    scanf("%d", &pos);
    while (true)
    {
        if ((pos >= 0 && pos <= 21) || (pos >= 101 && pos <= 105 && pos != 103) || (pos >= 201 && pos <= 205))
            break;
            
        printf("- Invalid!\n- Please input a correct position: ");
        scanf("%d", &pos);
    }
    
    printf("Please input the number of moves: ");
    scanf("%d", &moves);
    while (true)
    {
        if (moves >= 1)
            break;
            
        printf("- Invalid!\n- Please input a correct number of moves to finish the game (positive integer): ");
        scanf("%d", &moves);
    }
    
    
    for (i = 0; i <= idx; i++)
    {
        SetArr();
        //printf("\n------------------------------------------------------------------------------------\nChecking idx: %d...\n", idx_list[i]);
        st = idx_list[i];
        DFS(idx_list[i], 0, 0, 0, 0, 0, 0, false);
        
        for (int j = 1; j <= 20; j++)
        {
            if (arr[j].num == 0)
            {
                j = 30;
                continue;
            }
            //printf("Turn: %2d\tCnt: %6d\tProb: %.30Lf\n", j, arr[j].num, arr[j].prob);
            if (pos == idx_list[i] && j == moves)
            {
                ans_num = arr[j].num;
                ans_prob = arr[j].prob;
            }
        }
    }
    
    //printf("\n------------------------------------------------------------------------------------\n");
    
    if (ans_num == -1)
        printf("\n\nSorry, there's no possible way to finish the game in %d move(s) at position %d.\n", moves, pos);
    else
    {
        //printf("\n\nAt position %d, probability of finishing the game in %d move(s) is %.5LF(%.3LF%%).\n", pos, moves, ans_prob, ans_prob*100);
        printf("\nProbability: %.5LF(%.3LF%%).\n", ans_prob, ans_prob*100);
    }
    // 1st argument: starting point
    return 0;
}
