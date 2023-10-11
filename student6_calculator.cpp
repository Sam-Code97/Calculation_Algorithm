#include "studentscalculator.h"
#include <vector>

#include <math.h>
#include <assert.h>

using namespace std;


const char* nameOfStudent6(){
    return "Sam Aliwa";
}


/********************************************************************
ANROP:    float valueFromInfixoperation(x, op,  y);
VERSION:  071114 RAG
UPPGIFT:  returnerar x op y;
**********************************************************************/
float valueFromInfixexpression( float x, char op,  float y)
{

    if (op=='+') return x+y;
    if (op=='-') return x-y;
    if (op=='*') return x*y;
    if (op=='/') return x/y;
    if (op=='^') return float( pow(x,y) );

    assert( false );
    return float();
}//valueFromInfixoperation


int priorityOfOp(char op){
    if (op=='+') return 1;
    if (op=='-') return 1;
    if (op=='*') return 2;
    if (op=='/') return 2;
    if (op=='^') return 3;
    return -1;
}

bool isLegalOp(char op){
    return priorityOfOp(op)>=0;
}

void calculate_and_pop (const std::vector<Token> &tokens, std::vector<float> &stackOfValues, std::vector<char> &stackOfOperators){

    if(stackOfOperators.back() == '(')
        return;
    float back2 = stackOfValues.back();
    stackOfValues.pop_back();
    float back1 = stackOfValues.back();
    stackOfValues.pop_back();

    stackOfValues.push_back( valueFromInfixexpression(back1, stackOfOperators.back(), back2) );
    stackOfOperators.pop_back();

}

// Denna algoritm skall implementeras av studenten
bool applyParsingAlgorithm(const std::vector<Token> &tokens, std::vector<float> &stackOfValues, std::vector<char> &stackOfOperators)
{

    bool ok = true;
    for(int i=0; i<tokens.size(); i++){

        if(tokens[i].m_isValueToken )   // is digit
            stackOfValues.push_back(tokens[i].m_value);

        else if(isLegalOp(tokens[i].m_opSymbol) && stackOfOperators.size() > 0){    //more than one Op
            if(priorityOfOp(tokens[i].m_opSymbol) < priorityOfOp(stackOfOperators.back()))
                while(priorityOfOp(tokens[i].m_opSymbol) < priorityOfOp(stackOfOperators.back())){
                    if(stackOfValues.size() < 2)
                        return false;
                    calculate_and_pop(tokens, stackOfValues, stackOfOperators);
                    stackOfOperators.push_back(tokens[i].m_opSymbol);
                }
            else stackOfOperators.push_back(tokens[i].m_opSymbol);
        }

        else if(tokens[i].m_isValueToken == false){
            if(isLegalOp(tokens[i].m_opSymbol))
                stackOfOperators.push_back(tokens[i].m_opSymbol);

            else if( tokens[i].m_opSymbol == '(' )
                stackOfOperators.push_back('(');

            else if( tokens[i].m_opSymbol == ')' ){
                while(stackOfOperators.size() > 0 && stackOfOperators.back() != '(' ){
                    if(stackOfValues.size() < 2)
                        return false;
                    calculate_and_pop(tokens, stackOfValues, stackOfOperators);
                }
                stackOfOperators.pop_back();    // pops '('
            }

            else if(tokens[i].m_opSymbol == '=') // end of line
                while (stackOfOperators.size() > 0){
                    if(stackOfOperators.size() >= stackOfValues.size() // case: 5+  or 5++
                        || stackOfOperators.front() == '(') // case: (5+2
                        return false;
                    calculate_and_pop(tokens, stackOfValues, stackOfOperators);
                }

            else ok = false;
        }
    }
    return ok;
}

/*
        else if(tokens[i].m_isValueToken == false){
            if(isLegalOp(tokens[i].m_opSymbol) && stackOfOperators.size() == 0)
                stackOfOperators.push_back(tokens[i].m_opSymbol);

            else if( tokens[i].m_opSymbol == '(' ){
                stackOfOperators.push_back('(');
            }
            else if( tokens[i].m_opSymbol == ')' ){
                while( stackOfOperators.back() != '(' ){
                    if(stackOfValues.size() < 2)
                        return false;
                    calculate_and_pop(tokens, stackOfValues, stackOfOperators);
                }
            }

            else if(isLegalOp(tokens[i].m_opSymbol) && stackOfOperators.size() > 0){
                while(priorityOfOp(tokens[i].m_opSymbol) < priorityOfOp(stackOfOperators.back())){
                    if(stackOfValues.size() < 2)
                        return false;
                    calculate_and_pop(tokens, stackOfValues, stackOfOperators);
                    stackOfOperators.push_back(tokens[i].m_opSymbol);
                }
            }
*/

/*
        else if(tokens[i].m_isValueToken == false){
            if( isLegalOp(tokens[i].m_opSymbol) ){
                if(stackOfOperators.size() == 0)
                    stackOfOperators.push_back(tokens[i].m_opSymbol);

                else{
                    while(true){
                        if(priorityOfOp(tokens[i].m_opSymbol) < priorityOfOp(stackOfOperators.back())){
                            if(stackOfValues.size() < 2)
                                return false;
                            calculate_and_pop(tokens, stackOfValues, stackOfOperators);
                            stackOfOperators.push_back(tokens[i].m_opSymbol);
                        }
                        else {
                            stackOfOperators.push_back(tokens[i].m_opSymbol);
                            break;
                        }
                    }
                }

            }

            else if( tokens[i].m_opSymbol == '(' ){
                stackOfOperators.push_back('(');
            }
            else if( tokens[i].m_opSymbol == ')' ){
                while( stackOfOperators.back() != '(' ){
                    if(stackOfValues.size() < 2)
                        return false;
                    calculate_and_pop(tokens, stackOfValues, stackOfOperators);
                    stackOfOperators.pop_back();
                }
            }
*/









