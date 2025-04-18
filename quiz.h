/*
Author: Nava Karine Nizard
Course: CSCI-135
Instructor: Professor Tong Yi
Semester: Spring 2025
Brief: Declaration of functions
*/

#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cctype> //isspace()
#include <cstdlib> //rand() and srand()
#include <ctime>
#include "quiz.h" //declarations of functions
using namespace std;

struct Question 
{
    string text, answer, explanation, type, version, label;
};

void read_file(string fileName, Question ques[], int capacity, int& size);
string trim(string str);
int count_occurrences(string str, char ch);
string* extract_type(string type, int& num_types_curr_item);
void insert_order_unique(string type[], int type_capacity, int& type_count, string toAdd);
void insert_order_unique(string type[], int type_capacity, int& type_count, Question ques[], int& ques_size);
string choose_type(string* types, int type_count);
void randomize(Question ques[], int size);
void feedback(int num_correct, int num_questions);
void answer_by_type(Question ques[], int size, string chosen_type);
void reorder(Question ques[], int size, int idx);
bool type_related(string type_to_focus, string curr_type);

#endif
