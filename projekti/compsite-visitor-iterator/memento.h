#ifndef MEMENTO_H
#define MEMENTO_H

#include "visitor.h"
class componentIterator;

class Memento
{
    friend class componentIterator;
public:
    Memento(componentIterator * cip): iter(cip){};
    componentIterator* iter;
};
#endif // MEMENTO_H
