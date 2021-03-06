/*
SOURCE CODE


2/23/2015
Written over the span of 2 weeks.
*/
#include <iostream> //Include libraries for the use of their functions.
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class security{ //Declare a class called security.
private:
  int rot;
  string cryptogram;
public:
  // security(int r,string cryp);                          //Constructor method with default values initialized in the implementation section.
  security();
  void decision();                                      //A method which holds a menu for the user that is called in the main.
  void encryptFileUsingRot(int rot);                  //Encrypts a whole file using the rotation method. Taking in a rotation key inputted by the user
  string encryptWordUsingRot(int rot,string word);    //Encrypts a single word for the encryptFileUsingRot function. Taking in both the rotation key and a word from the encryptFileUsingRot function.
  void encryptFileUsingCrypto();                      //Encrypts a file using the cryptogram with a cryptogram.
  string decryptWordUsingRot(int rot,string word);      //Decrypts a single word using the rotation method for decryptUsingRot function. Passing the rotation key inputted by the user and a word from the decryptUsingRot function.
  void decryptUsingRot(int rot);                        //Decrypts a whole file using the rotation method. Taking in a rotation key inputted by the user.
  void decryptFileUsingCrypto();                        //Decrypts a whole file using the cryptogram method with a cryptogram.
};

//security::security(int r,string cryp)           //A constructor method with "r" initialized with 0 and "cryp" initialized with a space.
security::security() 
{
  rot = 0;     //Set attributes equal to the initial values.
  cryptogram = " ";
}

void security:: decision()  //A function that holds a menu for the user. Consisting of usable functions that were declared in the public section.
{
  int choice1;
  cout<<"\n1.Encrypt: ";
  cout<<"\n2.Decrypt: ";
  cin>>choice1;

  if(choice1==1)                                //Encrypt files if choice1 == 1.
    {
      int choice2;  //A local variable that takes in a response from the user.
      cout<<"\n1.Encrypt using ROT: ";
      cout<<"\n2.Encrypt using cryptogram: ";
      cin>>choice2;
      if(choice2==1)                            //Encrypt using ROT if choice2 == 1
        {
          int rot;  //A local variable that takes in the rotation key inputted by the user.
          cout<<"Enter ROT number: ";
          cin>>rot;
          encryptFileUsingRot(rot);             //Calls encryptFileUsingRot function, passing a "rot" number to the function.

        }
      else if(choice2==2)                       //Encrypt file using a cryptogram if choice2 == 2
        {
          encryptFileUsingCrypto();             //Calls encryptFileUsingCrypto() function.
        }

    }
  else if(choice1==2)                           //Go to decryption section if choice 1 == 2.
    {
      int choice3;  //A local variable that holds the response from the user.
      cout<<"1.Decrypt using ROT: ";
      cout<<"2.Decrypt using cryptogram: ";
      cin>>choice3;
      if(choice3==1)
        {
	  int rot2;  //Local variable that holds the rotation key. Must match the key used for the encryption.
	  cout<<"Enter ROT key: ";
          cin>>rot2;
          decryptUsingRot(rot2);                //  Calls decryptUsingRot method and passes "rot2".
        }
      else if(choice3==2)
        {
	  decryptFileUsingCrypto();           //Calls the decryptFileUsingCrypto function.
        }
    }
}

void security::encryptFileUsingRot(int rot)//Parameters include the rotation key which is passed from the decision function.
{
  string fileName;  //Local variable that holds what the user wants to encrypt.
  string resultFile;    //Local variable that holds the encryption file name inputted by the user.
  cout<<"Enter file name of desired encrypted file(Include suffix): ";
  cin>>fileName;
  cout<<"Enter file for the result to be stored in(Include suffix): ";
  cin>>resultFile;

  ifstream fin;
  ofstream fout;

  fin.open(fileName.data());    //Open the variable names using the data() function
  fout.open(resultFile.data());

  string word; //A local variable that stores the word that is read from the text file inputted by the user.
  while(fin>>word)  //As long as a word is read into "word", proceed.
    {
      string encword;   //A local variable that will include an encrypted word after calling the encryptWordUsingRot function.
      encword = encryptWordUsingRot(rot,word); //Call encryptWordUsingRot passing the rotation number and a word from the text file.
      fout<<encword<<" "; //Put the encrypted word into an output file with a space preceding it.
    }
  fin.close();//Close both files.
  fout.close();
}

string security::encryptWordUsingRot(int rot,string word)//Finished
{
  for(int i = 0; i < word.size();i++)
    {
      word[i]=tolower(word[i]);       //convert letters to lowercase(ASCII)
    }

  string encWord = word;
  for(int i = 0; i < encWord.size();i++)
    {
      char OG = word[i];          //set [i] char of word in OG(original gangsta) variable. Why is it okay to use c\har here and not int? DataType does not matter when loading word
      if(OG >= 'a' && OG <='z')
	{
	  int newchar;
	  newchar = OG + rot;         //add OG + rot and set to newchar
	  if(newchar > 'z')
	    newchar -=26;           //If newchar is greater that z, subtract 26. Why 26? What if ASCII is great than 1 \22? Always sub 26
	  encWord[i] = newchar;       //newchar gets placed in first element of the word
	}
    }
  return encWord;                 //return new word to encryptUsingRot(int rot)
}

void security::encryptFileUsingCrypto()
{
  string cryptogramFile;
  string resultCrypto;
  string dataFile;
  ifstream finData;
  ifstream finCryp;
  ofstream fout;

  cout<<"Enter file name containing cryptogram(Include suffix): ";
  cin>>cryptogramFile;
  cout<<"Enter file name you would like to encrypt(Include suffix): ";
  cin>>dataFile;
  cout<<"Enter the resulting filename(Include suffix): ";
  cin>>resultCrypto;

  finData.open(dataFile.data());//Open file containing the message
  finCryp.open(cryptogramFile.data());//Open file containing the cryptogram
  fout.open(resultCrypto.data());//Open file where the encrypted message will be placed

  string cryptogramKey;
  string data;

  finCryp>>cryptogramKey;//Read in the cryptogram key into cryptogramKey variable.

  while(finData>>data)//While a word is read into the variable data
    {
      string encWord = data;   //store word into encWord variable
      for(int i = 0; i < encWord.size();i++)// i less than size of word
	{
	  char character = encWord[i];//set first character from word to character
	  character = tolower(character);//change each character to a lower case letter
	  if(character >= 'a' && character <= 'z')
	    {
	      char newChar = cryptogramKey[character -'a'];
	      encWord[i] = newChar;
	    }
	}
      fout<<encWord<<" ";
    }
  finData.close();
  finCryp.close();
  fout.close();
}

void security:: decryptUsingRot(int rot)
{
  string decrypFile;
  string resultFile;
  ifstream fin;
  ofstream fout;

  cout<<"Enter file name that you would like to decrypt: ";
  cin>>decrypFile;
  cout<<"Enter file name to store the result: ";
  cin>>resultFile;
  fin.open(decrypFile.data());
  fout.open(resultFile.data());

  string word;
  while(fin>>word)
    {
      string decword;
      decword = decryptWordUsingRot(rot,word);
      fout<<decword<<" ";
    }
  fin.close();
  fout.close();
}

string security:: decryptWordUsingRot(int rot,string word)
{
  for(int i = 0; i < word.size();i++)
    {
      word[i]=tolower(word[i]);       //convert letters to lowercase(ASCII)
    }

  string decWord = word;
  for(int i = 0; i < decWord.size();i++)
    {
      char OG = word[i];          //set [i] char of word in OG(original gangsta) variable. Why is it okay to use char here and not int? DataType does not matter when loading word
      if(OG >= 'a' && OG <='z')
	{
	  int newchar;
	  newchar = OG + rot;         //add OG + rot and set to newchar
	  if(newchar > 'z')
	    newchar -=26;           //If newchar is greater that z, subtract 26. Why 26? What if ASCII is great than 1 22? Always sub 26
	  decWord[i] = newchar;       //"newchar" gets placed in first element of the word.
	}
    }
  return decWord;                 //Return new word to encryptUsingRot(int rot).
}

void security:: decryptFileUsingCrypto()
{
  string cryptogramFile;    //Local variables that will include the file name that are inputted by the user.
  string resultCrypto;
  string dataFile;
  ifstream finData;
  ifstream finCryp;
  ofstream fout;

  cout<<"Enter file name containing cryptogram(Include suffix): ";
  cin>>cryptogramFile;
  cout<<"Enter file name you would like to decrypt(Include suffix): ";
  cin>>dataFile;
  cout<<"Enter the resulting filename(Include suffix): ";
  cin>>resultCrypto;

  finData.open(dataFile.data());//Open file containing the message
  finCryp.open(cryptogramFile.data());//Open file containing the cryptogram
  fout.open(resultCrypto.data());//Open file where the encrypted message will be placed

  string cryptogramKey;
  string data;

  finCryp>>cryptogramKey;//Read in the cryptogram key into cryptogramKey variable.

  while(finData>>data)//While a word is read into the variable data
    {
      string encWord = data;   //store word into encWord variable
      for(int i = 0; i < encWord.size();i++)// i less than size of word
	{
	  char character = encWord[i];//set first character from word to character
	  character = tolower(character);//change each character to a lower case letter
	  if(character >= 'a' && character <= 'z')
	    {
	      int index = cryptogramKey.find(character,0);
	      char newChar ='a' + index;
	      encWord[i] = newChar;
	    }
	}
      fout<<encWord<<" ";
    }
  finData.close();    //Close files.
  finCryp.close();
  fout.close();
}
int main()
{
  security crypt;   //Create a object of type security.
  crypt.decision(); //Call the decision function of class security.
}
