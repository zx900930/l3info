#ifndef _ARBRE_H_
#define _ARBRE_H_

#include "string.h"
#include <math.h>

enum NodeType { ROOT, LEAF, RULES, RULE, PLUS, STAR, QUESTION, OR, CONCAT, SUBEXPR, ENSEMBLE, INTERVAL, CHAR };  // Voir exemple sur http://www.ensiie.fr/~guillaume.burel/compilation/

typedef struct Node* Tree;
typedef struct Node
{
	enum NodeType type;
	String leafData;	// Inclus du contenu seulement pour type = LEAF
	unsigned int nbSons;
	Tree* sons;
} Node;

Tree NewTree();
void AppendNode(Tree tree, enum NodeType type, String leafData);
void AppendNodeTree(Tree tree, Tree node);
void PrintTree(Tree tree, unsigned int level);

Tree BuildTree(String lexFileContent);

#endif
