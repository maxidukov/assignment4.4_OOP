#include <iostream>
#include <string>
#include <sstream>
#include <limits>

//void print_dynamic_array(int* arr, int logical_size, int actual_size);
//void append_to_dynamic_array(int*&,int,int&,int&);

inline void clear_stdin(){
  //std::cin.clear();
 std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

class Dyn_Arr_int{
  int as;
  int ls;
  int* arr;
  public:
    Dyn_Arr_int(int as, int ls = 0) : as(as), ls(ls) {
      arr = new int[as]();
      if(ls){
        for(int i{};i<ls;i++){
          std::cout<<"Введите arr["<<i<<"]: ";
          std::cin>>arr[i];
        }
        clear_stdin();
      }
    }
    void print_dynamic_array(){
      //std::cout<<"Динамический массив: ";
      for(int i{};i<as;i++){
        if(i<ls){
          std::cout<<arr[i];
        }else{
          std::cout<<"_";
        }
        if(i<as-1){
          std::cout<<" ";
        }
      }
      std::cout<<"\n";
    }
    void append_to_dynamic_array(int new_num){
       if(ls==as){
         as *= 2;
         int* new_arr = new int[as]();
         int* old_arr = arr;
         for(int i{};i<ls;i++){
            new_arr[i]=arr[i];
         }
         arr = new_arr;
         delete [] old_arr;
         //ls += 1;
       }
       arr[ls++] = new_num;
    }
    bool remove_dynamic_array_head(){
      if(!ls){
        return false;
      }
      if(ls-1<=as/3){
         as /= 3;
         int* new_arr = new int[as]();
         int* old_arr = arr;
         for(int i{};i<ls-1;i++){
            new_arr[i]=arr[i+1];
         }
         arr = new_arr;
         delete [] old_arr;
         ls -= 1;
       }else{
         for(int i{};i<ls-1;i++){
             arr[i]=arr[i+1];
         }
         arr[(ls--)-1] = 0;
       }
       return true;
    }
    int& operator[](int index){
      if(index<ls&&index>=0){
        return arr[index];
      }else{
        std::cout << "Ошибка! Индекс вне пределев массива, выход\n";
        exit(0);
      }
    }
    Dyn_Arr_int(Dyn_Arr_int &arr_orig) : as(arr_orig.as), ls(arr_orig.ls){
      arr = new int[as];
      for(int i{};i<ls;i++){
        arr[i]=arr_orig[i];
      }
    }
    Dyn_Arr_int operator=(Dyn_Arr_int &arr_orig){
      if (this == &arr_orig) {
        return *this;
      } else {
        ls = arr_orig.ls;
        as = arr_orig.as;
        if (arr_orig.ls) {
          arr = new int[as];
          for(int i{};i<ls;i++){
            arr[i]=arr_orig[i];
          }
        } else
          arr = nullptr;
        return *this;
      }
    }
    ~Dyn_Arr_int(){
      delete [] arr;
    }
};


int main() {

  int as{};
  int ls{};
  std::cout <<"Добавление элемента в конец массива.\n";
  std::cout << "Введите фактичеcкий размер массива: ";
  std::cin >> as;
  //do{
     std::cout << "Введите логичеcкий размер массива: ";
     std::cin >> ls;
     if(ls>as){
        std::cout<<"Ошибка! Логический размер массива не может превышать фактический!\n";
       return 1;
     }
  //}while(ls>as);
  /*int* arr = new int[as]();
  for(int i{};i<ls;i++){
    std::cout<<"Введите arr["<<i<<"]: ";
    std::cin>>arr[i];
  }*/
  Dyn_Arr_int arr(as,ls);
  std::cout<<"Динамический массив: ";
  arr.print_dynamic_array();
  int new_num{};
  std::string line;
  std::cout<<"Для прекращения ввода новых элементов просто нажмите Enter\n";
  while(1){

    std::cout<<"Введите элемент для добавления: ";
    std::getline(std::cin,line);
    //std::cin>>line;
    //clear_stdin();
    //if(line==""){
    if(line.empty()){
      break;
    }
    //isstream iss(line);
    std::istringstream iss(line);
    iss>>new_num;
    iss.clear();
    iss.str("");
    line = "";
    arr.append_to_dynamic_array(new_num);
    //clear_stdin();
    std::cout<<"Динамический массив: ";
    arr.print_dynamic_array();
  }
  //clear_stdin();
  std::cout<<"\nСпасибо! Ваш массив: ";
  arr.print_dynamic_array();

  std::cout <<"\n\nУдаление элемента из начала массива.\n";
  std::cout << "Введите фактичеcкий размер массива: ";
  std::cin >> as;
  //do{
     std::cout << "Введите логичеcкий размер массива: ";
     std::cin >> ls;
     if(ls>as){
        std::cout<<"Ошибка! Логический размер массива не может превышать фактический!\n";
       return 1;
     }
  //}while(ls>as);
  /*int* arr = new int[as]();
  for(int i{};i<ls;i++){
    std::cout<<"Введите arr["<<i<<"]: ";
    std::cin>>arr[i];
  }
  clear_stdin();*/
  Dyn_Arr_int arr2(as,ls);
  std::cout<<"Динамический массив: ";
  arr2.print_dynamic_array();
  //std::string line;
  while(1){
    std::cout<<"Удалить первый элемент? ";
    std::cin>>line;
    if(line=="да"){
      if(!arr2.remove_dynamic_array_head()){
        std::cout<<"Невозможно удалить первый элемент, так как массив пустой. До свидания!";
        return 2;
      }
    }else if(line=="нет"){
      break;
    }else{
      std::cout<<"Введите да или нет\n";
    }
    std::cout<<"Динамический массив: ";
    arr2.print_dynamic_array();
  }
  //clear_stdin();
  std::cout<<"\nСпасибо! Ваш динамический массив: ";
  arr2.print_dynamic_array();

}



