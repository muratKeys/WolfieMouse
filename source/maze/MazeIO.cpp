/********************************
 * Name:    IOInterface.hpp
 * Author:  Bumsik Kim; Bryant Gonzaga
 * Date Modified:   2 Feb. 2017
 ********************************/

#include "MazeIO.hpp"
#include "Maze.hpp"

#ifndef EOF
    #define EOF -1
#endif

static void clearLine(IOInterface* io);
/** FIXME: dynamically decide the starting direction */

/*******************************************************************************
 * Constructor
 ******************************************************************************/
MazeIO::MazeIO(Maze *mazePtr,  IOInterface *fileIO, IOInterface *printIO) :
    maze(mazePtr),
    maxRowSize(CONFIG_MAX_ROW_SIZE),
    maxColSize(CONFIG_MAX_COL_SIZE),
	fileIO(fileIO),
	printIO(printIO)
{
    // The initializer does it all
}

/*******************************************************************************
 * Public Methods
 ******************************************************************************/
Position MazeIO::getMousePosition(void)
{
    return mousePosition.getCurrentPos();
}

void MazeIO::setMousePosition(Position pos)
{
    mousePosition = PositionController(pos, eDirError);
}

void MazeIO::setMousePosition(PositionController posCon)
{
	mousePosition = posCon;
}

void MazeIO::setDestinations(const std::vector<Position> &des)
{
	destinations = des;
}

bool MazeIO::positionIsDestination(Position pos)
{
	for (int i = 0; i < destinations.size(); i++) {
		if (pos == destinations[i]) {
			return true; /* return true if position found in destination vector*/
		}
	}
	return false;
}

void MazeIO::printMaze(void)
{
    if (NULL == maze) {
        //printf("No maze object");
        return;
    }
    writeBufferFromMaze(true);
    writeIOFromBuffer(printIO);
}

void MazeIO::loadMaze(char* fileName)
{
    char buf;
    if (NULL == fileName) {
        //printf("No file to load maze.\n");
        return;
    }
    //Open maze file
    fileIO->open(fileName, "r");
    // Reading part
    Wall wallToPut;
    for (int i = 0; i < (CONFIG_MAX_ROW_SIZE * 2 + 1); i++) {
        for (int j = 0; j < (CONFIG_MAX_COL_SIZE * 2 + 1); j++) {
            if ((buf = fileIO->get_char()) == EOF) {
                //printf("error?\n"); /* TODO: check error condition of fgets */
            }
            switch (buf) {
            case '_':
            case '|':
                wallToPut = wall;
                if (j != CONFIG_MAX_COL_SIZE * 2) {
                	fileIO->get_char();
                }
                break;
            case '.':
                wallToPut = empty;
				fileIO->get_char();
                break;
            case '*':
                wallToPut = unknown;
				fileIO->get_char();
                break;
            case 'S': /* Starting point */
                maze->startPos.row = i / 2;
                maze->startPos.col = j / 2;
                wallToPut = wallError;
                continue;
            case 'G':
            	maze->goalPos.push_back(Position{i/2, j/2});
                wallToPut = wallError;
                continue;
            case ' ':
            default:
                wallToPut = wallError;
                continue;
                break;
            }
            if ((i % 2 == 0) && (j % 2 == 1)) {
                maze->rowWall[i / 2][j / 2] = wallToPut;
            } else if ((i % 2 == 1) && (j % 2 == 0)) {
                maze->colWall[i / 2][j / 2] = wallToPut;
            }
        }
        // TODO: Wait. Do we really need this function?
        clearLine(fileIO);
    }

    /* update the cell */
    maze->updateCell();
}

void MazeIO::saveMaze(char* fileName)
{
    // check maze object
    if (NULL == maze) {
        //printf("No maze object");
        return;
    }

    // try opening file
    fileIO->open(fileName, "w");

    writeBufferFromMaze(false);
    writeIOFromBuffer(fileIO);
}
/*******************************************************************************
 * Private Methods
 ******************************************************************************/
void MazeIO::writeBufferFromMaze(bool isShowMouse)
{
    char *ptr = buffer;
    for (int i = 0; i < (CONFIG_MAX_ROW_SIZE * 2 + 1); i++) {
        if (i % 2 == 0) {
            // row_plus/row_minus
            for (int j = 0; j < CONFIG_MAX_COL_SIZE; j++) {
                // print a space then wall
                *ptr++ = ' ';
                switch (maze->rowWall[i / 2][j]) {
                case empty:
                    *ptr++ = '.';
                    *ptr++ = '.';
                    break;
                case wall:
                	// The cell size is twice as long
                    *ptr++ = '_';
                    *ptr++ = '_';
                    break;
                case unknown:
                	// The cell size is twice as long
                    *ptr++ = '*';
                    *ptr++ = '*';
                    break;
                case wallError:
                default:
                    //printf("Error on rowWall!");
                    *ptr++ = '?';
                    break;
                }
            }
            *ptr++ = ' ';
        } else {
            // col_plus/col_minus
            for (int j = 0; j < CONFIG_MAX_COL_SIZE + 1; j++) {
                /* print wall first */
                switch (maze->colWall[i / 2][j]) {
                case empty:
                    *ptr++ = '.';
                    break;
                case wall:
                    *ptr++ = '|';
                    break;
                case unknown:
                    *ptr++ = '*';
                    break;
                case wallError:
                default:
                    //printf("Error on rowWall!");
                    *ptr++ = '?';
                    break;
                }
                // then print cell
                if (!(j >= CONFIG_MAX_COL_SIZE)) {
                    printCell(i / 2, j, isShowMouse, ptr);
                    ptr += 2;
                }
            }
        }
        /* print newline */
        *ptr++ = '\n';
    }
}

void MazeIO::writeIOFromBuffer(IOInterface *io)
{
	io->write(buffer, sizeof(char), sizeof(buffer));
}

void MazeIO::printCell(int row, int col, bool isShowMouse, char* buf)
{
    /* Check if this is mouse position */
    if (mousePosition.getCurrentPos().col == col &&
    	mousePosition.getCurrentPos().row == row && isShowMouse) {
    	switch(mousePosition.getCurrentDir()) {
			case row_minus:		//mouse pointing up
				*buf++ = 'M';
				*buf = '^';
				break;
			case col_minus:
				*buf++ = '<';	//mouse pointing left
				*buf = 'M';
				break;
			case row_plus:		//mouse pointing down
				*buf++ = 'M';
				*buf = 'v';
				break;
			case col_plus:		//mouse pointing right
				*buf++ = 'M';
				*buf = '>';
				break;
			case eDirError:
				*buf++ = 'M';
				*buf = 'M';
				break;
			default:
				*buf++ = ' ';
				*buf = 'M';
				break;
    	}
    } else if (positionIsDestination(Position{row, col}) && isShowMouse) {
    	*buf++ = ' ';
    	*buf = 'D';
    } else if (maze->getCell(row, col).attribute == start) {
        *buf++ = ' ';
        *buf = 'S';
    } else if (maze->getCell(row, col).attribute == goal) {
        *buf++ = ' ';
        *buf = 'G';
    } else if (isShowMouse) {
    	if (maze->getCell(row, col).distance == CELL_DISTANCE_UNREACHED) {
    		*buf++ = ' ';
    		*buf = 'x';
    	} else {
    		int dis = maze->getCell(row, col).distance;
    		*buf++ = (char) (dis/10 + 48);
    		*buf = (char) (dis%10 + 48);
    	}
    } else if (col != CONFIG_MAX_COL_SIZE) {
        *buf++ = ' ';
        *buf = ' ';
    }
}

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void clearLine(IOInterface* io)
{
    char buf;
    while ((buf = io->get_char()) != '\n') {
        if (buf == EOF)
            break;
    }
}
