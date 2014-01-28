#include <cstdlib>
#include <iostream>
#include <vector>
#include<iomanip>

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
		if(i%3==2)  cout<<endl;
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
	void input_pola();
	void process(vector<vector<int> > thegrid, int row, int col, int val);
	inline void output();

    bool initProcess();
    inline bool isValid(const int &row, const int &col, const  int &val);
	bool valid(const vector<vector<int> > &thegrid, const int &row, const int &col, const int &val);
};

Sudoku::Sudoku()
{
	vector<int> arow(9,INFINITY);
	for(int i=0;i<9;i++)
	grid.push_back(arow);
	done=false;
}

//fungsi input
void Sudoku::input_pola()
{
   	char h;
    cout<<"Masukan Pola Sudoku('B' or 'b' SEBAGAI BLANK/KOSONG): "<<endl;
    cout<<"Sudoku yang di masukkan 9 x 9"<<endl;
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
     if(done || !isValid(row,col,val) || !(valid(thegrid,row,col,val))) return;
     
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
	
		grid.at(i).at(j)=temp;
	}

     for(int i=0;i<9;i++)
	process(grid, 0, 0, i);
	return true;
}

void Sudoku::output()
{
   tampil(grid);
}


//validasi
bool Sudoku:: isValid(const int &row,const int &col, const int &value)
{
	return (row>=0 && row<9 && col>=0 && col<9 && value>=0 && value<9);
}

bool Sudoku:: valid(const vector<vector<int> > &thegrid, const int &row, const int &col, const int &val)
{
     if(thegrid.at(row).at(col)==val) return true;
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


//program utama
int main(int argc, char *argv[])
{
    cout<<"====================SUDOKU SOLVER======================="<<endl<<endl<<endl;
    Sudoku game;

    game.input_pola();
    cout<<endl<<"PROCESSING . . ."<<endl<<endl;
    
    if(game.initProcess())
    game.output();
    system("PAUSE");
    return EXIT_SUCCESS;
}
