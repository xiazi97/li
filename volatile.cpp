/*
  * 这是一个体现变量保持内存可见性的重要性的demo
  * volatile关键字
  * */
  #include<stdio.h>
  #include<unistd.h>
  #include<signal.h>
  #include<stdint.h>
  int a = 1;
  void sigcb(int no)
  {
      printf("pro exit!\n");
      a = 0;
  }
  
  int main()
  {
     uint64_t i = 0;
     signal(SIGINT,sigcb);
     while(a)
	 {
        i++;
     }
     return 0;
 }
