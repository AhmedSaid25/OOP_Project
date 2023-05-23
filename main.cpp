#include<iostream>
#include<fstream>
using namespace std;
//float array class
class FloatArray {
protected:
    int size;
    float* arr;

public:
    //variable to count number of elements in the array
    int cnt=0;
    // constructor that takes the array size
    FloatArray(int s) {
        size = s;
        arr = new float[size];
    }
    // Add func to add the element to the end of the array
    virtual void Add(float num) {
        arr[cnt] = num;
        cnt++;
    }
    //overloading insertion operator
    friend ofstream& operator<<(ofstream& out,FloatArray *temp){
        // write the array to the file
        out << temp->size << "|\t";
        for(int i = 0; i < temp->cnt ; i++){
            out << temp->arr[i] << "\t" ;
        }
        out << endl;
        return out;
    }
    // overloading extraction operator
    friend ifstream& operator>>(ifstream& in, FloatArray *obj) {
        //read from the file
        float num;
        for(int i=0;i<obj->size;i++) {
            in >> num;
            obj->Add(num);
        }
        return in;
    }
    //destructor
    ~FloatArray(){
        delete[]arr;
    }

};
// SortedArray inherits from FloatArray
class SortedArray :public FloatArray {

public:
    // parameterized constructor that takes the array size
    SortedArray(int sz) :FloatArray(sz) {
    }
    // add method that adds a float at the right place in the array
    virtual void Add(float num) {
        bool done = false;
        for (int i = cnt - 1; i >= 0; i--)
        {
            if (num > arr[i]) {
                arr[i + 1] = num; done = true; break;
            }
            else
                //shifting the elements
                arr[i + 1]=arr[i];
        }
        //if the array empty
        if (!done)
            arr[0] = num;
        cnt++;
    }
};
//FrontArray inherits from FloatArray
class  FrontArray :public FloatArray {
public:
    // A parameterized constructor that takes the array size
    FrontArray(int sz) :FloatArray(sz) {
    }
//function adds a float at the front of the array
    void Add(float num) {
        arr[size - 1 - cnt] = num;
        cnt++;
    }
};
//PositiveArray that inherits from SortedArray
class PositiveArray :public SortedArray {
public:
    // parameterized constructor that takes the array size
    PositiveArray(int sz) :SortedArray(sz) {
    }
    //adds a float to the array only if it’s a positive number.and use sorted method
    void Add(float num) {
        if(num>0){
            SortedArray::Add(num);
        }
    }
};
//NegativeArray that inherits from SortedArray
class  NegativeArray :public SortedArray {
public:
    // parameterized constructor that takes the array size
    NegativeArray(int sz) :SortedArray(sz) {
    }
    //adds a float to the array only if it’s a negative number.and use sorted method
    void Add(float num) {
        if (num<0){
            SortedArray::Add(num);
        }
    }

};
int main() {
    //input and output files name
    string inputfile, outputfile;
    // using polymorphism
    FloatArray *array;
    cout<<"Enter input file:"<<endl;
    cin >> inputfile;
    cout<<"Enter output file"<<endl;
    cin >> outputfile;
    ifstream in(inputfile);
    ofstream outfile(outputfile);
    for(int i = 0 ; i < 10 ; i++){
        string arraytype;
        in >> arraytype;
        int s;
        in >> s;
        if (arraytype == "Array") {
            array = new FloatArray(s);
        }
        else if (arraytype == "Sorted")
            array = new SortedArray(s);
        else if (arraytype == "Front")
            array = new FrontArray(s);
        else if (arraytype == "Positive")
            array = new PositiveArray(s);
        else if (arraytype == "Negative")
            array = new NegativeArray(s);

        in >>array;
        outfile <<array;
        delete array;
    }
    in.close();
    outfile.close();
    return 0;
}