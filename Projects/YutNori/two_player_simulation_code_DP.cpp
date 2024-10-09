#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

struct total {
    bool is_checked;
    long double prob;
};

total dp_turn1[300][300], dp_turn2[300][300];
long double front = 0.530125;
long double back = 0.469875;
long double prob_list[10];
int idx_list[40], idx = -1;

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
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            dp_turn1[i][j].is_checked = false;
            dp_turn2[i][j].is_checked = false;
            dp_turn1[i][j].prob = 0.0;
            dp_turn2[i][j].prob = 0.0;
        }
    }
}

long double calc(int Do, int Gae, int Gul, int Yut, int Mo)
{
    return pow(prob_list[0], Do) * pow(prob_list[1], Gae) * pow(prob_list[2], Gul) * pow(prob_list[3], Yut) * pow(prob_list[4], Mo);
}

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

int tmp_pos;
bool tmp_contact;
long double DFS(int turn, int prev_turn, int Do, int Gae, int Gul, int Yut, int Mo, int pos1, int pos2)
{
    if (prev_turn == 1 && pos1 > 21 && pos1 < 100)
        return calc(Do, Gae, Gul, Yut, Mo);
        
    if (prev_turn == 2 && pos2 > 21 && pos2 < 100)
        return calc(Do, Gae, Gul, Yut, Mo);
   
    long double tmp_prob = 0.0F;
    if (turn == 1)
    {
        //printf("A\n");
        if (dp_turn1[pos1][pos2].is_checked)
            return dp_turn1[pos1][pos2].prob;
        
        // Do
        tmp_pos = move(pos1, 1);
        tmp_contact = (tmp_pos == pos2);
        tmp_prob += DFS((tmp_contact)?1:2, 1, Do+1, Gae, Gul, Yut, Mo, tmp_pos, (tmp_contact)?0:pos2);
        
        // Gae
        tmp_pos = move(pos1, 2);
        tmp_contact = (tmp_pos == pos2);
        tmp_prob += DFS((tmp_contact)?1:2, 1, Do, Gae+1, Gul, Yut, Mo, tmp_pos, (tmp_contact)?0:pos2);
        
        // Gul
        tmp_pos = move(pos1, 3);
        tmp_contact = (tmp_pos == pos2);
        tmp_prob += DFS((tmp_contact)?1:2, 1, Do, Gae, Gul+1, Yut, Mo, tmp_pos, (tmp_contact)?0:pos2);
        
        // Yut
        tmp_pos = move(pos1, 4);
        tmp_contact = (tmp_pos == pos2);
        tmp_prob += DFS(1, 1, Do, Gae, Gul, Yut+1, Mo, tmp_pos, (tmp_contact)?0:pos2);
        
        // Mo
        tmp_pos = move(pos1, 5);
        tmp_contact = (tmp_pos == pos2);
        tmp_prob += DFS(1, 1, Do, Gae, Gul, Yut, Mo+1, tmp_pos, (tmp_contact)?0:pos2);
        
        
        dp_turn1[pos1][pos2].is_checked = true;
        dp_turn2[pos2][pos1].is_checked = true;
        dp_turn1[pos1][pos2].prob = tmp_prob;
        dp_turn2[pos2][pos1].prob = tmp_prob;
        
        //printf("dp_turn1[%d][%d] = %.4LF\n", pos1, pos2, dp_turn1[pos1][pos2]);
        return tmp_prob;
    }
    
         
    else
    {
        //printf("B\n");
        if (dp_turn2[pos1][pos2].is_checked)
            return dp_turn2[pos1][pos2].prob;
        
        // Do
        tmp_pos = move(pos2, 1);
        tmp_contact = (tmp_pos == pos1);
        tmp_prob += DFS((tmp_contact)?2:1, 2, Do+1, Gae, Gul, Yut, Mo, (tmp_contact)?0:pos1, tmp_pos);
        
        // Gae
        tmp_pos = move(pos2, 2);
        tmp_contact = (tmp_pos == pos1);
        tmp_prob += DFS((tmp_contact)?2:1, 2, Do, Gae+1, Gul, Yut, Mo, (tmp_contact)?0:pos1, tmp_pos);
        
        // Gul
        tmp_pos = move(pos2, 3);
        tmp_contact = (tmp_pos == pos1);
        tmp_prob += DFS((tmp_contact)?2:1, 2, Do, Gae, Gul+1, Yut, Mo, (tmp_contact)?0:pos1, tmp_pos);
        
        // Yut
        tmp_pos = move(pos2, 4);
        tmp_contact = (tmp_pos == pos1);
        tmp_prob += DFS(2, 2, Do, Gae, Gul, Yut+1, Mo, (tmp_contact)?0:pos1, tmp_pos);
        
        // Mo
        tmp_pos = move(pos2, 5);
        tmp_contact = (tmp_pos == pos1);
        tmp_prob += DFS(2, 2, Do, Gae, Gul, Yut, Mo+1, (tmp_contact)?0:pos1, tmp_pos);
        
        dp_turn1[pos2][pos1].is_checked = true;
        dp_turn2[pos1][pos2].is_checked = true;
        dp_turn1[pos2][pos1].prob = tmp_prob;
        dp_turn2[pos1][pos2].prob = tmp_prob;
        
        //printf("dp_turn2[%d][%d] = %.4LF\n", pos1, pos2, dp_turn2[pos1][pos2]);
        return tmp_prob;
    }
}

int main()
{
    //printf("Hello!\n");
    
    int pos1, pos2;
    
    printf("Please input two positions that you want to compare.\n");
    printf("p1: ");
    scanf("%d", &pos1);
    printf("p2: ");
    scanf("%d", &pos2);
    
    SetList();
    SetArr();
    
    long double coleman = DFS(1, -1, 0, 0, 0, 0, 0, 21, 202);
    
    /* for (int i = 0; i <= idx; i++)
    {
        printf("pos1: %d\n--------------------------\n", idx_list[i]);
        for (int j = 0; j <= idx; j++)
            printf("%d vs %d: %.10LF%%\n", idx_list[i], idx_list[j], dp_turn1[i][j].prob);
            
        printf("--------------------------\n");
    } */
    
    printf("%d vs %d: %.20LF%%\n", pos1, pos2, dp_turn1[pos1][pos2].prob * 100);
    
    if (dp_turn1[pos1][pos2].is_checked)
        printf("true\n");
    else
        printf("false\n");
    
    return 0;
}
