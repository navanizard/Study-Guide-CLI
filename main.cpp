/*
Author: Nava Karine Nizard
Course: CSCI-135
Instructor: Professor Tong Yi
Date: April 10, 2025.
Assignment: Project 2C

This program reorders the questions by bringing the questions
on the types the user got wrong 3 times to the fore-front.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cctype> //isspace()
#include <cstdlib> //rand() and srand()
#include <ctime>
#include "quiz.h" //declarations of functions
using namespace std;

int main() 
{
    const int CAPACITY = 1000;
    int questionCount = 0;
    Question ques[CAPACITY];
    read_file("cs135_midterm_f24_v1.txt", ques, CAPACITY, questionCount);
    read_file("cs135_midterm_f24_v2.txt", ques, CAPACITY, questionCount);
    read_file("cs135_midterm_s24_v1.txt", ques, CAPACITY, questionCount);

    const int TYPE_CAPACITY = 30;
    string types[TYPE_CAPACITY];
    int typeCount = 0;

    insert_order_unique(types, TYPE_CAPACITY, typeCount, ques, questionCount);
    string userType = choose_type(types, typeCount);
    answer_by_type(ques, questionCount, userType);
    return 0;
}

