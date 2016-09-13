#include "lexanalyzer.h"

using namespace std;

lexanalyzer::lexanalyzer(char *argv[])
{
    input.open(argv[1]);
    output.open("output.txt");
    token = "";
    current = ' ';
        // open specified and output files
        // initialize variable(s)
}

void lexanalyzer::charReader()
{

    while(input.get(current)) // read through file
    {                         // character by character



        if(current == '#') //check for comments
        {

            while(input.get(current)) // if we find a comment skip
            {                         // to the end of the line
                if(current == '\n')
                    break;
            }
        }
        if((current == ' ') || (current == '\n') || (current == '\0'))
        {
            // If we hit a whitespace or endline character
            // do not do anything
        }
        else if(isalpha(current) != 0) // check if the character we have
        {                              // is a letter, if so we look for an ID
            token += current;

            input.get(current);
            while((isalpha(current) != 0)||(isdigit(current) != 0)) // keep reading characters until
            {                                                       // we dont have a digit or letter
                token += current;
                input.get(current);
            }
            input.unget();
            checkKeywords(token);
                // go back one character and test
                // what we found against keywords
        }
        else if(isdigit(current) != 0) // check for a number
        {
            token += current;

            input.get(current);
            while(isdigit(current) != 0) // keep going till we dont find a number
            {
                token += current;
                input.get(current);
            }
            input.unget();

            printToken(token, "NUMBER");
        }
        else if(current == '"') // if we encounter a quote we must read
        {                       // characters untill another quote is found
            token += current;
            input.get(current);
            while(current != '"')
            {
                token += current;
                input.get(current);
            }
            token += current;
            printToken(token, "STRING");
        }        
        else if((current == '<')) // check for less than operators
        {                         // or assignment operators
            token += current;
            input.get(current);
            if(current == '-')
            {
                token += current;
                printToken(token, "ASSIGNOP");
            }
            else if(current == '=')
            {
                token += current;
                printToken(token, "RELOP");
            }
            else
            {
                printToken(token, "RELOP");
                input.unget();
            }
        }
        else if((current == '>')) // check for greater than operators
        {
            token += current;
            input.get(current);
            if(current == '=') // look for ">="
            {
                token += current;
                printToken(token, "RELOP");
            }
            else
            {
                printToken(token, "RELOP");
                input.unget();
            }
        }
        else if(current == '=')  // check for relation operators starting
        {                        // with an equals sign
            token += current;
            input.get(current);
            if((current == '<') || (current == '>'))
            {
                token += current;
                printToken(token, "RELOP");
            }
            else
            {
                printToken(token, "RELOP");
                input.unget();
            }
        }
        else if(current == '!') // check for a not
        {                       // or not equals operator
            token += current;
            input.get(current);
            if(current == '=')
            {
                token += current;
                printToken(token, "RELOP");
            }
            else
            {
                printToken(token, "NOT");
                input.unget();
            }
        }
        else if((current == '*') || (current == '/')) // check for multiplication
        {                                             // or division operators
            token += current;
            printToken(token, "MULOP");
        }
        else if((current == '+') || (current == '-')) // check for addition
        {                                             // or subtraction operators
            token += current;
            printToken(token, "ADDOP");
        }
        else if(current == '(') // check for a left
        {                       // parenthesis
            token += current;
            printToken(token, "PARENL");
        }
        else if(current == ')') // check for a right
        {                       // parenthesis
            token += current;
            printToken(token, "PARENR");
        }
        else if(current == '{') // check for a left
        {                       // curly bracket
            token += current;
            printToken(token, "CURLL");
        }
        else if(current == '}') // check for a right
        {                       // curly bracket
            token += current;
            printToken(token, "CURLR");
        }
        else if(current == ',') // check for a comma
        {
            token += current;
            printToken(token, "COMMA");
        }
        else if(current == ';') // check for a semicolon
        {
            token += current;
            printToken(token, "SEMICOLON");
        }
        else if(current == '&') // check for an ampersand
        {
            token += current;
            printToken(token, "AND");
        }
        else if(current == '|') // check for a verticle line
        {
            token += current;
            printToken(token, "OR");
        }
        else                    // print out an error if
        {                       // we didn't find a token
            token += current;
            printToken(token, "ERROR");
        }
        token = "";
    }
}

void lexanalyzer::checkKeywords(string token)
{
        // long if chain comparing found token to keywords
        // (else, if, while, function, etc.)

    if(token.compare("else") == 0)
    {
        printToken(token, "ELSE");
    }
    else if(token.compare("function") == 0)
    {
        printToken(token, "FUNCTION");
    }
    else if(token.compare("if") == 0)
    {
        printToken(token, "IF");
    }
    else if(token.compare("return") == 0)
    {
        printToken(token, "RETURN");
    }
    else if(token.compare("var") == 0)
    {
        printToken(token, "VAR");
    }
    else if(token.compare("while") == 0)
    {
        printToken(token, "WHILE");
    }
    else
        printToken(token, "ID");
}

void lexanalyzer::printToken(string token, string type)
{
    output << "TOKEN:" << left << setw(10) << type << "  " << setw(20) << token << endl;
        // print out the token type and the token itsself
}
