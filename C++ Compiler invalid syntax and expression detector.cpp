// stack implementation using linklist
#include <iostream>
#include <string>
using namespace std;


class node{
    node * next;
    float data;
    public:
    node(){
        this->next = NULL;
        this->data = 0.0;
    }
    node(float data){
        this->data = data;
        this->next = NULL;
    }
    void set_next(node* next){
        this->next = next;
    }
    void set_data(float data){
        this->data = data;
    }
    node* get_next(){
        return this->next;
    }
    float get_data(){
        return this->data;
    }

};

class stack{
    node* top;
    public:
    stack(){
        this->top = NULL;
    }
    void set_top(node* top){
        this->top = top;
    }
    node* get_top(){
        return this->top;
    }

     void push(int v){
        if(top == NULL){
            node* temp = new node();
            top = temp;
            temp->set_data(v);
            return;
        }
        node* temp = new node();
        temp->set_data(v);
        temp->set_next(top);
        top = temp;
        
    }

    void pop(){
        node* temp = top;
        top = top->get_next();
        delete temp;
    }

    float peek(){// tell what is in the top
        return top->get_data();
    }

    bool isempty(){
        if(top == NULL){
            return true;
        }
        return false;
    }

   

    void display(){
        node* temp = top;
        while(top != NULL){
            cout<<top->get_data()<<" ";
            top = top->get_next();
        }
    }
};

// functions
int checkprecedence(char op){
    if(op == '^'){
        return 1;
    }
    else if(op == '*' || op == '/'){
        return 2;
    }
    else if(op == '+' || op == '-'){
        return 3;
    }
    else if(op == '%'){
        return 4;
    }
    else{
        return 0;
    }

}

bool checkop(char o){
    if(o == '+'|| o == '-' || o == '*' || o == '/' || o == '^' || o == '%'){
        return true;
    }
    else{
        return false;
    }
}

bool checkparenO(char o){
    if(o == '(' || o == '{'|| o == '[' ){
        return true;
    }
    else{
        return false;
    }
}

bool checkparenC(char o){
    if(o == ')' || o == '}'|| o == ']' ){
        return true;
    }
    else{
        return false;
    }
}

int typecheck(char c){
    if(c == '{' || c == '}'){
        return 3;
    }
    else if(c == '[' || c == ']'){
        return 2;
    }
    else if(c == '(' || c == ')'){
        return 3;
    }
    else{
        return 0;
    }
}

string postfix(string input){ // function to convert an expression to postfix 
    stack s2;
    string output = " ";

    for(int i = 0; i < input.length(); i++){
        if(input[i] == '('){
                s2.push(input[i]); 
        }
        else if(isdigit(input[i])){
            output += input[i];
        }
        else if(checkop(input[i])){
            if(s2.isempty()){
                s2.push(input[i]);
            }
            else{
                if(checkprecedence(s2.peek() == '(')){
                    s2.push(input[i]);
                }
                else if(checkprecedence(input[i]) > checkprecedence(s2.peek()) ){
                    s2.push(input[i]);
                }
                else if(checkprecedence(input[i]) < checkprecedence(s2.peek()) ){
                    
                    while(checkprecedence(input[i]) < checkprecedence(s2.peek()) || checkprecedence(s2.peek()) == checkprecedence(input[i])){
                        output += s2.peek();
                        s2.pop();
                    }
                    s2.push(input[i]);
                }
                else if(checkprecedence(s2.peek()) == checkprecedence(input[i])){   
                    output += s2.peek();
                    s2.pop();
                    s2.push(input[i]);
                }

            }
        }

        else if(input[i] == ')'){
            while(s2.peek() != '('){
                output += s2.peek();
                s2.pop();
            }
            s2.pop();
        }
        

    }

    // while(s.isempty() == false){// to empty stack in last
    //     output += s.peek();
    //     s.pop();
    // }

        return output;

    }


float evaluatepostfix(string exp){ // function to evaluate an expression
        stack s1;
        float r, x, y; 
        for(int i = 0; i < exp.length(); i++){
            if(isdigit(exp[i])){
                s1.push(float(exp[i]-'0'));
            }
            else if(exp[i] == ' '){

            }
            else{
                x = s1.peek();
                s1.pop();
                y = s1.peek();
                s1.pop();
                if(exp[i] == '+'){
                    r = x + y;
                    s1.push(r);
                }
                else if(exp[i] == '-'){
                    r =  x - y;
                    s1.push(r);
                }
                else if(exp[i] == '*'){
                    r =  x * y;
                    s1.push(r);
                }
                else if(exp[i] == '/'){
                    r =  x / y;
                    s1.push(r);
                }
                // else if(exp[i] == '%'){
                //     r =  x % y;
                //     s1.push(r);
                // }
                else if(exp[i] == '^'){
                    for(int i=0; i < y; i++ ){
                        x *= x;
                    }
                    r = x;
                    s1.push(r);
                }
            }
        }
        r = s1.peek();
        s1.pop();

        return r;
    }

bool check_invalid_expression(string exp){// function to check invalid expression
    stack s;

    for(int i = 0; i < exp.length(); i++){
        if(exp[i] == '{' || exp[i] == '[' || exp[i] == '('){
            s.push(exp[i]);
        }
        else if(exp[i] == '}' || exp[i] == ']' || exp[i] == ')'){
            if(s.isempty() || typecheck(s.peek()) != typecheck(exp[i])){
                return false;
                break;
            }
            else{
                s.pop();
            }
        }

        else if(exp[i] == ' '){
            continue;
        }
        
        else{
            if(i == 0){
                if(isdigit(exp[i])){
                    continue;
                }
            }
            else if(isdigit(exp[i])){
                int j = 1;
                while(isdigit(exp[i+j]) == true){
                    j++;
                }
                // cout<<"j = "<<j<<endl;
                // cout<<i<<endl;
                i += j-1;
                if(checkparenO(exp[i+1])){
                    return false;
                    break;
                }

                // else if( isdigit(exp[i]) ){
                else if(checkop(exp[i-j]) == false){
                    if(checkparenO(exp[i-j]) == false){
                        return false;
                        break;
                        }
                    
                    }
            }

            else if(checkop(exp[i]) && checkop(exp[i+1]) ){
                return false;
                break;
            }

            else if((exp[i] == '/' || exp[i] == '%') && exp[i+1] == '0'){
                return false;
                break;
            }
            continue;
        }
    }

    if(s.isempty() == false){
        return false;
    }
    return true;
}



int main(){
    string input;
    cout<<"Enter your expression here: "<<endl;
    cin >> input;
    if(check_invalid_expression(input)){
        cout<<postfix(input)<<endl;
        cout<<evaluatepostfix("562+*")<<endl;
    }

    else{
        cout<<"invalid expression"<<endl;
    }

    return 0;
}

// ((1+2)*2+4/(3+5*1)-9) expression
// 12+24+*35+1*9-/in precedence change 
//12+2*4351*+/+9-  in normal precedence
//562+*124/- = 37
// 8-[6-{4-(8-6+3)}]