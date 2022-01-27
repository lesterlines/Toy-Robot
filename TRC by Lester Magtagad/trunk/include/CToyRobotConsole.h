/******************************************************************
*
* CToyRobotConsole.h : header file
*
* $Workfile:: CToyRobotConsole.h
*
* $Revision:: 1
*
* $Date: 1/27/2022
*
* ****************************************************************
*
* $History:: CToyRobotConsole.h
*
* *************** Version 1 ***************
* User: Lester Magtagad    Date: 1/27/2022    Time: 6:00p
* Created in $..\..\..\..\src\CToyRobotConsole.h
* Initial version
*
******************************************************************/
#ifndef CTOYROBOTCONSOLE_H
#define CTOYROBOTCONSOLE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Defines.h"

class CToyRobot
{
public:
    CToyRobot();
    ~CToyRobot();
    bool PlaceRobot(int nX, int nY, int nXmax, int nYmax, std::string strFacing);
    int MoveRobot();
    int RotateLeft();
    int RotateRight();
    std::string Report();
    void ParseCommands(std::vector<std::string>& vec);
    void ShowErrorMessage(int nErrorCode);

private:
    int m_nXPosition;
    int m_nYPosition;
    int m_nXMaxVal;
    int m_nYMaxVal;
    std::string m_strFacing;

    std::string GetState();
    void SetState(int nX, int nY, std::string strFacing);
};

#endif //CTOYROBOTCONSOLE_H

