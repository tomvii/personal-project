#include "pch.h"
#include "work_2.h"
using namespace std;

Wordnode *log_list[HASH_LENGTH] = { NULL };  //哈希散列指针数组



int main(int argc, char *argv[])
{
	//Wordnode *log_list[HASH_LENGTH] = { NULL };  //哈希散列指针数组
	File fnew;                 //控制文件模块
	Words wnew;                //控制单词模块
	vector<string> file_str;
	int i;
	if (argc != 2)               //参数合法性检查
	{
		cout << "Wrong parameters!" << endl;
		return 0;
	}
	//if (argc == 1)
	//{
	//	strcpy_s(fnew.file_name, "input6.txt");
	//}

	strcpy_s(fnew.file_name, argv[1]);      //获取文件名
	ifstream f;
	f.open(fnew.file_name, ios::in);		//打开文件
	if (!f.is_open())						//检测文件是否存在
	{
		cout << "can't open this file!" << endl;
		return 0;
	}
	fnew.count_chars = C_chars(f, fnew, wnew, file_str);	//计算字符数(行数)
	fnew.count_words = C_words(f, fnew, wnew, log_list, file_str);	//计算单词数(插入哈希节点)

	//cout << "chars = " << fnew.count_chars << "," << "lines = " << fnew.count_lines<<","<<"words = "<<fnew.count_words<<endl;
	rank_word(log_list, wnew);						//词频排名

	ofstream fo;
	fo.open("result.txt", ios::out);			//输出文件
	if (!fo.is_open())							//输出文件合法性检查
	{
		cout << "can't output the file!" << endl;
		return 0;
	}
	fo << "characters: " << fnew.count_chars << "\n";	//构造输出结果
	fo << "words: " << fnew.count_words << "\n";
	fo << "lines: " << fnew.count_lines << "\n";
	for (i = 1; i < 11; i++)
	{
		if (wnew.count_rank[i] != 0)
		{
			fo << "<" << wnew.word_rank[i] << ">: " << wnew.count_rank[i] << "\n";
		}
		else
			break;
	}
	f.close();
	fo.close();								//关闭文件
	//cout << "WordCount complete!" << endl;
	
	return 0;

}