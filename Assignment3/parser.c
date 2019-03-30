#include "tokens.h"
#include "tree.h"
#include "varim.h"
#include "parser.h"

ptn match_token(int expected_token) {
    int next_input_token = consume_next_input_token();
    if (expected_token == next_input_token) {
        return new_token_node(expected_token);
    }
    else {
        raise_syntax_error(expected_token, next_input_token);
    }
}

ptn match_epsilon() {
    return new_epsilon_node();
}

ptn match_B() {
    ptn ob_node = match_token('{');
    ptn L_node = match_L();
    ptn cb_node = match_token('}');
    return new_B_node(ob_node, L_node, cb_node);
}

ptn match_L() {
    int lookahead_token = peek_at_next_input_token();
    if (lookahead_token == INT) {
        ptn D_node = match_D();
        ptn semi_node = match_token(';');
        ptn L_node = match_L();
        return new_L_node(D_node, semi_node, L_node);
    }
    else if (lookahead_token == IF || lookahead_token == ID) {
        ptn S_node = match_S();
        ptn semi_node = match_token(';');
        ptn L_node = match_L();
        return new_L_node(S_node, semi_node, L_node);
    } 
    else {
        ptn e_node = match_epsilon();
        return new_L_node(e_node);
    }
}

ptn match_D() {
    ptn INT_node = match_token(INT);
    ptn ID_node = match_token(ID);
    ptn eq_node = match_token('=');
    ptn E_node = match_E();
    return new_D_node(INT_node, ID_node, eq_node, E_node);
}

ptn match_S() {
    int lookahead_token = peek_at_next_input_token();
    if (lookahead_token == IF) {
        ptn IF_node = match_token(IF);
        ptn fb_node = match_token('(');
        ptn E_node = match_E();
        ptn rb_node = match_token(')');
        ptn B1_node = match_B();
        ptn ELSE_node = match_token(ELSE);
        ptn B2_node = match_B();
        return new_S_node(IF_node, fb_node, E_node, rb_node, B1_node, ELSE_node, B2_node);
    }
    else {
        ptn ID_node = match_token(ID);
        ptn eq_node = match_token('=');
        ptn E_node = match_E();
        return new_S_node(ID_node, eq_node, E_node);
    }
}

ptn match_E() {
    ptn T_node = match_T();
    ptn Ep_node = match_Ep();
    return new_E_node(T_node, Ep_node);
}

ptn match_Ep() {
    int lookahead_token = peek_at_next_input_token();
    if (lookahead_token == '+') {
        ptn plus_node = match_token('+');
        ptn T_node = match_T();
        ptn Ep_node = match_Ep();
        return new_Ep_node(plus_node, T_node, Ep_node);
    }
    else {
        ptn e_node = match_epsilon();
        return new_Ep_node(e_node);
    }
}

ptn match_T() {
    ptn F_node = match_F();
    ptn Tp_node = match_Tp();
    return new_T_node(F_node, Tp_node);
}

ptn match_Tp() {
    int lookahead_token = peek_at_next_input_token();
    if (lookahead_token == '*') {
        ptn star_node = match_token('*');
        ptn F_node = match_F();
        ptn Tp_node = match_Tp();
        return new_Tp_node(star_node, F_node, Tp_node);
    }
    else {
        ptn e_node = match_epsilon();
        return new_Tp_node(e_node);
    }
}

ptn match_F() {
    int lookahead_token = peek_at_next_input_token();
    if (lookahead_token == '(') {
        ptn fb_node = match_token('(');
        ptn E_node = match_E();
        ptn rb_node = match_token(')');
        return new_F_node(fb_node, E_node, rb_node);
    }
    else if (lookahead_token == ID) {
        ptn ID_node = match_token(ID);
        return new_F_node(ID_node);
    }
    else {
        ptn NUM_node = match_token(NUM);
        return new_F_node(NUM_node);
    }
}