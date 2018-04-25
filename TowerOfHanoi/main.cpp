
#include <stack>

using namespace std;

typedef stack<int> Peg;

int solveTower(Peg& a, Peg& b, Peg& c);

int main(int argc, char *argv[])
{
    const int kNumberOfDisks(5);
    Peg a;
    Peg b;
    Peg c;

    for(i = kNumberOfDisks; i > 0; i--)
    {
        a.push(i);
    }

    solveTower(a, b, c);
}

bool canIMoveToPeg(int disk, Peg* candidatePeg, bool& isEmpty)
{
    bool result(false);

    if (candidatePeg->size() == 0)
    {
        result = true;
        isEmpty = true;
    }
    else
    {
        bool isDiskEven = (disk % 2) == 0;
        bool isTopEven = (candidatePeg->top() % 2) == 0;

        if (isDiskEven != isTopEven)
            result = true;

        isEmpty = false;
    }

    return result;
}

int solveTower
(
    Peg& a,
    Peg& b,
    Peg& c
)
{
    Peg* sourcePeg(&a);
    Peg* targetPeg1;
    Peg* targetPeg2;

    int disks(a.size());
    int moves(0);

    if (a.size())
    {
        if (disks % 2)
            b.push(a.pop());
        else
            c.push(a.pop());

        moves++;

        while (b.size() < disks)
        {
            int disk = sourcePeg->pop();

            if (sourcePeg == &a)
            {
                sourcePeg = &b;
                targetPeg1 = &b;
                targetPeg2 = &c;
            }
            else if (sourcePeg == &b)
            {
                sourcePeg = &c;
                targetPeg1 = &c;
                targetPeg2 = &a;
            }
            else // has to be c
            {
                sourcePeg = &a;
                targetPeg1 = &a;
                targetPeg2 = &b;
            }

            bool isTarg1Empty;
            bool isTarg2Empty;
            bool canTarg1AcceptDisk;
            bool canTarg2AcceptDisk;

            canTarg1AcceptDisk = canIMoveToPeg(targetPeg1, isTarg1Empty);
            canTarg2AcceptDisk = canIMoveToPeg(targetPeg1, isTarg2Empty);
        }

    }

    return moves;
}
