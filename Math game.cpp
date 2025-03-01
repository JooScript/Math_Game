#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

enum enOperationType
{
    Add = 1,
    Subtract = 2,
    Multiply = 3,
    Devide = 4,
    Mix = 5
};

enum enDiffcultyLevel
{
    Easy = 1,
    Medium = 2,
    Hard = 3,
    Mixx = 4
};

struct stGameInfo
{
    enOperationType OperationType;
    enDiffcultyLevel DiffcultyLevel;
    string FinalResult = "";
    short Number1 = 0, Number2 = 0, Rounds = 0, RightTimes = 0, WrongTimes = 0;
};

short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;
}

short ReadValidateShortInRange(string Message, short From, short To)
{
    short Number;

    do
    {
        cout << Message;
        cin >> Number;
    } while (!(Number >= From && Number <= To));

    return Number;
}

enOperationType ReadOperationType(string Message)
{
    return (enOperationType)ReadValidateShortInRange(Message, 1, 5);
}

enOperationType ReadRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}

enDiffcultyLevel ReadDiffcultyLevel(string Message)
{
    return (enDiffcultyLevel)ReadValidateShortInRange(Message, 1, 4);
}

short ReadRounds(string Message)
{
    return ReadValidateShortInRange(Message, 1, 100);
}

short NumbersDifficculty(stGameInfo &Info)
{
    switch (Info.DiffcultyLevel)
    {
    case enDiffcultyLevel::Easy:
        return RandomNumber(0, 9);
    case enDiffcultyLevel::Medium:
        return RandomNumber(10, 99);
    case enDiffcultyLevel::Hard:
        return RandomNumber(100, 999);
    case enDiffcultyLevel::Mixx:
        return RandomNumber(0, 999);
    default:
        return RandomNumber(0, 0);
    }
}

void ReadNumbers(stGameInfo &Info)
{
    Info.Number1 = NumbersDifficculty(Info);
    Info.Number2 = NumbersDifficculty(Info);
}

float OperationResult(stGameInfo Info)
{
    switch (Info.OperationType)
    {
    case enOperationType::Add:
        return Info.Number1 + Info.Number2;
    case enOperationType::Subtract:
        return Info.Number1 - Info.Number2;
    case enOperationType::Multiply:
        return Info.Number1 * Info.Number2;
    case enOperationType::Devide:
        return Info.Number1 / Info.Number2;
    default:
        return 0;
        break;
    }
}

void OperationPrint(stGameInfo Info)
{
    cout << endl;
    switch (Info.OperationType)
    {
    case enOperationType::Add:
        cout << Info.Number1 << "\n";
        cout << Info.Number2 << " + ";
        break;
    case enOperationType::Subtract:
        cout << Info.Number1 << "\n";
        cout << Info.Number2 << " - ";
        break;
    case enOperationType::Multiply:;
        cout << Info.Number1 << "\n";
        cout << Info.Number2 << " * ";
        break;
    case enOperationType::Devide:
        cout << Info.Number1 << "\n";
        cout << Info.Number2 << " / ";
        break;
    default:
        cout << "\nOperationPrint EROOOOOOOOOOOOOOOOOOOOR\n";
        break;
    }
    cout << "\n__________\n";
}

void PrintCorrectOrWrong(short Number, short Result)
{
    if (Number == Result)
    {
        cout << "Right answer :-)\n";
    }
    else
    {
        cout << "Wrong answer :-(\n";
        cout << "The right answer is: " << Result << "\n";
    }
}

string FinalResult(stGameInfo Info)
{
    if (Info.RightTimes > Info.WrongTimes)
    {
        return "Success :-)";
    }
    else if (Info.RightTimes < Info.WrongTimes)
    {
        return "Fail :-(";
    }
    else
    {
        return "Draw";
    }
}

string PrintDiffcultyLevel(stGameInfo Info)
{
    switch (Info.DiffcultyLevel)
    {
    case enDiffcultyLevel::Hard:
        return "Hard";
    case enDiffcultyLevel::Medium:
        return "Medium";
    case enDiffcultyLevel::Easy:
        return "Easy";
    case enDiffcultyLevel::Mixx:
        return "Mix";
    default:
        return "\nPrintDiffcultyLevel EROOOOOOR\n";
    }
}

string PrintOperationType(stGameInfo Info)
{
    switch (Info.OperationType)
    {
    case enOperationType::Add:
        return "Addition";
    case enOperationType::Subtract:
        return "Subtraction";
    case enOperationType::Multiply:
        return "Multiplication";
    case enOperationType::Devide:
        return "Devide";
    case enOperationType::Mix:
        return "Mix";
    default:
        return "\nPrintOperationType EROOOOOOR\n";
    }
}

void PrintFinalCard(stGameInfo Info)
{
    cout << "\n_______________________\n";
    cout << "Final result is " << Info.FinalResult;
    cout << "\n_______________________\n";
    cout << "Number of questions : " << Info.Rounds;
    cout << "\nQuestions level : " << PrintDiffcultyLevel(Info);
    cout << "\nOperation type : " << PrintOperationType(Info);
    cout << "\nNumber of right answers: " << Info.RightTimes;
    cout << "\nNumber of wrong answers: " << Info.WrongTimes;
    cout << "\n_______________________\n";
}

void GamePlay(stGameInfo Info, short &CorrectTimes, short &WrongTimes)
{
    float Number = 0;
    short X = 0;
    CorrectTimes = 0, WrongTimes = 0;

    for (short i = 1; i <= Info.Rounds; i++)
    {
        ReadNumbers(Info);
        if (Info.OperationType == enOperationType::Mix || X >= 1)
        {
            X++;
            Info.OperationType = ReadRandomOperationType();
        }
        OperationPrint(Info);
        cin >> Number;
        PrintCorrectOrWrong(Number, OperationResult(Info));
        if (Number == OperationResult(Info))
        {
            CorrectTimes++;
        }
        else
        {
            WrongTimes++;
        }
    }
}

void StartGame(stGameInfo Info)
{
    char Again = 'Y';

    do
    {
        system("clear");
        Info.Rounds = ReadRounds("Please enter how many questions you want to answer (1 to 100) ");
        Info.DiffcultyLevel = ReadDiffcultyLevel("Please enter question level [1]: Easy, [2]: Medium, [3]: Hard, [4]: Mix  ");
        Info.OperationType = ReadOperationType("Please enter operation type [1]: Add, [2]: Subtract, [3]: Multiply, [4]: Devide, [5]: Mix  ");
        short CorrectTimes = 0, WrongTimes = 0;
        GamePlay(Info, CorrectTimes, WrongTimes);
        Info.RightTimes = CorrectTimes;
        Info.WrongTimes = WrongTimes;
        Info.FinalResult = FinalResult(Info);
        PrintFinalCard(Info);
        cout << "\nDo you want to play again? Y/n? ";
        cin >> Again;
    } while (Again == 'Y' || Again == 'y');
}

int main()
{

    srand((unsigned)time(NULL));

    stGameInfo Info;
    StartGame(Info);

    return 0;
}
