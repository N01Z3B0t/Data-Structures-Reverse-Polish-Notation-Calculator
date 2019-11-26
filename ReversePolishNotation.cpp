/*
*/
/*============================================================================
 Name        : HW01_RPNCalc.cpp
 Author      : ErniE Reynoso
 Version     : 1.1
 Objective   : The program will take in a Polish expression that:
			   Separates the operators and operands by a single space
			   Terminates the expression with an equals sign.
			   Use a linked list to maintain the stack.

			   Handle the following situations (errors):
			   Too many operators (+ - / *)
			   Too many operands (doubles)
			   Division by zero

			   The program will continue to take and evaluate expressions until the user enters a zero (0) on a line by itself followed by a new line.
			   Sample output should show the handling of all the error conditions as well as make use of all of the operators.

			   Sample IO:
			   Input Output
			   10 15 + = 25
			   10 15 - = -5
			   2.5 3.5 + = 6 (or 6.0)
			   10 0 / = Error: Division by zero
			   10 20 * / = Error: Too many operators
			   12 20 30 / = Error: Too many operands
			  -10 -30 - = 20
			   100 10 50 25 / * - -2 / = -40
============================================================================*/
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>


using namespace std;

//Division by Zero Error
class DivByZero:public runtime_error
{
public:
    DivByZero():runtime_error("Division By Zero\n"){}
};

//Output Formatting
void header() {
	string HEADER = "REVERSE POLISH NOTATION CALCULATOR";
	unsigned int hdrLen = HEADER.length();

	cout << string(hdrLen, '+') << endl;
	cout << HEADER << endl;
	cout << string(hdrLen, '+') << endl;
}
//Output Formatting
void footer() {
	string HEADER = "REVERSE POLISH NOTATION CALCULATOR";
	unsigned int hdrLen = HEADER.length();

	cout << string(hdrLen, '=') << endl;
}

//Node structure
struct Node {
public:
	float data;
	Node* next;

	Node(float data, Node* next = 0)
	{
		this->data = data;
		this->next = next;
	}
};



//Linked List Class for Stack
class LinkedList {
private:		//Private members
	Node* top;

public:			//Public members
	int counter;

	LinkedList()	//LinkedList Constructor
	{
		top = NULL;
		counter = 0;
	}

	bool isEmpty()
	{
	  if (counter == 0)
	    {
		return true;
	    }
	  else
	    {
	      return false;
	    }
	}

	void push(float data)
	{
		Node* temp = new Node(data);
		temp->next = top;
		top = temp;
		counter++;

	}

	void printRPN()
	{
		string HEADER = string(17, '*');
		cout << HEADER << endl;
		for (Node* temp = top; temp != 0; temp = temp->next)
		{
			cout << "|\t" << temp->data << "\t|";
			cout << endl;
		}
		cout << HEADER << "\n" << endl;
	}


	float pop()
	{
		float popVal;

		if (isEmpty() == true)
		{
			cout << "Error: Stack Empty" << endl;
//			return -1;

		}//end if

		popVal = top->data;
		cout << "Popped Value: " << popVal << endl;
//		system("PAUSE");
		// Create a pointer to keep track of the top node
		Node* temp;
		temp = top;

		// Move the top of the stack to the next element
		// or null if there is no next element
		top = top->next;
		counter--;

		// Free up memory
		delete temp;
//		printRPN();

		// Send back the data

		//cout << " " << endl;


		//cout << "\n" << string(45, '*') << endl;	//Formatting Header
		//cout << "Number of items in the Queue: " << counter + 1 << endl;
		//cout << "Queue: ";
		//while (&temp != NULL) {
			//cout << temp->data << " -> ";
			//temp = temp->next;
		//}//end while
		return popVal;

	}

};







int main(void)
{
	LinkedList rpn;
	float value, result;
	string s, buffer;
	string operation;
	header();

	cout << "Enter value: \n>> ";
	getline(cin, s);

	stringstream str(s);

//	while(s!="0")
//	  {

	    while (s!= "=")
	      {

		while(!str.eof())
		  {
		    str >> buffer;

			if (stringstream(buffer) >> value)
			{
				rpn.push(value);
				rpn.printRPN();
			}
			      if (buffer == "+"  || buffer == "-" || buffer == "*" || buffer == "/")
				{
					  operation = buffer;
					  float lVal, rVal;
					  rVal = rpn.pop();
					  lVal = rpn.pop();



					    if (operation == "+")
					    {
						    result = lVal + rVal;
						    rpn.push(result);
						    rpn.printRPN();
					    }//end if

					    if (operation == "-")
					    {
						    result = lVal - rVal;
						    rpn.push(result);
						    rpn.printRPN();

					    }//end if

					    if (operation == "*")
					    {
						    result = lVal * rVal;
						    rpn.push(result);
						    rpn.printRPN();

					    }//end if

					    try
					    {
					      if (operation == "/")
						  {
							  if (rVal == 0)
							  {
							      cout << "Undefined" << endl;
							      throw DivByZero();
							  }//end if
							  else
							    {
								  result = lVal / rVal;
								  rpn.push(result);
								  rpn.printRPN();
							    }//end else
						  }//end if
					    }//end try

					    catch(DivByZero& e)
						    {
							cout << "Error: " << e.what() << endl;
							system("PAUSE");
						    }//end catch
					if(operation == "="){

					}


				  }//end if
			      rpn.printRPN();
		      }// end while str.eof()
			    cout << "Enter value: \n>> ";
			    	getline(cin, s);
	      }// end while "="


//	  }//end while "0"

	footer();





	//system("PAUSE");
	return 0;
}// end main


