#include <iostream>
#include "variable.h"


int IMesh::x_size() const
{
    return (final_position() - initial_position()) / position_step() + 1;
};