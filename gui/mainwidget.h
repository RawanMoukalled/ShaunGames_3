#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>

/**
* \file mainwidget.h
* \brief MainWidget class
*
* This is the main sign in window, where the user is given the chance to go on as a guest or to login/sign up.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit MainWidget(QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~MainWidget();

signals:

public slots:
    /**
    * \brief Slot that closes widget and opens the game selection menu
    */
    void goToGameSelection();


private:
    QPushButton *m_guestSignIn;  ///< Button for signing in as guest
    QPushButton *m_signIn; ///< Button for signing in for existing users
    QPushButton *m_signUp; ///< Button for signing up for new users

    QLineEdit *m_existingUsernameEdit; ///< Edit field for log in username input
    QLabel *m_existingUsernameLabel; ///< Label for log in username input
    QLineEdit *m_existingPasswordEdit; ///< Edit field for log in password input
    QLabel *m_existingPasswordLabel; ///< Label for log in password input

    QLineEdit *m_firstNameEdit; ///< Edit field for sign up first name input
    QLabel *m_firstNameLabel; ///< Label for sign up first name input
    QLineEdit *m_lastNameEdit; ///< Edit field for sign up last name input
    QLabel *m_lastNameLabel; ///< Label for sign up last name input
    QLineEdit *m_usernameEdit; ///< Edit field for sign up username input
    QLabel *m_usernameLabel; ///< Label for sign up username input
    QLineEdit *m_passwordEdit; ///< Edit field for sign up password input
    QLabel *m_passwordLabel; ///< Label for sign up password input

    QVBoxLayout *m_mainLayout; ///< Layout of the whole page
    QHBoxLayout *m_userLayout; ///< Layout of the sign in and sign up boxes
    QGridLayout *m_signInLayout; ///< Layout of the sign in box
    QGridLayout *m_signUpLayout; ///< Layout of the sign up box

    /**
    * \brief Sets the sign in box layout
    */
    void setSignInLayout();

    /**
    * \brief Sets the sign up box layout
    */
    void setSignUpLayout();

    /**
    * \brief Sets the sign in and sign up boxes layout
    */
    void setUserLayout();

    /**
    * \brief Sets the main layout of the scene
    */
    void setMainLayout();

    /**
    * \brief Sets the connections for the widget
    */
    void setConnections();
};

#endif // MAINWIDGET_H
