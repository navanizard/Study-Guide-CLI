/*
Author: Nava Karine Nizard
Course: CSCI-135
Instructor: Professor Tong Yi
Semester: Spring 2025
Brief: This program dynamically generates and tracks questions in a quiz 
based on user performance, prioritizing incorrect answers for review.
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
    // read_file("cs135_midterm_f24_v2.txt", ques, CAPACITY, questionCount);
    // read_file("cs135_midterm_s24_v1.txt", ques, CAPACITY, questionCount);
    // read_file("135_final_short_ques.txt", ques, CAPACITY, questionCount);

    const int TYPE_CAPACITY = 30;
    string types[TYPE_CAPACITY];
    int typeCount = 0;

    randomize(ques, questionCount);
    insert_order_unique(types, TYPE_CAPACITY, typeCount, ques, questionCount);
    string userType = choose_type(types, typeCount);
    answer_by_type(ques, questionCount, userType);

    return 0;
}

