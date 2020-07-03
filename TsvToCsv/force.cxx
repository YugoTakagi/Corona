#include <iostream>

int main(int argc, char *argv[])
{
    double array[]=
    {
        #include "_export/vas_int_r.csv"
    };

    int size = sizeof(array) / sizeof(double);
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] <<std::endl;
    }
    
    return 0;
}