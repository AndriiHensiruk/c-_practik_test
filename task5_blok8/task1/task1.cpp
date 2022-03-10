# include <iostream>
int main()
{
    std::cout << "Enter max size masuvu :: ";
    int n;
    std::cin >> n;
    int* masiv = new int[n];

    for (int i = 0; i<n; i++)
    {
        std::cout << "Enter "<<i<<"number ::";
        std::cin >> masiv[i];
    }
    int k=0;
    for (int i = 0; i < n; i++)
        if (masiv[i] < 0)
            k++;
    std::cout <<"number of negative elements :: "<< k;
    delete[] masiv;
    return 0;
}