// RUN: %check_clang_tidy %s readability-use-std-min-max %t

#define MY_MACRO_MIN(a, b) ((a) < (b) ? (a) : (b))

constexpr int myConstexprMin(int a, int b) {
  return a < b ? a : b;
}

constexpr int myConstexprMax(int a, int b) {
  return a > b ? a : b;
}

#define MY_IF_MACRO(condition, statement) \
  if (condition) {                        \
    statement                             \
  }

class MyClass {
public:
  int member1;
  int member2;
};

void foo() {
  int value1,value2,value3;
  short value4;
  MyClass obj;

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: value1 = std::max<int>(value1, value2);
  if (value1 < value2)
    value1 = value2; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: value2 = std::min<int>(value1, value2);
  if (value1 < value2)
    value2 = value1; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `>` [readability-use-std-min-max]
  // CHECK-FIXES: value2 = std::min<int>(value2, value1);
  if (value2 > value1)
    value2 = value1; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `>` [readability-use-std-min-max
  // CHECK-FIXES: value1 = std::max<int>(value2, value1);
  if (value2 > value1)
    value1 = value2; 

  // No suggestion needed here
  if (value1 == value2)
    value1 = value2;
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: value1 = std::max<int>(value1, value4);
  if(value1<value4)
    value1=value4; 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: value3 = std::min<int>(value1+value2, value3);
  if(value1+value2<value3)
    value3 = value1+value2; 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: value1 = std::max<int>(value1, myConstexprMin(value2, value3));
  if (value1 < myConstexprMin(value2, value3))
    value1 = myConstexprMin(value2, value3); 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `>` [readability-use-std-min-max]
  // CHECK-FIXES: value1 = std::min<int>(value1, myConstexprMax(value2, value3));
  if (value1 > myConstexprMax(value2, value3))
    value1 = myConstexprMax(value2, value3); 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `<=` [readability-use-std-min-max]
  // CHECK-FIXES: value2 = std::min<int>(value1, value2);
  if (value1 <= value2)
    value2 = value1; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `<=` [readability-use-std-min-max]
  // CHECK-FIXES: value1 = std::max<int>(value1, value2);
  if (value1 <= value2)
    value1 = value2; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `>=` [readability-use-std-min-max]
  // CHECK-FIXES: value1 = std::max<int>(value2, value1);
  if (value2 >= value1)
    value1 = value2; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `>=` [readability-use-std-min-max]
  // CHECK-FIXES: value2 = std::min<int>(value2, value1);
  if (value2 >= value1)
    value2 = value1; 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: obj.member1 = std::max<int>(obj.member1, obj.member2);
  if (obj.member1 < obj.member2)
    obj.member1 = obj.member2; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: obj.member2 = std::min<int>(obj.member1, obj.member2);
  if (obj.member1 < obj.member2)
    obj.member2 = obj.member1; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `>` [readability-use-std-min-max]
  // CHECK-FIXES: obj.member2 = std::min<int>(obj.member2, obj.member1);
  if (obj.member2 > obj.member1)
    obj.member2 = obj.member1; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `>` [readability-use-std-min-max]
  // CHECK-FIXES: obj.member1 = std::max<int>(obj.member2, obj.member1);
  if (obj.member2 > obj.member1)
    obj.member1 = obj.member2; 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: obj.member1 = std::max<int>(obj.member1, value4);
  if (obj.member1 < value4)
    obj.member1 = value4; 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: value3 = std::min<int>(obj.member1 + value2, value3);
  if (obj.member1 + value2 < value3)
    value3 = obj.member1 + value2; 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `<=` [readability-use-std-min-max]
  // CHECK-FIXES: obj.member2 = std::min<int>(value1, obj.member2);
  if (value1 <= obj.member2)
    obj.member2 = value1; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `<=` [readability-use-std-min-max]
  // CHECK-FIXES: value1 = std::max<int>(value1, obj.member2);
  if (value1 <= obj.member2)
    value1 = obj.member2; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `>=` [readability-use-std-min-max]
  // CHECK-FIXES: value1 = std::max<int>(obj.member2, value1);
  if (obj.member2 >= value1)
    value1 = obj.member2; 

  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::min` instead of `>=` [readability-use-std-min-max]
  // CHECK-FIXES: obj.member2 = std::min<int>(obj.member2, value1);
  if (obj.member2 >= value1)
    obj.member2 = value1; 
  
  // No suggestion needed here
  if (MY_MACRO_MIN(value1, value2) < value3)
    value3 = MY_MACRO_MIN(value1, value2); 
  
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: use `std::max` instead of `<` [readability-use-std-min-max]
  // CHECK-FIXES: value4 = std::max<short>(value4, value2);
  if (value4 < value2){
    value4 = value2; 
  }

  // No suggestion needed here
  if(value1 < value2)
    value2 = value1;
  else
    value2 = value3;
  
  // No suggestion needed here
  if(value1<value2){
    value2 = value1; 
  }
  else{
    value2 = value3;  
  }

  // No suggestion needed here
  if(value1<value2){
    value2 = value1; 
    int res = value1 + value2;
  }

  // No suggestion needed here
  MY_IF_MACRO(value1 < value2, value1 = value2;)
}