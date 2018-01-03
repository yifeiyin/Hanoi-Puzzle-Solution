#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>

using std::cout;
using std::endl;
using std::string;
using std::vector;

const int disk_num = 6;
const int peg_num = 3;
const bool SLEEP = false;

class Movement
{
public:
    int from;
    int to;

    Movement()
    {
        from = to = 0;
    }

    Movement(int f, int t)
    {
        from = f; to = t;
    }

    bool operator==(Movement & m)
    {
        return (from == m.from) && (to == m.to);
    }

    string GetString()
    {
        return std::to_string(from) + " -> " + std::to_string(to);
    }
};

class Record
{
public:
    vector<Movement> movements;
    bool solved;

    Record()
    {

    }

    Record(vector<Movement> m, bool s)
    {
        movements = m; solved = s;
    }

    Record(bool s)
    {
        solved = s;
    }
};

class Peg
{
public:
    int stack[disk_num];

    Peg()
    {
        for (int i = 0; i < disk_num; i++)
            stack[i] = 0;
    }

    bool IsEmpty()
    {
        for (int i = 0; i < disk_num; i++)
            if (stack[i] != 0)
                return false;
        return true;
    }

    int GetTop()
    {
        for (int i = disk_num - 1; i >= 0; i--)
            if (stack[i] != 0)
            {
                return stack[i];
            }
        return 0;
    }

    int Pop()
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

    bool Push(int disk)
    {
        for (int i = 0; i < disk_num; i++)
        {
            if (stack[i] == 0)
            {
                bool tmp = i != 0 && stack[i-1] > disk;
                bool tmp2 = i == 0;
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

    Peg (Peg & op)
    {
        for (int i = 0; i < disk_num; i++)
            stack[i] = op.stack[i];
    }

    Peg & operator=(Peg & op)
    {
        if (*this == op)
            return *this;

        for (int i = 0; i < disk_num; i++)
            this->stack[i] = op.stack[i];
        return *this;
    }

    bool operator==(Peg & op)
    {
        for (int i = 0; i < disk_num; i++)
            if (stack[i] != op.stack[i])
                return false;
        return true;
    }

    friend bool Move(Peg & from, Peg & to)
    {
        if (from.IsEmpty())
            return false;

        int disk = from.Pop();
        if (to.Push(disk))
            return true;
        else
            from.Push(disk);

        return false;
    }

    bool MoveTo(Peg & to)
    {
        return Move(*this, to);
    }
};

class Pegs
{
public:
    Peg pegs[peg_num];

    Pegs()
    {
        for(int i = 0; i < disk_num; i++)
            pegs[0].Push(disk_num - i);
    }

    void Print()
    {
        for (int i = disk_num - 1; i >= 0 ; i--)
        {
            for (int j = 0; j < peg_num; j++)
            {
                cout << " |";
                if  (pegs[j].stack[i] == 0) cout << "   ";
                else                        cout << "-" << pegs[j].stack[i] << "-";
                cout << "|   ";
            }
            cout << endl;
        }
    }

    bool Move(int from, int to)
    {
//        this->Print(); //DEBUG
//        cout << from << " " << to << endl; //DEBUG
//        bool tmp = pegs[from].MoveTo(pegs[to]); //DEBUG
//        this->Print(); //DEBUG
//        cout << endl; //DEBUG
//        return tmp; //DEBUG
        return pegs[from].MoveTo(pegs[to]);
    }

    Pegs(Pegs & op)
    {
        for (int i = 0; i < peg_num; i++)
            pegs[i] = op.pegs[i];
    }

    Pegs & operator=(Pegs & op)
    {
        if (&op == this)
            return *this;

        for (int i = 0; i < peg_num; i++)
            this->pegs[i] = op.pegs[i];
        return *this;
    }

    bool IsWhatWeWant()
    {
        Peg empty, full;
        for (int i = 0; i < disk_num; i++)
            full.Push(disk_num - i);

        if (pegs[0] == empty && (pegs[1] == full || pegs[2] == full))
            return true;
        return false;
    }



    Record Solve(vector<Movement> movements_so_far, Pegs pegs_so_far, int search_limit, unsigned long initial_time, unsigned long time_limit)
    {
        if (pegs_so_far.IsWhatWeWant())
        {
            return Record(movements_so_far, true);
        }

        if ((int)movements_so_far.size() >= search_limit)
        {
            cout << "Search limits exceeded(" << movements_so_far.size()<<"): "; //DEBUG
            for (unsigned long i = 0; i < movements_so_far.size(); i++) //DEBUG
                cout << movements_so_far[i].GetString() << "  "; //DEBUG
            cout << endl;
            pegs_so_far.Print(); //DEBUG
            cout << endl; //DEBUG
            return Record(movements_so_far, false);
        }

        if (clock() - initial_time > time_limit)
        {
            cout << "Time limits exceeded\n"; // DEBUG
            return Record(movements_so_far, false);
        }

        if (SLEEP)
            //if (std::fmod((clock() - initial_time), (CLOCKS_PER_SEC/10.0)) >= CLOCKS_PER_SEC/10.0)
                system("sleep 0.15"); //SLEEP

        for (int from = 0; from < peg_num; from++)
        {
            for (int to = 0; to < peg_num; to++)
            {
                if (from == to)
                    continue;
                if (!movements_so_far.empty())
                {
//                    if (movements_so_far.back().from == to &&
//                            movements_so_far.back().to == from)
//                        continue;

                    if (movements_so_far.back().to == from)
                        continue;

                    if (movements_so_far.size() >= 2)
                        if (movements_so_far[movements_so_far.size()-2].from == to &&
                                movements_so_far[movements_so_far.size()-2].to == from)
                            continue;

                }

                Pegs p = pegs_so_far;

                if (p.Move(from, to))
                {
                    system("clear");
                    cout << "A valid move has been found: " << from << " -> " << to << endl; //DEBUG
//                    cout << "Previous moves("<<movements_so_far.size()<<"): ";// DEBUG
//                    for (unsigned long debug = 0; debug < movements_so_far.size(); debug++)// DEBUG
//                        cout << movements_so_far[debug].GetString() << " ";// DEBUG
                    cout << "Time consumed: " << clock()/(CLOCKS_PER_SEC*1.0) << endl;
                    cout << "Current status:" << endl;// DEBUG
                    p.Print();// DEBUG
                    cout << endl; // DEBUG
                    vector<Movement> m = movements_so_far;
                    m.push_back(Movement(from, to));

                    Record r;
                    r = Solve(m, p, search_limit, initial_time, time_limit);

                    if (r.solved == true)
                    {
                        return r;
                    }
                }
            }
        }
        return Record (false);
    }
};

int main()
{
    Pegs p;
    p.Print();

    Record main_r = p.Solve({}, p, 200, clock(), 1000000 * 5);

    if (main_r.solved)
            cout << "Solution found("<< main_r.movements.size() <<"):\n";
    else
            cout << "Failed to find a solution\n";

    for (unsigned long i = 0; i < main_r.movements.size(); i++)
        cout << main_r.movements[i].GetString() << " ";

    cout << endl;
    cout << "Time consumed: " << clock()/(CLOCKS_PER_SEC*1.0) << endl;


    return 0;
}
