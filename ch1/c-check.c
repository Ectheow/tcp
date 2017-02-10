#include <stdio.h>
#define MAXLINE 1000

#define QC_IN_QUOTES 0
#define CC_IN_COMMENT 1
#define CC_START_COMMENT_SLASH 2
#define CC_END_COMMENT_STAR 3
#define ALL_IN_CODE 4
#define ALL_ERROR 5
#define QC_IN_ESCAPE 6

char error_buffer[MAXLINE];

int check_brackets(char c, int open_closes, char open, char close, int buffer_state, char err[], int maxerr);
int check_quotes(char c, int buffer_state, char err[], int maxerr);
int check_comments(char c, int buffer_state, char err[], int maxerr);

int m_getline(char line[], int maxline);

#define CURLY 0
#define SQUARE 1
#define PAREN 2
#define N_BRACKET_TYPES 3

int main()
{

    int bracket_counts[N_BRACKET_TYPES], i, lineno, c, state;
    char bracket_types[2*N_BRACKET_TYPES];
    char line[MAXLINE];
    char err[MAXLINE];

    i=0;
    c=0;
    lineno=0;
    state = ALL_IN_CODE;

    for (i=0; i<MAXLINE; i++) 
        line[i] = '\0';
    for(i=0; i<N_BRACKET_TYPES; i++) 
        bracket_counts[i] = 0;

    bracket_types[2*CURLY] = '{';
    bracket_types[2*CURLY+1] = '}';
    bracket_types[2*SQUARE] = '[';
    bracket_types[2*SQUARE+1] = ']';
    bracket_types[2*PAREN] = '(';
    bracket_types[2*PAREN+1] = ')';

    while((c = getchar()) != EOF) {
        if (state != CC_IN_COMMENT && ((state = check_quotes((char)c, state, err, MAXLINE)) == ALL_ERROR)) {
            printf("Error in quote: %s\n",
                    err);
            return 1;
        }
        if(state != QC_IN_QUOTES && ((state = check_comments((char)c, state, err, MAXLINE)) == ALL_ERROR)) { 
            printf("Error in comment: %s\n",
                    err);
            return 1;
        }

        if (state == ALL_IN_CODE) 
            for(i = 0; i< N_BRACKET_TYPES; i++) {
                bracket_counts[i] = check_brackets(
                        c,
                        bracket_counts[i],
                        bracket_types[2*i],
                        bracket_types[2*i+1],
                        state,
                        err,
                        MAXLINE);
                if (bracket_counts[i] < 0) {
                    printf("Error on line: %d: %s: extra closing bracket type '%c'\n",
                            lineno,
                            line,
                            bracket_types[2*i]);

                    return 1;
                }
            }
        if ( c == '\n')
            ++lineno;
    }

    if (state == QC_IN_QUOTES) {
        printf("Error: unterminated quote\n");
        return 1;
    }
    if (state == CC_IN_COMMENT) { 
        printf("Error: unterminated comment\n");
    }
    for (i = 0; i< N_BRACKET_TYPES; i++) {
        if (bracket_counts[i] != 0) {
            printf("Error: mismatched bracket of type: '%c': %d\n",
                    bracket_types[2*i],
                    bracket_counts[i]);
        }
    }
    return 0;
}

int check_quotes(char c, int buffer_state, char err[], int maxerr) {
    if (!(buffer_state == ALL_IN_CODE ||
                buffer_state == QC_IN_QUOTES)) {
        return buffer_state;
    }

    if (c == '"' && buffer_state == ALL_IN_CODE) {
        buffer_state = QC_IN_QUOTES;
    } else if (c == '\\' && buffer_state == QC_IN_QUOTES) {
        buffer_state = QC_IN_ESCAPE;
    } else if (c == '"' && buffer_state == QC_IN_QUOTES) {
        buffer_state = ALL_IN_CODE;
    } else if (buffer_state == QC_IN_ESCAPE) {
        buffer_state = QC_IN_QUOTES;
    }

    return buffer_state;

}

int check_comments(char c, int buffer_state, char err[], int maxerr) 
{
    int i;


    if (buffer_state == QC_IN_QUOTES || buffer_state == QC_IN_ESCAPE) {
        return buffer_state;
    }

    if (c == '/' && buffer_state == ALL_IN_CODE) 
        buffer_state = CC_START_COMMENT_SLASH;
    else if(c == '/' && buffer_state == CC_END_COMMENT_STAR) 
        buffer_state = ALL_IN_CODE;
    else if(c == '*' && buffer_state == CC_IN_COMMENT) 
        buffer_state = CC_END_COMMENT_STAR;
    else if(c == '*' &&  buffer_state == CC_START_COMMENT_SLASH) 
        buffer_state = CC_IN_COMMENT;

    return buffer_state;
}

int check_brackets(char c, int open_closes, char open, char close, int buffer_state, char err[], int maxerr)
{
    if (buffer_state != ALL_IN_CODE)
        return open_closes;

    if (c == open)
        return ++open_closes;
    else if(c == close)
        return --open_closes;

    return open_closes;

}

int mismatched_bracket(char line[], int maxline, int open_closes, char open, char close)
{
    int i;

    for(i=0; i<maxline && line[i] != '\0'; ++i) {
        if (line[i] == open) {
            ++open_closes;
        } else if(line[i] == close) {
            --open_closes;
            if (open_closes < 0) 
                return open_closes;
        }
    }

    return open_closes;
}


int m_getline(char line[], int maxline) 
{

    int c,i;
    i = 0;
    c = EOF;

    for (c = getchar(); c != EOF && i < maxline && c != '\n'; c = getchar()) {
        line[i] = c;
        ++i;
    }

    if (i < maxline-1 && c == '\n') {
        line[i] = '\n';
        ++i;
    } 

    line[i] = '\0';

    return i;
}
