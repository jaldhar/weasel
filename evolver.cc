// Evolver - "Dawkins Weasel" genetic algorithm (Interface)
//
// By Jaldhar H. Vyas <jaldhar@braincells.com>
//
// (C) 2016 Consolidated Braincells Inc.  All rights reserved.
// "Do What Thou Wilt" Shall Be The Whole Of The License.

#include <algorithm>
#include <array>
using namespace std;

#include "evolver.h"

static const array<const char, 27> CHARSET = {{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '
}};

Evolver::Evolver(const char* tp, int n, int mt) : _targetPhrase{tp},
_numCopies{n}, _mutationThreshold{mt} {
}

Evolver::Evolver(const Evolver& that) : _targetPhrase(that._targetPhrase),
_numCopies{that._numCopies}, _mutationThreshold{that._mutationThreshold} {
}

Evolver& Evolver::operator=(const Evolver& that) {
    if (this != &that) {
        this->_targetPhrase = that._targetPhrase;
        this->_numCopies = that._numCopies;
        this->_mutationThreshold = that._mutationThreshold;
    }
    return *this;
}

bool Evolver::operator==(const Evolver& that) const {
    return this->_targetPhrase == that._targetPhrase &&
        this->_numCopies == that._numCopies &&
        this->_mutationThreshold == that._mutationThreshold;
}

bool Evolver::operator!=(const Evolver& that) const {
    return !operator==(that);
}

Evolver::iterator Evolver::begin() {
    return Evolver::iterator(*this, 0);
}

Evolver::iterator Evolver::end() {
    return Evolver::iterator(*this, _targetPhrase.size(), true);
}

void Evolver::swap(Evolver& that) {
    if (this != &that) {
        this->_targetPhrase.swap(that._targetPhrase);
        std::swap(this->_numCopies, that._numCopies);
        std::swap(this->_mutationThreshold, that._mutationThreshold);
    }
}

void swap(Evolver& lhs, Evolver& rhs) {
    lhs.swap(rhs);
}

EvolverIterator::EvolverIterator(Evolver& e, string::size_type hiScore,
bool end) : _e(e), _hiScore{hiScore}, _rnd{random_device{}()}, _end{end} {
    uniform_int_distribution<int> dist(0,26);
    generate_n(back_inserter(_currentPhrase), _e._targetPhrase.size(),
        [this, &dist]() -> char { return CHARSET[dist(this->_rnd)];
    });
}

EvolverIterator::EvolverIterator(const EvolverIterator& that) : _e(that._e),
_hiScore{that._hiScore}, _rnd{that._rnd}, _end{that._end},
_currentPhrase{that._currentPhrase} {
}

EvolverIterator& EvolverIterator::operator=(const EvolverIterator& that) {
    if (this != &that) {
        this->_e = that._e;
        this->_hiScore = that._hiScore;
        this->_rnd = that._rnd;
        this->_end = that._end;
        this->_currentPhrase = that._currentPhrase;
    }
    return *this;
}

bool EvolverIterator::operator==(const EvolverIterator& that) const {
    return this->_e == that._e &&
        this->_hiScore == that._hiScore &&
        this->_end == that._end;
}

bool EvolverIterator::operator!=(const EvolverIterator& that) const {
    return !operator==(that);
}

EvolverIterator EvolverIterator::operator++() {
    if (_hiScore == _e._targetPhrase.size()) {
        _end = true;
    } else {

        uniform_int_distribution<int> dist(0,26);
        uniform_int_distribution<int> pcnt(0,99);

        for (auto n = 0; n < _e._numCopies; n++) {

            string trial;

            transform(_currentPhrase.cbegin(), _currentPhrase.cend(),
            back_inserter(trial), [this, &dist, &pcnt](const char c) -> char {
                if (pcnt(this->_rnd) < this->_e._mutationThreshold) {
                    return CHARSET[dist(this->_rnd)];
                } else {
                    return c;
                }
            });

            string::size_type score = 0;
            for (auto c1 = _e._targetPhrase.cbegin(), c2 = trial.cbegin();
            c1 != _e._targetPhrase.cend(); ++c1, ++c2) {
                if (*c1 == *c2) {
                    score++;
                }
            }

            if (score > _hiScore) {
                _hiScore = score;
                _currentPhrase = trial;
            }

            if (_hiScore == _e._targetPhrase.size()) {
                break;
            }
        }
    }

    return *this;
}

EvolverIterator EvolverIterator::operator++(int) {
    EvolverIterator result(*this);
    operator++();
    return result;
}

EvolverIterator::value_type EvolverIterator::operator*() const {
    value_type result;
    result._phrase = _currentPhrase;
    result._score  = _hiScore;

    return result;
}


void EvolverIterator::swap(EvolverIterator& that) {
    if (this != &that) {
        this->_e.swap(that._e);
        std::swap(this->_hiScore, that._hiScore);
        std::swap(this->_rnd, that._rnd);
        std::swap(this->_end, that._end);
        this->_currentPhrase.swap(that._currentPhrase);
    }
}

void swap(EvolverIterator& lhs, EvolverIterator& rhs) {
    lhs.swap(rhs);
}
