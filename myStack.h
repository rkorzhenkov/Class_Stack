#ifndef __MYSTACK_H__
#define __MYSTACK_H__
#include<stdio.h>
#include<malloc.h>
#include <iostream>
using namespace std;

class stackElement {
      private:
              float x; // значение
              stackElement* prev; //указатель на предыдущий элемент
              stackElement* next; //указатель на следующий элемент
              
      
      public:
             stackElement();
             stackElement(const float& xx);
             
             stackElement(const float& xx, stackElement* prvPtr, stackElement* nxtPtr);
             
             stackElement(const stackElement& sE);
             
             
             ~stackElement(); //деструктор
              
			  void copy(const stackElement& sE);
             
             float get();
             stackElement& nextEl();
             stackElement *nextElPtr();
             stackElement& previousEl(); 
             stackElement *previousElPtr(); 
             void linkToPreviousEl(stackElement& prevElement);
             
             void linkToNextEl(stackElement& nextElement);
             void nullNextElPtr();
             
             void nullPreviousElPtr();
            
             void insertUpper(stackElement& prv);
             void insertLower(stackElement& nxt);
             
             void excludeFromChain();
             
            
};


class stack {
	private:
            stackElement* header;
            int length;
 
    public:   
	          stack();
	~stack();

void push(stackElement& sE);

void input_stack();

void stkPrint();
stackElement& pop();

stackElement& stkTop();

int getlength();

void sort();

void inverse();


void mergeToTop(stack& paste);


void delete_by_index(float key);



stack& operator-=(float key);

friend ostream& operator<<(ostream& output, stack& stk);

friend istream& operator>>(istream& input, stack& stk);

stack& operator=(stack& Q);

stackElement& elem_num (int k);
};

#endif
