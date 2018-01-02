//#include <iostream>
//#include <vector>
//using std::cout;
//using std::endl;
//using std::vector;

//const int disk_num = 5;
//const int peg_num = 3;

//class struct_move
//{
//public:
//    int from = 0;
//    int to = 0;

//    bool operator==(struct_move & s)
//    {
//        return ((from == s.from) && (to == s.to));
//    }
//};

//class Peg
//{
//public:
//    int stack [disk_num];

//    Peg()
//    {
//        for (int i = 0; i < disk_num; i++)
//            stack[i] = 0;
//    }

//    bool isEmpty()
//    {
//        for (int i = 0; i < disk_num; i++)
//            if (stack[i] != 0)
//                return false;
//        return true;
//    }

//    int pop()
//    {
//        for (int i = disk_num - 1; i >= 0; i--)
//            if (stack[i] != 0)
//            {
//                int tmp = stack[i];
//                stack[i] = 0;
//                return tmp;
//            }
//        return 0;
//    }

//    bool push(int disk)
//    {
//        for (int i = 0; i < disk_num; i++)
//        {
//            if (stack[i] == 0)
//            {
//                bool tmp = stack[i] != 0 && stack[i-1] < disk;
//                bool tmp2 = stack[i] == 0;
//                if (tmp || tmp2)
//                {
//                    stack[i] = disk;
//                    return true;
//                }
//                else
//                {
//                    return false;
//                }
//            }
//        }
//        return false;
//    }

//    Peg & operator=(Peg & op)
//    {
//        Peg * out = new Peg;
//        for (int i = 0; i < disk_num; i++)
//            op.stack[i] = out->stack[i];
//        return *out;
//    }

//    friend bool Move(Peg & from, Peg & to)
//    {
//        if (from.isEmpty())
//            return false;

//        int disk = from.pop();
//        if (to.push(disk))
//            return true;
//        else
//            from.push(disk);

//        return true;
//    }
//};

//void Print(Peg * p, int peg_num, vector<struct_move> moves = {})
//{
//    if (!moves.empty())
//    {
//        for (int i = 0; i < (int)moves.size(); i++)
//        {
//            if (!Move(p[moves[i].from], p[moves[i].to]))
//            {
//                    cout << "error\n";
//            }
//        }
//    }
//    for (int i = disk_num - 1; i >= 0 ; i--)
//    {
//        for (int j = 0; j < peg_num; j++)
//        {
//            cout << " |";
//            if  (p[j].stack[i] == 0) cout << "   ";
//            else                     cout << "-" << p[j].stack[i] << "-";
//            cout << "|   ";
//        }
//        cout << endl;
//    }
//}

//bool Solve_outside(Peg * pegs, int peg_num);
//vector<struct_move> Solve(vector<struct_move> moves_so_far, Peg* pegs, int peg_num, int moves_limit, long initial_time);

//int main2()
//{
//    Peg pegs [3];
//    pegs[0].push(5);
//    pegs[0].push(4);
//    pegs[0].push(3);
//    pegs[0].push(2);
//    pegs[0].push(1);

//    Print(pegs, 3);

//    vector<struct_move> m = Solve({}, pegs, 3, 100, 0);

//    for (int i = 0; i < m.size(); i++)
//        cout << i << " :  " << m[i].from << " -> " << m[i].to << endl;

//    return 0;
//}

//bool Solve_outside(Peg * pegs, int peg_num)
//{
////    vector<struct_move> empty;
////    vector<struct_move> solution = Solve(empty, pegs, peg_num, 100, (long)ctime);
//    return true;
//}

//vector<struct_move> Solve(vector<struct_move> moves_so_far, Peg* pegs, int peg_num, int moves_limit, long initial_time)
//{
//    for (int i_from = 0; i_from < peg_num; i_from++)
//        for (int i_to = 0; i_to < peg_num; i_to++)
//        {
//            if (i_from == i_to)
//                continue;
//            struct_move tmp;
//            tmp.to = i_from;
//            tmp.from = i_to;
//            if (moves_so_far.back() == tmp)
//                continue;

//            if ((int)moves_so_far.size() >= moves_limit)
//            {
//                cout << "Moves exceeds limits.\n";
//            }

//            if (pegs[0].isEmpty())
//                return moves_so_far;

//            Peg * pegs2 = new Peg [peg_num];
//            for (int i = 0; i < peg_num; i++)
//                pegs2[i] = pegs[i];

//            if (Move(pegs[i_from], pegs[i_to]))
//            {
//                struct_move tmp;
//                tmp.from = i_from;
//                tmp.to = i_to;

//                vector<struct_move> moves_so_far2;
//                moves_so_far2 = moves_so_far;
//                moves_so_far2.push_back(tmp);

//                Solve(moves_so_far2, pegs2, peg_num, moves_limit, initial_time);
//            }
//        }
//    return {};
//}

//class Pegs
//{
//public:
//    Peg pegs[peg_num];

////    Print()
////    {

////    }
//};
