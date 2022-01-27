/******************************************************************
*
* CToyRobotConsole.cpp : implementation file
*
* $Workfile:: CToyRobotConsole.cpp
*
* $Revision:: 1
*
* $Date: 1/27/2022
*
* ****************************************************************
*
* $History:: CToyRobotConsole.cpp
*
* *************** Version 1 ***************
* User: Lester Magtagad    Date: 1/27/2022    Time: 6:00p
* Created in $..\..\..\..\src\CToyRobotConsole.cpp
* Initial version
*
******************************************************************/

#include "CToyRobotConsole.h"

/*
* Constructor
*    Initializes member variables
*
*/
CToyRobot::CToyRobot()
{
    m_nXPosition = 0;
    m_nYPosition = 0;
    m_strFacing = "NORTH";
}

/*
* Destructor
*
*/
CToyRobot::~CToyRobot()
{
    // Nothing to do with destructor yet
}

/*
* Sets of error messages
*
* @param nErrorCode
*   Error code
*
*/
void CToyRobot::ShowErrorMessage(int nErrorCode)
{
    switch (nErrorCode)
    {
    case ERROR_1:
        std::cout << "ERROR: Invalid input/commands\n";
        break;

    case ERROR_2:
        std::cout << "ERROR: Facing string is invalid...\n";
        break;

    case ERROR_3:
        std::cout << "ERROR: Vector size is less than expected...\n";
        break;

    case ERROR_4:
        std::cout << "WARNING: Robot will fall facing NORTH, movement ignored...\n";
        break;

    case ERROR_5:
        std::cout << "WARNING: Robot will fall facing EAST, movement ignored...\n";
        break;

    case ERROR_6:
        std::cout << "WARNING: Robot will fall facing SOUTH, movement ignored...\n";
        break;

    case ERROR_7:
        std::cout << "WARNING: Robot will fall facing WEST, movement ignored...\n";
        break;

    case ERROR_8:
        std::cout << "ERROR: Invalid placement...\n";
        break;

    default:
        std::cout << "Other errors...\n";
        break;
    }
}

/*
* Parse the place command given by the user
*
* @param nX
*   placement x axis
*
* @param nY
*   placement y axis
*
* @param nXmax
*   maximum x-axis value
*
* @param nYmax
*   maximum y-axis value
*
* @param strFacing
*   initial facing of the robot
*
* @return
*   returns true if robot will not fall off, otherwise false
*/
bool CToyRobot::PlaceRobot(int nX, int nY, int nXmax, int nYmax, std::string strFacing)
{

    m_nXMaxVal = nXmax;
    m_nYMaxVal = nYmax;

    // Robot must not fall off
    if ((nX >= XMIN_SIZE && nX <= m_nXMaxVal) && (nY >= YMIN_SIZE && nY <= m_nYMaxVal))
    {
        m_nXPosition = nX;
        m_nYPosition = nY;
        m_strFacing = strFacing;
    }
    else
    {
        return false;
    }

    return true;
}

/*
* Moves the robot from its current state to
* another point unit
*
* @return
*   returns specific error codes
*/
int CToyRobot::MoveRobot()
{
    int nXpos, nYpos;
    std::string strFacing;

    std::vector<std::string> v_strParsed;

    ParseCommands(v_strParsed);

    // Check the vector size, size must be equal to 3
    if (v_strParsed.size() != 3)
    {
        ShowErrorMessage(ERROR_3);
        return ERROR_3;
    }

    // Store each element to their respective containers
    // for readability purposes
    nXpos = std::stoi(v_strParsed.at(0));
    nYpos = std::stoi(v_strParsed.at(1));
    strFacing = v_strParsed.at(2);

    // This condition sequence is to check if the robot
    // will fall off the table. The conditional heirarchy
    // is Facing first and then the XY positions. Determine
    // the facing of the robot and increment/decrement the X/Y
    // position if the robot will remain on the table. Otherwise,
    // revert back the position and show a warning message that
    // the movement is ignored.
    if (NORTH == strFacing)
    {
        nYpos++;

        if (nYpos > m_nYMaxVal)
        {
            nYpos--;
            ShowErrorMessage(ERROR_4);
        }
    }
    else if (EAST == strFacing)
    {
        nXpos++;

        if (nXpos > m_nXMaxVal)
        {
            nXpos--;
            ShowErrorMessage(ERROR_5);
        }
    }
    else if (SOUTH == strFacing)
    {
        nYpos--;

        if (nYpos < YMIN_SIZE)
        {
            nYpos++;
            ShowErrorMessage(ERROR_6);
        }
    }
    else if (WEST == strFacing)
    {
        nXpos--;

        if (nXpos < XMIN_SIZE)
        {
            nXpos++;
            ShowErrorMessage(ERROR_7);
        }
    }
    else
    {
        ShowErrorMessage(ERROR_2);
    }

    // Always update the state if there is movement or not
    SetState(nXpos, nYpos, strFacing);

    return NO_ERR;
}

/*
* Rotate the robot 90 degrees left
*
* @return
*   returns specific error codes
*/
int CToyRobot::RotateLeft()
{
    if (NORTH == m_strFacing)
        m_strFacing = WEST;
    else if (EAST == m_strFacing)
        m_strFacing = NORTH;
    else if (WEST == m_strFacing)
        m_strFacing = SOUTH;
    else if (SOUTH == m_strFacing)
        m_strFacing = EAST;
    else
    {
        ShowErrorMessage(ERROR_2);
        return ERROR_2;
    }

    // Update the state after changing the facing
    SetState(m_nXPosition, m_nYPosition, m_strFacing);

    return NO_ERR;
}

/*
* Rotate the robot 90 degrees right
*
* @return
*   returns specific error codes
*/
int CToyRobot::RotateRight()
{
    if (NORTH == m_strFacing)
        m_strFacing = EAST;
    else if (EAST == m_strFacing)
        m_strFacing = SOUTH;
    else if (WEST == m_strFacing)
        m_strFacing = NORTH;
    else if (SOUTH == m_strFacing)
        m_strFacing = WEST;
    else
    {
        ShowErrorMessage(ERROR_2);
        return ERROR_2;
    }

    // Update the state after changing the facing
    SetState(m_nXPosition, m_nYPosition, m_strFacing);

    return NO_ERR;
}

/*
* Sets the new state of the robot
*
* @param nX
*   New state x coordinate
*
* @param nY
*   New state y coordinate
*
* @param strFacing
*   New state facing
*
*/
void CToyRobot::SetState(int nX, int nY, std::string strFacing)
{
    m_nXPosition = nX;
    m_nYPosition = nY;
    m_strFacing = strFacing;
}

/*
* Gets the current state of the robot
*
* @return
*   return a string with X,Y,F information
*/
std::string CToyRobot::GetState()
{
    return (std::to_string(m_nXPosition) + "," + std::to_string(m_nYPosition) + "," + m_strFacing);
}

/*
* Function wrapper of GetState as an interface
*
* @return
*   returns a GetState() method
*/
std::string CToyRobot::Report()
{
    return GetState();
}

/*
* Parse the given string on the current state of the robot
*
* @param &v_strParsed
*   Reference vector of string to parse each command
*
*/
void CToyRobot::ParseCommands(std::vector<std::string>& v_strParsed)
{
    std::string strState;
    std::string strContainer;

    //std::vector<std::string> v_strParsed;

    // This is optional, make only the capacity by 3
    v_strParsed.reserve(3);

    // Store the current state of the robot
    strState = GetState();

    char chDelim = ',';

    // Using string stream for parsing the string state command
    std::stringstream sstream(strState);

    while (std::getline(sstream, strContainer, chDelim))
    {
        v_strParsed.push_back(strContainer);
    }

    // Test output vector size
    //std::cout << "VECTOR SIZE: " << v_strParsed.size() << std::endl;

    // Checker if the string correctly parsed, comment out when not needed
    /*for (const auto& v_check : v_strParsed)
    {
        std::cout << v_check << std::endl;
    }*/
}

