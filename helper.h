#ifndef HELPER_H
#define HELPER_H

#include <QWidget>
#include <QFont>

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
    * \brief Makes given widget small.
    */
    static void makeWidgetSmall(QWidget *widget);

    /**
    * \brief Makes given widget large.
    */
    static void makeWidgetLarge(QWidget *widget);

private:
    static QFont m_smallFont; ///< 12-pt font
    static QFont m_largeFont; ///< 18-pt font
    static bool m_uninitialized; ///< Boolean value that keeps track of whether helper values have been initialized

    /**
    * \brief Initializes class attributes
    **/
    static void initialize();
};

#endif // HELPER_H