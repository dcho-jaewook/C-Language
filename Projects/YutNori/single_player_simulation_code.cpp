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

// Initializing Function
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
// 각 조합이 특정 횟수만큼 등장할 확률을 반환
// ex) 도, 개, 걸, 윷, 모가 각각 1, 1, 0, 0, 1번 등장할 확률은 xx%
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

// 깊이 우선 탐색을 통해 현재 포지션에서 가능한 모든 결과 조사
// is_prev 변수를 통해 윷과 모가 나왔을 때 "횟수 페널티 없이 다시 던지기" 구현
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
    long double ans_prob, ans_prob_exact;
    
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
    
    
    ans_prob_exact = ans_prob = 0.0;
    
    for (i = 0; i <= idx; i++)
    {
        SetArr();
        st = idx_list[i];
        DFS(idx_list[i], 0, 0, 0, 0, 0, 0, false);
        
        for (int j = 1; j <= 20; j++)
        {
            if (arr[j].num == 0)
            {
                j = 30;
                continue;
            }
            if (pos == idx_list[i])
            {
                ans_num = arr[j].num;
                ans_prob += arr[j].prob;
                
                printf("\n- %d move(s): %.5LF(%.3LF%%)", j, arr[j].prob, arr[j].prob*100);
            }
        }
    }
    return 0;
}
