#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <conio2.h>

using namespace std;

const int INFINITY=32000;
struct trio
{
	int row;
	int col;
	int value;
};

//fungsi menampilkan petak 9x9
void tampil(const vector<vector<int> > &somegrid)
{
	cout<<endl<<endl;
     for(int i=0;i<9;i++)
     {
     	for(int j=0;j<9;j++)
     	{
			int n=somegrid.at(i).at(j);
			(n!=INFINITY)?cout<<n+1: cout<<'B';
     		(j%3==2)? cout<<"  ":cout<<" ";
		}
		if(i%3==2)
			cout<<endl;
     	cout<<endl;
     }
     cout<<endl;
}

class Sudoku
{
	vector<vector<int> > grid;
	bool done;

	public:
    	Sudoku();
    	void input();
    	void contoh_sudoku();
		void input_pola();
		void process(vector<vector<int> > thegrid, int row, int col, int val);
		inline void output();
		void error(const int &errorcode, const int &row=-1, const int &col=-1);
		bool initProcess();
		void sample(int choice);
   	 	inline bool isValid(const int &row, const int &col, const  int &val);
		bool valid(const vector<vector<int> > &thegrid, const int &row, const int &col, const int &val);
        inline bool cek_trio(const trio &sample);
};

Sudoku::Sudoku()
{
	vector<int> arow(9,INFINITY);
	for(int i=0;i<9;i++)
	grid.push_back(arow);
	done=false;
}

//menu
void Sudoku:: input()
{
    int pilihan;
    system("cls");
	gotoxy(12,5); cout<<"==================== SUDOKU SOLVER =======================";
	gotoxy(27,7); cout<<"-------------------------";
    gotoxy(27,8); cout<<"|     MENU PILIHAN      |";
	gotoxy(27,9); cout<<"-------------------------";
	gotoxy(27,10); cout<<"|  1. Contoh Program    |";
	gotoxy(27,11); cout<<"|  2. Input Sudoku      |";
	gotoxy(27,12); cout<<"|  3. keluar            |";
	gotoxy(27,13); cout<<"-------------------------";
    gotoxy(12,15); cout<<"==========================================================";
    gotoxy(30,16); cout<<"Pilihan Anda [1-3] : "; cin>>pilihan;
    //validasi pilihan menu
	while(pilihan<1 || pilihan>3)
	{
		gotoxy(26,18); textcolor(RED); cout<<"Pilihan hanya ada 1-3! Ulangi!"; getch();
		gotoxy(26,18); clreol();
		gotoxy(51,16); textcolor(GREEN); clreol(); cin>>pilihan;
	}
	switch(pilihan)
	{
		case 1:
			system("cls");
        	contoh_sudoku();
			break;
		case 2:
        	system("cls");
			input_pola();
			break;
		case 3:
			exit(0);

		default:
        error(3);
	}
}

//contoh implisit sudoku
void Sudoku:: contoh_sudoku()
{
	cout<<"Contoh Input : ";
    string str=" 26 "
    "1 4 5 "
	"1 5 8 "
	"2 3 1 "
	"2 9 7 "
	"3 1 3 "
	"3 6 4 "
	"3 7 9 "
	"3 8 5 "
	"3 9 2 "
	"4 1 4 "
	"4 5 7 "
	"4 7 8 "
	"5 1 9 "
	"5 9 5 "
	"6 3 2 "
	"6 5 1 "
	"6 9 6 "
	"7 1 1 "
	"7 2 2 "
	"7 3 3 "
	"7 4 7 "
	"7 9 9 "
	"8 1 6 "
	"8 7 4 "
	"9 5 5 "
	"9 6 2 " ;
    istringstream istr(str);
	cout<<"Posisi yang diketahui : ";
	int n;
	istr>>n;
	cout<<n<<endl;

	trio sample;
	for(int i=0;i<n;i++)
	{
		istr>>sample.row>>sample.col>>sample.value;
		sample.row--;
		sample.col--;
		sample.value--;
	    if(cek_trio(sample))
	    {
            grid.at(sample.row).at(sample.col)=sample.value;
        }
        else
        i--;
    }
	cout<<"GRID input Sudoku :(B = Blank / kosong)"<<endl;
	tampil(grid);
}

//fungsi input
void Sudoku::input_pola()
{
    gotoxy(5,2); cout<<"============================= INPUT SODUKU ============================";
   	gotoxy(27,4); cout<<"Tampilkan Contoh Input(y/n)? ";
   	char h;
   	cin>>h;
   	h=tolower(h);
   	//validasi
   	while(!(h=='y' || h=='n'))
   	{
   	    gotoxy(27,7); textcolor(RED); cout<<"Pilihan hanya ada y/n! Ulangi!"; getch();
   	    gotoxy(27,7); clreol();
        gotoxy(56,4); clreol(); textcolor(GREEN); cin>>h;
	}
    if(h=='y')
        sample(1);
    cout<<"\n\n\t\t\t     Tekan Enter untuk lanjut";
    system("pause > nul");
    system("cls");
    gotoxy(5,2); cout<<"============================= INPUT SODUKU ============================";
    gotoxy(17,4); cout<<"Masukan Pola Sudoku('B' atau 'b' = Blank (kosong))";
    gotoxy(25,5); cout<<"Sudoku yang di masukkan 9 x 9"<<endl;
	for(int i=0;i<9;i++)
	for(int j=0;j<9;j++)
	{
		cin>>h;
		if(h!='0' && isdigit(h))
			grid.at(i).at(j)=int(h-'1');
	}
}


//area proses
void Sudoku::process(vector<vector<int> > thegrid, int row, int col, int val)
{
     if(done || !isValid(row,col,val) || !(valid(thegrid,row,col,val)))
	 	return;
     thegrid.at(row).at(col)=val;
     if(row==8 && col==8)
     {
        cout<<"Selesai: "<<endl;
        grid=thegrid;
        done=true;
     }
     bool flag=false;
     for(int i=0;i<9;i++)
     if(col<8)
        process(thegrid,row,col+1,i);
        else
           process(thegrid,row+1,0,i);
}

bool Sudoku::initProcess()
{
	for(int i=0;i<9;i++)
	for(int j=0;j<9;j++)
	{
		int temp=grid.at(i).at(j);
		grid.at(i).at(j)=INFINITY;
		if(!valid(grid,i,j,temp))
		{
            error(2);
	        return false;
        }
		grid.at(i).at(j)=temp;
	}
	for(int i=0;i<9;i++)
		process(grid, 0, 0, i);
	return true;
}

void Sudoku:: sample(int choice)
{
    system("cls");
	gotoxy(5,2); cout<<"============================ CONTOH INPUT ============================"; cout<<endl<<endl;
	if(choice==1)
	{
		cout<<  "\n\n\t\tB B B 5 8 B B B B\t\t\tbbb58bbbb\n"
                "\t\tB B 1 B B B B B 7\t\t\tbb1bbbbb7\n"
                "\t\t3 B B B B 4 9 5 2\t\t\t3bbbb4952\n"
                "\t\t4 B B B 7 B 8 B B\t\t\t4bbb7b8bb\n"
                "\t\t9 B B B B B B B 5\t   atau   \t9bbbbbbb5\n"
                "\t\tB B 2 B 1 B B B 6\t\t\tbb2b1bbb6\n"
                "\t\t1 2 3 7 B B B B 9\t\t\t1237bbbb9\n"
                "\t\t6 B B B B B 4 B B\t\t\t6bbbbb4bb\n"
                "\t\tB B B B 5 2 B B B\t\t\tbbbb52bbb\n\n\n\n";
    }
    gotoxy(5,17); cout<<"=====================================================================";
}

void Sudoku::output()
{
   if(!done)
      error(2);
   else
      tampil(grid);
}


//validasi
bool Sudoku:: isValid(const int &row,const int &col, const int &value)
{
	return (row>=0 && row<9 && col>=0 && col<9 && value>=0 && value<9);
}

bool Sudoku:: valid(const vector<vector<int> > &thegrid, const int &row, const int &col, const int &val)
{
    if(thegrid.at(row).at(col)==val)
		return true;
	if(thegrid.at(row).at(col)!=INFINITY)
		return false;
	for(int i=0;i<9;i++)
	if(thegrid.at(i).at(col)==val)
	return false;
	for(int j=0;j<9;j++)
	{
       if(thegrid.at(row).at(j)==val)
       return false;
    }
	int m,n;
	m=(row/3)*3;
	n=(col/3)*3;

	for(int i=m;i<m+3;i++)
	  for(int j=n;j<n+3;j++)
	    if(thegrid.at(i).at(j)==val)
        return false;

	return true;
}

bool Sudoku::cek_trio(const trio &sample)
{
	return isValid(sample.row,sample.col,sample.value);
}

//Validasi error
void Sudoku::error(const int &errorcode, const int &row, const int &col)
{
	cout<<"ERROR: ";
	switch(errorcode)
	{
		case 0:
		cout<<"INVALID INPUT-ULANGI "<<endl;
		break;

		case 1:
		cout<<"Nomer invalid "<<"ROW-NO: "<<row<<"COL-NO: "<<col<<endl;
		cout<<"Tidak Bisa Diselesaikan "<<endl;
		break;

		case 2:
		cout<<"Tidak ada Solusi"<<endl;
        cout<<"Pastikan Puzzle yang dimasukkan benar!!"<<endl<<endl;
		break;

		default:
		cout<<"ERROR"<<endl;
		system("pause");
		exit(1);
	}

}

//program utama
int main(int argc, char *argv[])
{
    system("title SUDOKU SOLVER");
    textcolor(GREEN);
	while(true)
	{
		try
		{
			Sudoku game;
    		game.input();
    		cout<<endl<<"PROCESSING . . ."<<endl<<endl;
    		if(game.initProcess())
    			game.output();
            cout<<"   ========================================================================\n\n";
            cout<<"\t\t\t   Tekan Enter untuk kembali";
            system("pause > nul");
		}
		catch(out_of_range)
		{
			cout<<"Out of Range"<<endl;
		}
		catch(...)
		{
			cout<<"Error"<<endl;
		}
	}
    system("PAUSE");
    return EXIT_SUCCESS;
}
