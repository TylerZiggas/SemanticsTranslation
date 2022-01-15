#include "semantics.h"

void Semantics::verify(NodeT* node) {
	if (node == NULL) {
		return;
	}

	if (node->label == "<vars>") {
		for (unsigned int tokenCounter = 0; tokenCounter < node->tokens.size(); tokenCounter++) {
			if (node->tokens[tokenCounter].tokenID == idTk && node->tokens[tokenCounter].tokenInstance != "empty") {
				checkDeclaration(node->tokens[tokenCounter]);
			}
		}
	} else {
		vector<string> labels = { "<R>", "<in>", "<assign>", "<label>", "<goto>" };
		for (unsigned int labelCounter = 0; labelCounter < labels.size(); labelCounter++) {
			if (node->label == labels[labelCounter]) {
				for (unsigned int tokenCounter = 0; tokenCounter < node->tokens.size(); tokenCounter++) {
					if (node->tokens[tokenCounter].tokenID == idTk) {
						checkDefined(node->tokens[tokenCounter]);
					}
				}
			}
		}
	}

	verify(node->nodeOne);
	verify(node->nodeTwo);
	verify(node->nodeThree);
	verify(node->nodeFour);
	verify(node->nodeFive);
}

void Semantics::checkDeclaration(Token tk) {
	int isDeclared = -1;
	for (unsigned int tableCounter = 0; tableCounter < st.size(); tableCounter++) {
		if (st[tableCounter].identifier.tokenInstance == tk.tokenInstance) {
			isDeclared = tableCounter;
			break;
		}
	}

	if (isDeclared > -1) {
		cout << endl <<  "SEMANTICS ERROR: The variable [" << tk.tokenInstance << "] at line (L " << tk.lineNumber <<
			") -> has already been declared at line (L " << st[isDeclared].identifier.lineNumber << ")" << endl;
		exit(EXIT_FAILURE); 
	} else {
		tableHolder.identifier = tk;
		st.push_back(tableHolder);
	}
}


void Semantics::checkDefined(Token tk) {
	int isDeclared = -1;
	for (unsigned int tableCounter = 0; tableCounter < st.size(); tableCounter++) {
		if (st[tableCounter].identifier.tokenInstance == tk.tokenInstance) {
			isDeclared = tableCounter;
			break;
		}
	}

	if (isDeclared < 0) {
		cout << endl << "SEMANTICS ERROR: The variable [" << tk.tokenInstance << "] at line (L " << tk.lineNumber << ") has not been declared" << endl;
		exit(EXIT_FAILURE);
	}
}