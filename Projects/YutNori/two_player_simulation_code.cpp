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

cell arr1[35], arr2[35];

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
        arr1[i].num = 0;
        arr1[i].prob = 0.0;
        arr2[i].num = 0;
        arr2[i].prob = 0.0;
    }
}

long double calc(int Do, int gae, int gul, int yut, int mo)
{
    return pow(prob_list[0], Do) * pow(prob_list[1], gae) * pow(prob_list[2], gul) * pow(prob_list[3], yut) * pow(prob_list[4], mo);
}

// alex x chatgpt
// arguments: current position, moves
// return: final position
int move(int cur, int moves)
{
    // freopen("output.txt", "w", stdout);
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

void DFS(int cur, int Do, int gae, int gul, int yut, int mo, int cnt, bool is_prev, int p_num)
{
    if (cur > 21 && cur < 100)
    {
        //printf("%d %d %d %d %d %d %d\n", cur, Do, gae, gul, yut, mo, cnt);
        if (p_num == 1)
        {
            arr1[cnt].num++;
            arr1[cnt].prob += calc(Do, gae, gul, yut, mo);
        }
        
        else
        {
            arr2[cnt].num++;
            arr2[cnt].prob += calc(Do, gae, gul, yut, mo);
        }
        return;
    }
    
    if (is_prev)
        cnt--;
        
    cnt++;
    
    DFS(move(cur, 1), Do + 1, gae, gul, yut, mo, cnt, false, p_num);
    DFS(move(cur, 2), Do, gae + 1, gul, yut, mo, cnt, false, p_num);
    DFS(move(cur, 3), Do, gae, gul + 1, yut, mo, cnt, false, p_num);
    DFS(move(cur, 4), Do, gae, gul, yut + 1, mo, cnt, true, p_num);
    DFS(move(cur, 5), Do, gae, gul, yut, mo + 1, cnt, true, p_num);
    return;
}

int main()
{
    int i, j, k, p1, p2, p1_end, p2_end;
    
    SetList();
    
    printf("Please input two positions that you want to compare.\n");
    printf("p1: ");
    scanf("%d", &p1);
    printf("p2: ");
    scanf("%d", &p2);
    
    SetArr();
    DFS(p1, 0, 0, 0, 0, 0, 0, false, 1);
    DFS(p2, 0, 0, 0, 0, 0, 0, false, 2);
    
    printf("\n------------------------------------------------------------------------------------\nChecking idx: %d...\n", p1);
    for (j = 1; j <= 20; j++)
    {
        if (arr1[j].num == 0)
        {
            p1_end = j-1;
            j = 30;
            continue;
        }
        printf("Turn: %2d\tCnt: %6d\tProb: %.20Lf (%.5LF%%)\n", j, arr1[j].num, arr1[j].prob, arr1[j].prob * 100);
    }
    
    printf("\n------------------------------------------------------------------------------------\nChecking idx: %d...\n", p2);
    for (j = 1; j <= 20; j++)
    {
        if (arr2[j].num == 0)
        {
            p2_end = j-1;
            j = 30;
            continue;
        }
        printf("Turn: %2d\tCnt: %6d\tProb: %.20Lf (%.5LF%%)\n", j, arr2[j].num, arr2[j].prob, arr2[j].prob * 100);
    }
    // 1st argument: starting point
    
    long double sum = 0.0, p1_win = 0.0;
    for (int i_p1 = 1; i_p1 <= p1_end; i_p1++)
    {
        sum = 0.0;
        for (int i_p2 = i_p1; i_p2 <= p2_end; i_p2++)
            sum += arr2[i_p2].prob;
        
        p1_win += arr1[i_p1].prob * sum;
    }
    
    printf("\n------------------------------------------------------------------------------------\n");
    printf("\np1: %d\np2: %d\n", p1, p2);
    printf("Probability of p1(%d) win is %.10Lf (%.4LF%%)\n", p1, p1_win, p1_win * 100);
    printf("Probability of p2(%d) win is %.10Lf (%.4LF%%)\n", p2, (1-p1_win), (1-p1_win) * 100);
    
    return 0;
}
