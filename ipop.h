/* @Author 
* Student Name: Mustafa Saðlam 
* Student ID: 150140129
* Date: 24.12.2016
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define SIZE_STR 100

using namespace std;

struct Data{
	char* data;
	long num;// for queue storing values as long int to avoid converting char to long or long to char
	Data* next;
};

struct stack{	
	Data* top;
	bool isSempty();
	void push(char* toPush);
	char* pop();
	char* getHead();
	void makeSempty();
};

struct queue{
	Data *front, *back;
	bool isQempty();
	void enqueue(long toPush);
	long dequeue();
	long getAns();
	void makeQempty();
};

struct major{
	char postfix[SIZE_STR];
	char prefix[SIZE_STR];
	
	Data* head;
	stack s;
	queue q;
	
	void begin();
	void postfixer(bool isargc2);
	bool evaluator();
	void terminate();
};


void major::begin(){
	head = NULL;
	s.top = NULL;
	q.front = q.back = NULL;
}

bool stack::isSempty(){
	return top == NULL;
}

bool queue::isQempty(){
	return front == NULL;
}

void stack::push(char* toPush){
	Data* newElement = new Data;
	newElement->data = toPush;
	newElement->next = NULL;	
	
	if(isSempty()) top = newElement;
	else{
		newElement->next = top;
		top = newElement;
	}
}
	
void queue::enqueue(long toPush){
	Data* newElement = new Data;
	newElement->num = toPush;
	newElement->next = NULL;	
	
	if(isQempty())front = back = newElement;
	else{
		back->next = newElement;
		back = newElement;
	}
}	

long queue::getAns(){
	if(!isQempty()){
		return back->num;
	}
}

char* stack::getHead(){
	if(!isSempty()){
		return top->data;
	}
}

long queue::dequeue(){
	if(!isQempty()){
		Data* toPop = front;
		long dataToPop = toPop->num;
		front = front->next;
		delete toPop;
		return dataToPop;
	}
}

char* stack::pop(){
	if(!isSempty()){
		Data* toPop = top;
		char* dataToPop = toPop->data;
		top = top->next;
		delete toPop;
		return dataToPop;
	}
}

void queue::makeQempty(){
	if(!isQempty()){
		Data* traverse;
		while(traverse){
			traverse = front;
			front = front->next;
			delete traverse;
		}
	}
}

void stack::makeSempty(){
	if(!isSempty()){
		Data* traverse;
		while(top){
			traverse = top;
			top = top->next;
			delete traverse;
		}
	}
}		
		
void major::terminate(){
	if(!s.isSempty()) s.makeSempty();
	if(!q.isQempty()) q.makeQempty();
}

void major::postfixer(bool isargc2){
	char* token;
	postfix[0] = 0;
	int i= 0;
	token = strtok(prefix, " \n");
	while( token != NULL ){
		if(*token == '(')
			s.push(token);
			
		else if(strcmp(token, "abs") == 0)
			s.push(token);
			
		else if(strcmp(token, "sqrt") == 0 ){
			if( !s.isSempty() ){
				while (strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat(postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		else if(strcmp(token, "exp") == 0 ){
			if( !s.isSempty() ){
				while (strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat(postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		
		else if(strcmp(token, "mod") == 0){
			if( !s.isSempty() ){
				while (strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "exp") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat(postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		
		else if(strcmp(token, "log") == 0){
			if( !s.isSempty() ){
				while (strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "exp") == 0
					|| strcmp(s.getHead(), "mod") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat(postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);	
		}
		
		else if(strcmp(token, "min") == 0){
			if( !s.isSempty() ){
				while (strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "exp") == 0
					|| strcmp(s.getHead(), "mod") == 0
					|| strcmp(s.getHead(), "log") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat( postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		
		else if(strcmp(token, "max") == 0){
			if( !s.isSempty() ){
				while (strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "exp") == 0
					|| strcmp(s.getHead(), "mod") == 0
					|| strcmp(s.getHead(), "log") == 0
					|| strcmp(s.getHead(), "min") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat( postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		
		else if(strcmp(token, "product") == 0){
			if( !s.isSempty() ){
				while (strcmp(s.getHead(), "exp") == 0 
					|| strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "log") == 0
					|| strcmp(s.getHead(), "mod") == 0
					|| strcmp(s.getHead(), "min") == 0
					|| strcmp(s.getHead(), "max") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat(postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		
		else if(strcmp(token, "div") == 0){
			if( !s.isSempty() ){
				while (strcmp(s.getHead(), "product") == 0 
					|| strcmp(s.getHead(), "exp") == 0 
					|| strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "log") == 0
					|| strcmp(s.getHead(), "mod") == 0
					|| strcmp(s.getHead(), "min") == 0
					|| strcmp(s.getHead(), "max") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat(postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		// sum cannot be placed on product or div in the stack
		else if ((strcmp(token, "sum") == 0)){
			if(!s.isSempty()){
				while(strcmp(s.getHead(),"product") == 0 
					|| strcmp(s.getHead(), "div") == 0
					|| strcmp(s.getHead(), "exp") == 0 
					|| strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "log") == 0
					|| strcmp(s.getHead(), "mod") == 0
					|| strcmp(s.getHead(), "min") == 0
					|| strcmp(s.getHead(), "max") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat(postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		
		else if ((strcmp(token, "sub") == 0)){
			if(!s.isSempty()){
				while(strcmp(s.getHead(),"product") == 0 
					|| strcmp(s.getHead(), "div") == 0 
					|| strcmp(s.getHead(), "sum") == 0
					|| strcmp(s.getHead(), "exp") == 0 
					|| strcmp(s.getHead(), "sqrt") == 0
					|| strcmp(s.getHead(), "log") == 0
					|| strcmp(s.getHead(), "mod") == 0
					|| strcmp(s.getHead(), "min") == 0
					|| strcmp(s.getHead(), "max") == 0
					|| strcmp(s.getHead(), "abs") == 0){
					strcat(postfix, s.pop()); strcat(postfix, " ");
					if(s.isSempty()) break;
				}
			}
			s.push(token);
		}
		
		//if current cahr is ) then pop all in the stack until a (
		
		else if( strcmp(token, ")") == 0){
			while (strcmp(s.getHead(), "(") != 0){
				strcat(postfix, s.pop()); strcat(postfix, " ");
			}
			s.pop();
		}
		//operands are directly concatanate to the postfix string
		else{
			strcat(postfix, token);
			strcat(postfix, " ");
		}
					
		token = strtok(NULL, " \n");
	}

	while(!s.isSempty()){
		char tempPop[10];
		strcpy(tempPop,s.pop());
		tempPop[strcspn(tempPop, "\n")] = 0;
		strcat(postfix, tempPop);
		strcat(postfix, " ");
	}
	if(evaluator()){
		if(!isargc2) cout << endl << "Postfix string : " << postfix << endl ;
		if(!isargc2 && !q.isQempty()) cout << "Answer : " << q.getAns() << endl << endl;
	}
}

bool major::evaluator(){
	s.makeSempty();
	int pushC = 0;// pushing count
	long ans, out;
	char tempAns[16];
	char* taken = strtok(postfix, " \n");
	while(taken){
		if((*taken >= '0' && *taken <= '9') || (*taken == '-' && strcmp(taken,"-inf") != 0)){
			s.push(taken);
			pushC++;//incrementing pushing count to store how many number pushed;
		}
			
		else if(strcmp(taken,"ans") == 0 ){
			sprintf(tempAns, "%ld", q.getAns());
			s.push(tempAns);
			pushC++;
		}
		
		else if(strcmp(taken,"inf") == 0 || strcmp(taken,"-inf") == 0){
			cerr << "Syntax error. No meaning of " << taken << endl << endl;
			return false;
		}
		
		if(strcmp(taken, "sum" ) == 0){
			ans = 0;
			while(!s.isSempty()){
				if(atol(s.getHead()) == LONG_MIN){
					ans = LONG_MIN;
					break;
				}
				else if(atol(s.getHead()) == LONG_MAX){
					ans = LONG_MAX;
					break;
				}
				ans += atol(s.pop());
				pushC--;//decrementing pushing count to avoid operation confusions
			}
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "product") == 0){
			ans = 1;
			while(!s.isSempty()){
				if(atol(s.getHead()) == LONG_MIN){
					if(ans>0) ans = LONG_MIN;
					if(ans<0) ans = LONG_MAX;
					break;
				}
				else if(atol(s.getHead()) == LONG_MAX){
					if(ans>0) ans = LONG_MAX;
					if(ans<0) ans = LONG_MIN;
					break;
				}
				ans *= atol(s.pop());
				pushC--;
			}
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);			
		}
		
		if(strcmp(taken, "sub") == 0){
			long subtrahend, minuend;
			
			if(!s.isSempty()){
				subtrahend = atol(s.pop());
				pushC--;
			}
			else cout << "Syntax error." << endl;
			
			if(!s.isSempty()){
				minuend = atol(s.pop());
				pushC--;
			}
			else cout << "Syntax error." << endl;
			
			ans = minuend - subtrahend;
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "div") == 0){
			long dividend, divisor;
			
			if(!s.isSempty()){
				divisor = atol(s.pop());
				pushC--;
				if(divisor == 0){
					cout << "Syntax error." << endl << endl;
					s.pop();//for poping the dividend and clearing the stack
					return false;
				}
			}
			else cout << "Syntax error." << endl;
			
			if(!s.isSempty()){
				dividend = atol(s.pop());
				pushC--;
			}
			else cout << "Syntax error." << endl;
			
			ans = dividend/divisor;
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "abs") == 0){
			long toabsolute;
			
			if(!s.isSempty()){
				toabsolute = atol(s.pop());
				pushC--;
			
				if(toabsolute < 0) ans = -toabsolute;
				else ans = toabsolute;
			}
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "mod") == 0){
			long base, tomod;
			if(!s.isSempty()){
				base = atol(s.pop());
				pushC--;
					
			}
			if(pushC>0){
				if(!s.isSempty()){
					tomod = atol(s.pop());
					pushC--;
				}
				ans = base%tomod;
			}
			else ans = base%10;
			
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "sqrt") == 0){
			if(atol(s.getHead()) < 0){
				cout << "Syntax error." << endl << endl;
				s.pop();//for poping the tomod and clearing the stack
				return false;
			}
			if(!s.isSempty()){
				pushC--;
				ans = (long)(sqrt((double)atol(s.pop())));
			}
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "exp") == 0){
			double num1, num2;
			if(!s.isSempty()){
				num1 = atof(s.pop());
				pushC--;
			}
			if(pushC>0){
				if(!s.isSempty()){
					num2 = atof(s.pop());
					pushC--;
				}
				ans = (long)pow(num2, num1);
			}
			else ans = (long)exp(num1) +1;
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "log") == 0){
			double num1, num2;
			if(!s.isSempty()){
				num1 = atof(s.pop());
				pushC--;
			}
			if(pushC>0){
				if(!s.isSempty()){
					num2 = atof(s.pop());
					pushC--;
				}
				if(num2 <= 1){
					cout << "Syntax error." << endl << endl;
					return false;
				}
				ans = (long)(log(num1)/log(num2));
			}
			else ans = (long)(log(num1));
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "min") == 0){
			long num1;
			if(!s.isSempty()) ans = atol(s.pop());
			else cout << "Syntax error." << endl;
			while(!s.isSempty() && pushC>0){
				num1 = atol(s.pop());
				pushC--;
				if (num1<ans) ans = num1;
				else continue;
			}
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
		
		if(strcmp(taken, "max") == 0){
			long num1;
			if(!s.isSempty()) ans = atol(s.pop());
			else cout << "Syntax error." << endl;
			while(!s.isSempty() && pushC>0){
				num1 = atol(s.pop());
				pushC--;
				if (num1>ans) ans = num1;
				else continue;
			}
			sprintf(tempAns, "%ld", ans);
			s.push(tempAns);
		}
			
		taken = strtok(NULL, " \n");
	}
	q.enqueue(ans);// queueing the last ans value which the answer of the whole operation
	return true;
}

