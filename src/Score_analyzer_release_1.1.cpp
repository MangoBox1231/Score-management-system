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

struct info{//������Ϣ 
	string day;
	string name;
	string grade;
};

struct score{//������Ʒ��� 
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
	
	//���ڵ�ǰϵͳ�ĵ�ǰʱ������� 
	time_t now=time(0);
	tm *ltm=localtime(&now);
	
	_year<<1900+ltm->tm_year;
	
	ss<<_year.str();
	ss>>year;
	ss.clear();
	
	if((1+ltm->tm_mon)<=9)//��ʽ���� 
		_month<<"0"<<(1+ltm->tm_mon);
	else
		_month<<(1+ltm->tm_mon);
	
	ss<<_month.str();
	ss>>month;
	ss.clear();
	
	if((ltm->tm_mday)<=9)//��ʽ���� 
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

int format(){//���ַ�������תΪ���������� 
	memset(_Rscore_,-2,sizeof(_Rscore_)/sizeof(_Rscore_[0]));//�������� 
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

int read(string R){//���ɼ������ڴ� 
	char Rscore[256];
	int cnt,j=0;
	stringstream ss;
	ifstream RFile(R.c_str());//���ļ� 
	if(!RFile){
        cout<<endl<<"���ִ���(Error#read_RFile)"<<endl;
        RFile.close();
        return 1;
    }
    while(!RFile.eof()){
    	bool flag=true;
    	cnt=0;//��ʼ�� 
    	string _score;
    	memset(Rscore,0,strlen(Rscore));
    	RFile.getline(Rscore,50);//��ȡһ������ 
    	for(int i=0;i<strlen(Rscore);i++){//ɸѡ������ 
    		if(Rscore[i]=='#'){
    			flag=false;
    			break;
			}
    		if(Rscore[i]>='0'&&Rscore[i]<='9'||Rscore[i]=='.'||Rscore[i]=='-'){
    			_score+=Rscore[i];
			}
		}
		if(flag){//��������ʱ�������� 
			_Rscore[j++]=_score;
		}
	}
	RFile.close();
	return 0;
}

void look_for(){//��ѯ���� 
	int testopen; 
	info looktemp1;// info_�ṹ�� ������Ϣ 
	stringstream lookd;//��ʽ��һ������ͨ�����븳ֵ���ַ���(��� 42��) 
	
	cout<<"-----------------------��ѯ------------------------"<<endl;
	
	cout<<"����������(yymmdd,�޿ո�):";
	cin>>looktemp1.day;// info_���� 
	cout<<"����������:";
	cin>>looktemp1.name;// info_���� 
	cout<<"�������꼶(һ������������):";
	cin>>looktemp1.grade;// info_�꼶 
	
	lookd<<"data\\main\\"<<looktemp1.day<<"\\"<<looktemp1.day<<looktemp1.name<<looktemp1.grade<<".txt";//���븳ֵ���ַ���
	if(_access(lookd.str().c_str(),00)==-1){
		cout<<endl<<"���޴���������ڡ��������꼶�Ƿ���ȷ��"<<endl<<endl;
		cout<<"---------------------------------------------------"<<endl;
		return;
	}
	ShellExecute(NULL,"open",lookd.str().c_str(),NULL,NULL,SW_SHOW);//Windows API��txt�ı��ļ�
	
	cout<<endl;
	cout<<"���!"<<endl<<endl; 
	cout<<"---------------------------------------------------"<<endl;
}

void compare(){//�ȽϺ��� 
	info cmp1,cmp2;
	score sc1,sc2;
	stringstream read1,read2,ss;
	stringstream _Directory1,_Directory2,_FilePath;
	string Directory1,Directory2,FilePath;
	cout<<"-----------------------�Ա�------------------------"<<endl;

	//cmp1
	cout<<"�������һ������(yymmdd,�޿ո�):";
	cin>>cmp1.day;// info_���� 
	cout<<"�������һ������:";
	cin>>cmp1.name;// info_���� 
	cout<<"�������һ���꼶(һ������������):";
	cin>>cmp1.grade;// info_�꼶
	cout<<endl; 
	
	//cmp2
	cout<<"������ڶ�������(yymmdd,�޿ո�):";
	cin>>cmp2.day;// info_���� 
	cout<<"������ڶ�������:";
	cin>>cmp2.name;// info_���� 
	cout<<"������ڶ����꼶(һ������������):";
	cin>>cmp2.grade;// info_�꼶
	
	//��ʽ���ַ���������ֵ
	read1<<"data\\main\\"<<cmp1.day<<"\\"<<cmp1.day<<cmp1.name<<cmp1.grade<<".txt";
	read2<<"data\\main\\"<<cmp2.day<<"\\"<<cmp2.day<<cmp2.name<<cmp2.grade<<".txt";
	
	string r1,r2;
	
	ss<<read1.str();//ͨ��sstream�� ��ʽ�� תΪ ��ͨ�ַ��� 
	ss>>r1;
	ss.clear();
	
	ss<<read2.str();
	ss>>r2;
	ss.clear();
	
	//�ļ�����-��ȡcmp1
    if(read(r1)){
    	cout<<endl<<"#1�ļ�δ�ɹ��򿪣�������Ϣ�����Ƿ���ȷ��"<<endl;
    	cout<<endl<<"---------------------------------------------------"<<endl;
		return; 
	}
	if (!format()){
		cout<<endl<<"���ִ���(Error#compare_format_1)"<<endl;
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
    
    //�ļ�����-��ȡcmp2
    if(read(r2)){
    	cout<<"#2�ļ�δ�ɹ��򿪣�������Ϣ�����Ƿ���ȷ��"<<endl;
    	cout<<endl<<"---------------------------------------------------"<<endl;
		return; 
	}
	if (!format()){
		cout<<"���ִ���(Error#compare_format_2)"<<endl;
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
    
    get_time();//��ȡ��ǰʱ�� 
    
    _Directory1<<"data\\temp\\"<<year<<month<<day;//Ŀ��·��1
    
    _Directory2<<"data\\temp\\"<<year<<month<<day<<"\\"<<ntime;//Ŀ��·��2
    
    ss<<_Directory1.str();//��������ת�� 
	ss>>Directory1;
	ss.clear();
	
	ss<<_Directory2.str();//��������ת�� 
	ss>>Directory2;
	ss.clear();
	
	_FilePath<<"data\\temp\\"<<year<<month<<day<<"\\"<<ntime<<"\\"<<year<<month<<day<<cmp1.name<<cmp2.name<<".txt";//Ŀ���ļ�·��
	
	ss<<_FilePath.str();//��������ת�� 
	ss>>FilePath;
	ss.clear();
	
	if(_access(Directory1.c_str(),00)==-1){//����Ŀ��·�� 
		if(!CreateDirectory(Directory1.c_str(),NULL)){
			cout<<"���ִ���(Error#compare_CreateDirectory_1)"<<endl;
			cout<<endl<<"---------------------------------------------------"<<endl;
			return;
		}
	}
	if(_access(Directory2.c_str(),00)==-1){//����Ŀ��·�� 
		if(!CreateDirectory(Directory2.c_str(),NULL)){
			cout<<"���ִ���(Error#compare_CreateDirectory_2)"<<endl;
			cout<<endl<<"---------------------------------------------------"<<endl;
			return;
		}
	}
	
	ofstream CFile(FilePath.c_str(),ios_base::out);//�����ļ� 
	if(!CFile) {
        cout<<endl<<"���ִ���(Error#key_in_File):"<<endl<<endl;
        cout<<"---------------------------------------------------"<<endl;
        return;
    }
	CFile<<"#Date : "<<year<<'/'<<month<<'/'<<day<<endl;
	CFile<<"#Name : "<<cmp1.name<<" <-> "<<cmp2.name<<endl<<endl;
	CFile<<"#------------------Comparation------------------#"<<endl<<endl;
	//�ԱȲ��ӱ�ʶ--�ļ������ 
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
    
    CFile.close();//�ر��ļ� 
	
	ShellExecute(NULL,"open",FilePath.c_str(),NULL,NULL,SW_SHOW);//Windows API��txt�ı��ļ�
	
	cout<<endl<<"��ɣ�"<<endl<<endl;
	cout<<"---------------------------------------------------"<<endl;
}

void key_in(){//¼�뺯�� 
	info INtemp1;
	score INtemp2; 
	stringstream _Directory,_FilePath,ss;
	string Directory,FilePath;
	
	cout<<"-----------------------¼��------------------------"<<endl;
	cout<<"����������(yymmdd,�޿ո�):";
	cin>>INtemp1.day;// info_���� 
	
	_Directory<<"data\\main\\"<<INtemp1.day;//Ŀ��·��
	
	ss<<_Directory.str();
	ss>>Directory;
	
	ss.clear();
	
	cout<<"����������:";
	cin>>INtemp1.name;// info_���� 
	cout<<"�������꼶(һ������������):";
	cin>>INtemp1.grade;// info_�꼶
	
	_FilePath<<"data\\main\\"<<INtemp1.day<<"\\"<<INtemp1.day<<INtemp1.name<<INtemp1.grade<<".txt";//Ŀ���ļ�·�� 
	
	ss<<_FilePath.str();
	ss>>FilePath;
	
	ss.clear();
	
	if(_access(Directory.c_str(),00)==-1){//����Ŀ��·�� 
		if(!CreateDirectory(Directory.c_str(),NULL)){
			cout<<"���ִ���(Error#key_in_CreateDirectory)"<<endl<<endl;;
			cout<<"---------------------------------------------------"<<endl;
			return;
		}
	}
	
	cout<<endl<<"����ɼ�(����-1��ʾ�޴���)"<<endl;
	cout<<"����������(Chinese)�ɼ�:";
	cin>>INtemp2.Chinese_score;// score_Chinese
	cout<<"��������ѧ(Maths)�ɼ�:";
	cin>>INtemp2.Maths_score;// score_Maths
	cout<<"������Ӣ��(English)�ɼ�:";
	cin>>INtemp2.English_score;// score_English
	cout<<"����������(Physics_score)�ɼ�:";
	cin>>INtemp2.Physics_score;// score_Physics
	cout<<"�����뻯ѧ(Chemistry)�ɼ�:";
	cin>>INtemp2.Chemistry_score;// score_Chemistry
	cout<<"����������(Politics)�ɼ�:";
	cin>>INtemp2.Politics_score;// score_Politics
	cout<<"��������ʷ(History)�ɼ�:";
	cin>>INtemp2.History_score;// score_History
	cout<<"���������(Geography)�ɼ�:";
	cin>>INtemp2.Geography_score;// score_Geography
	cout<<"����������(Biological)�ɼ�:";
	cin>>INtemp2.Biological_score;// score_Biological
	cout<<endl;
	
	double cnt=0;//���� ���ڼ���ƽ���� 
	//���� 
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
	
	//��ƽ���� 
	INtemp2.Average=0;
	INtemp2.Average=INtemp2.Sum/cnt;
	
	ofstream File(FilePath.c_str(),ios_base::out);//�����ļ� 
	if(!File) {
        cout<<endl<<"���ִ���(Error#key_in_File):"<<endl;
        return;
    }
    //�ļ������ 
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
    
    ShellExecute(NULL,"open",FilePath.c_str(),NULL,NULL,SW_SHOW);//Windows API��txt�ı��ļ�
    
    cout<<"¼����ɣ�"<<endl<<endl; 
	cout<<"---------------------------------------------------"<<endl;
}

void getFileNames(string path, vector<string>& files){
	//�ļ����
	//ע�⣺�ҷ�����Щ���´���˴���long���ͣ�ʵ�������лᱨ������쳣
	intptr_t hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1){
		do{
			//�����Ŀ¼,�ݹ����
			//�������,���ļ�����·������vector��
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
	cout<<"��ѡ���ļ���(main/temp)"<<endl<<">>";//�����ļ����� 
	cin>>_path;
	cout<<endl;
	
	_path_<<"data\\"<<_path;//��ʽת�� 
	ss<<_path_.str();
	ss>>npath;
	
	if(_access(npath.c_str(),00)==-1){
		cout<<"���ļ��в�����"<<endl;
		cout<<endl<<"---------------------------------------------------"<<endl;
		return;
	}
	
	vector<string> fileNames;
	string path(npath); 	//�Լ�ѡ��Ŀ¼����
	getFileNames(path, fileNames);
	if(fileNames.empty()){
		cout<<"(��)"<<endl;
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
	cout<<"��ѡ���ļ���(main/temp|all)"<<endl<<">>";//�����ļ����� 
	cin>>_path;
	cout<<endl;
	
	if(_path=="all"){
		Delete_Files("data\\main");
		Delete_Files("data\\temp");
		cout<<"��ɣ�"<<endl;
		cout<<endl<<"---------------------------------------------------"<<endl;
		return;
	}
	
	_path_<<"data\\"<<_path;//��ʽת�� 
	ss<<_path_.str();
	ss>>npath;
	
	if(_access(npath.c_str(),00)==-1){
		cout<<"���ļ��в�����"<<endl;
		cout<<endl<<"---------------------------------------------------"<<endl;
		return;
	}
	
	Delete_Files(npath);
	
	cout<<"��ɣ�"<<endl;
	cout<<endl<<"---------------------------------------------------"<<endl;
}

void Developers(){
	string choices;
	char _choices;

	while(true){
		cout<<"-----------------������ѡ��------------------------"<<endl;
		cout<<"���� 1 �� �г������ļ�"<<endl<<"���� 2 �� ɾ�������ļ�"<<endl<<"���� 3 �� �˻������˵�"<<endl;
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
      			cout << "��Ч��ѡ��" << endl;
      			break;
		}
	}
	
}

void Initialization(){
	string Directory;
	Directory="data";
	if(_access(Directory.c_str(),00)==-1){//����һ��·�� 
		if(!CreateDirectory(Directory.c_str(),NULL)){
			cout<<"���ִ���(Error#Initialization_CreateDirectory)"<<endl;
			return;
		}
	}
	Directory="data\\main";
	if(_access(Directory.c_str(),00)==-1){//��������·�� 
		if(!CreateDirectory(Directory.c_str(),NULL)){
			cout<<"���ִ���(Error#Initialization_CreateDirectory)"<<endl;
			return;
		}
	}
	Directory="data\\temp";
	if(_access(Directory.c_str(),00)==-1){//��������·�� 
		if(!CreateDirectory(Directory.c_str(),NULL)){
			cout<<"���ִ���(Error#Initialization_CreateDirectory)"<<endl;
			return;
		}
	}
}

void Delete_Files(string dir){//ɾ��temp�ļ�������compare�������������ļ� 
	//��Ŀ¼�������"\\*.*"���е�һ������
	string newDir = dir + "\\*.*";
	//���ڲ��ҵľ��
	intptr_t handle;
	struct _finddata_t fileinfo;
	//��һ�β���
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1){//�ж��ļ��Ƿ���� --- �� -> -1 
		return;
	}

	do{
		if (fileinfo.attrib & _A_SUBDIR){//���Ϊ�ļ��У������ļ���·�����ٴα���
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
			newDir = dir + "\\" + fileinfo.name;
			Delete_Files(newDir.c_str());//�ȱ���ɾ���ļ����µ��ļ�����ɾ���յ��ļ���
			//cout << newDir.c_str() << endl;//���ɾ����·��
			if (!_rmdir(newDir.c_str()) == 0){//ɾ�����ļ���
				cout << "���ִ���(Error#Delete_File_remove_empty_directory)" << endl;
			}
		}
		else{
			string file_path = dir + "\\" + fileinfo.name;
			//cout << file_path.c_str() << endl;//���ɾ�����ļ��� 
			if (!remove(file_path.c_str()) == 0) {//ɾ���ļ�
				cout << "���ִ���(Error#Delete_File_remove_file)" << endl;
			}
		}
	} while(!_findnext(handle, &fileinfo));

	_findclose(handle);
	return;
}

void program_exit(){
	string Choice;
	cout<<"�Ƿ������棿(����� �Ա� �������ļ�����)"<<"[Y/N]"<<endl<<">>";
	cin>>Choice;
	if(Choice=="Y"||Choice=="y")
		Delete_Files("data\\temp");
	else
		return;
}

int main(){
	Initialization();//��ʼ�� 
	string choice;
	char _choice;
	cout<<"��ӭʹ�óɼ�����ϵͳ��"<<endl;
	while(true){
		cout<<"-------------���˵�--------------"<<endl;
		cout<<"���� 1 �� ��ѯ"<<endl<<"���� 2 �� �Ա�"<<endl<<"���� 3 �� ¼��"<<endl<<"���� 4 �� ������ѡ��"<<endl<<"���� 5 �� �˳�"<<endl;
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
   				cout<<endl<<"��ִ���˳�����"<<endl;
				Sleep(1500); 
   				return 0;
   				break;
   			default :
      			cout << "��Ч��ѡ��" << endl;
      			break;
   		}
	}
	return 0;
}

