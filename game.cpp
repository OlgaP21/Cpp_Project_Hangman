#include <ctime>
#include "game.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QChar>

void chooseWordFromFile(QString& word) {
    QFile file(":/data/words.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    int number_of_rows = file.readLine().toInt();
    std::srand(static_cast<unsigned int>(time(NULL)));
    int row_number{std::rand()%number_of_rows};
    int row_count{0};
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString row = in.readLine();
        if (row_count == row_number) {
            word = row;
            break;
        }
        row_count += 1;
    }
    file.close();
}

Game::Game()
{
    chooseWordFromFile(m_word);
    for (auto it{m_word.begin()}; it != m_word.end(); it++) {
        if (*it == QChar(' ')) {
            m_guess.append("  ");
        } else {
            m_guess.append("_ ");
        }
    }
    m_state = 0;
    m_letters = {"Kasutatud tähed:\n"};
}

QString Game::getWord() {
    return m_word;
}

QString Game::getGuess() {
    return m_guess;
}

int Game::getState() {
    return m_state;
}

QString Game::getLetters() {
    return m_letters;
}

bool Game::openLetter(QChar letter) {
    bool letter_in_word{false};
    int index{0};
    for (auto it{m_word.begin()}; it != m_word.end(); it++) {
        if (*it == letter) {
            m_guess.replace(index*2, 1, letter);
            letter_in_word = true;
        }
        index += 1;
    }
    if (!letter_in_word) m_state += 1;
    m_letters.append(letter);
    m_letters.append(QChar(' '));
    return letter_in_word;
}

bool Game::win() {
    return m_state < 7 && !m_guess.contains(QChar('_'));
}
