#include <iostream>
using std::cout;
using std::endl;

const int disk_num = 5;

class Peg
{
public:
    int stack [disk_num];

    Peg()
    {
        for (int i = 0; i < disk_num; i++)
            stack[i] = 0;
    }

    bool isEmpty()
    {
        for (int i = 0; i < disk_num; i++)
            if (stack[i] != 0)
                return false;
        return true;
    }

    int pop()
    {
        for (int i = disk_num - 1; i >= 0; i--)
            if (stack[i] != 0)
            {
                int tmp = stack[i];
                stack[i] = 0;
                return tmp;
            }
        return 0;
    }

    bool push(int disk)
    {
        for (int i = 0; i < disk_num; i++)
        {
            if (stack[i] == 0)
            {
                bool tmp = stack[i] != 0 && stack[i-1] < disk;
                bool tmp2 = stack[i] == 0;
                if (tmp || tmp2)
                {
                    stack[i] = disk;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }

    friend bool Move(Peg & from, Peg & to)
    {
        if (from.isEmpty())
            return false;

        int disk = from.pop();
        if (to.push(disk))
            return true;
        else
            from.push(disk);

        return true;
    }
};

void Print(Peg * p, int peg_num);

int main()
{
    Peg pegs [3];
    pegs[0].push(5);
    pegs[0].push(4);
    pegs[0].push(3);
    pegs[0].push(2);
    pegs[0].push(1);

    Print(pegs, 3);

    Move(pegs[0], pegs[1]);
    cout << endl;
    Print(pegs,3);
    return 0;
}

void Print(Peg * p, int peg_num)
{
    for (int i = disk_num - 1; i >= 0 ; i--)
    {
        for (int j = 0; j < peg_num; j++)
        {
            cout << " |";
            if  (p[j].stack[i] == 0) cout << "   ";
            else                     cout << "-" << p[j].stack[i] << "-";
            cout << "|   ";
        }
        cout << endl;
    }
}
