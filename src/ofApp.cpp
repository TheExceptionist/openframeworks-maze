#include <iostream>
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetWindowTitle("Graphics Example");
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetFrameRate(60);

	mouseXPercent = 0.5f;
	mouseYPercent = 0.5f;

	m_game_state = PLAY_STATE;

	m_win_color[0] = rand() % 255 + 1;
	m_win_color[1] = rand() % 255 + 1;
	m_win_color[2] = rand() % 255 + 1;

	m_lose_color[0] = rand() % 255 + 1;
	m_lose_color[1] = rand() % 255 + 1;
	m_lose_color[2] = rand() % 255 + 1;

	m_game_font.loadFont("verdana.ttf", 32);

	hasStarted = false;

	generateGridRand();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	switch (m_game_state)
	{
	case PLAY_STATE:
		drawGrid();
		break;
	case WIN_STATE:
		drawEnd(0);
		break;
	case LOSE_STATE:
		drawEnd(1);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;

	std::cout << "Tile X: " << tile_x << " Tile Y: " << tile_y << std::endl;

	if (!hasStarted && m_grid[tile_x][tile_y] == START_TILE) hasStarted = true;

	if (hasStarted)
	{
		if (m_grid[tile_x][tile_y] == LOSE_TILE) m_game_state = LOSE_STATE;
		if (m_grid[tile_x][tile_y] == WIN_TILE) m_game_state = WIN_STATE;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::drawGrid()
{
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			//Get the id of the grid tile
			int id = m_grid[i][j];
			//Declare color
			ofColor c;

			switch (id)
			{
			case LOSE_TILE:
				c.r = 255;
				c.g = 0;
				c.b = 0;
				break;
			case ALIVE_TILE:
				c.r = 0;
				c.g = 255;
				c.b = 0;
				break;
			case WIN_TILE:
				c.r = 0;
				c.g = 0;
				c.b = 255;
				break;
			case START_TILE:
				c.r = 255;
				c.g = 255;
				c.b = 0;
				break;
			}

			ofSetColor(c);
			ofDrawRectangle((i * TILE_SIZE) + TILE_SIZE/2, (j * TILE_SIZE) + TILE_SIZE/2, TILE_SIZE, TILE_SIZE);
		}
	}
}

void ofApp::drawEnd(int type)
{
	ofColor c;

	if (type == 0) {
		c.r = m_win_color[0];
		c.g = m_win_color[1];
		c.b = m_win_color[2];
		
	}
	else if (type == 1) {
		c.r = m_lose_color[0];
		c.g = m_lose_color[1];
		c.b = m_lose_color[2];
		
	}

	ofSetColor(c);
	ofDrawRectangle(0, 0, 1024 * TILE_SIZE, 768 * TILE_SIZE);

	c.r = 0;
	c.g = 0;
	c.b = 0;

	ofSetColor(c);

	if(type == 0) m_game_font.drawString("You Win!!!", (1024 + TILE_SIZE) / 2, (768 + TILE_SIZE) / 2);
	if(type == 1) m_game_font.drawString("You Lose!!!", (1024 + TILE_SIZE) / 2, (768 + TILE_SIZE) / 2);
}

void ofApp::generateGridRand()
{
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			//Get the id of the grid tile
			m_grid[i][j] = rand() % 2;
		}
	}

	m_grid[rand() % GRID_WIDTH][rand() % GRID_HEIGHT] = WIN_TILE;
	m_grid[0][0] = START_TILE;
	
	m_start_x = 0;
	m_start_y = 0;

	//generateGrid();
}

void ofApp::generateGrid()
{
	/*for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			int id = m_grid[i][j];
		}
	}*/

	bool finished = false;
	//       0         1       2
	//0: (-1, -1), (0, -1), (1, -1) 
	//1: (-1, 0), (0, 0), (1, 0) 
	//2: (-1, 1), (0, 1), (1, 1) 

	//Always will be 3x3
	int neighbors[3][3];

	setNeighbors(neighbors, m_start_x, m_start_y);

	while (!finished) 
	{
		
	}
}

void ofApp::setNeighbors(int array[3][3], int x, int y)
{
	if (x - 1 > -1 && y - 1 > -1) array[0][0] = m_grid[x - 1][y - 1];
	if (y - 1 > -1) array[0][1] = m_grid[x][y - 1];
	if (x + 1 < GRID_WIDTH && y - 1 > -1) array[0][2] = m_grid[x + 1][y - 1];

	if (x - 1 > -1) array[1][0] = m_grid[x - 1][y];
	//Center piece, is never out-of-bounds
	array[1][1] = m_grid[x][y];
	if (x + 1 < GRID_WIDTH) array[1][2] = m_grid[x + 1][y];

	if (x - 1 > -1 && y + 1 < GRID_HEIGHT) array[2][0] = m_grid[x - 1][y + 1];
	if (y - 1 > -1 && y + 1 < GRID_HEIGHT) array[2][1] = m_grid[x][y + 1];
	if (x + 1 < GRID_WIDTH && y + 1 < GRID_HEIGHT) array[2][2] = m_grid[x + 1][y + 1];
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
