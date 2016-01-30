/*
 * hw1.c
 * TCSS 333 - Binary Calculator
 *
 *  Created on: Apr 1, 2015
 *      Author: Shannon Murphy
 */

#include <stdio.h>

float getFirstNum(char c, float firstNum, float power, int decimal) {
	if ((c == '0' || c == '1') && decimal == 0) {
		firstNum = (firstNum * 2.0) + (c - '0');
	} else if (decimal == 1) {
		if (c == '1') {
			firstNum += power;
		}
	}
	return firstNum;
}

float getSecondNum(char c, float secondNum, float power, int decimal) {
	if ((c == '0' || c == '1') && decimal == 0) {
		secondNum = (secondNum * 2.0) + (c - '0');
	} else if (decimal == 1) {
		if (c == '1') {
			secondNum += power;
		}
	}
	return secondNum;
}

void printDecimals(float total) {
	double powerOfTwo = 0.5;
	if (total == 0) {
		printf("%d", 0);
	}
	while (total > 0) {
		if (total - powerOfTwo >= 0) {
			total = total - powerOfTwo;
			printf("%d", 1);
		} else if (total - powerOfTwo < 0){
			printf("%d", 0);
		}
		powerOfTwo = powerOfTwo / 2;
	}
}

void printTotal(float total) {
	int power = 0;
	double powerOfTwo;
	if (total < 1) {
		printf("%d", 0);
	}
	while (pow(2, power) <= total) {
		power++;
		powerOfTwo = pow(2, power);
	}
	powerOfTwo = powerOfTwo / 2;
	while (powerOfTwo >= 1) {
		if (total - powerOfTwo >= 0) {
			total = total - powerOfTwo;
			printf("%d", 1);
		} else if (total - powerOfTwo < 0){
			printf("%d", 0);
		}
		powerOfTwo = powerOfTwo / 2;
	}
	printf("%c", '.');
	printDecimals(total);
}

char getOperationType(char c) {
	char operationType;
	if (c == '+') {
		operationType = 'a';
	} else if (c == '-') {
		operationType = 's';
	} else if (c == '*') {
		operationType = 'm';
	} else if (c == '/') {
		operationType = 'd';
	}
	return operationType;
}

float getTotal(char operationType, float firstNum, float secondNum) {
	float total;
	if (operationType == 'a') {
		total = firstNum + secondNum;
	} else if (operationType == 's') {
		total = firstNum - secondNum;
	} else if (operationType == 'm') {
		total = firstNum * secondNum;
	} else if (operationType == 'd') {
		total = firstNum / secondNum;
	}
	return total;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char c;
	float firstNum = 0;
	float secondNum = 0;
	int decimal = 0;
	float power = 0.5;
	int operation = 0;
	char operationType;
	float total;
	while (1) {
		scanf("%c", &c);
		if (c == 'Q') {
			return 0;
		}
		if (operation == 0) { // first number
			if (c == '+' || c == '-' ||c == '*' || c == '/') {
				operationType = getOperationType(c);
				decimal = 0;
				power = 0.5;
				operation = 1;
			} else if (c == '.') {
				decimal = 1;
			}
			firstNum = getFirstNum(c, firstNum, power, decimal);
			if (decimal == 1 && (c == '0' || c == '1')) {
				power = power / 2;
			}
		} else if (operation == 1) { // second number
			if (c == '.') {
				decimal = 1;
			}
			secondNum = getSecondNum(c, secondNum, power, decimal);
			if (decimal == 1 && (c == '0' || c == '1')) {
				power = power / 2;
			}
			if (c == '\n') {
				total = getTotal(operationType, firstNum, secondNum);
				printTotal(total);
				firstNum = 0;
				secondNum = 0;
				decimal = 0;
				operation = 0;
				power = 0.5;
			}
		}
	}
	return 0;
}
