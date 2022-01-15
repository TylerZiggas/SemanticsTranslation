#pragma once
#ifndef SEMANTICS_H
#define SEMANTICS_H
#include <iostream> // Includes for file, strings, and vectors
#include <string> 
#include <vector>        
#include "node.h" // Inclusions for different nodes we have and token options
#include "token.h"
using namespace std;

typedef struct symbol_table { // Our symbol table that stores our tokens
	Token identifier;
} SymbolTable;

class Semantics {
private:
	SymbolTable tableHolder; // Creation of our symbol table
	vector<SymbolTable> st;

public:
	void verify(NodeT*);
	void checkDeclaration(Token); // Function declarations to check variables
	void checkDefined(Token);
};

#endif