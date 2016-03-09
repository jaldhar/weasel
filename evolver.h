// Evolver - "Dawkins Weasel" genetic algorithm (Interface)
//
// By Jaldhar H. Vyas <jaldhar@braincells.com>
//
// (C) 2016 Consolidated Braincells Inc.  All rights reserved.
// "Do What Thou Wilt" Shall Be The Whole Of The License.

#ifndef _EVOLVER_H_
#define _EVOLVER_H_

#include <iterator>
#include <random>
#include <string>

class EvolverIterator;

class Evolver {
public:
    typedef EvolverIterator iterator;

    Evolver(const char* tp, int n, int mt);
    Evolver(const Evolver& that);
    ~Evolver()=default;

    Evolver& operator=(const Evolver& that);
    bool     operator==(const Evolver& that) const;
    bool     operator!=(const Evolver& that) const;

    iterator begin();
    iterator end();

    void     swap(Evolver& that);

private:
    std::string _targetPhrase;
    int         _numCopies;
    int         _mutationThreshold;

    friend iterator;
};

void swap(Evolver& lhs, Evolver& rhs);

struct EvolverGeneration {
    std::string _phrase;
    int         _score;
};

class EvolverIterator : public
std::iterator<std::output_iterator_tag, EvolverGeneration> {
public:
    EvolverIterator(Evolver& e, std::string::size_type hiScore, bool end = false);
    EvolverIterator(const EvolverIterator& that);
    ~EvolverIterator()=default;

    EvolverIterator&  operator=(const EvolverIterator& that);
    bool              operator==(const EvolverIterator& that) const;
    bool              operator!=(const EvolverIterator& that) const;
    EvolverIterator   operator++();
    EvolverIterator   operator++(int);
    value_type        operator*() const;

    void              swap(EvolverIterator& that);

private:
    Evolver& _e;
    std::string::size_type _hiScore;
    std::minstd_rand _rnd;
    bool _end;
    std::string _currentPhrase;
};

void swap(EvolverIterator& lhs, EvolverIterator& rhs);

#endif
