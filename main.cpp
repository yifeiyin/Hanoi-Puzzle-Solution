#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>

using std::cout;
using std::endl;
using std::string;
using std::vector;

const int disk_num = 4;
const int peg_num = 3;

const bool SLEEP = false;
// Set to true to make it run slower.

const bool CLEAR = false;
// Set to false when (1)running on Windows, or (2)a more accurate timing is required.

// +-----------------------------+
// + * Movement consists of two integers indicating "from" location and "to" location.
// +-----------------------------+
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
        return std::to_string(from+1) + " -> " + std::to_string(to+1);
    }
};

// +-----------------------------+
// + * Record consists of (1)a set of movements, and (2)a boolean variable indicating
// +   wheather the set of movements is the solution or the failed attempt.
// + * Record is only used when to return solutions in Pegs::Solve(...)
// +-----------------------------+
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

// +-----------------------------+
// + * Peg is the representation of a peg.
// + * The most important parts are functions Pop(), Push(), Move().
// +-----------------------------+
class Peg
{
public:
    int stack[disk_num];

    Peg()
    {
        for (int i = 0; i < disk_num; i++)
            stack[i] = 0;
    }

    // Copy construct function
    Peg (Peg & op)
    {
        for (int i = 0; i < disk_num; i++)
            stack[i] = op.stack[i];
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
                if (i == 0 || stack[i-1] > disk)
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

    // Assignment operator overload
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


// +------------------------+
// + The toppest class
// +------------------------+
class Pegs
{
public:
    Peg pegs[peg_num];

    Pegs()
    {

    }

    // Copy construct function
    Pegs(Pegs & op)
    {
        for (int i = 0; i < peg_num; i++)
            pegs[i] = op.pegs[i];
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
        return pegs[from].MoveTo(pegs[to]);
    }

    Pegs & operator=(Pegs & op)
    {
        if (&op == this)
            return *this;

        for (int i = 0; i < peg_num; i++)
            this->pegs[i] = op.pegs[i];
        return *this;
    }

    //
    // Anticipated result can be modified here.
    //
    bool IsWhatWeWant()
    {
//        Peg empty, full;
//        for (int i = 0; i < disk_num; i++)
//            full.Push(disk_num - i);

//        if (pegs[0] == empty && (pegs[1] == full || pegs[2] == full))
//            return true;
//        return false;

        Peg want_we_want [3];
        want_we_want[2].Push(4);
        want_we_want[2].Push(3);
        want_we_want[1].Push(2);
        want_we_want[2].Push(1);
//        want_we_want[2].Push(5);
//        want_we_want[2].Push(6);

        if (pegs[0] == want_we_want[0] &&
                pegs[1] == want_we_want[1] &&
                pegs[2] == want_we_want[2])
            return true;
        return false;
    }


    //
    // This function can be done outside the class since it
    // does not do anything to the member itself.
    //
    Record Solve(vector<Movement> movements_so_far, Pegs pegs_so_far, int search_limit, unsigned long initial_time, unsigned long time_limit)
    {
        // Check if it is the solution
        if (pegs_so_far.IsWhatWeWant())
        {
            return Record(movements_so_far, true);
        }

        // Check if it is exceeding search limit
        if (static_cast<int>(movements_so_far.size()) >= search_limit)
        {
            cout << "Search limits exceeded(" << movements_so_far.size() <<"): "; //DEBUG
            for (unsigned long i = 0; i < movements_so_far.size(); i++) //DEBUG
                cout << movements_so_far[i].GetString() << "  "; //DEBUG
            cout << endl;
            pegs_so_far.Print(); //DEBUG
            cout << endl; //DEBUG

            return Record(movements_so_far, false);
        }

        // Check if it is exceeding time limit
        if (clock() - initial_time > time_limit)
        {
            cout << "Time limits exceeded." << endl; // DEBUG
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

                // Check if the movement can cause infinite self looping
                if (!movements_so_far.empty())
                {
                    if (movements_so_far.back().to == from)
                        continue;

                    // [!]
                    if (movements_so_far.size() >= 2)
                        if (movements_so_far[movements_so_far.size()-2].from == to &&
                                movements_so_far[movements_so_far.size()-2].to == from)
                            continue;
                }

                Pegs p = pegs_so_far;

                cout << "  @Checking: " << Movement(from,to).GetString() << endl; // DEBUG
                cout << "  @Previous moves(" << movements_so_far.size() << "): "; // DEBUG
                for (unsigned long debug = 0; debug < movements_so_far.size(); debug++) // DEBUG
                    cout << movements_so_far[debug].GetString() << " "; // DEBUG

                cout << endl << "  @Current status:" << endl; // DEBUG
                p.Print(); // DEBUG
                cout << endl; // DEBUG

                if (p.Move(from, to))
                {
                    if (CLEAR)
                        system("clear");
                    cout << "A valid move has been made: " << Movement(from,to).GetString() << endl; // DEBUG

//                    cout << "Previous moves(" << movements_so_far.size() << "): "; // DEBUG
//                    for (unsigned long debug = 0; debug < movements_so_far.size(); debug++) // DEBUG
//                        cout << movements_so_far[debug].GetString() << " "; // DEBUG

                    cout << "Time consumed: " << clock()/(CLOCKS_PER_SEC*1.0) << endl; // DEBUG
                    cout << "Current status:" << endl; // DEBUG
                    p.Print(); // DEBUG
                    cout << endl; // DEBUG

                    vector<Movement> m = movements_so_far;
                    m.push_back(Movement(from, to));

                    Record r;
                    r = Solve(m, p, search_limit, initial_time, time_limit);

                    if (r.solved == false)
                    {
                        cout << "Reaching a dead end with (" << r.movements.size() << ") moves"
                                ", rolling back." << endl;

                    }
                    if (r.solved == true)
                    {
                        return r;
                    }
                }
            }
        }
        return Record(movements_so_far, false);
    }
};

int main()
{
    Pegs ppp;

    for(int i = 0; i < disk_num; i++)
        ppp.pegs[0].Push(disk_num - i);


    Record result = ppp.Solve({}, ppp, 300, clock(), CLOCKS_PER_SEC * 10);

    if (result.solved)
            cout << "Solution found(" << result.movements.size() << "):" << endl;
    else
            cout << "Failed to find a solution." << endl;

    for (unsigned long i = 0; i < result.movements.size(); i++)
        cout << result.movements[i].GetString() << " ";

    cout << endl;
    cout << "Time consumed: " << clock()/(CLOCKS_PER_SEC*1.0) << endl;


    return 0;
}
