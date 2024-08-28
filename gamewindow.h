#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "game.h"

#include <QMainWindow>
#include <QSignalMapper>
#include <QChar>
#include <QMessageBox>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void on_button_clicked();

private:
    Ui::GameWindow *ui;
    QSignalMapper *m_signal_mapper;
    Game *game;
    const QString m_drawing[7] {
        " _____\n",
        " |        |\n",
        "  |        o\n",
        "   |       /|\\\n",
        "   |       / \\\n",
        "  |        _\n",
        "/|\\       "
    };
    QMessageBox* message_box;

    void openLetter(QChar);
    bool gameOver();
    bool startNewGame(bool);
    void clear();
};

#endif // GAMEWINDOW_H
