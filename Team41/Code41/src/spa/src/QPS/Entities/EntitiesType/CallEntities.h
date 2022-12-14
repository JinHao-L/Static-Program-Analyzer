#pragma once

#include "Entities.h"
#include "QPS/Entities/Readers/CallReader.h"

class CallEntities : public Entities {
public:
    CallEntities();

    ~CallEntities() override;

    bool isCall() override;

    string toString() override;

    int hashCode() override;
};