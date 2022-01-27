/******************************************************************
*
* ToyRobotConsoleMain.cpp : implementation file
*
* $Workfile:: ToyRobotConsoleMain.cpp
*
* $Revision:: 1
*
* $Date: 1/27/2022
*
* ****************************************************************
*
* $History:: ToyRobotConsoleMain.cpp
*
* *************** Version 1 ***************
* User: Lester Magtagad    Date: 1/27/2022    Time: 6:00p
* Created in $..\..\..\..\src\ToyRobotConsoleMain.cpp
* Initial version
*
******************************************************************/

#include <iostream>
#include <exception>
#include <algorithm>
#include "CToyRobotConsole.h"

const std::string strConstFacing[] = { "NORTH",
                                      "SOUTH",
                                      "EAST",
                                      "WEST" };

/*
* Parse the place command given by the user
*
* @param strInputParam
*   String input command
*
* @param chDelim
*   Delimeter
*
* @return
*   returns a vector
*/
std::vector<std::string> ProcessParamData(std::string strInputParam, char chDelim)
{
    std::string strContainer;
    std::vector<std::string> v_strParsed;
    //char chDelim = ' ';

    // Using string stream for parsing the place parameter
    std::stringstream sstream(strInputParam);

    while (std::getline(sstream, strContainer, chDelim))
    {
        v_strParsed.push_back(strContainer);
    }

    return v_strParsed;
}

/*
* Parse the facing parameter given by the user
*
* @param strTmpFacing
*   Facing command
*
* @return
*   returns true if facing is found, otherwise false
*/
bool ProcessFacingParam(std::string strTmpFacing)
{
    int nCtr = 0;
    bool bRet = false;

    for (int i = 0; i < FSIZE; i++)
    {
        if (strConstFacing[i] == strTmpFacing)
            nCtr++;

        if (nCtr == 1)
        {
            bRet = true;
            break;
        }
    }

    return bRet;
}

/*
* Uppercase all string inputs
*
* @param strCon
*   Identify the string input
*
*/
void UpperCaseCommand(std::string& strCon)
{
    std::string strConverted;

    std::transform(strCon.begin(), strCon.end(), strCon.begin(), ::toupper);
}

/*
* Main function starts here
*
*/
int main()
{
    int xPos = 0;
    int yPos = 0;
    int nXmaxVal = XMAX_SIZE;
    int nYmaxVal = YMAX_SIZE;

    std::string strFacing;
    std::string strCommand;
    std::string strInputParam;

    std::vector<std::string> v_strInitParam, v_strPlaceParam;

    std::cout << "Toy Robot Challenge" << std::endl;

    CToyRobot* pToyRobot = new CToyRobot();

    while (strInputParam != "exit")
    {
        std::getline(std::cin, strInputParam);

        v_strInitParam = ProcessParamData(strInputParam, ' ');

        if (v_strInitParam.size() != 2)
        {
            std::cout << "WARNING: Input parameter is invalid, please retry...\n";
            continue;
        }

        // Uppercase the place command
        std::string strCommUpper = v_strInitParam.at(0);
        UpperCaseCommand(strCommUpper);

        if (PLACE != strCommUpper)
        {
            std::cout << "WARNING: PLACE command will be accepted first...\n";
            continue;
        }

        strCommand = v_strInitParam.at(0);

        v_strPlaceParam = ProcessParamData(v_strInitParam[1], ',');

        if (v_strPlaceParam.size() != 3)
        {
            std::cout << "WARNING: PLACE parameter is invalid, please retry...\n";
            continue;
        }

        try
        {
            xPos = std::stoi(v_strPlaceParam.at(0));
            yPos = std::stoi(v_strPlaceParam.at(1));

            // Store facing and make it uppercase then process it
            strFacing = v_strPlaceParam.at(2);
            UpperCaseCommand(strFacing);
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;;
        }
        // End of PLACE command validation

        if (!ProcessFacingParam(strFacing))
        {
            std::cout << "WARNING: Facing input is invalid, ignored...\n";
            continue;
        }

        // Place the robot after the validation
        if (pToyRobot->PlaceRobot(xPos, yPos, nXmaxVal, nYmaxVal, strFacing) != true)
        {
            std::cout << "WARNING: Placement of robot is invalid, ignored...\n";
            continue;
        }

        std::string strCommMovement;

        // This is another while loop for the remaining commands
        // When you invoke the report command it will go back from
        // the start which the program will be asking a new place command
        while (strCommMovement != "REPORT")
        {
            std::getline(std::cin, strCommMovement);

            UpperCaseCommand(strCommMovement);

            if (REPORT == strCommMovement)
            {
                std::cout << "Output: " << pToyRobot->Report() << std::endl;
            }
            else if (MOVE == strCommMovement)
            {
                if (pToyRobot->MoveRobot() != NO_ERR)
                {
                    continue;
                }
            }
            else if (LEFT == strCommMovement)
            {
                if (pToyRobot->RotateLeft() != NO_ERR)
                {
                    continue;
                }
            }
            else if (RIGHT == strCommMovement)
            {
                if (pToyRobot->RotateRight() != NO_ERR)
                {
                    continue;
                }
            }
            else
            {
                std::cout << "WARNING: Invalid movements, ignored...\n";
            }
        }
    }

    return 0;
}

