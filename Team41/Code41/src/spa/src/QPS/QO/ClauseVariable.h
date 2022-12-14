#pragma once

#include <string>
#include "QueryDeclaration.h"

using namespace std;

class ClauseVariable {
public:
    // enum representing possible variable types in PQL
    enum variable_type {
        identifier, wildcard, synonym, integer
    };

    /**
     * Getter for the variable type.
     *
     * @return variable_type representing the type.
     */
    [[nodiscard]] variable_type getType() const;

    /**
     * Getter for the label.
     *
     * @return string representing the label.
     */
    [[nodiscard]] string getLabel() const;

    /**
     * Getter for the declaration type.
     *
     * @return QueryDeclaration::design_entity_type representing the declaration type.
     */
    Entities *getDesignEntityType() const;

    /**
     * Checks if the variable is an identifier.
     *
     * @return boolean indicating if identifier.
     */
    bool isIdentifier() const;

    /**
     * Checks if the variable is a wildcard.
     *
     * @return boolean indicating if wildcard.
     */
    bool isWildCard() const;

    /**
     * Checks if the variable is an synonym.
     *
     * @return boolean indicating if synonym.
     */
    bool isSynonym() const;

    /**
     * Checks if the variable is an integer.
     *
     * @return boolean indicating if integer.
     */
    bool isInteger() const;

    /**
     * Gets the QueryDeclaration instance for the variable.
     *
     * @return QueryDeclaration instance.
     */
    QueryDeclaration getQueryDeclaration() const;

    /**
     * Constructors for the ClauseVariable class.
     *
     * @param type of the new variable.
     * @param label for the name of the new variable.
     * @param designEntityType for the declaration type of the new variable.
     * @param qd for the QueryDeclaration of the new variable.
     */
    ClauseVariable(variable_type type, string label, Entities *designEntityType);

    ClauseVariable(variable_type type, string label, QueryDeclaration qd);

    ClauseVariable();

    /**
     * Equivalence comparator for the ClauseVariable class.
     *
     * @return boolean indicating if equivalent.
     */
    bool equals(ClauseVariable) const;

private:
    // variable type of the variable instance
    variable_type type;

    // name of the clause variable
    string label;

    QueryDeclaration qd;

    // declaration type of the clause variable (must be declared)
    Entities *designEntityType;
};
