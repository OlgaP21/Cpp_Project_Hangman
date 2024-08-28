#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "game.h"

#include <QLabel>
#include <QString>
#include <QList>
#include <QSignalMapper>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Hangman");
    m_signal_mapper = new QSignalMapper(this);
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    for (int i{0}; i < buttons.size(); i++) {
        QPushButton* button = buttons.at(i);
        QString text = button->text();
        m_signal_mapper->setMapping(button, text);
        connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
    }
    game = new Game();
    QLabel* label = this->findChild<QLabel*>("guess_label");
    label->setText(game->getGuess());
    message_box = new QMessageBox();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_button_clicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QChar letter = button->text().at(0);
    openLetter(letter);
    if (gameOver()) {
        bool newGame = startNewGame(game->win());
        delete game;
        if (newGame) {
            game = new Game();
            clear();
        } else {
            this->close();
        }
    }
}

void GameWindow::openLetter(QChar letter) {
    if (game->openLetter(letter)) {
        QLabel* guess_label = this->findChild<QLabel*>("guess_label");
        guess_label->setText(game->getGuess());
    } else {
        QString drawing;
        for (int i{0}; i < game->getState(); i++) {
            drawing.append(m_drawing[i]);
        }
        QLabel* drawing_label = this->findChild<QLabel*>("drawing_label");
        drawing_label->setText(drawing);
    }
    QLabel* letters_label = this->findChild<QLabel*>("letters_label");
    letters_label->setText(game->getLetters());
}

bool GameWindow::gameOver() {
    bool player_win{game->win()};
    if (game->getState() > 6 && !player_win) {
        return true;
    } else if (player_win) {
        return true;
    } else {
        return false;
    }
}

bool GameWindow::startNewGame(bool win) {
    QString message = " Õige sõna oli: ";
    message.append(game->getWord());
    if (win) {
        message.prepend("Võit!");
    } else {
        message.prepend("Kaotus!");
    }
    message_box->setText(message);
    message_box->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    message_box->setButtonText(QMessageBox::Yes, tr("Jah"));
    message_box->setButtonText(QMessageBox::No, tr("Ei"));
    int reply = message_box->exec();
    switch (reply) {
        case QMessageBox::Yes:
            return true;
        case QMessageBox::No:
            return false;
    }
}

void GameWindow::clear() {
    QLabel* letters_label = this->findChild<QLabel*>("letters_label");
    letters_label->setText(game->getLetters());
    QLabel* drawing_label = this->findChild<QLabel*>("drawing_label");
    drawing_label->setText("");
    QLabel* guess_label = this->findChild<QLabel*>("guess_label");
    guess_label->setText(game->getGuess());
}
