#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
void process(vector<vector<int> > thegrid, int row, int col, int val);
bool initProcess();

void inputGrid();
void output();


const int INFINITY=32000;
struct trio
{
	int row;
	int col;
	int value;
};

vector<vector<int> >grid;
bool done;

//fungsi menampilkan petak 9x9
void showGrid(const vector<vector<int> > &somegrid)
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
	void inputGrid();
	void process(vector<vector<int> > thegrid, int row, int col, int val);
	inline void output();

    bool initProcess();
};

//fungsi input
void Sudoku::inputGrid()
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
   showGrid(grid);
}

//program utama
int main(int argc, char *argv[])
{
    cout<<"====================SUDOKU SOLVER======================="<<endl<<endl<<endl;
    Sudoku game;
    game.inputGrid();
    game.initProcess();
    game.output();
    system("PAUSE");
    return EXIT_SUCCESS;
}
