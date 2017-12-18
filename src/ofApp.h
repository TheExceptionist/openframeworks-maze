#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"

#define LOSE_STATE 0
#define WIN_STATE 1
#define PLAY_STATE 2

#define LOSE_TILE 0
#define ALIVE_TILE 1
#define WIN_TILE 2
#define START_TILE 3

static const int TILE_SIZE = 32;

//Added the tilesize to the width and height, otherwise a portion of the grid would not generate
static const int GRID_WIDTH = (1024 + TILE_SIZE) / TILE_SIZE;
static const int GRID_HEIGHT = (768 + TILE_SIZE) / TILE_SIZE;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		float mouseXPercent, mouseYPercent;
private:
		void drawGrid();
		void drawEnd(int type);
		//Used to place tiles around the grid randomly
		void generateGridRand();
		void generateGrid();
		void setNeighbors(int array[3][3], int x, int y);

		int m_game_state;
		int m_grid[GRID_WIDTH][GRID_HEIGHT];

		int m_win_color[3];
		int m_lose_color[3];

		int m_start_x, m_start_y;

		bool hasStarted;

		ofTrueTypeFont m_game_font;
};

#endif