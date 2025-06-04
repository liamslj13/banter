#include <cassert>
#include <iostream>

#include "../src/h/lex.h"
#include "../src/h/ast.h"
#include "../src/h/parser.h"

struct  parserTests {
    static void test_parser() {
        testDeclarationStatements();

        std::cout << "Unfinished: parser tests \n";
    }

    static void testDeclarationStatements() {
        std::string src = "var x = 5;";
        const lex l(src);
        parser p(l);

        std::unique_ptr<Program> program = p.parseProgram();
        assert(program != nullptr);
        assert(program->statements.size() == 1);

        Statement* stmt = program->statements[0].get();
        assert(stmt != nullptr);
        assert(stmt->type() == "declare_statement");

        auto* declareStmt = dynamic_cast<DeclareStatement*>(stmt);
        assert(declareStmt != nullptr);
        assert(declareStmt->name != nullptr);
        assert(declareStmt->value != nullptr);

        assert(declareStmt->name->tok.lit == "x");
        assert(declareStmt->value->tokenLiteral() == "5");

        std::cout << "✓ testDeclarationStatements passed\n";
    }

};
