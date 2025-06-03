#include <cassert>
#include <iostream>

#include "src/h/lex.h"
#include "../src/h/ast.h"
#include "../src/h/parser.h"

struct  parserTests {
    static void test_parser() {
        std::string src = R"(
store frog = 5;
store frog2 = "this is a string";
store frog3 = false;
store anArray = [1, 2];
anArray[1];
return 3;
&referenceStmt = 5;
func what(x, y, z) { x = y; y = z; }

if (false) {
    frog = 3;
} else { 68
    return 3;
} while (true) {
    frog = 3;
}

what(frog, frog2, frog3);
)"; // 92 total tok

        lex lexer(src);
        // LMAO
        Token t1 = lexer.nextToken();
        Token t2 = lexer.nextToken();
        Token t3 = lexer.nextToken();
        Token t4 = lexer.nextToken();
        Token t5 = lexer.nextToken();
        Token t6 = lexer.nextToken();
        Token t7 = lexer.nextToken();
        Token t8 = lexer.nextToken();
        Token t9 = lexer.nextToken();
        Token t10 = lexer.nextToken();
        Token t11 = lexer.nextToken();
        Token t12 = lexer.nextToken();
        Token t13 = lexer.nextToken();
        Token t14 = lexer.nextToken();
        Token t15 = lexer.nextToken();
        Token t16 = lexer.nextToken();
        Token t17 = lexer.nextToken();
        Token t18 = lexer.nextToken();
        Token t19 = lexer.nextToken();
        Token t20 = lexer.nextToken();
        Token t21 = lexer.nextToken();
        Token t22 = lexer.nextToken();
        Token t23 = lexer.nextToken();
        Token t24 = lexer.nextToken();
        Token t25 = lexer.nextToken();
        Token t26 = lexer.nextToken();
        Token t27 = lexer.nextToken();
        Token t28 = lexer.nextToken();
        Token t29 = lexer.nextToken();
        Token t30 = lexer.nextToken();
        Token t31 = lexer.nextToken();
        Token t32 = lexer.nextToken();
        Token t33 = lexer.nextToken();
        Token t34 = lexer.nextToken();
        Token t35 = lexer.nextToken();
        Token t36 = lexer.nextToken();
        Token t37 = lexer.nextToken();
        Token t38 = lexer.nextToken();
        Token t39 = lexer.nextToken();
        Token t40 = lexer.nextToken();
        Token t41 = lexer.nextToken();
        Token t42 = lexer.nextToken();
        Token t43 = lexer.nextToken();
        Token t44 = lexer.nextToken();
        Token t45 = lexer.nextToken();
        Token t46 = lexer.nextToken();
        Token t47 = lexer.nextToken();
        Token t48 = lexer.nextToken();
        Token t49 = lexer.nextToken();
        Token t50 = lexer.nextToken();
        Token t51 = lexer.nextToken();
        Token t52 = lexer.nextToken();
        Token t53 = lexer.nextToken();
        Token t54 = lexer.nextToken();
        Token t55 = lexer.nextToken();
        Token t56 = lexer.nextToken();
        Token t57 = lexer.nextToken();
        Token t58 = lexer.nextToken();
        Token t59 = lexer.nextToken();
        Token t60 = lexer.nextToken();
        Token t61 = lexer.nextToken();
        Token t62 = lexer.nextToken();
        Token t63 = lexer.nextToken();
        Token t64 = lexer.nextToken();
        Token t65 = lexer.nextToken();
        Token t66 = lexer.nextToken();
        Token t67 = lexer.nextToken();
        Token t68 = lexer.nextToken();
        Token t69 = lexer.nextToken();
        Token t70 = lexer.nextToken();
        Token t71 = lexer.nextToken();
        Token t72 = lexer.nextToken();
        Token t73 = lexer.nextToken();
        Token t74 = lexer.nextToken();
        Token t75 = lexer.nextToken();
        Token t76 = lexer.nextToken();
        Token t77 = lexer.nextToken();
        Token t78 = lexer.nextToken();
        Token t79 = lexer.nextToken();
        Token t80 = lexer.nextToken();
        Token t81 = lexer.nextToken();
        Token t82 = lexer.nextToken();
        Token t83 = lexer.nextToken();
        Token t84 = lexer.nextToken();
        Token t85 = lexer.nextToken();
        Token t86 = lexer.nextToken();
        Token t87 = lexer.nextToken();
        Token t88 = lexer.nextToken();
        Token t89 = lexer.nextToken();
        Token t90 = lexer.nextToken();
        Token t91 = lexer.nextToken();
        Token t92 = lexer.nextToken();

        std::cout << "Unfinished: parser tests \n";
    }
};
