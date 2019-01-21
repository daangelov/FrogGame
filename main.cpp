#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

class FrogGame
{

private:
    unsigned int size;
    string start;
    string goal;
    string current;
    string *path;
    unsigned long currentPathIndex;

    string jump(string current, int from, int to) const;
    bool isDeadEnd(string& current) const;

    string* getPossibleMoves(string& current) const;
    bool dfs(string& current);

public:

    FrogGame(int n);
    ~FrogGame();
    void findPath();
    void printPath() const;
};

FrogGame::FrogGame(int n)
{
    this->start = string(n, '>') + "_" + string(n, '<');
    this->current = start;
    this->goal = string(n, '<') + "_" + string(n, '>');
    this->path = new string[(n + 1) * (n + 1)];
    this->currentPathIndex = 0;
    this->size = 2 * n + 1;
}

FrogGame::~FrogGame()
{
    // cout << "Dest called";
    delete path;
}

string FrogGame::jump(string current, int from, int to) const
{
    char temp = current[from];
    current[from] = current[to];
    current[to] = temp;

    return current;
}

bool FrogGame::isDeadEnd(string& current) const
{
    for (unsigned int i = 0; i < this->size - 3; ++i)
    {
        if (current[i] == '>' && current[i + 1] == '>' &&
            current[i + 2] == '<' && current[i + 3] == '<') return true;
    }
    return false;
}

string* FrogGame::getPossibleMoves(string& current) const
{
    string* possibleMoves = new string[4];
    int j = 0;
    for (unsigned int i = 0; i < this->size; ++i)
    {
        if (i < this->size - 1 && current.at(i) == '>' && current.at(i + 1) == '_')
            possibleMoves[j++] = this->jump(current, i, i + 1);

        if (i < this->size - 2 && current.at(i) == '>' && current.at(i + 2) == '_')
            possibleMoves[j++] = this->jump(current, i, i + 2);

        if (i > 0 && current.at(i) == '<' && current.at(i - 1) == '_')
            possibleMoves[j++] = this->jump(current, i, i - 1);

        if (i > 1 && current.at(i) == '<' && current.at(i - 2) == '_')
            possibleMoves[j++] = this->jump(current, i, i - 2);
    }

    return possibleMoves;
}

bool FrogGame::dfs(string& current)
{
    if (current.compare(this->goal) == 0) return true;

    if (isDeadEnd(current)) return false;

    string* moves = getPossibleMoves(current);
    for (int i = 0; i < 4; ++i)
    {
        if (moves[i].empty()) break;

        if (dfs(moves[i]))
        {
            this->path[this->currentPathIndex] = moves[i];
            this->currentPathIndex++;
            return true;
        }
    }
    return false;
}

void FrogGame::findPath()
{
    this->dfs(this->start);
}

void FrogGame::printPath() const
{
    this->path[currentPathIndex] = this->start;
    for (int i = this->currentPathIndex; i >= 0; i--)
    {
        cout << this->path[i] << endl;
    }
}

// Main
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Invalid argument n!";
        return 0;
    }

    int n = atoi(argv[1]);

    clock_t start, end;

    FrogGame frogGame(n);
    start = clock(); // Execution starts
    frogGame.findPath();
    end = clock(); // Execution ends

    frogGame.printPath();
    cout << "Time: " << (end - start) / (double) CLOCKS_PER_SEC << endl;
}
