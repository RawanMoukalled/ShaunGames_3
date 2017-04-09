#include "gui/mainwidget.h"
#include "gui/gameselection.h"
#include "helper.h"
#include <QSqlQuery>
#include <QSqlError>

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
    Helper::initialize();

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
* Frees allocated memory.
*/
MainWidget::~MainWidget() {
    delete m_guestSignIn;
    delete m_signIn;
    delete m_signUp;
    delete m_existingUsernameEdit;
    delete m_existingUsernameLabel;
    delete m_existingPasswordEdit;
    delete m_existingPasswordLabel;
    delete m_firstNameEdit;
    delete m_firstNameLabel;
    delete m_lastNameEdit;
    delete m_lastNameLabel;
    delete m_usernameEdit;
    delete m_usernameLabel;
    delete m_passwordEdit;
    delete m_passwordLabel;
    delete m_mainLayout;
    delete m_userLayout;
    delete m_signInLayout;
    delete m_signUpLayout;

    for (QVector<QSpacerItem*>::iterator sp=m_spacerItems.begin(); sp!=m_spacerItems.end(); ++sp) {
        delete *sp;
    }
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

    QSpacerItem *sp = new QSpacerItem(50,10);
    m_spacerItems.push_back(sp);
    m_userLayout->addItem(sp);
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

/**
* Goes to Game Selection menu.
*/
void MainWidget::goToGameSelection() {
    GameSelection *selection = new GameSelection;
    selection->show();
    close();
}

/**
* Signs in by retrieving the account with the given username and password
*/
void MainWidget::signIn() {
    QString username = m_existingUsernameEdit->text();
    QString password = m_existingPasswordEdit->text();

    if(!username.isEmpty() && !password.isEmpty()) {
        bool opened = Helper::shaunDB.open();
        QSqlQuery query;
        if(opened) {
            query.exec("SELECT ID FROM ACCOUNT WHERE USERNAME='"+username+"' AND PASSWORD='"+password+"'");
            query.next();
            if(query.isValid()) {
                Helper::setUserId(query.value(0).toInt());
                goToGameSelection();
            } else {
                QMessageBox::information(0,"Alert", "Wrong username/password combination.");
            }
        }
        Helper::shaunDB.close();
    }
    else {
        QMessageBox::information(0,"Alert", "Please enter all fields.");
    }
}

/**
* Signs up by adding an entry to the database
*/
void MainWidget::signUp() {
    QString firstname = m_firstNameEdit->text();
    QString lastname = m_lastNameEdit->text();
    QString username = m_usernameEdit->text();
    QString password = m_passwordEdit->text();

    if(!firstname.isEmpty() && !lastname.isEmpty() && !username.isEmpty() && !password.isEmpty()) {
        bool opened = Helper::shaunDB.open();
        QSqlQuery query;
        if(opened) {
            query.exec("SELECT COUNT(*) FROM ACCOUNT WHERE USERNAME='" + username +"'");
            query.next();
            //check if username already exists
            if (query.value(0).toInt() <= 0) {
                query.prepare("INSERT INTO ACCOUNT (FIRSTNAME, LASTNAME, USERNAME, PASSWORD) VALUES (:firstname, :lastname, :username, :password)");
                query.bindValue(":firstname", firstname);
                query.bindValue(":lastname", lastname);
                query.bindValue(":username", username);
                query.bindValue(":password", password);
                query.exec();
                goToGameSelection();
            } else {
                QMessageBox::information(0,"Alert", "Account already found with same username: " + username);
            }
        }

        Helper::shaunDB.close();
    } else {
        QMessageBox::information(0,"Alert", "Please enter all fields.");
    }
}

/**
* Sets connections.
*/
void MainWidget::setConnections() {
    QObject::connect(m_signIn, SIGNAL(clicked()), SLOT(signIn()));
    QObject::connect(m_signUp, SIGNAL(clicked()), SLOT(signUp()));
    QObject::connect(m_guestSignIn, SIGNAL(clicked()), SLOT(goToGameSelection()));
}
