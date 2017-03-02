#include "mainwidget.h"
#include "gameselection.h"
/**
* \file mainwidget.cpp
* \brief Contains MainWidget class definition
*/

/**
* Initializes all buttons, input fields and labels and shows them on the screen.
*/
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    m_guestSignIn = new QPushButton("Proceed as Guest");
    m_signIn = new QPushButton("Sign In");
    m_signUp = new QPushButton("Sign up");

    m_existingUsernameEdit = new QLineEdit;
    m_existingUsernameLabel = new QLabel("Username");
    m_existingPasswordEdit = new QLineEdit;
    m_existingPasswordLabel = new QLabel("Password");

    m_firstNameEdit = new QLineEdit;
    m_firstNameLabel = new QLabel("First Name");
    m_lastNameEdit = new QLineEdit;
    m_lastNameLabel = new QLabel("Last Name");
    m_usernameEdit = new QLineEdit;
    m_usernameLabel = new QLabel("Username");
    m_passwordEdit = new QLineEdit;
    m_passwordLabel = new QLabel("Password");

    m_existingPasswordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    m_mainLayout = new QVBoxLayout;
    m_userLayout = new QHBoxLayout;
    m_signInLayout = new QGridLayout;
    m_signUpLayout = new QGridLayout;

    setMainLayout();
    setLayout(m_mainLayout);

    setConnections();
}

/**
* Adds the username and password fields to the sign in layout.
*/
void MainWidget::setSignInLayout() {
    m_signInLayout->addWidget(m_existingUsernameLabel,0,0);
    m_signInLayout->addWidget(m_existingUsernameEdit,0,1);
    m_signInLayout->addWidget(m_existingPasswordLabel,1,0);
    m_signInLayout->addWidget(m_existingPasswordEdit,1,1);
    m_signInLayout->addWidget(m_signIn,2,0,1,2);
}

/**
* Adds the first name, last name, username and password fields to the sign in layout.
*/
void MainWidget::setSignUpLayout() {
    m_signUpLayout->addWidget(m_firstNameLabel,0,0);
    m_signUpLayout->addWidget(m_firstNameEdit,0,1);
    m_signUpLayout->addWidget(m_lastNameLabel,1,0);
    m_signUpLayout->addWidget(m_lastNameEdit,1,1);
    m_signUpLayout->addWidget(m_usernameLabel,2,0);
    m_signUpLayout->addWidget(m_usernameEdit,2,1);
    m_signUpLayout->addWidget(m_passwordLabel,3,0);
    m_signUpLayout->addWidget(m_passwordEdit,3,1);
    m_signUpLayout->addWidget(m_signUp,4,0,1,2);
}

/**
* Adds the sign in and sign up layouts to the user layout.
*/
void MainWidget::setUserLayout() {
    setSignInLayout();
    setSignUpLayout();
    m_userLayout->addItem(m_signInLayout);
    m_userLayout->addItem(new QSpacerItem(50,10));
    m_userLayout->addItem(m_signUpLayout);
}

/**
* Adds the user layout annd the guest button to the main layout.
*/
void MainWidget::setMainLayout() {
    setUserLayout();
    m_mainLayout->addItem(m_userLayout);
    m_mainLayout->addWidget(m_guestSignIn);
}

void MainWidget::goToGameSelection() {
    GameSelection *selection = new GameSelection;
    selection->show();
    close();
}

void MainWidget::setConnections() {
    QObject::connect(m_signIn, SIGNAL(clicked()), SLOT(goToGameSelection()));
    QObject::connect(m_signUp, SIGNAL(clicked()), SLOT(goToGameSelection()));
    QObject::connect(m_guestSignIn, SIGNAL(clicked()), SLOT(goToGameSelection()));
}
