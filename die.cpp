#include "die.h"

using namespace std;

Die::Die() {
    m_numOfSides = 6;
    m_dieValue = 1;
    random_device rd;
    m_generator.seed(rd());
}

void Die::set_numOfSides(int sides) {
    if (sides == 4 || sides == 6 || sides == 8) {
        m_numOfSides = sides;
    } else {
        m_numOfSides = 6;
    }
}

int Die::get_numOfSides() const {
    return m_numOfSides;
}

void Die::set_dieValue(int value) {
    m_dieValue = value;
}

int Die::get_dieValue() const {
    return m_dieValue;
}

int Die::rollDie() {
    uniform_int_distribution dist(1, m_numOfSides);
    m_dieValue = dist(m_generator);
    return m_dieValue;
}