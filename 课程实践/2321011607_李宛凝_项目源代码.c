#include <stdio.h>
#include <string.h>
#define N 50
#define len 20


struct Person{
	char code[20];//人员编号
	char id[19];//身份证号
	char name[10];//姓名
	int age;//年龄
	char sex[6]; //性别
	char phone[12];//电话
	float temp[14];//体温
	float record_temp[2];//记录提问的范围
	int flag;//健康状况 0 绿色 1 黄色 低烧 2 红色 高烧
}per[N];
int n=0,m=0,k=1;//当前记录的人员数  m表示要增加的人数

void menu();//显示功能菜单
void help(); //显示帮助
void refresh();//刷新信息
void display();//显示人员信息
void insert();//增加人员信息
void save();//保存人员信息
void seek();//查询相关人员信息
void print();//打印人员信息
void modify();//修改人员信息
void delete();//删除人员信息
void bubbleSort();//冒泡排序


int main() {
while(k){
	menu();
}
//display();
	return 0;
}

void  save(){
	FILE *fp=NULL;
	fp=fopen("per.csv","w");
	int i;
	for(i=0;i<n;i++){
		fprintf(fp,"%s,%s,%d,%s,%s,%s,%d\n",per[i].code,per[i].name,per[i].age,per[i].sex,per[i].id,per[i].phone,per[i].flag);
	}
	fclose(fp);//关闭文件
	printf("保存成功！！");//打印输出成功
	system("pause");//程序暂停

}
//用冒泡排序将人员信息按编号从小到大排序
void bubbleSort(struct Person persons[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (strcmp(persons[j].code, persons[j+1].code) > 0) {
                // 交换两个人员的位置
                struct Person temp = persons[j];
                persons[j] = persons[j+1];
                persons[j+1] = temp;
            }
        }
    }
}
void display(){
	int i,j;
	//int n=2;
	int r_tab=9;
	int c_tab=8;
	printf("共有%d位人员信息:\n",n);
	if(n!=0){
		printf("%c",' ');
		for(i=0;i<r_tab*c_tab+10;i++){
			printf("%c",'-');
		}
		printf("\n");
		printf("|%-8s|%-8s|%-8s|%-8s|%-18s|%-8s|%-8s|%-8s|\n","人员编号","人员姓名","年龄","性别","身份证号","健康状况","最高体温","最低体温");
		printf("%c",' ');
		for(i=0;i<r_tab*c_tab+10;i++){
			printf("%c",'-');
		}
		printf("\n");
		bubbleSort(per,n);//排序
		for(j=0;j<n;j++){
            printf("|%-8s|%-8s|%-8d|%-8s|%-18s|%-8d|%-8.1f|%-8.1f|\n",per[j].code,per[j].name,per[j].age,per[j].sex,per[j].id,per[j].flag,per[j].temp[0],per[j].temp[1]);
            printf("%c",' ');//换行
		for(i=0;i<r_tab*c_tab+10;i++){
			printf("%c",'-');
		}
		if(per[j].flag==1)
            printf("健康\n");
            else if(per[j].flag==2)
            printf("您已低烧\n");
            else if(per[j].flag==3)printf("您已高烧");
            else printf("请输入正确的健康状况");
            printf("\n");
		}
	}
	system("pause");
}

void refresh(){
	FILE *fp=NULL;
	fp=fopen("per.csv","r");
	char s[len*10];
	//fscanf(fp,"%s\n",&s);
	int i=0,j;
	while(fscanf(fp,"%s\n",&s)!=EOF){
		char *ptr,*retptr;//声明两个指针，指向字符
		j=0;
		ptr=s;
		while((retptr=strtok(ptr,","))!=NULL){
			switch(j){
				case 0:strcpy(per[i].code,retptr);break;
				case 1:strcpy(per[i].name,retptr);break;
			    case 2:per[i].age=atoi(retptr);break;//将字符串转换为整型
				case 3:strcpy(per[i].sex,retptr);break;
				case 4:strcpy(per[i].id,retptr);break;
				case 5:strcpy(per[i].phone,retptr);break;
				case 6:per[i].flag=atoi(retptr);break;
			}
			j++;
			ptr=NULL;
		}
		i++;
	}
	fclose(fp);
	n=i;
	display();
}


//查询界面
void seek(){
	printf("\n");
	printf("-----------------------------------\n");
	printf("----------1.按编号查询-------------\n");
	printf("----------2.按姓名查询-------------\n");
	printf("----------3.按ID号查询-------------\n");
	printf("----------4.按电话查询-------------\n");
	printf("----------5.退出本菜单-------------\n");
    printf("-----------------------------------\n");
    int item;
    char s1[21];
    int i,flag;
    while(1){
    	printf("请选择子菜单编号：\n");
    	scanf("%d",&item);
    	flag=0;
    	switch(item){
    		case 1:
			       printf("请输入要查询的人员编号：\n");
			       scanf("%s",s1);
			       for(i=0;i<n;i++){
			       	if(strcmp(per[i].code,s1)==0){
			       		flag=1;
			       		print(&per[i]);//打印人员信息
			       		break;
					   }
				   }
				   if(flag==0)
				   printf("输入的编号不存在！");
				   break;
			case 2:
				   printf("请输入要查询的人员姓名：\n");
			       scanf("%s",s1);
			       for(i=0;i<n;i++){
			       	if(strcmp(per[i].name,s1)==0){
			       		flag=1;
			       		print(&per[i]);//打印人员信息
			       		break;
					   }
				   }
				   if(flag==0)
				   printf("输入的姓名不存在！");break;
			case 3:
				   printf("请输入要查询的人员身份证号：\n");
			       scanf("%s",s1);
			       for(i=0;i<n;i++){
			       	if(strcmp(per[i].id,s1)==0){
			       		flag=1;
			       		print(&per[i]);//打印人员信息
			       		break;
					   }
				   }
				   if(flag==0)
				   printf("输入的身份证号不存在！");
				   break;
			case 4:
				   printf("请输入要查询的人员电话号：\n");
			       scanf("%s",s1);
			       for(i=0;i<n;i++){
			       	if(strcmp(per[i].phone,s1)==0){
			       		flag=1;
			       		print(&per[i]);//打印人员信息
			       		break;
					   }
				   }
				   if(flag==0)
				   printf("输入的电话号不存在！");
				   break;
			case 5:return;
				   default:printf("请输入1-5之间的数字！！！");
		}
	}
    system("pause");//让执行暂停一下
}

void print(struct Person*p) {
	int i;
	int r_tab=9;
	int c_tab=8;
	printf("%c",' ');
	for(i=0;i<r_tab*c_tab+10;i++){
		printf("%c",'-');
	}
	printf("\n");
	printf("|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n","人员编号","人员姓名","年龄","性别","身份证号","健康状况","最高体温","最低体温");
	printf("%c",' ');
	for(i=0;i<r_tab*c_tab+10;i++){
		printf("%c",'-');
	}
	printf("\n");
	printf("|%-8s|%-8s|%-8d|%-8s|%-18s|%-8d|%-8.1f|%-8.1f|\n",p->code,p->name,p->age,p->sex,p->id,p->flag,p->temp[0],p->temp[1]);
	printf("%c",' ');//换行
		for(i=0;i<r_tab*c_tab+10;i++){
			printf("%c",'-');
		}
		printf("\n");
		system("pause");
}

void modify(){
	printf("请输入要修改的人员编号：\n");
	char s1[20];
	scanf("%s",s1);
	int i,num=-1,item;
	for(i=0;i<n;i++){  //查找要修改人员的数组下标
		if(strcmp(per[i].code,s1)==0)
		num=i;
	}
	if(num!=-1){
	printf("\n");
	printf("-----------------------------------\n");
	printf("----------1.修改姓名-------------\n");
	printf("----------2.修改年龄-------------\n");
	printf("----------3.修改性别------------\n");
	printf("----------4.修改手机号码-------------\n");
	printf("----------5.修改身份证号-------------\n");
	printf("----------6.修改健康状况-------------\n");
	printf("----------7.修改最高体温-------------\n");
	printf("----------8.修改最低体温-------------\n");
	printf("----------9.退出本菜单-------------\n");
    printf("-----------------------------------\n");
    while(1){
    	printf("请选择子菜单编号：\n");
    	scanf("%d",&item);
    	switch(item) {
    		case 1:
			printf("请输入新的姓名：\n");
			scanf("%s",s1);
			strcpy(per[num].name,s1);
			break;
    		case 2:
			printf("请输入新的年龄：\n");
			scanf("%d",&per[num].age);
			break;
    		case 3:
			printf("请输入新的性别：\n");
			scanf("%s",s1);
			strcpy(per[num].sex,s1);
			break;
			case 4:
			printf("请输入新的手机号码：\n");
			scanf("%d",&s1);
			strcpy(per[num].phone,s1);
			break;
			case 5:
			printf("请输入新的身份证号：\n");
			scanf("%d",&s1);
			strcpy(per[num].id,s1);
			break;
			case 6:
			printf("请输入新的健康状况：\n");
			scanf("%s",&per[num].flag);
			break;
			case 7:
			printf("请输入新的最高体温：\n");
			scanf("%f",&s1);
			strcpy(per[num].name,s1);
			break;
			case 8:
			printf("请输入新的最低体温：\n");
			scanf("%f",&s1);
			strcpy(per[num].code,s1);
			break;
			case 9:return;
		}
	}
	}
	printf("信息修改完毕，显示结果请选择菜单6，并及时保存结果！");
	system("pause");
}

void delete(){
	char s1[20];
	int flag=0;//0表示查找失败 1表示查找成功
	printf("请输入要查询的人员编号：\n") ;
	scanf("%s",s1);
	int i,j;
	for(i=0;i<n;i++){
		if(strcmp(per[i].code,s1)==0){
		flag=1;
		for(j=i;j<n-1;j++)
		per[j]=per[j+1];
	}
	}
	if(flag==0)
	printf("要删除的人员编号不存在！\n");
	if(flag==1){
	printf("删除成功，显示结果请选择菜单");
	n--;
	}
	system("pause");
}

//帮助信息
void help(){
	printf("\n0. 欢迎使用系统帮助！\n");
	printf("\n1.初次进入系统后，请先刷新信息，再执行其他操作；若文件不存在或者没有内容，请选择增加人员信息；\n");
	printf("\n2.按照菜单提示键入数字编号；\n");
	printf("\n3.增加人员信息后，切记保存；\n");
	printf("\n4.谢谢您的使用！\n");
	system("pause");//让执行暂停一下
}
//界面
void menu(){
	printf("\n");
	printf("           -------2321011607--------               \n");
	printf("           --------李 宛 凝---------               \n");
	printf("**************************************************\n");
	printf("*              疫情防控信息管理系统              *\n");
	printf("**************************************************\n");
	printf("******************系统功能菜单********************\n");
	printf("    ------------------   ------------------\n");
	printf(" ********************************************\n");
	printf("* 0.系统帮助及说明  * * *  1.刷新人员信息    *\n");
	printf(" ********************************************\n");
	printf("* 2.查询人员信息    * * *  3.修改人员信息    *\n");
	printf("********************************************\n");
	printf("* 4.增加人员信息    * * *  5.按编号删除信息  *\n");
	printf(" ********************************************\n");
	printf("* 6.显示当前信息    * * *  7.保存当前人员信息*\n");
	printf("********************************************\n");
	printf("* 8.退出系统        *\n");
	printf("*********************\n");
	printf("---------------------   --------------------\n");
	printf("请选择菜单编号：");
	int num=-1;
	scanf("%d",&num);
	switch(num){
		case 0:help();break;
		case 1:refresh();break;
		case 2:seek();break;
		case 3:modify();break;
		case 4:insert();break;
		case 5:delete();break;
		case 6:display();break;
		case 7:save();break;
		case 8:k=0;printf("退出成功");return;
		default:printf("请输入0-8之间的数字！！！！！！！");break;
	}
}

//插入人员
void insert(){
	int i=n,j,flag;
	printf("请输入要增加的人员人数：\n");
	scanf("%d",&m);
	if(m>0){
		do{
			flag=1;
			while(flag){//判断输入的编号是否重复
				flag=0;
				printf("请输入第%d位的人员编号：\n",i+1);
				scanf("%s",&per[i].code);
				for(j=0;j<i;j++){
					if(strcmp(per[i].code,per[j].code)==0){
						printf("已有该编号，请重新输入");
						flag=1;
						break;
					}
				}
			}
		printf("请输入第%d位的人员的姓名：\n",i+1);
		scanf("%s",&per[i].name);
		printf("请输入第%d位的人员的年龄：\n",i+1);
		scanf("%d",&per[i].age);
		printf("请输入第%d位的人员的性别：\n",i+1);
		scanf("%s",&per[i].sex);
		printf("请输入第%d位的人员的身份证号：\n",i+1);
		scanf("%s",&per[i].id);
		printf("请输入第%d位的人员的电话号码：\n",i+1);
		scanf("%s",&per[i].phone);
		printf("请输入第%d位的人员的健康状况：\n",i+1);
		scanf("%d",&per[i].flag);
		i++;
		}while(i<m+n);
		n=m+n;
		printf("信息增加完毕！！！");
	}
	else{
		printf("新增人员数量有误，请重新输入：__\n");
	}
	system("pause");
}
