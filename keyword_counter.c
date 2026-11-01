#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// List of C keywords
static const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

static const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

// List of C operators
static const char *operators[] = {
    "+", "-", "*", "/", "%",
    "=", "+=", "-=", "*=", "/=", "%=",
    "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "!",
    "&", "|", "^", "~", "<<", ">>",
    "->", ".",
    "?",
    ",",
    "(", ")", "[", "]", "{", "}",
    ";",
    "++", "--",
    NULL
};

static const int num_operators = sizeof(operators) / sizeof(operators[0]) - 1;

static bool is_keyword(const char *token) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

static bool is_operator(const char *token) {
    for (int i = 0; i < num_operators; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return true;
        }
    }
    return false;
}

typedef struct {
    char *value;
    int type; // 1=keyword, 2=identifier, 3=operator
} Token;

static Token *tokenize(const char *input, int *token_count) {
    const int max_tokens = 1000;
    Token *tokens = malloc(max_tokens * sizeof(Token));
    int count = 0;
    
    if (tokens == NULL) {
        *token_count = 0;
        return NULL;
    }
    
    int len = strlen(input);
    int i = 0;
    
    while (i < len && count < max_tokens) {
        // Skip whitespace
        while (i < len && isspace(input[i])) {
            i++;
        }
        if (i >= len) break;
        
        // Handle comments
        if (input[i] == '/') {
            if (i + 1 < len && input[i+1] == '/') {
                i += 2;
                while (i < len && input[i] != '\n') i++;
                continue;
            } else if (i + 1 < len && input[i+1] == '*') {
                i += 2;
                while (i + 1 < len && !(input[i] == '*' && input[i+1] == '/')) i++;
                if (i + 1 < len) i += 2;
                continue;
            }
        }
        
        // Handle string literals
        if (input[i] == '"' || input[i] == '\'') {
            char quote = input[i];
            i++;
            while (i < len && input[i] != quote) {
                if (input[i] == '\\' && i + 1 < len) i += 2;
                else i++;
            }
            if (i < len && input[i] == quote) i++;
            continue;
        }
        
        // Handle character literals
        if (input[i] == '\'') {
            i++;
            if (i < len && input[i] == '\\') i += 2;
            else if (i < len) i++;
            if (i < len && input[i] == '\'') i++;
            continue;
        }
        
        // Handle numeric literals (skip)
        if (isdigit(input[i])) {
            while (i < len && (isdigit(input[i]) || input[i] == '.' || 
                              input[i] == 'e' || input[i] == 'E' || 
                              input[i] == '+' || input[i] == '-')) {
                i++;
            }
            continue;
        }
        
        // Handle preprocessor directives (skip)
        if (input[i] == '#') {
            while (i < len && input[i] != '\n') i++;
            continue;
        }
        
        // Handle operators (multi-character first)
        bool found_operator = false;
        
        if (i + 2 < len) {
            char op3[4] = {input[i], input[i+1], input[i+2], '\0'};
            if (is_operator(op3)) {
                tokens[count].value = strdup(op3);
                tokens[count].type = 3;
                count++; i += 3; found_operator = true;
            }
        }
        
        if (!found_operator && i + 1 < len) {
            char op2[3] = {input[i], input[i+1], '\0'};
            if (is_operator(op2)) {
                tokens[count].value = strdup(op2);
                tokens[count].type = 3;
                count++; i += 2; found_operator = true;
            }
        }
        
        if (!found_operator) {
            char op1[2] = {input[i], '\0'};
            if (is_operator(op1)) {
                tokens[count].value = strdup(op1);
                tokens[count].type = 3;
                count++; i++; found_operator = true;
            }
        }
        
        if (found_operator) continue;
        
        // Handle identifiers and keywords
        if (isalpha(input[i]) || input[i] == '_') {
            int start = i;
            while (i < len && (isalpha(input[i]) || isdigit(input[i]) || input[i] == '_')) {
                i++;
            }
            int token_len = i - start;
            tokens[count].value = malloc(token_len + 1);
            strncpy(tokens[count].value, input + start, token_len);
            tokens[count].value[token_len] = '\0';
            
            if (is_keyword(tokens[count].value)) {
                tokens[count].type = 1;
            } else {
                tokens[count].type = 2;
            }
            count++;
            continue;
        }
        
        // Skip other characters
        i++;
    }
    
    *token_count = count;
    return tokens;
}

static void free_tokens(Token *tokens, int count) {
    for (int i = 0; i < count; i++) {
        free(tokens[i].value);
    }
    free(tokens);
}

int main() {
    printf("=== C Keyword, Identifier, and Operator Counter ===\n\n");
    printf("Enter a C statement (press Ctrl+D to finish):\n");
    
    char input[10000];
    size_t input_len = 0;
    int ch;
    
    while ((ch = getchar()) != EOF) {
        if (input_len < sizeof(input) - 1) {
            input[input_len++] = (char)ch;
        } else {
            printf("Input too long!\n");
            return 1;
        }
    }
    input[input_len] = '\0';
    
    // Remove trailing whitespace
    while (input_len > 0 && isspace(input[input_len - 1])) {
        input_len--;
        input[input_len] = '\0';
    }
    
    if (input_len == 0) {
        printf("No input provided. Using default example.\n");
        strcpy(input, "int a = b + c * d - e / f;");
    }
    
    printf("\nInput: %s\n\n", input);
    
    int token_count;
    Token *tokens = tokenize(input, &token_count);
    
    if (tokens == NULL) {
        printf("Error tokenizing input!\n");
        return 1;
    }
    
    int keyword_count = 0, identifier_count = 0, operator_count = 0;
    
    for (int i = 0; i < token_count; i++) {
        switch (tokens[i].type) {
            case 1: keyword_count++; break;
            case 2: identifier_count++; break;
            case 3: operator_count++; break;
        }
    }
    
    printf("=== Results ===\n");
    printf("Keywords:     %d\n", keyword_count);
    printf("Identifiers:  %d\n", identifier_count);
    printf("Operators:    %d\n", operator_count);
    printf("Total tokens: %d\n\n", token_count);
    
    printf("=== Token Details ===\n");
    printf("%-20s %-12s\n", "Token", "Type");
    printf("----------------------\n");
    
    for (int i = 0; i < token_count; i++) {
        const char *type_str = "Unknown";
        switch (tokens[i].type) {
            case 1: type_str = "Keyword"; break;
            case 2: type_str = "Identifier"; break;
            case 3: type_str = "Operator"; break;
        }
        printf("%-20s %-12s\n", tokens[i].value, type_str);
    }
    
    free_tokens(tokens, token_count);
    return 0;
}
