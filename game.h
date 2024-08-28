#ifndef GAME_H
#define GAME_H

#include <QString>

class Game
{
public:
    Game();
    QString getWord();
    QString getGuess();
    int getState();
    QString getLetters();
    bool openLetter(QChar);
    bool win();
private:
    QString m_word{};
    QString m_guess{};
    int m_state{};
    QString m_letters{};
};

#endif // GAME_H
