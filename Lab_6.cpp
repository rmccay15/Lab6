
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

class Signal{
private:
	int length;
	float *data,max,avg;
	void maximum();
	void average();

public:
	Signal();
	~Signal(){delete data;};
	Signal(int filenumber);
	Signal(char* filename);
	void Sig_info();
	
	int menu();
	void scale(float scale_num);
	void statistics();
	void center();
	void normalize();
	void save_file();
	void offset(float offset_num);

};

void Signal::offset(float offset_num)
{
	for(int i = 0;i<length;i++)
	{
		data[i] += offset_num;
	}	
}

void Signal::save_file()
{
	char file_name[20];
	cout<<"Excluding the extension, what would you like to call the file? "<<endl;
	cin>>file_name;
	strcat(file_name,".txt");
	ofstream file;
	file.open(file_name);
	file<<length<<" "<<max;
	for(int i=0;i<length;i++)
	{
		file<<"\n"<<data[i];
	}
	file.close();
}

void Signal::center()
{
	for(int i=0;i<length;i++)
	{
		data[i] -= avg;
		cout<<data[i]<<endl;
	}
}

void Signal::normalize()
{
	for(int i=0;i<length;i++)
	{
		data[i] /= max;
	}
}

void Signal::statistics()
{
	maximum();
	average();
}

void Signal::scale(float scale_num)
{
	for(int i=0;i<length;i++)
	{
		data[i] *= scale_num;
		cout<<data[i]<<endl;
	}
}

void Signal::Sig_info()
{
	maximum();
	average();
	cout<<endl<<endl<<"Length: "<<length<<"\nMaximum: "<<max<<"\nAverage: "<<avg<<endl;
}

void Signal::average()
{
	avg =0;
	for(int i=0;i<length;i++)
	{
		avg += data[i];
	}
	avg /= (float)length;
}

void Signal::maximum()
{
	float maximum; 
	for(int i=1;i<length;i++)
	{
		maximum = data[i-1];
		if(data[i]>maximum)
		{
			max = data[i];
		}else{
			max=maximum;
		}	
	}
}

Signal::Signal(int filenumber)
{
	char new_file[16] = "Raw_data_";
	if(filenumber<10){
		strcat(new_file,"0");
	}
	char num[3];	
	sprintf(num,"%d",filenumber);
	strcat(new_file,num);	
	strcat(new_file,".txt");
	ifstream file;
	file.open(new_file);
	if(file.is_open())
	{
		int num;
		file>>length>>num;
		data = new float[length];
		while(!file.eof())
		{
			for(int i=0;i<length;i++)
			{
				file>>data[i];
			}
		}
	}
	file.close();
}

Signal::Signal()
{
	int num;	
	ifstream file;
	file.open("default.txt");
	if(file.is_open())
	{	
		int num;
		length =0;
		file>>length>>num;
		data = new float[length];
		while(!file.eof())
		{	
			for(int i=0;i<length;i++)
			{
				file>>data[i];
			}
		}
	}
	else
	{
		cout<<"\nError opening default file\n"<<endl;
	}
	file.close();
}

Signal::Signal(char* filename)
{
	fstream file;
	file.open(filename,ios::in);
	if(file.is_open())
	{
		int num;
		file>>length>>num;
		data = new float[length];
		while(!file.eof())
		{
			for(int i=0;i<length;i++)
			{
				file>>data[i];
			}
		}
	}
}


int Signal::menu()
{
	int choice = -1;
	cout<<"\nChoose An Option:\n1. Scale\n2. Offset\n3. Normalize\n4. Center\n5. Statistics\n6. Signal Info\n7. Save File\n0. Exit\n: "<<endl;
	cin>>choice;
	switch(choice)
	{
	case 0:
	{
		return 0;

	}
	case 1:
	{
		float num;
		cout<<"\nEnter a number to scale the data: "<<endl;
		cin>>num;
		scale(num);
		
		break;
	}
	case 2:
	{
		float offset_num;
		cout<<"Enter an offset number: "<<endl;
		cin>>offset_num;
		offset(offset_num);
		
		break;
	}
	case 3:
	{
		normalize();
		
		break;
	}
	case 4:
	{
		center();
		break;
	}
	case 5:
	{
		statistics();
		break;
	}
	case 6:
	{
		Sig_info();
		break;
	}
	case 7:
	{
		save_file();
		break;
	}
	default:
	{
		cout<<"\n*************ERROR*************\nChoice must be between 0-7!\n"<<endl;
		menu();
		break;
	}

	}
	if(choice > 0 && choice < 8){
		menu();
	}
	
	return 0;
}
int main(int argc,char** argv){
	
	
	if(argc==1){
		Signal sig;
		sig.statistics();
		sig.menu();
		
	}else if(argv[1][1]=='n'){
		if(argc==2){
			cout<<"\n***********ERROR************\nCorrect Formats: ./a.out -n <file number> OR ./a.out -f <file name>\n"<<endl;
			return 0;		
		}
		Signal sig(atoi(argv[2]));
		sig.statistics();
		sig.menu();
	}else if(argv[1][1] == 'f'){
		if(argc==2){
			cout<<"\n***********ERROR************\nCorrect Formats: ./a.out -n <file number> OR ./a.out -f <file name>\n"<<endl;
			return 0;		
		}
		Signal sig(argv[2]);
		sig.statistics();
		sig.menu();
	}else{
		cout<<"\n***********ERROR************\nCorrect Formats: ./a.out -n <file number> OR ./a.out -f <file name>\n"<<endl;
	}
	return 0;
}
