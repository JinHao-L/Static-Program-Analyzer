#pragma once

#include "Entities.h"
#include "QPS/Entities/Readers/ConstantReader.h"

class ConstantEntities : public Entities {
public:
    ConstantEntities();

    ~ConstantEntities() override;

    bool isConstant() override;

    string toString() override;

    int hashCode() override;
};
