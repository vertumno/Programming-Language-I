/**
 * @file    evaluate_expression.cpp
 * @brief   Main function that shows brief dialog with user and receives
 * 			his input. Calls arithmetic manipulations functions and informs
 *			at the end the result of the given postfix expression.
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @since   26/10/2017
 * @date    27/10/2017
 */

#include "task_two/arithmetic_manipulation.h"

int main(int argc, char const *argv[])
{
	// Showing brief dialog with user and getting expression.
	// ========================================================================================
	string expression;
	cout << endl << "===========================================================================" << endl;
	cout << "My man! Welcome to my Postfix Calculator. Fancy name, eh?" << endl;
	cout << endl << "Before you begin, you must know a few things:" << endl;
	cout << "I - You *must* split each term of your equation with a single blank space." << endl;
	cout << "II - You *must* provide a valid postfix expression." << endl;
	cout << "Failing in any of these rules, the algorithm will be terminated." << endl;
	cout << endl << "Now, please type in your expression: " << endl;
	getline(cin, expression);
	// ========================================================================================
	
	// Splitting expression's components by blank spaces.
	// ========================================================================================
	vector<string> postfix = split_sentence_blank_spaces(expression);
	// ========================================================================================

	// Informing the user of his expression's result.
	// ========================================================================================
	cout << endl;
	cout << "Result: " << compute_expression(postfix) << " Infix: " << postfix_to_infix(postfix);
	cout << endl;
	// ========================================================================================

	cout << "===========================================================================" << endl << endl;
}