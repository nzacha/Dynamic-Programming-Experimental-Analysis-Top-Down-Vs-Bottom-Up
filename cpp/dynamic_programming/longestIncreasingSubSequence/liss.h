#ifndef liss_h
#define liss_h
class LISS_Arguments : public Problem_Arguments{
    public:
        int  *array1D, **array2D, *data;

        LISS_Arguments(int* data){
            this->data = data;
        }
};
#endif