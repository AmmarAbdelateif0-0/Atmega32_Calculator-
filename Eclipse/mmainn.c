/*
 * main.c
 *
 *  Created on: May 1, 2024
 *      Author: aboam
 */

#include "STD_TYPES.h"

#include"DIO_ErrorState.h"
#include "DIO_Interface.h"

#include"Keypad_Interface.h"

#include "CLCD_Interface.h"

typedef enum ERRORS{
	ER_MATHERROR,
	ER_SYNTAXERROR,
	ER_MATH_SYNTAX_OK,
}Errors_t;
int count=0;
char stack[30];
int numbers[30];
int top=-1;
void push(char x){
	stack[++top]= x;
}
char pop(){
	if(top== -1){
		return -1;
	}
	else{
		return stack[top--];
	}
}

u8 is_digit_t(char num){
	if( ( (num)>='0' ) && ( (num)<='9') ){
		return 1;
	}
	else
	{
		return 0;
	}
}
u8 priority(char operation){
	if(operation=='+' || operation=='-')
		return 1;
	else if(operation=='*' || operation=='/')
		return 2;

	return 0;

}
u8 IsOperator(char c){
	if(c=='+' || c=='-' || c=='*' || c=='/')
		return 1;
	return 0;
}
Errors_t validation(s8 *e,s8*postf){
	u8 Local_u8ErrorState=ER_MATH_SYNTAX_OK;
	int i=0;
	while(*e !='\0'){
		if(IsOperator((*e)) ){
			if( ( (*e=='-') || (*e=='+') ) && (i==0) ){
				if(*e=='+')
				{
					e++;
					continue;
				}
				postf[i]=*e;
				i++;
				e++;
				continue;
			}
			else if( ( (*e=='-') || (*e=='+') ) && (i!=0)){
				if( (e[i]=='-' && e[i+1]=='-') || (e[i]=='+' && e[i+1]=='+')){
					postf[i]='+';
					e++;
					e++;
					i++;
				}
				else if((e[i]=='-' && e[i+1]=='+') || ( e[i]=='+' && e[i+1]=='-' )){
					postf[i]='-';
					e++;
					e++;
					i++;
				}
				else if((e[i]=='-' && e[i+1]=='*') ||(e[i]=='-' && e[i+1]=='/') || (e[i]=='+' && e[i+1]=='*') ||(e[i]=='+' && e[i+1]=='/') ){
					Local_u8ErrorState=ER_SYNTAXERROR;
					return Local_u8ErrorState;
				}
				else if((e[i]=='-' && is_digit_t(e[i+1])) ||(e[i]=='+' && is_digit_t(e[i+1]))  ){
					postf[i]=*e;
					e++;
					i++;
				}
			}
			else if( ( (*e=='*') || (*e=='/') ) && (i==0) ){
				Local_u8ErrorState=ER_SYNTAXERROR;
				return Local_u8ErrorState;
			}
			else if( ( (*e=='*') || (*e=='/') ) && (i!=0)){
				if( (e[i]=='/' && e[i+1]=='/') || (e[i]=='*' && e[i+1]=='*') || (e[i]=='*' && e[i+1]=='/') || ( e[i]=='/' && e[i+1]=='*' )){
					Local_u8ErrorState=ER_SYNTAXERROR;
					return Local_u8ErrorState;
				}
				else if((e[i]=='/' && e[i+1]=='+') || ( e[i]=='*' && e[i+1]=='+' )){
					postf[i]=*e;
					e++;
					e++;
					i++;
				}
				else if((e[i]=='*' && is_digit_t(e[i+1])) ||(e[i]=='/' && is_digit_t(e[i+1]))  ){
					postf[i]=*e;
					e++;
					i++;
				}
			}

		}
		else{
			postf[i]=*e;
			i++;
			e++;
		}
	}
}

void infix_to_ABC(s8 * e,s8 * postf){
	int i=0;
	int j=0;
	int decimal=1;
	while(*e !='\0'){
		if(is_digit_t((*e)) || (*e == '-') ){
			if(decimal>1){

				numbers[j-1]*=decimal;
				// *e -'0'
				numbers[j-1]+=(*e-'0');
			}
			else{
				// *e -'0'
				numbers[j]=(*e-'0');
				postf[i]='A'+j;
				decimal=10;
				j++;
				i++;
			}
		}
		else{

			postf[i]=*e;
			decimal=1;
			i++;
		}
		e++;
	}

}
void infix_to_pstfix(s8 * e,s8 * postf){
	u8 i=0;
	while(*e !='\0'){
		if(is_digit_t((*e))){
			postf[i]=*e;
			i++;
		}
		else{
			while(priority(stack[top])>=priority(*e)){
				postf[i]=pop();
				i++;
			}
			push(*e);
		}
		e++;

	}
	while(top != -1)
	{
		postf[i]=pop();
		i++;
	}
}

int evaluation_postfixexp(s8 * postf){
	char ele;
	int i=0,num1,num2,result=0;

	while(i<=count)
	{
		ele =postf[i];
		if(is_digit_t(ele)){
			push(ele);
		}
		else{
			num1=pop();
			num2=pop();
			switch(ele){
			case '+':
				result=(num1-'0')+(num2-'0');
				break;
			case '-':
				result=(num2-'0')-(num1-'0');
				break;
			case '*':
				result=(num1-'0')*(num2-'0');
				break;
			case '/':
				result=(num2-'0')/(num1-'0');
				break;
			}
			push(result+'0');
		}
		i++;

	}
	return pop();

}
u8 is_pressed_C(char keypressed){
	if(keypressed=='o')
	{
		CLCD_EnuClearDisplay();
		return 1;
	}
	return 0;
}

void main(void){
	u8 Local_u8Key=0xff;
	s8 exp[30];
	s8 *e;
	s8  postfix[30];
	int result=0;

	DIO_EnuInit();
	CLCD_EnuInit();

	s8 i=0;


	while(1){
		while(KPD_u8GetPressedKey()!='='){
			do{
				Local_u8Key=KPD_u8GetPressedKey();
			}while(Local_u8Key==0XFF);

			if(is_pressed_C(Local_u8Key))
			{
				continue;
			}
			else if(Local_u8Key == '='){
				break;
			}


			exp[i]=Local_u8Key;
			i++;
			CLCD_EnuSendData(Local_u8Key);
		}
		e=exp;
		count=i;
		infix_to_pstfix(e,postfix);

		result=evaluation_postfixexp(postfix)-'0';

		CLCD_EnuGoToXY(1,0);

		CLCD_EnuWriteNumber(result);
		i=0;
	}
}
