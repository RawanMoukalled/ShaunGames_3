#ifndef HELPER_H
#define HELPER_H

#include <QtGui>
#include <QSqlDatabase>

/**
* \file helper.h
* \brief Helper class
*
* This class provides various helper functions that are needed across windows.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Helper
{
public:
    /**
    * \brief Makes given widget small
    * \param widget Widget whose size to change
    */
    static void makeWidgetSmall(QWidget *widget);

    /**
    * \brief Makes given widget large
    * \param widget Widget whose size to change
    */
    static void makeWidgetLarge(QWidget *widget);

    static const double PI; ///< PI

    /**
    * \brief Takes an angle in degrees, turns it into radians
    * \param degrees Angle in degrees
    * \returns Angle in radians
    */
    static double toRadians(double degrees);

    /**
    * \brief Retrieves the user ID
    * \returns The user ID
    */
    static int getUserId();

    /**
    * \brief Sets the user ID
    * \param id The user ID
    */
    static void setUserId(int id);

    /**
    * \brief Initializes class attributes
    **/
    static void initialize();

    static QSqlDatabase shaunDB; ///< The database for the game

private:
    static bool m_uninitialized; ///< Keeps track of whether the helper has been initialized
    static QFont m_smallFont; ///< 12-pt font
    static QFont m_largeFont; ///< 18-pt font
    static int m_userId; ///< The account id
};

#endif // HELPER_H
