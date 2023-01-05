#include <iostream>
#include <vector>
#include <io.h>
#include <ctime>
#include <fstream>
#include <cstring>
#include <sstream>
#include <direct.h>
#include <windows.h>//Windows API
using namespace std;

//const int MAX=1000;
string _Rscore[15];
double _Rscore_[15];
string year,month,day,ntime;

struct info{//输入信息 
	string day;
	string name;
	string grade;
};

struct score{//输入各科分数 
	double Chinese_score;
	double Maths_score;
	double English_score;
	double Physics_score;
	double Chemistry_score;
	double Politics_score;
	double History_score;
	double Geography_score;
	double Biological_score;
	double Sum;
	double Average;
};

void get_time(){
	stringstream _year,_month,_day,_ntime,ss;
	
	//基于当前系统的当前时间和日期 
	time_t now=time(0);
	tm *ltm=localtime(&now);
	
	_year<<1900+ltm->tm_year;
	
	ss<<_year.str();
	ss>>year;
	ss.clear();
	
	if((1+ltm->tm_mon)<=9)//格式处理 
		_month<<"0"<<(1+ltm->tm_mon);
	else
		_month<<(1+ltm->tm_mon);
	
	ss<<_month.str();
	ss>>month;
	ss.clear();
	
	if((ltm->tm_mday)<=9)//格式处理 
		_day<<"0"<<(ltm->tm_mday);
	else
		_day<<(ltm->tm_mday);
	
	ss<<_day.str();
	ss>>day;
	ss.clear();
	
	_ntime<<ltm->tm_hour<<ltm->tm_min<<ltm->tm_sec;
	
	ss<<_ntime.str();
	ss>>ntime;
	ss.clear();
	
}

int format(){//将字符串数组转为浮点型数组 
	memset(_Rscore_,-2,sizeof(_Rscore_)/sizeof(_Rscore_[0]));//重置数组 
	string s1;
	stringstream ss;
	char c1;
	int j=0;
	for(int i=0;i<15;i++){
		s1=_Rscore[i];
		if(s1.length()>0){
			ss<<s1;
			ss>>_Rscore_[j++];
			ss.clear();
		}
	}
	return 1;
}

int read(string R){//将成绩读入内存 
	char Rscore[256];
	int cnt,j=0;
	stringstream ss;
	ifstream RFile(R.c_str());//打开文件 
	if(!RFile){
        cout<<endl<<"出现错误(Error#read_RFile)"<<endl;
        RFile.close();
        return 1;
    }
    while(!RFile.eof()){
    	bool flag=true;
    	cnt=0;//初始化 
    	string _score;
    	memset(Rscore,0,strlen(Rscore));
    	RFile.getline(Rscore,50);//获取一行数据 
    	for(int i=0;i<strlen(Rscore);i++){//筛选出数字 
    		if(Rscore[i]=='#'){
    			flag=false;
    			break;
			}
    		if(Rscore[i]>='0'&&Rscore[i]<='9'||Rscore[i]=='.'||Rscore[i]=='-'){
    			_score+=Rscore[i];
			}
		}
		if(flag){//当有数字时存入数组 
			_Rscore[j++]=_score;
		}
	}
	RFile.close();
	return 0;
}

void look_for(){//查询函数 
	int testopen; 
	info looktemp1;// info_结构体 输入信息 
	stringstream lookd;//格式化一个可以通过插入赋值的字符串(详见 42行) 
	
	cout<<"-----------------------查询------------------------"<<endl;
	
	cout<<"请输入日期(yymmdd,无空格):";
	cin>>looktemp1.day;// info_日期 
	cout<<"请输入姓名:";
	cin>>looktemp1.name;// info_姓名 
	cout<<"请输入年级(一个阿拉伯数字):";
	cin>>looktemp1.grade;// info_年级 
	
	lookd<<"data\\main\\"<<looktemp1.day<<"\\"<<looktemp1.day<<looktemp1.name<<looktemp1.grade<<".txt";//插入赋值的字符串
	if(_access(lookd.str().c_str(),00)==-1){
		cout<<endl<<"查无此项，请检查日期、姓名、年级是否正确！"<<endl<<endl;
		cout<<"---------------------------------------------------"<<endl;
		return;
	}
	ShellExecute(NULL,"open",lookd.str().c_str(),NULL,NULL,SW_SHOW);//Windows API打开txt文本文件
	
	cout<<endl;
	cout<<"完成!"<<endl<<endl; 
	cout<<"---------------------------------------------------"<<endl;
}

void compare(){//比较函数 
	info cmp1,cmp2;
	score sc1,sc2;
	stringstream read1,read2,ss;
	stringstream _Directory1,_Directory2,_FilePath;
	string Directory1,Directory2,FilePath;
	cout<<"-----------------------对比------------------------"<<endl;

	//cmp1
	cout<<"请输入第一个日期(yymmdd,无空格):";
	cin>>cmp1.day;// info_日期 
	cout<<"请输入第一个姓名:";
	cin>>cmp1.name;// info_姓名 
	cout<<"请输入第一个年级(一个阿拉伯数字):";
	cin>>cmp1.grade;// info_年级
	cout<<endl; 
	
	//cmp2
	cout<<"请输入第二个日期(yymmdd,无空格):";
	cin>>cmp2.day;// info_日期 
	cout<<"请输入第二个姓名:";
	cin>>cmp2.name;// info_姓名 
	cout<<"请输入第二个年级(一个阿拉伯数字):";
	cin>>cmp2.grade;// info_年级
	
	//格式化字符串并插入值
	read1<<"data\\main\\"<<cmp1.day<<"\\"<<cmp1.day<<cmp1.name<<cmp1.grade<<".txt";
	read2<<"data\\main\\"<<cmp2.day<<"\\"<<cmp2.day<<cmp2.name<<cmp2.grade<<".txt";
	
	string r1,r2;
	
	ss<<read1.str();//通过sstream将 格式化 转为 普通字符串 
	ss>>r1;
	ss.clear();
	
	ss<<read2.str();
	ss>>r2;
	ss.clear();
	
	//文件操作-读取cmp1
    if(read(r1)){
    	cout<<endl<<"#1文件未成功打开，请检查信息输入是否正确！"<<endl;
    	cout<<endl<<"---------------------------------------------------"<<endl;
		return; 
	}
	if (!format()){
		cout<<endl<<"出现错误(Error#compare_format_1)"<<endl;
		cout<<endl<<"---------------------------------------------------"<<endl;
		return;
	}
    sc1.Chinese_score=_Rscore_[0];
    sc1.Maths_score=_Rscore_[1];
    sc1.English_score=_Rscore_[2];
    sc1.Physics_score=_Rscore_[3];
    sc1.Chemistry_score=_Rscore_[4];
    sc1.Politics_score=_Rscore_[5];
    sc1.History_score=_Rscore_[6];
    sc1.Geography_score=_Rscore_[7];
    sc1.Biological_score=_Rscore_[8];
    sc1.Sum=_Rscore_[9];
    sc1.Average=_Rscore_[10]; 
    
    //文件操作-读取cmp2
    if(read(r2)){
    	cout<<"#2文件未成功打开，请检查信息输入是否正确！"<<endl;
    	cout<<endl<<"---------------------------------------------------"<<endl;
		return; 
	}
	if (!format()){
		cout<<"出现错误(Error#compare_format_2)"<<endl;
		cout<<endl<<"---------------------------------------------------"<<endl;
		return;
	}
	sc2.Chinese_score=_Rscore_[0];
    sc2.Maths_score=_Rscore_[1];
    sc2.English_score=_Rscore_[2];
    sc2.Physics_score=_Rscore_[3];
    sc2.Chemistry_score=_Rscore_[4];
    sc2.Politics_score=_Rscore_[5];
    sc2.History_score=_Rscore_[6];
    sc2.Geography_score=_Rscore_[7];
    sc2.Biological_score=_Rscore_[8];
    sc2.Sum=_Rscore_[9];
    sc2.Average=_Rscore_[10];
    
    get_time();//获取当前时间 
    
    _Directory1<<"data\\temp\\"<<year<<month<<day;//目标路径1
    
    _Directory2<<"data\\temp\\"<<year<<month<<day<<"\\"<<ntime;//目标路径2
    
    ss<<_Directory1.str();//数据类型转换 
	ss>>Directory1;
	ss.clear();
	
	ss<<_Directory2.str();//数据类型转换 
	ss>>Directory2;
	ss.clear();
	
	_FilePath<<"data\\temp\\"<<year<<month<<day<<"\\"<<ntime<<"\\"<<year<<month<<day<<cmp1.name<<cmp2.name<<".txt";//目标文件路径
	
	ss<<_FilePath.str();//数据类型转换 
	ss>>FilePath;
	ss.clear();
	
	if(_access(Directory1.c_str(),00)==-1){//创建目标路径 
		if(!CreateDirectory(Directory1.c_str(),NULL)){
			cout<<"出现错误(Error#compare_CreateDirectory_1)"<<endl;
			cout<<endl<<"---------------------------------------------------"<<endl;
			return;
		}
	}
	if(_access(Directory2.c_str(),00)==-1){//创建目标路径 
		if(!CreateDirectory(Directory2.c_str(),NULL)){
			cout<<"出现错误(Error#compare_CreateDirectory_2)"<<endl;
			cout<<endl<<"---------------------------------------------------"<<endl;
			return;
		}
	}
	
	ofstream CFile(FilePath.c_str(),ios_base::out);//创建文件 
	if(!CFile) {
        cout<<endl<<"出现错误(Error#key_in_File):"<<endl<<endl;
        cout<<"---------------------------------------------------"<<endl;
        return;
    }
	CFile<<"#Date : "<<year<<'/'<<month<<'/'<<day<<endl;
	CFile<<"#Name : "<<cmp1.name<<" <-> "<<cmp2.name<<endl<<endl;
	CFile<<"#------------------Comparation------------------#"<<endl<<endl;
	//对比并加标识--文件内输出 
	if(sc1.Chinese_score<=-1||sc2.Chinese_score<=-1)
		CFile<<"Chinese : "<<"\t\t"<<sc1.Chinese_score<<"\t"<<'!'<<"\t\t"<<sc2.Chinese_score<<"\t"<<'!'<<endl;
	else if(sc1.Chinese_score>sc2.Chinese_score)
		CFile<<"Chinese : "<<"\t\t"<<sc1.Chinese_score<<"\t"<<'+'<<"\t\t"<<sc2.Chinese_score<<"\t"<<'-'<<endl;
	else if(sc1.Chinese_score<sc2.Chinese_score)
		CFile<<"Chinese : "<<"\t\t"<<sc1.Chinese_score<<"\t"<<'-'<<"\t\t"<<sc2.Chinese_score<<"\t"<<'+'<<endl;
	else
		CFile<<"Chinese : "<<"\t\t"<<sc1.Chinese_score<<"\t"<<'='<<"\t\t"<<sc2.Chinese_score<<"\t"<<'='<<endl;
	
	if(sc1.Maths_score<=-1||sc2.Maths_score<=-1)
		CFile<<"Maths : "<<"\t\t"<<sc1.Maths_score<<"\t"<<'!'<<"\t\t"<<sc2.Maths_score<<"\t"<<'!'<<endl;
    else if(sc1.Maths_score>sc2.Maths_score)
		CFile<<"Maths : "<<"\t\t"<<sc1.Maths_score<<"\t"<<'+'<<"\t\t"<<sc2.Maths_score<<"\t"<<'-'<<endl;
	else if(sc1.Maths_score<sc2.Maths_score)
		CFile<<"Maths : "<<"\t\t"<<sc1.Maths_score<<"\t"<<'-'<<"\t\t"<<sc2.Maths_score<<"\t"<<'+'<<endl;
	else
		CFile<<"Maths : "<<"\t\t"<<sc1.Maths_score<<"\t"<<'='<<"\t\t"<<sc2.Maths_score<<"\t"<<'='<<endl;
    
    if(sc1.English_score<=-1||sc2.English_score<=-1)
		CFile<<"English : "<<"\t\t"<<sc1.English_score<<"\t"<<'!'<<"\t\t"<<sc2.English_score<<"\t"<<'!'<<endl;
    else if(sc1.English_score>sc2.English_score)
		CFile<<"English : "<<"\t\t"<<sc1.English_score<<"\t"<<'+'<<"\t\t"<<sc2.English_score<<"\t"<<'-'<<endl;
	else if(sc1.English_score<sc2.English_score)
		CFile<<"English : "<<"\t\t"<<sc1.English_score<<"\t"<<'-'<<"\t\t"<<sc2.English_score<<"\t"<<'+'<<endl;
	else
		CFile<<"English : "<<"\t\t"<<sc1.English_score<<"\t"<<'='<<"\t\t"<<sc2.English_score<<"\t"<<'='<<endl;
    
    if(sc1.Physics_score<=-1||sc2.Physics_score<=-1)
		CFile<<"Physics : "<<"\t\t"<<sc1.Physics_score<<"\t"<<'!'<<"\t\t"<<sc2.Physics_score<<"\t"<<'!'<<endl;
    else if(sc1.Physics_score>sc2.Physics_score)
		CFile<<"Physics : "<<"\t\t"<<sc1.Physics_score<<"\t"<<'+'<<"\t\t"<<sc2.Physics_score<<"\t"<<'-'<<endl;
	else if(sc1.Physics_score<sc2.Physics_score)
		CFile<<"Physics : "<<"\t\t"<<sc1.Physics_score<<"\t"<<'-'<<"\t\t"<<sc2.Physics_score<<"\t"<<'+'<<endl;
	else
		CFile<<"Physics : "<<"\t\t"<<sc1.Physics_score<<"\t"<<'='<<"\t\t"<<sc2.Physics_score<<"\t"<<'='<<endl;
    
    if(sc1.Chemistry_score<=-1||sc2.Chemistry_score<=-1)
		CFile<<"Chemistry : "<<"\t"<<sc1.Chemistry_score<<"\t"<<'!'<<"\t\t"<<sc2.Chemistry_score<<"\t"<<'!'<<endl;
    else if(sc1.Chemistry_score>sc2.Chemistry_score)
		CFile<<"Chemistry : "<<"\t"<<sc1.Chemistry_score<<"\t"<<'+'<<"\t\t"<<sc2.Chemistry_score<<"\t"<<'-'<<endl;
	else if(sc1.Chemistry_score<sc2.Chemistry_score)
		CFile<<"Chemistry : "<<"\t"<<sc1.Chemistry_score<<"\t"<<'-'<<"\t\t"<<sc2.Chemistry_score<<"\t"<<'+'<<endl;
	else
		CFile<<"Chemistry : "<<"\t"<<sc1.Chemistry_score<<"\t"<<'='<<"\t\t"<<sc2.Chemistry_score<<"\t"<<'='<<endl;
    
    if(sc1.Politics_score<=-1||sc2.Politics_score<=-1)
		CFile<<"Politics : "<<"\t\t"<<sc1.Politics_score<<"\t"<<'!'<<"\t\t"<<sc2.Politics_score<<"\t"<<'!'<<endl;
    else if(sc1.Politics_score>sc2.Politics_score)
		CFile<<"Politics : "<<"\t\t"<<sc1.Politics_score<<"\t"<<'+'<<"\t\t"<<sc2.Politics_score<<"\t"<<'-'<<endl;
	else if(sc1.Politics_score<sc2.Politics_score)
		CFile<<"Politics : "<<"\t\t"<<sc1.Politics_score<<"\t"<<'-'<<"\t\t"<<sc2.Politics_score<<"\t"<<'+'<<endl;
	else
		CFile<<"Politics : "<<"\t\t"<<sc1.Politics_score<<"\t"<<'='<<"\t\t"<<sc2.Politics_score<<"\t"<<'='<<endl;
    
    if(sc1.History_score<=-1||sc2.History_score<=-1)
		CFile<<"History : "<<"\t\t"<<sc1.History_score<<"\t"<<'!'<<"\t\t"<<sc2.History_score<<"\t"<<'!'<<endl;
    else if(sc1.History_score>sc2.History_score)
		CFile<<"History : "<<"\t\t"<<sc1.History_score<<"\t"<<'+'<<"\t\t"<<sc2.History_score<<"\t"<<'-'<<endl;
	else if(sc1.History_score<sc2.History_score)
		CFile<<"History : "<<"\t\t"<<sc1.History_score<<"\t"<<'-'<<"\t\t"<<sc2.History_score<<"\t"<<'+'<<endl;
	else
		CFile<<"History : "<<"\t\t"<<sc1.History_score<<"\t"<<'='<<"\t\t"<<sc2.History_score<<"\t"<<'='<<endl;
    
    if(sc1.Geography_score<=-1||sc2.Geography_score<=-1)
		CFile<<"Geography : "<<"\t"<<sc1.Geography_score<<"\t"<<'!'<<"\t\t"<<sc2.Geography_score<<"\t"<<'!'<<endl;
    else if(sc1.Geography_score>sc2.Geography_score)
		CFile<<"Geography : "<<"\t"<<sc1.Geography_score<<"\t"<<'+'<<"\t\t"<<sc2.Geography_score<<"\t"<<'-'<<endl;
	else if(sc1.Geography_score<sc2.Geography_score)
		CFile<<"Geography : "<<"\t"<<sc1.Geography_score<<"\t"<<'-'<<"\t\t"<<sc2.Geography_score<<"\t"<<'+'<<endl;
	else
		CFile<<"Geography : "<<"\t"<<sc1.Geography_score<<"\t"<<'='<<"\t\t"<<sc2.Geography_score<<"\t"<<'='<<endl;
    
    if(sc1.Biological_score<=-1||sc2.Biological_score<=-1)
		CFile<<"Biological : "<<"\t"<<sc1.Biological_score<<"\t"<<'!'<<"\t\t"<<sc2.Biological_score<<"\t"<<'!'<<endl;
    else if(sc1.Biological_score>sc2.Biological_score)
		CFile<<"Biological : "<<"\t"<<sc1.Biological_score<<"\t"<<'+'<<"\t\t"<<sc2.Biological_score<<"\t"<<'-'<<endl;
	else if(sc1.Biological_score<sc2.Biological_score)
		CFile<<"Biological : "<<"\t"<<sc1.Biological_score<<"\t"<<'-'<<"\t\t"<<sc2.Biological_score<<"\t"<<'+'<<endl;
	else
		CFile<<"Biological : "<<"\t"<<sc1.Biological_score<<"\t"<<'='<<"\t\t"<<sc2.Biological_score<<"\t"<<'='<<endl;
    
    if(sc1.Sum<=-1||sc2.Sum<=-1)
		CFile<<"Sum : "<<"\t\t"<<sc1.Sum<<"\t"<<'!'<<"\t\t"<<sc2.Sum<<"\t"<<'!'<<endl;
    else if(sc1.Sum>sc2.Sum)
		CFile<<"Sum : "<<"\t\t"<<sc1.Sum<<"\t"<<'+'<<"\t\t"<<sc2.Sum<<"\t"<<'-'<<endl;
	else if(sc1.Sum<sc2.Sum)
		CFile<<"Sum : "<<"\t\t"<<sc1.Sum<<"\t"<<'-'<<"\t\t"<<sc2.Sum<<"\t"<<'+'<<endl;
	else
		CFile<<"Sum : "<<"\t\t"<<sc1.Sum<<"\t"<<'='<<"\t\t"<<sc2.Sum<<"\t"<<'='<<endl;
    
    if(sc1.Average<=-1||sc2.Average<=-1)
		CFile<<"Average : "<<"\t\t"<<sc1.Average<<"\t"<<'!'<<"\t\t"<<sc2.Average<<"\t"<<'!'<<endl;
    else if(sc1.Average>sc2.Average)
		CFile<<"Average : "<<"\t\t"<<sc1.Average<<"\t"<<'+'<<"\t\t"<<sc2.Average<<"\t"<<'-'<<endl;
	else if(sc1.Average<sc2.Average)
		CFile<<"Average : "<<"\t\t"<<sc1.Average<<"\t"<<'-'<<"\t\t"<<sc2.Average<<"\t"<<'+'<<endl;
	else
		CFile<<"Average : "<<"\t\t"<<sc1.Average<<"\t"<<'='<<"\t\t"<<sc2.Average<<"\t"<<'='<<endl;
    
    CFile.close();//关闭文件 
	
	ShellExecute(NULL,"open",FilePath.c_str(),NULL,NULL,SW_SHOW);//Windows API打开txt文本文件
	
	cout<<endl<<"完成！"<<endl<<endl;
	cout<<"---------------------------------------------------"<<endl;
}

void key_in(){//录入函数 
	info INtemp1;
	score INtemp2; 
	stringstream _Directory,_FilePath,ss;
	string Directory,FilePath;
	
	cout<<"-----------------------录入------------------------"<<endl;
	cout<<"请输入日期(yymmdd,无空格):";
	cin>>INtemp1.day;// info_日期 
	
	_Directory<<"data\\main\\"<<INtemp1.day;//目标路径
	
	ss<<_Directory.str();
	ss>>Directory;
	
	ss.clear();
	
	cout<<"请输入姓名:";
	cin>>INtemp1.name;// info_姓名 
	cout<<"请输入年级(一个阿拉伯数字):";
	cin>>INtemp1.grade;// info_年级
	
	_FilePath<<"data\\main\\"<<INtemp1.day<<"\\"<<INtemp1.day<<INtemp1.name<<INtemp1.grade<<".txt";//目标文件路径 
	
	ss<<_FilePath.str();
	ss>>FilePath;
	
	ss.clear();
	
	if(_access(Directory.c_str(),00)==-1){//创建目标路径 
		if(!CreateDirectory(Directory.c_str(),NULL)){
			cout<<"出现错误(Error#key_in_CreateDirectory)"<<endl<<endl;;
			cout<<"---------------------------------------------------"<<endl;
			return;
		}
	}
	
	cout<<endl<<"输入成绩(输入-1表示无此项)"<<endl;
	cout<<"请输入语文(Chinese)成绩:";
	cin>>INtemp2.Chinese_score;// score_Chinese
	cout<<"请输入数学(Maths)成绩:";
	cin>>INtemp2.Maths_score;// score_Maths
	cout<<"请输入英语(English)成绩:";
	cin>>INtemp2.English_score;// score_English
	cout<<"请输入物理(Physics_score)成绩:";
	cin>>INtemp2.Physics_score;// score_Physics
	cout<<"请输入化学(Chemistry)成绩:";
	cin>>INtemp2.Chemistry_score;// score_Chemistry
	cout<<"请输入政治(Politics)成绩:";
	cin>>INtemp2.Politics_score;// score_Politics
	cout<<"请输入历史(History)成绩:";
	cin>>INtemp2.History_score;// score_History
	cout<<"请输入地理(Geography)成绩:";
	cin>>INtemp2.Geography_score;// score_Geography
	cout<<"请输入生物(Biological)成绩:";
	cin>>INtemp2.Biological_score;// score_Biological
	cout<<endl;
	
	double cnt=0;//计数 用于计算平均分 
	//求总 
	INtemp2.Sum=0;
	if(INtemp2.Chinese_score>-1){
		INtemp2.Sum+=INtemp2.Chinese_score;
		cnt++;
	}
	if(INtemp2.Maths_score>-1){
		INtemp2.Sum+=INtemp2.Maths_score;
		cnt++;
	}
	if(INtemp2.English_score>-1){
		INtemp2.Sum+=INtemp2.English_score;
		cnt++;
	}
	if(INtemp2.Physics_score>-1){
		INtemp2.Sum+=INtemp2.Physics_score;
		cnt++;
	}
	if(INtemp2.Chemistry_score>-1){
		INtemp2.Sum+=INtemp2.Chemistry_score;
		cnt++;
	}
	if(INtemp2.Politics_score>-1){
		INtemp2.Sum+=INtemp2.Politics_score;
		cnt++;
	}
	if(INtemp2.History_score>-1){
		INtemp2.Sum+=INtemp2.History_score;
		cnt++;
	}
	if(INtemp2.Geography_score>-1){
		INtemp2.Sum+=INtemp2.Geography_score;
		cnt++;
	}
	if(INtemp2.Biological_score>-1){
		INtemp2.Sum+=INtemp2.Biological_score;
		cnt++;
	}
	
	//求平均分 
	INtemp2.Average=0;
	INtemp2.Average=INtemp2.Sum/cnt;
	
	ofstream File(FilePath.c_str(),ios_base::out);//创建文件 
	if(!File) {
        cout<<endl<<"出现错误(Error#key_in_File):"<<endl;
        return;
    }
    //文件内输出 
    File<<"#Date : "<<INtemp1.day<<endl;
    File<<"#Name : "<<INtemp1.name<<endl;
    File<<"#Grade : "<<INtemp1.grade<<endl;
    File<<endl;
    File<<"#----------Score----------#"<<endl<<endl;
    File<<"Chinese : "<<INtemp2.Chinese_score<<endl;
    File<<"Maths : "<<INtemp2.Maths_score<<endl;
    File<<"English : "<<INtemp2.English_score<<endl;
    File<<"Physics : "<<INtemp2.Physics_score<<endl;
    File<<"Chemistry : "<<INtemp2.Chemistry_score<<endl;
    File<<"Politics : "<<INtemp2.Politics_score<<endl;
    File<<"History : "<<INtemp2.History_score<<endl;
    File<<"Geography : "<<INtemp2.Geography_score<<endl;
    File<<"Biological : "<<INtemp2.Biological_score<<endl;
    File<<"Total : "<<INtemp2.Sum<<endl;
    File<<"Average : "<<INtemp2.Average;
    File.close();
    
    ShellExecute(NULL,"open",FilePath.c_str(),NULL,NULL,SW_SHOW);//Windows API打开txt文本文件
    
    cout<<"录入完成！"<<endl<<endl; 
	cout<<"---------------------------------------------------"<<endl;
}

void getFileNames(string path, vector<string>& files){
	//文件句柄
	//注意：我发现有些文章代码此处是long类型，实测运行中会报错访问异常
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1){
		do{
			//如果是目录,递归查找
			//如果不是,把文件绝对路径存入vector中
			if ((fileinfo.attrib & _A_SUBDIR)){
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


void list_file(){
	stringstream _path_,ss;
	string _path,npath;
	cout<<"请选择文件夹(main/temp)"<<endl<<">>";//输入文件夹名 
	cin>>_path;
	cout<<endl;
	
	_path_<<"data\\"<<_path;//格式转换 
	ss<<_path_.str();
	ss>>npath;
	
	if(_access(npath.c_str(),00)==-1){
		cout<<"此文件夹不存在"<<endl;
		cout<<endl<<"---------------------------------------------------"<<endl;
		return;
	}
	
	vector<string> fileNames;
	string path(npath); 	//自己选择目录测试
	getFileNames(path, fileNames);
	if(fileNames.empty()){
		cout<<"(空)"<<endl;
	}
	for (const auto &ph : fileNames) {
		cout<< ph << endl;
	}
	cout<<endl<<"---------------------------------------------------"<<endl;
}

void Delete_Files(string dir);

void chose_delete(){
	stringstream _path_,ss;
	string _path,npath;
	cout<<"请选择文件夹(main/temp|all)"<<endl<<">>";//输入文件夹名 
	cin>>_path;
	cout<<endl;
	
	if(_path=="all"){
		Delete_Files("data\\main");
		Delete_Files("data\\temp");
		cout<<"完成！"<<endl;
		cout<<endl<<"---------------------------------------------------"<<endl;
		return;
	}
	
	_path_<<"data\\"<<_path;//格式转换 
	ss<<_path_.str();
	ss>>npath;
	
	if(_access(npath.c_str(),00)==-1){
		cout<<"此文件夹不存在"<<endl;
		cout<<endl<<"---------------------------------------------------"<<endl;
		return;
	}
	
	Delete_Files(npath);
	
	cout<<"完成！"<<endl;
	cout<<endl<<"---------------------------------------------------"<<endl;
}

void Developers(){
	string choices;
	char _choices;

	while(true){
		cout<<"-----------------开发者选项------------------------"<<endl;
		cout<<"输入 1 则 列出数据文件"<<endl<<"输入 2 则 删除数据文件"<<endl<<"输入 3 则 退回至主菜单"<<endl;
		cout<<"---------------------------------------------------"<<endl<<">>";
		cin>>choices;
		_choices=choices[0];
		switch(_choices){
			case '1':
				list_file();
				break;
			case '2':
				chose_delete();
				break;
			case '3':
				return;
				break;
			default :
      			cout << "无效的选项" << endl;
      			break;
		}
	}
	
}

void Initialization(){
	string Directory;
	Directory="data";
	if(_access(Directory.c_str(),00)==-1){//创建一级路径 
		if(!CreateDirectory(Directory.c_str(),NULL)){
			cout<<"出现错误(Error#Initialization_CreateDirectory)"<<endl;
			return;
		}
	}
	Directory="data\\main";
	if(_access(Directory.c_str(),00)==-1){//创建二级路径 
		if(!CreateDirectory(Directory.c_str(),NULL)){
			cout<<"出现错误(Error#Initialization_CreateDirectory)"<<endl;
			return;
		}
	}
	Directory="data\\temp";
	if(_access(Directory.c_str(),00)==-1){//创建二级路径 
		if(!CreateDirectory(Directory.c_str(),NULL)){
			cout<<"出现错误(Error#Initialization_CreateDirectory)"<<endl;
			return;
		}
	}
}

void Delete_Files(string dir){//删除temp文件夹内因compare函数而产生的文件 
	//在目录后面加上"\\*.*"进行第一次搜索
	string newDir = dir + "\\*.*";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1){//判断文件是否存在 --- 否 -> -1 
		return;
	}

	do{
		if (fileinfo.attrib & _A_SUBDIR){//如果为文件夹，加上文件夹路径，再次遍历
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			newDir = dir + "\\" + fileinfo.name;
			Delete_Files(newDir.c_str());//先遍历删除文件夹下的文件，再删除空的文件夹
			//cout << newDir.c_str() << endl;//输出删除的路径
			if (!_rmdir(newDir.c_str()) == 0){//删除空文件夹
				cout << "出现错误(Error#Delete_File_remove_empty_directory)" << endl;
			}
		}
		else{
			string file_path = dir + "\\" + fileinfo.name;
			//cout << file_path.c_str() << endl;//输出删除的文件名 
			if (!remove(file_path.c_str()) == 0) {//删除文件
				cout << "出现错误(Error#Delete_File_remove_file)" << endl;
			}
		}
	} while(!_findnext(handle, &fileinfo));

	_findclose(handle);
	return;
}

void program_exit(){
	string Choice;
	cout<<"是否清理缓存？(清空因 对比 产生的文件数据)"<<"[Y/N]"<<endl<<">>";
	cin>>Choice;
	if(Choice=="Y"||Choice=="y")
		Delete_Files("data\\temp");
	else
		return;
}

int main(){
	Initialization();//初始化 
	string choice;
	char _choice;
	cout<<"欢迎使用成绩管理系统！"<<endl;
	while(true){
		cout<<"-------------主菜单--------------"<<endl;
		cout<<"输入 1 则 查询"<<endl<<"输入 2 则 对比"<<endl<<"输入 3 则 录入"<<endl<<"输入 4 则 开发者选项"<<endl<<"输入 5 则 退出"<<endl;
		cout<<"---------------------------------"<<endl<<">>";
		cin>>choice;
		_choice=choice[0];
		switch(_choice){
			case '1' :
      			look_for();
      			break;
   			case '2' :
   				compare();
   				break;
   			case '3' :
   				key_in();
   				break;
   			case '4' :
   				Developers();
   				break;
   			case '5' :
   				program_exit();
   				cout<<endl<<"已执行退出操作"<<endl;
				Sleep(1500); 
   				return 0;
   				break;
   			default :
      			cout << "无效的选项" << endl;
      			break;
   		}
	}
	return 0;
}

