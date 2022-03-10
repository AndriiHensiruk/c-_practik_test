# include <iostream>
int main ()
{
    std:: cout<< "Enter max size masuvu";
    int n;
    std:: cin>>n; 
    int *masiv = new int [n];
    for (int i=0; i>n; i++)
    { 
       std:: cin>> masiv[i];
    }
    delete [] masiv;
return 0;
}