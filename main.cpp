// Math Game Project.

#include <asm-generic/errno.h>
#include <iostream>
#include <cstdlib>
using namespace std;

enum enLevelChoices { Easy=1, Med=2, Hard=3, MixLevels=4 };
enum enOperationChoices { Add=1, Sub=2, Mul=3, Dev=4, MixTypes=5 };

enum enLevels { EasyLevel=1, MedLevel=2, HardLevel=3 };
enum enOperationTypes { Addition=1, Subtraction=2, Multiplication=3, Division=4 };

enum enRightOrWrong { Right, Wrong };
enum enPassOrFail { Pass, Fail };

struct stQuetionInfo
{
    int firstNumber = 0;
    int secondNumber = 0;

    enLevels Level;
    enOperationTypes operationType;

    float quetionAnswer = 0;
    float userAnswer = 0;

    enRightOrWrong rightOrWrong;
};

struct stGameResults
{
    int numberOfQuetions = 0;

    enLevelChoices levelChoice;
    enOperationChoices operationChoice;
    enPassOrFail passOrFail;

    int rightAnswers = 0;
    int wrongAnswers = 0;
};

int ReadNumberInRange(int from, int to, const string &messege)
{
    int userInput = 0;

    do {

        cout << messege;
        cin >> userInput;

    } while ( userInput < from || userInput > to );

    return userInput;
}

float ReadUserAnswer()
{
    float userInput;
    cin >> userInput;
    return userInput;
}

enLevelChoices ReadLevelChoice()
{
    int level = ReadNumberInRange(1, 4, "Enter quetion level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ");

    return (enLevelChoices) level;
}

enOperationChoices ReadOperationChoice()
{
    int operationChoice = ReadNumberInRange(1, 5, "Enter operation type [1] Add, [2] Sub, [3] mul, [4] Dev, [5] Mix ? ");

    return (enOperationChoices) operationChoice ;
}

int RandomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

enLevels GetLevel( enLevelChoices levelChoice )
{
    enLevels level;

    if (levelChoice == enLevelChoices::MixLevels)
    {
        levelChoice = (enLevelChoices) RandomNumber(1, 3);
    }

    switch (levelChoice) 
    {
        case enLevelChoices::Easy:
            level = enLevels::EasyLevel;
            break;

        case enLevelChoices:: Med:
            level = enLevels::MedLevel;
            break;

        case enLevelChoices::Hard:
            level = enLevels::HardLevel;
            break;

        default:
            break;
    }

    return level;
}

enOperationTypes GetOperationType(enOperationChoices operationChoice)
{
    enOperationTypes operationTypes;

    if (operationChoice == enOperationChoices::MixTypes)
    {
        operationChoice = (enOperationChoices) RandomNumber(1, 4);
    }

    switch (operationChoice)
    {
        case enOperationChoices::Add:
            operationTypes = enOperationTypes::Addition;
            break;

        case enOperationChoices::Sub:
            operationTypes = enOperationTypes::Subtraction;
            break;

        case enOperationChoices::Mul:
            operationTypes = enOperationTypes::Multiplication;
            break;

        case enOperationChoices::Dev:
            operationTypes =  enOperationTypes::Division;
            break;

        default:
            break;
    }

    return operationTypes;
}

int GetNumBasedOnLevel(enLevels level)
{
    int number;

    switch (level)
    {
        case enLevels::EasyLevel:
            number = RandomNumber(1, 10);
            break;

        case enLevels::MedLevel:
            number = RandomNumber(11, 50);
            break;

        case enLevels::HardLevel:
            number = RandomNumber(51,100);
            break;
    }

    return number;
}

void PrintOperation(stQuetionInfo quetionInfo)
{
    cout << quetionInfo.firstNumber << endl;
    cout << quetionInfo.secondNumber << endl;
    cout << "_____ ";

    switch (quetionInfo.operationType)
    {
        case enOperationTypes::Addition:
            cout << '+' << endl;
            break;

        case enOperationTypes::Subtraction:
            cout << '-' << endl;
            break;

        case enOperationTypes::Multiplication:
            cout << 'X' << endl;
            break;

        case enOperationTypes::Division:
            cout << '/' << endl;
            break;
    }
}

float GetQuetionAnswer(stQuetionInfo quetionInfo)
{
    float quetionAnswer;

    switch (quetionInfo.operationType)
    {
        case enOperationTypes::Addition:
            quetionAnswer = quetionInfo.firstNumber + quetionInfo.secondNumber;
            break;

        case enOperationTypes:: Subtraction:
            quetionAnswer = quetionInfo.firstNumber - quetionInfo.secondNumber;
            break;

        case enOperationTypes::Multiplication:
            quetionAnswer = quetionInfo.firstNumber * quetionInfo.secondNumber;
            break;

        case enOperationTypes:: Division:
            quetionAnswer = (float) quetionInfo.firstNumber / quetionInfo.secondNumber;
            break;
    }

    return quetionAnswer;
}

enRightOrWrong CheckUserAswer(stQuetionInfo quetionInfo)
{
    if ( quetionInfo.userAnswer == quetionInfo.quetionAnswer)
    {
        return enRightOrWrong::Right;
    }

    else {
        return enRightOrWrong::Wrong;
    }
}

void PrintQuetionResult(enRightOrWrong rightOrWrong)
{
    switch (rightOrWrong)
    {
        case enRightOrWrong::Right:
            cout << "\033[42mRight answer :-)" << endl;
            break;

        case enRightOrWrong::Wrong:
            cout << "\033[41mWrong answer :-(" << endl;
            break;
    }
    
    cout << "\033[0m";
}

void StartTheGame( stQuetionInfo &quetionInfo, stGameResults &gameResults)
{
    gameResults.numberOfQuetions = ReadNumberInRange(1, 100, "Enter how many quetion do you want to  answer (Max 100): ");
    gameResults.levelChoice = ReadLevelChoice();
    gameResults.operationChoice = ReadOperationChoice();

    for (int counter=1; counter <= gameResults.numberOfQuetions; counter++)
    {
        quetionInfo.Level = GetLevel(gameResults.levelChoice);
        quetionInfo.firstNumber = GetNumBasedOnLevel(quetionInfo.Level);
        quetionInfo.secondNumber = GetNumBasedOnLevel(quetionInfo.Level);
        quetionInfo.operationType = GetOperationType(gameResults.operationChoice);

        PrintOperation(quetionInfo);    

        quetionInfo.quetionAnswer = GetQuetionAnswer(quetionInfo);
        quetionInfo.userAnswer = ReadUserAnswer();

        quetionInfo.rightOrWrong = CheckUserAswer(quetionInfo);

        PrintQuetionResult(quetionInfo.rightOrWrong);

        switch (quetionInfo.rightOrWrong)
        {
            case enRightOrWrong::Right:
                gameResults.rightAnswers ++;
                break;

            case enRightOrWrong::Wrong:
                gameResults.wrongAnswers ++;
                break;
        }
    }
}

enPassOrFail GetPassOrFail(stGameResults gameResults)
{
    cout << endl;
    cout << gameResults.rightAnswers << endl;
    cout << gameResults.wrongAnswers << endl;
    if ( gameResults.rightAnswers >= gameResults.wrongAnswers )
    {
        return enPassOrFail::Pass;
    }

    else {
        return enPassOrFail::Fail;
    }
}

void PrintPassFailBar(enPassOrFail passOrFail)
{
    if (passOrFail == enPassOrFail::Pass)
    {
        cout << "\033[42m----------------------------------" << endl;
        cout << "        Final result is Pass :-) " << endl;
        cout << "----------------------------------" << endl;
    }

    else {
        cout << "\033[41m----------------------------------" << endl;
        cout << "        Final result is Fail :-( " << endl;
        cout << "----------------------------------" << endl;
    }
}

string GetLevelName(enLevelChoices level)
{
    switch (level)
    {
        case enLevelChoices::Easy:
            return "Easy";
            
        case enLevelChoices::Med:
            return "Med";

        case enLevelChoices::Hard:
            return "Hard";

        case enLevelChoices::MixLevels:
            return "Mix";
    }
}

string GetOperationascii(enOperationChoices operationChoice)
{
    switch (operationChoice)
    {
        case enOperationChoices::Add:
            return "+";

        case enOperationChoices::Sub:
            return "-";

        case enOperationChoices::Mul:
            return "x";

        case enOperationChoices::Dev:
            return "/";

        case enOperationChoices::MixTypes:
            return "Mix";
    }
}

void PrintGameResults(stGameResults gameResults)
{
    PrintPassFailBar(gameResults.passOrFail);

    cout << "\n Number of quetions : " << gameResults.numberOfQuetions << endl;
    cout << " Quetion level        : " << GetLevelName(gameResults.levelChoice) << endl;
    cout << " Operation Type       : " << GetOperationascii(gameResults.operationChoice) << endl;
    cout << " Number of right answers: " << gameResults.rightAnswers << endl;
    cout << " Number of wrong answers: " << gameResults.wrongAnswers << endl;
    cout << "----------------------------------" << endl;
}

void RestorScreen()
{
    cout << "\033[0m";
    system("clear");
}

void PlayGame()
{
    char playGame = 'Y';

    do {

        RestorScreen();

        stQuetionInfo quetionInfo;
        stGameResults gameResults;

        StartTheGame(quetionInfo, gameResults);

        gameResults.passOrFail = GetPassOrFail(gameResults);

        PrintGameResults(gameResults);

        cout << "\n Do want to play again? (Y/N): ";
        cin >> playGame;

    } while (playGame == 'Y' || playGame == 'y');
}

int main()
{
    srand((unsigned) time (NULL));
    
    PlayGame();

    return 0;
}
