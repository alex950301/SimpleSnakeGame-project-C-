#include <iostream>
#include <windows.h>
#include <vector>
#include <queue>
#include <utility>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
using namespace std ;
int Map[8][8] = {0} ;
class Snake {
    public :
        int score , cookie_x , cookie_y ;
        queue< pair<int,int> > head ;
        int position[2][50] ;

        void display() ;
        bool check( int , int ) ;
        bool checkpoint( int , int ) ;
        int refresh() ;

};
void Snake::display() {
	cout << "position(X,Y): " << cookie_x << " " << cookie_y << endl ;
	cout << "+ - - - - - - - - +" << endl ;
    for( int i = 0 ; i < 8 ; i++ ) {
    	cout << "| " ;
        for( int j = 0 ; j < 8 ; j++ ) {
			if( Map[i][j] == 0 ) cout << "  " ;
			else if( Map[i][j] == 9 ) cout << "¡·" ;
			else cout << "¡½" ;
		}
		cout << "|" ;
        cout << endl ;
    }
    cout << "+ - - - - - - - - +" << endl ;
}

bool Snake::check( int x , int y ) {
    bool flag = 1 ;
    queue< pair<int,int> > temp = head ;
    for( int i = 0 ; i < temp.size() ; i++ ) {
        int X = temp.front().first ;
        int Y = temp.front().second ;
        if( x == X && y == Y ) flag = 0 ;
        temp.pop() ;
    }
    return flag ;
}

int Snake::refresh() {
    int num = rand() % 8 ;
    return num ;
}

bool Snake::checkpoint( int x , int y ) {
	bool flag = 1 ;
	for( int i = 0 ; i < sizeof(position) ; i++ ) {
		if( x == position[0][i] && y == position[1][i] ) flag = 0 ;
	}
	return flag ;
}
int main() {
	int difficulty , Time ;
	cout << "Choose your difficluty (1~3):" ;
	cin >> difficulty ;

	if( difficulty == 1 ) Time = 500 ;
	else if( difficulty == 2 ) Time = 250 ;
	else if( difficulty == 3 ) Time = 125 ;

	Sleep(100) ;
    Snake information ;
    information.score = 0 ;
    int x = 0 , y = 0 , keyboard ;

    bool flag = 1 ;

	information.head.push({1,1}) ;

	srand(time(0)) ;
	information.cookie_x = rand() % 8 ;
	information.cookie_y = rand() % 8 ;
	int pos_X = 1 , pos_Y = 0 ;
    while( 1 ) {
        information.display() ;

        int keyboard1 , keyboard2 ;

        if( _kbhit() ) {
        	keyboard1 = getch() ;
	    	keyboard2 = getch() ;
	    	if( keyboard2 == 75 && keyboard2 != 77 ) { //left
	    		pos_X = 0 ; pos_Y = -1 ;
			}
			else if( keyboard2 == 80 && keyboard2 != 72 ) { //down
				pos_X = 1 ; pos_Y = 0 ;
			}
			else if( keyboard2 == 77 && keyboard2 != 75 ) { //right
				pos_X = 0 ; pos_Y = 1 ;
			}
			else if( keyboard2 == 72 && keyboard2 != 80 ) { //up
				pos_X = -1 ; pos_Y = 0 ;
			}
        }
        x += pos_X ;
		y += pos_Y ;
        Sleep(Time) ;


        system("cls") ;
        if( x > 7 ) x %= 8 ;
        else if( x < 0 ) x = 8 + x ;
        if( y > 7 ) y %= 8 ;
        else if( y < 0 ) y = 8 + y ;

		if( flag == 1 ) {
            flag = 0 ;
            information.cookie_x = information.refresh() ;
			information.cookie_y = information.refresh() ;

			queue< pair<int,int> > temp = information.head ;
			int i = 0 ;
			while( !temp.empty() ) {
				information.position[0][i] = temp.front().first ;
				information.position[1][i] = temp.front().second ;
				i++ ;
				temp.pop() ;
			}

            while( information.checkpoint( information.cookie_x , information.cookie_y ) == 0 ) {
            	information.cookie_x = information.refresh() ;
				information.cookie_y = information.refresh() ;
			}
            Map[information.cookie_x][information.cookie_y] = 9 ;
        }

		information.head.push({x,y}) ;
        Map[x][y] = 1 ;

		if( information.check( x , y ) == 0 ) {
			system("cls") ;
			information.display() ;
			cout << "\t\t----LOSE!----" << endl << endl ;
			cout << "YOUR SCORE : " << information.score << endl ;
			break ;
		} else if( x == information.cookie_x && y == information.cookie_y ) {
            information.score++ ;
            if( information.head.size() > 15 ) {
                system("cls") ;
                cout << "\t\t----WIN!----" << endl << endl ;
                cout << "YOUR SCORE : " << information.score << endl ;
                break ;
            }
            flag = 1 ;
        } else {
        	int dx = information.head.front().first ;
        	int dy = information.head.front().second ;
        	Map[dx][dy] = 0 ;
        	information.head.pop() ;
		}

    }
    cout << "SUCCEED_EXIT --- Wait for 3 seconds." << endl ;
    Sleep(Time) ;
    return 0 ;
}
