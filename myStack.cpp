#include<stdio.h>
#include<malloc.h>
#include <iostream>
#include "myStack.h"
using namespace std;

             stackElement::stackElement():
                            x(0),
                            prev(NULL),
                            next(NULL)
             {} //конструктор по умолчанию
             
             stackElement::stackElement(const float& xx):
                          x(xx),
                          prev(NULL),
                          next(NULL)
             {} //конструктор с известным значением
             
             stackElement::stackElement(const float& xx, stackElement* prvPtr, stackElement* nxtPtr):
                                x(xx),
                                prev(prvPtr),
                                next(nxtPtr)
             {} //конструктор с известным значением и указателем
             
             stackElement::stackElement(const stackElement& sE):
                                x(sE.x),
                                prev(sE.prev),
                                next(sE.next)
             {} //constructor - copier
             
             
             stackElement::~stackElement() {} //деструктор
              
			  void stackElement::copy(const stackElement& sE) { //делает копию существующего элемента
                  this->x = sE.x;
                  this->prev = sE.prev;
                  this->next = sE.next;
                  return;    
            
             }
             
             float stackElement::get() {
                   return x;      
             } //получить значение
             
             stackElement& stackElement::nextEl() {
                          if (this->next != NULL)
                             return *(this->next);
                          else {
                               printf("There's no next stackElement!\n");
                               return *this;
                          }
             } //возвращение следующего элемента
             
             stackElement* stackElement::nextElPtr() {
                          return this->next;
             } //возвратить указатель на следующий элемент
             
             stackElement& stackElement::previousEl() {
                          if (this->prev != NULL)
                             return *(this->prev);
                          else {
                               printf("There's no previous stackElement!\n");
                               return *this;
                          }
             } //возвращает предыдущий элемент
             
             stackElement* stackElement::previousElPtr() {
                          return this->prev;
             } //возвращает указатель на предыдущий элемент
             
             
             
             void stackElement::linkToPreviousEl(stackElement& prevElement) {
                  this->prev = &prevElement;
                  prevElement.next = this;
                  return;
             } //соединяет элемент с данным предыдущим
             
             void stackElement::linkToNextEl(stackElement& nextElement) {
                  this->next = &nextElement;
                  nextElement.prev = this;
                  return;
             } //соединяет элемент с данным следующим
             
             void stackElement::nullNextElPtr() {
                  this->next = NULL;
                  return;     
             } //обнуление указателя на следующий элемент
             
             void stackElement::nullPreviousElPtr() {
                  this->prev = NULL;
                  return;     
             } //обнуление указателя на предыдущий элемент
            
             void stackElement::insertUpper(stackElement& prv) {  //вставка элемента перед данным в цепи
                  stackElement* nxt;
                  int flag = 1;
                  if (prv.next != NULL)
                     nxt = prv.next;
                  else 
                       flag = 0;
                  this->linkToPreviousEl(prv);
                  if (flag == 1)
                     this->linkToNextEl(*nxt);
                  return;                  
             }
             
             void stackElement::insertLower(stackElement& nxt) {  // вставка элемента после данного в цепи
                  stackElement* prv;
                  int flag = 1;
                  if (nxt.prev != NULL)
                     prv = nxt.prev;
                  else 
                       flag = 0;
                  this->linkToNextEl(nxt);
                  if (flag == 1)
                     this->linkToPreviousEl(*prv);
                  return;                  
             }
             
             void stackElement::excludeFromChain() {  //исключение элемента из цепи
                  stackElement *nxt;
                  stackElement *prv;
                  int flag_next = 1;
                  int flag_prev = 1;
                  if (this->next == NULL)
                     flag_next = 0;
                  else
                      nxt = this->next;
                  if (this->prev == NULL)
                     flag_prev = 0;
                  else
                      prv = this->prev;
                  if (flag_next * flag_prev == 1)
                     nxt->linkToPreviousEl(*prv);
                  else if (flag_next == 0)
                       prv->next = NULL;
                  else 
                       nxt->prev = NULL;
                  this->next = NULL;
                  this->prev = NULL;
                  return;
             }



 
	          stack::stack():
                      header(new stackElement()),
                      length(0)
                      {}
	stack::~stack(){}

void stack::push(stackElement& sE) { 
     sE.insertLower(*(this->header));
     ++(this->length);
     return;
} 

void stack::input_stack() {
	int initial_length;
	int i, n;
	float elem;
	initial_length = this -> length;
	printf("input number of elements to input: ");
  	scanf("%d", &n);
  	for(i = initial_length + 1; i <= initial_length + n; i++) {
    	printf("input element # %d: ", i);
    	scanf("%f", &elem);
    	this->push(*(new stackElement(elem)));
  	}
  	return;
}

void stack::stkPrint() {
  int i;
  stackElement* sEP;
  i = this->length;
  sEP = this->header;
  if(i == 0) {
       printf("Stack is empty!\n");
       return;
  }
  do {
    i--;
    sEP = sEP->previousElPtr();
    printf("%f\n", sEP->get());
  } while(i>0);
  printf("End of stack!\n");
  return;
}

stackElement& stack::pop() {
  if((this->length) > 0) {
    this->length--;
    
    stackElement &sE = this->header->previousEl();
    sE.excludeFromChain();
    
    return(sE);
  } else {
    printf("stack is empty!\n");
    return *(this->header);
  }
}

stackElement& stack::stkTop() {
  if((this->length) > 0) {
    return( this->header->previousEl() );
  } else {
    printf("stack is empty!\n");
    return *(this->header);
  }
}

int stack::getlength() {
 return(this->length);
}

void stack::sort() {
     if (this->length < 2) 
        return;
     stack sorted;
     stackElement* current;
     sorted.header = this->header;
     sorted.length = 1;
     int flag, j;
     
     stackElement* sE;
     stackElement* prv = NULL;
     sE = this->header->previousElPtr()->previousElPtr();
     for (int i = this->length - 2; i >= 0; --i) {
         if (i > 0)
            prv = sE->previousElPtr();
         sE->excludeFromChain();
         current = sorted.header->previousElPtr();
         flag = 0;
         j = sorted.length;
         while (flag == 0 && j > 0) {
               --j;
               if (sE->get() >= current->get())
                  flag = 1;
               if (j > 0 && flag == 0)
                  current = current->previousElPtr();                  
         }
         if (flag == 1)
            sE->insertUpper(*current);
         else
             sE->insertLower(*current);
         ++(sorted.length);
         if (i > 0)
            sE = prv;
     }
     return;
}

void stack::inverse() {  //инвертация стека
	int n = this->length;
	if (n < 2)
	   return;           //если длина < 2 - ничего не делать
    stackElement *current;   //последний новоупорядоченный элемент
	stackElement *beforeLast; //следующий для последнего староупорядоченного 
	stackElement *last;       //последний староупорядоченный
	
	current = (this->header);
	beforeLast =  (this->header);
	
	for (int i = 1; i < n; ++i)
	    beforeLast = beforeLast->previousElPtr();
     last = beforeLast->previousElPtr();
     for (int i = 1; i <= n; ++i) {
         last->excludeFromChain();
         last->insertLower(*current);
         current = last;
         last = beforeLast;
         beforeLast = beforeLast->nextElPtr();
     }
     return;
}


void stack::mergeToTop(stack& paste) {
     int n_bottom = this->length;
     int n_top = paste.getlength();
     stackElement *sE;
     sE = paste.header;
     for (int i = 1; i <= n_top; i++)
         sE = sE->previousElPtr();
     this->header->linkToNextEl(*sE);
     this->header->excludeFromChain();
     this->header = paste.header;
     this->length = n_top + n_bottom;
     return;
}


void stack::delete_by_index(float key) {
     int n = this->length;
     if (n == 0)
        return;
     stackElement* sE;
     stackElement* removed;
     sE = this->header->previousElPtr();
     while (n > 0) {
             --n;
             if (sE->get() == key) {
                           removed = sE;
                           if (n>0) 
                              sE = sE->previousElPtr();
                           removed->excludeFromChain();
                           --(this->length);
                           delete removed;
             } else
                   if (n>0)
                      sE = sE->previousElPtr();
                      
     }
	return;
}

stack& stack::operator-=(float key) {
	this->delete_by_index(key);
	return *this;
}

ostream& operator<<(ostream& output, stack& stk) {
	int i;
  stackElement* sEP;
  i = stk.length;
  sEP = stk.header;
  if(i == 0) {
       output<<"Stack is empty!"<<endl;
       return output;
	}
	
	do {
    i--;
    sEP = sEP->previousElPtr();
    output<< (sEP->get()) << endl;
  } while(i>0);
  output << "End of stack!" << endl;
  return output;
}

istream& operator>>(istream& input, stack& stk) {
	int initial_length;
	int i, n;
	float elem;
	initial_length = stk.length;
	cout<<"Input number of elements: ";
  	input>>n;
  	for(i = initial_length + 1; i <= initial_length + n; i++) {
  		cout<<"Input element #"<<i<<": ";
    	input>>elem;
    	stk.push(*(new stackElement(elem)));
  	}
  	return input;
}

stack& stack::operator=(stack& Q) {
	this->header = Q.header;
	this->length = Q.length;
	return *this;
}

stackElement& stack::elem_num (int k) {
	stackElement* sE= this->header;
	for (int i=1;i<=k;i++)
		sE=sE->previousElPtr();
	return *sE;
}

