/* Author: Shengdong (Andy) Li
   Date: 3/4/20
   Heap: A project that takes input from console or a file, creates a binary heap via insertion and bubbling up, visually displays this heap
   using inorder traversal, then extracts and bubbles down to display sorted input

   (◡ ‿ ◡ ✿)
*/

#include <iostream>
#include <cstring>
#include <fstream>

void getInput(char* in); //Literally cin.getline()
void bubbleup(int* z, int toAdd, int bubble); //Validates the heap from the bottom up
void bubbledown(int* z, int bubble); //Validates the heap from bottom down
void displayHeap(int* z, int bubble, int depth); //Displays the heap sideways using inorder traversal

using namespace std;

int main(){
  char* in = new char[999](); //User input for console input option

  int* z = new int[999](); //Where the heap will be stored, starts at 1
  int botleft = 1; //The location of the bottom left most empty node

  int choice = 0; //Variable to store whether the user chose console or file input

  bool running = true; //Actually not needed in this case, while(true) works just as well, but running is cooler

  bool valid = false; //Variable to store the validity of certain inputs

  while(running){
    //First ask for whether they want file input or console input
    while(true){
      cout << "Please Enter (1) for Console Input or (2) for File Input!" << endl;
      cin >> choice;
      cin.clear();
      cin.ignore(999, '\n');
      //1 asdjflkadsjfklasjd would be valid here, but I'm too lazy to fix it
      if(choice == 1 || choice == 2){
        break;
      }
      cout << "Please enter 1 or 2" << endl;
    }
    switch (choice){
    case 1:
      cout << "Ok, Please Enter Your Input" << endl;
      getInput(in);
      valid = true;
      break;
    case 2:
      //File Input Here
      cout << "Please enter the name of your file" << endl;
      getInput(in);
      //Creates a new file reader, opening the name of the file the user inputted
      ifstream stream(in);
      //Checks if the file was found or not
      if(!stream.good()){
        cout << "File not found!" << endl;
      }else{
        stream.getline(in, 999);
        valid = true;
      }
      break;
    }
    if(valid){
      //Prints the input just to make sure the input's good
      cout << "Input to be processed is: " << in << "." << endl;
      valid = false;
      int inputlen = strlen(in);
      //Stores the split ints from range 1-1000
      char* buf = new char[5](); 
      int counter = 0;
      //Loop through the input
      for(int a = 0; a < inputlen; ++a){
        //Add to the buffer
        buf[counter++] = in[a];
        //Until a space or end of input
        if(in[a] == ' ' || a == inputlen-1){
          //In which case, add it to the heap and bubble up!
          bubbleup(z, atoi(buf), botleft++);
          //Reset buffer and counters
          buf = new char[5]();
          counter = 0;
        }
      }
      //Prepare for next iteration
      valid = false;
    }
    //Actual
    // for(int a = 1; a < botleft; ++a){
    //   cout << z[a] << " ";
    // }
    //cout << endl;
    //Calls the display heap function after we fill up the heap
    cout << "Visual display of heap (powered by bubbles!):\n" << endl;
    displayHeap(z, 1, 0);
    //Then, just keep on extracting, printing, swapping, and bubbling down until the root node is null, displaying sorted values from high to low
    cout << "Sorted input (brought to you by bubbles!): ";
    while(z[1] != 0){
      //Print root
      cout << z[1] << " ";
      //Plugin the botleft to the spot
      z[1] = z[botleft-1];
      z[botleft-1] = '\0';
      botleft -= 1;
      //Then validate the heap from top down
      bubbledown(z, 1);
    }
    cout << endl;
    //Reset heap
    delete[] z;
    z = new int[999]();
    botleft = 1;
    cout << "\nThank you for choosing bubbles! (✿｡◕ ‿ ◕｡)\n" << endl;
  }
}

//Function literally gets input
void getInput(char* in){
  while(true){
    cin.getline(in, 999);
    if(strcmp(in, (char*)"") == 0){
      cout << "Please Enter Some Input" << endl;
    }else{
      break;
    }
  }
}

//Validates the heap from bottom up
void bubbleup(int* z, int toadd, int bubble){
  //First add to the botleft
  z[bubble] = toadd;
  //If we're already at the top then heap is validated, get out
  if(bubble == 1){
    return;
  }
  //Otherwise, define the parent node
  int pin = (int)(bubble/2);
  //While the current, new node is bigger than the parent
  while(z[bubble] > z[pin]){
    //Swap child with parent
    int temp = z[bubble];
    z[bubble] = z[pin];
    z[pin] = temp;
    //If the parent is at the top, get out
    if(pin == 1){
      return;
    }
    //Update child location to parent, find new parent location
    bubble = pin;
    pin = (int)(bubble/2);
  }
}

//This function is explicitly for bubbling down the top node, since recursion is used.
void bubbledown(int* z, int bubble){
  //Define the left and right children
  int left = bubble*2;
  int right = bubble*2+1;
  int largest = bubble;

  //Find the largest of 3: left, right, and current
  if(z[left] != 0 && z[left] > z[largest]){
    largest = left;
  }
  if(z[right] != 0 && z[right] > z[largest]){
    largest = right;
  }

  //If the largest is left or right
  if(largest != bubble){
    //Bubble them up! (swap) and move current down
    int temp = z[bubble];
    z[bubble] = z[largest];
    z[largest] = temp;
    //Recurse and bubble down again if needed
    bubbledown(z, largest);
  }
}

//This function uses inorder traversal to display the heap visually
void displayHeap(int* z, int bubble, int depth){
  //If the root node is null, get out, nothing to see here
  if(z[bubble] == 0){
    return;
  }
  //Recursively Step to the right
  displayHeap(z, bubble*2+1, depth+1);
  //Print spaces depending on depth to better display parent child relationships
  for(int a = 0; a < depth; ++a){
    cout << "    ";
  }
  //Then print value 
  cout << z[bubble] << "\n" << endl;
  //Recursively Step to the left
  displayHeap(z, bubble*2, depth+1);
}
