/*
Author: Nava Karine Nizard
Course: CSCI-135
Instructor: Professor Tong Yi
Semester: Spring 2025
Brief: Definition / Implementation of functions
*/

#include "quiz.h" //declarations of functions
using namespace std;

//Read the data from a txt file into a Question array
void read_file(string fileName, Question ques[], int capacity, int& size){
    //test the file if it can be opened.
    ifstream fin(fileName);
    if(fin.fail()){
        cerr << "File could not be opened. ";
        exit(1);
    }

    string line, text, answer, explanation, version, label, type;

    //Read the data line by line
    while(getline(fin, line) && !line.starts_with("question: ")) //Read the data until it starts with "question:"
        ; 

    while(line.starts_with("question: ")){
            text = line.substr(strlen("question: ")); //remove the text "question: " to only get the contents.
            while(getline(fin, line) && !line.starts_with("answer: ")){
                text+= '\n' + line;
            }

        if(line.starts_with("answer: ")){
            answer = line.substr(strlen("answer: "));
            while(getline(fin, line) &&   !(line.starts_with("explanation: ") || 
                                            line.starts_with("type: ") || 
                                            line.starts_with("version: ") || 
                                            line.starts_with("label: ") || 
                                            line.starts_with("question: "))){
                answer+= '\n' + line;
            } 
        }

        if(line.starts_with("explanation: ")){
            explanation = line.substr(strlen("explanation: "));
            while(getline(fin, line) &&   !(line.starts_with("version: ") || 
                                            line.starts_with("label: ") || 
                                            line.starts_with("type: ") ||
                                            line.starts_with("question: "))){
                explanation+= '\n' + line;
            }
        }

        do{
            if(line.starts_with("version: ")){ 
                version = line.substr(strlen("version: "));
            }

            if(line.starts_with("label: ")){ 
                label = line.substr(strlen("label: "));
            }

            if(line.starts_with("type: ")){ 
                type = line.substr(strlen("type: "));
            }

        } while(getline(fin, line) && !line.starts_with("question: "));

        //if there's insufficient capacity, quit the program.
        if (size >= capacity){
            return; 
        }
        //Store all the data collected into the array, after a full question is read.
        ques[size].text = text;
        ques[size].answer = answer;
        ques[size].explanation = explanation;
        ques[size].version = version;
        ques[size].label = label;
        ques[size].type = type;
        size++;
        //Reset variables for a new question
        text = answer = explanation = version = label = type = ""; 
    }
    fin.close();
}

//Trims all white spaces preceding and following text
string trim(string str)
{
    int len = str.length();
    int startIdx = 0;
    int endIdx = len - 1;

    while(isspace(str[startIdx])){
        startIdx++;
    }
    while(isspace(str[endIdx])){
        endIdx--;
    }

    return str.substr(startIdx, endIdx - startIdx + 1);
}

//Counts the occurrences of a specified char in a string
int count_occurrences(string str, char ch) 
{
    int len = str.length();
    int count = 0;
    for (int i = 0; i < len; i++){
        if (str[i] == ch){
            count++;
        }
    }
    return count;
}

//Create a dynamically allocated array with all the types
string* extract_type(string type, int& num_types_curr_item)
{
    num_types_curr_item = count_occurrences(type, ';') + 1; //amount of types in this line
    string* types_array = new string[num_types_curr_item]; //create a DA array with the size of the types
    int len = type.length();
    int typeCount = 0;
    int startIdx = 0;
    int endIdx = 0;
    for (int i = 0; i < len; i++){ //loop through the string
        if (type[i] == ';') { //when you find a semicolon
            endIdx = i;
            string newString = type.substr(startIdx, endIdx - startIdx); //get substring before ';'
            types_array[typeCount] = trim(newString);
            typeCount++;
            startIdx = endIdx + 1; //after the semicolon
        }
    }
    types_array[typeCount] = trim(type.substr(startIdx)); //handle the last string after the semicolon
    typeCount++;
    return types_array;
}

//Adds the type to a sorted array in the correct position.
void insert_order_unique(string type[], int type_capacity, int& type_count, string toAdd)
{
    if (type_count >= type_capacity){ //if there's not sufficient space, leave
        return;
    }

    for (int i = 0; i < type_count; i++){ //loop through the array
        if(type[i] == toAdd){ //no duplicates
            return;
        }
        if(type[i] > toAdd){ //if toAdd comes before the curr type
            for(int j = type_count; j > i; j--){ //loop through the rest of the types backwards
                type[j] = type[j - 1]; //shift all the elements to the right to make space
            }
            type[i] = toAdd; 
            type_count++;
            return;
        }
    }
    type[type_count] = toAdd;
    type_count++;

}

void insert_order_unique(string type[], int type_capacity, int& type_count, Question ques[], int& ques_size)
{
    for (int i = 0; i < ques_size; i++){ //loop through every question in the Question array
        int curr_type_count = 0;
        string *type_array = extract_type(ques[i].type, curr_type_count); //extarct the types into a DA array
        for(int j = 0; j < curr_type_count; j++){
            insert_order_unique(type, type_capacity, type_count, type_array[j]); //insert each type into the
        }                                                                       //bigger array
        delete[] type_array;
    }
}

//Returns the user's chosen type after printing out a list of types to select from
string choose_type(string* types, int type_count)
{
    cout << "0. ALL TYPES" << endl;
    for(int i = 0; i < type_count; i++){
        cout << i + 1 << ". " << types[i] << endl;
    }

    int userType;
    do{
        cout << "Enter a type: ";
        cin >> userType;
    }while(userType < 0 || userType > type_count);
    cin.ignore(); //cin and getline interfering
    if(userType == 0){
        return "";
    }
    else{
        return types[userType - 1];
    }
}

//Shuffle and randomize each question in the Question array
void randomize(Question ques[], int size)
{
    int numToRandomize = size;
    srand(time(NULL));
    while(numToRandomize > 1){ //when there's one element left, no need to shuffle
        int rand_int = rand() % numToRandomize; //pick a random idx from the first numToRandomize elements
        Question temp = ques[rand_int];
        ques[rand_int] = ques[numToRandomize - 1]; //swap the chosen element with the last unshuffled
        ques[numToRandomize - 1] = temp;          // element (numToRandomize - 1)
        numToRandomize--; //now the last one is in place, so reduce the range
    }
}

//Calculates the percentage and corresponding feedback based on the score
void feedback(int num_correct, int num_questions)
{
    cout << "Number of correct answers: " << num_correct << " out of " <<
        num_questions << " questions." << endl;
    double percentage = num_correct * 100.0 / num_questions;
    cout << "Percentage of correct problems: " << percentage << "%" << endl;

    if (percentage >= 90){
        cout << "Excellent!" << endl;
    }
    else if(percentage >= 80){
        cout << "Good!" << endl;
    }
    else if(percentage >= 70){
        cout << "Pass." << endl;
    }
    else{
        cout << "Please ask help ASAP." << endl;
    }
}

//Simulate a question-by-question quiz based on the user-given type
void answer_by_type(Question ques[], int size, string chosen_type)
{
    cout << endl; //new line after choosing a type
    int correctQuestionCount = 0;
    int selectedQuestions = 0;
    for (int i = 0; i < size; i++){ //loop through each question
        if (ques[i].type.find(chosen_type) != -1){ //if the question includes the user type, display it
            selectedQuestions++;
            int tries = 0;
            bool correct = false;
            string userAnswer;
            cout << "Question " << i + 1 << "." << endl; //starts at index 0
            cout << ques[i].text << endl;
            do{
                cout << "Enter your answer: ";
                getline(cin, userAnswer);
                tries++;
                cout << "Number of tries: " << tries << endl;
                if (userAnswer == ques[i].answer){
                    correct = true;
                    correctQuestionCount++;
                }
                cout << boolalpha << correct << endl;
            } while(tries < 3 && !correct);

            if(tries == 3 && !correct && ques[i].explanation != ""){ //after 3 incorrect
                cout << "Answer: " << ques[i].answer << endl << "Explanation: " << 
                ques[i].explanation << endl;
            }
            if((tries == 3 && !correct) || chosen_type == ""){
                reorder(ques, size, i);
            }

            cout << endl;
        }
    }
    feedback(correctQuestionCount, selectedQuestions);
}

void reorder(Question ques[], int size, int idx) //idx is the idx of the type they failed
{
    // METHOD 1 (didnt work)
    // int idx_of_first_unrelated_ques = idx + 1; //look at all the ques after the curr
    // while(!type_related(ques[idx].type, ques[idx_of_first_unrelated_ques].type)){
    //         idx_of_first_unrelated_ques++;
    // }
    // int idx_of_last_related_ques = size - 1; 
    // while(type_related(ques[idx].type, ques[idx_of_last_related_ques].type)){
    //     idx_of_last_related_ques--; //get the last one in the array that has a related type
    // }
    // int last = idx_of_last_related_ques;
    // for (int i = idx_of_first_unrelated_ques; i < last; i++){
    //     if(!type_related(ques[idx].type, ques[i].type)){
    //         swap(ques[i], ques[idx_of_last_related_ques]);
    //     }
    //     idx_of_last_related_ques--;
    //     idx_of_first_unrelated_ques++;
    // }

    string type_to_focus = ques[idx].type;
    for (int i = idx + 1; i < size; i++){
        if (type_related(type_to_focus, ques[i].type)){ //if the type we're checking is already in the right place,
            continue; //move to next iteration. Don't swap anything
        }
        int curr_type = i + 1; //the one to switch with (the first related one)
        while(curr_type < size && !type_related(type_to_focus, ques[curr_type].type)){ //as long as still within bounds and unrelated
            curr_type++;
        }
        //if you leave the while loop, either because it's out of bounds or because you found a related type
        //so check if still within bounds
        if (curr_type < size){
            swap(ques[curr_type], ques[i]); //swap the related one with the one unrelated
        }
        else{ //if it's out of bounds, no more elements to swap with, so you're done
            break;
        }
    }

}

bool type_related(string type_to_focus, string curr_type)
{
    int type1_size = 0, type2_size = 0;
    string* type1 = extract_type(type_to_focus, type1_size); //create an array with the types in the first string
    string* type2 = extract_type(curr_type, type2_size); //create an array with the types in the second string
    
    for (int i = 0; i < type1_size; i++){ //loop through the first
        for (int j = 0; j < type2_size; j++){ //loop through the second
            if (type1[i] == type2[j]){ //check if they're the same type
                delete[] type1;
                delete[] type2;
                return true;
            }
        }
    }
    delete[] type1; //remove DA memory
    delete[] type2;
    return false;

    //WRONG:
    // return (curr_type.find(type_to_focus) != -1);
}
