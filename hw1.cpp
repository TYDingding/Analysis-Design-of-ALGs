#include<iostream>
#include <fstream> 
#include<cstring>
using namespace std;

char target[6];

int charToInt(char);
int f(int,int);
int g(int,int);
int encryption(char[]);

int main()
{
    int lineCount = 2;
    char buffer[256];  
    ifstream in("input.txt");  
    if (! in.is_open())  
    { cout << "Error opening file"; exit (1); }  

    if(!in.eof())
    {
      in.getline(buffer, 100);
      string temp(buffer);
      lineCount = atoi(temp.c_str());
      cout<<lineCount<<endl;
    }

    while (!in.eof() )  
    {
      in.getline (buffer,100);
      string temp(buffer);
      cout<<temp<<"     ";
      char target[7];
      int length = temp.copy(target, 5);
      target[length] = '\0';
      cout << encryption(target) << endl;
    }  

    system("pause");
    return 0;
}

int charToInt(char cha)
{
      return int(cha)-96;
}

int f(int head, int length)
{
      int upper = length - 1;
      int lower = 26 - head;
      int sum = 0;
      int upperMulti = 1;
      int lowerMulti = 1;
      for(int i = upper; i > 0; i--)
      {
            upperMulti *= lower;
            lowerMulti *= upper;
            upper--;
            lower--;
      }
      return upperMulti/lowerMulti;
}

int g(int length)
{
      int sum = 0;
      for(int i = 1; i < 28 - length; i++)
      {
            sum += f(i, length);
      }
      return sum;
}

int encryption(char tar[])
{
      int code = 1;
      int length = 1;
      int head = charToInt(tar[0]);
      for(int i = 0; tar[i] != 0 && i < 6; i++)
      {
            length = i+1;
      }
      for(int i = 1; i < length; i++)
      {
            code += g(i);
      }
      for(int i = 1; i < head; i++)
      {
            code += f(i, length);
      }

      for(int i = 0; i < length; i++)
      {
            for(int t = charToInt(tar[i]) + 1; t < charToInt(tar[i+1]) && tar[i+1] != 0; t++)
            {
                  code += f(t, length - i -1);
            }
      }
      return code;     
}