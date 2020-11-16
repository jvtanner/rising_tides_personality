/*This program should allow user to take a personality test,
 * storing values for each of the OCEAN traits,
 * then compare them to a bank of characters, each with
 * their own predetermined traits, and tell user which
 * character has trait scores closest to their own.
 */



#include "YouGotHufflepuff.h"
#include "Testing/YouGotHufflepuffTests.h"
#include "hashset.h"
#include <cmath>
using namespace std;

HashMap<char, double> normalizeFormula(HashMap<char, int>& values);

double matchMaker(HashMap<char, double> user, HashMap<char, double> celeb);


void administerQuiz(const HashSet<Question>& questions,
                    int numQuestions,
                    const HashSet<Person>& people) {

    int askPersonalityQuestion(const Question& question);

    HashMap<char, int> values;

    values['O'] = 0;
    values['C'] = 0;
    values['E'] = 0;
    values['A'] = 0;
    values['N'] = 0;


    HashSet<Question> qBank;
    for (int i=0; i<numQuestions; i++){
        Question question = randomElement(questions);
        /*making sure we don't ask the same q twice*/
        if (!qBank.contains(question)){
            qBank.add(question);
            /*storing the user input as an integer*/
            int answer = askPersonalityQuestion(question);

            if (question.factors.containsKey('O')){
                values['O'] += (question.factors['O'] * (answer - 3));
            }
            if (question.factors.containsKey('C')){
                values['C'] += (question.factors['C'] * (answer - 3));
            }
            if (question.factors.containsKey('E')){
                values['E'] += (question.factors['E'] * (answer - 3));
            }
            if (question.factors.containsKey('A')){
                values['A'] += (question.factors['A'] * (answer - 3));
            }
            if (question.factors.containsKey('N')){
                values['N'] += (question.factors['N'] * (answer - 3));
            }
        /*if the question has been asked before, go back and pick another*/
        } else {
            i--;
        }
    }
    displayScores(values);
    if (values['O'] == 0 && values['C'] == 0 && values['E'] == 0
            && values['A'] == 0 && values['N']){
        displayMessage("Agree or disagree on something please!");
    }
    Person twinsie;
    HashMap<char, double> normalizedValues = normalizeFormula(values);
    for (Person celeb: people){
        HashMap<char, double> celebNormalizedValues = normalizeFormula(celeb.scores);
        double match = matchMaker(normalizedValues, celebNormalizedValues);
        double closest = -1;
        if (match > closest){
            twinsie = celeb;
            closest = match;
        }
    }
    void displayScores(const HashMap<char, int>& scores);
    displayMessage("You've matched with the Incredible " + twinsie.name);
}

HashMap<char, double> normalizeFormula(HashMap<char, int>& values){
    /*create a new hashmap which will hold the normalized values*/
    HashMap<char, double> normalizedValues;
    /*Normalize the scores*/
    double vectorLength = sqrt(pow(values.get('O'), 2) + pow(values.get('C'), 2)
                           + pow(values.get('E'), 2) + pow(values.get('A'), 2)
                           + pow(values.get('N'), 2));
    for (char trait: values){
        double normalValue = values[trait]/vectorLength;
        normalizedValues[trait] = normalValue;
    }
    return normalizedValues;
}

double matchMaker(HashMap<char, double> user, HashMap<char, double> celeb){
    return user['O']*celeb['O'] + user['C']*celeb['C']
           + user['E']*celeb['E'] + user['A']*celeb['A']
           + user['N']*celeb['N'];
}

/*
1. Create a Personality quiz
    - create a hashmap for the personality traits, set values to 0
    - pull a question from the hashset Questions
    - store the response in a variable
    - interpret the response as (-2, -1, 0, +1, +2) and update hashmap category
2. Administer the quiz and store the results
3. Compare the results to the persons hashset
*/







/* * * * *   Test Cases Below This Point   * * * * */

/* Because administerQuiz is a function that requires interaction with the user,
 * you won't be able to directly test that administerQuiz returns the correct
 * values. Similarly, you can't call the askPersonalityQuestion, displayScores,
 * or displayMessage functions, as those are wired into the demo and don't
 * work in testing.
 *
 * However, you are welcome to add test cases to test any helper functions you
 * write! To do so, use the ADD_TEST macro to define tests, just as you did in
 * Assignment 1 and for Rising Tides.
 *
 * You aren't required to include test cases in this part of the assignment,
 * though we definitely would encourage you to do so! This is a multistep
 * assignment that's going to require each individual function to work
 * correctly, and adding tests for the functions you write is a great way to
 * find and fix bugs early on.
 */

