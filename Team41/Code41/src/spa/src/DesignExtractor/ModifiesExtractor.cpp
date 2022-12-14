#include "ModifiesExtractor.h"
#include "DesignExtractorUtils.h"

ModifiesExtractor::ModifiesExtractor(TNode *ast, unordered_map<TNode *, string> &nodeToStmtNumMap,
                                     unordered_map<string, unordered_set<string>> &callsMap,
                                     list<string> &procCallOrder) :
        VarRelationExtractor(ast, nodeToStmtNumMap, callsMap, procCallOrder) {}

void ModifiesExtractor::dfs(TNode *node, unordered_set<string> &modifiesSet) {
    if (node->isProcedure()) {
        dfs(node->getChildren()[0], modifiesSet); // only 1 child stmtLst
        mapRelation(node, modifiesSet);
    } else if (node->isStmtLst()) {
        unordered_set<string> modifiesSetChild;
        for (TNode *child: node->getChildren()) {
            dfs(child, modifiesSetChild);
            DesignExtractorUtils::combineSetsClear(modifiesSet, modifiesSetChild);
        }
    } else if (node->isRead() || node->isAssign()) {
        modifiesSet = {node->getChildren()[0]->getTokenVal()}; // left child varName
        mapRelation(node, modifiesSet);
    } else if (node->isWhile()) {
        dfs(node->getChildren()[whileStmtLst], modifiesSet); // right child stmtLst
        mapRelation(node, modifiesSet);
    } else if (node->isIf()) {
        unordered_set<string> modifiesSetChild;
        const vector<TNode *> &ch = node->getChildren();
        for (size_t i = 1; i <= 2; ++i) { // if stmt has stmtLst on 2nd and 3rd child
            dfs(ch[i], modifiesSetChild);
            DesignExtractorUtils::combineSetsClear(modifiesSet, modifiesSetChild);
        }
        mapRelation(node, modifiesSet);
    }
}

bool ModifiesExtractor::extract() {
    return VarRelationExtractor::extract();
}

unordered_map<string, unordered_set<string>> ModifiesExtractor::getProcModifiesMap() {
    return this->procRelationMap;
}

unordered_map<string, unordered_set<string>> ModifiesExtractor::getStmtModifiesMap() {
    return this->stmtRelationMap;
}
