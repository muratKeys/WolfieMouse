#include <common_maze.h>
#include <MouseController.hpp>
#include <algorithm>

/*******************************************************************************
 * Constructor
 ******************************************************************************/
MouseController::MouseController() :
        MouseController(NULL, NULL, NULL, NULL, NULL)
{
}

MouseController::MouseController(char *filename, IOInterface *fileIO,
            IOInterface *printIO, RealMouse *finder, RealMouse *mover) :
        Maze(filename, fileIO, printIO),
		finder(finder),
		mover(mover),
		destinations(goalPos)
{
    pathStack = Queue<PositionController>();
    availablePositionStack = Queue<PositionController>();
    /* FIXME: Set the default start point */
    setPos(startPos);
    setDir(CONFIG_DEFAULT_START_DIRECTION);
    updateCell();
}

/*******************************************************************************
 * Public Methods
 ******************************************************************************/
bool MouseController::scanWalls(void)
{
    bool newInfo = false;
    Position curPos = getCurrentPos();
    Direction curDir = getCurrentDir();
    Position nextPos = getNextPos();
    // Firstly detect a wall right in front of the mouse
    Wall result; // = finder->examineWall(curPos, curDir, *this);
    //if (getWall(curPos, curDir) != result) {
    //    newInfo = true;
    //}
    //setWall(curPos, curDir, result);
    // Then examine the walls of the cell the mouse is facing
    for (int i = (int) row_plus; i <= (int) col_minus; i++) {
    	Direction dir = (Direction) i;
    	if (getWall(nextPos, dir) != unknown) {
    	    continue;
    	}
        result = finder->examineWall(nextPos, dir, *this);
        if (result == wallError) {
            continue;
        }
        if (getWall(nextPos, dir) != result) {
               newInfo = true;
        }
        setWall(nextPos, dir, result);
    }
    // Lastly, update state of cells.
    updateCell(curPos);
    updateCell(nextPos);
    // If path stack is empty then we need new info
    if (pathStack.isEmpty()) {
        return true;
    }
    return newInfo;
}

void MouseController::getDistanceAllCell()
{
    int currentPathDistance = CELL_DISTANCE_START + 1;  //This is how far the 'water' has flowed
    int row;
    int col;
    /* set all distance as UNREACHED */
    initDistance();

    /* Firstly set the distance of the current position to 0 */
    setDis(getCurrentPos(), CELL_DISTANCE_START);

    while (1) {
        /* Creating a loop which scans the whole maze */
        for (row = 0; row < CONFIG_MAX_ROW_SIZE; row++) {
            for (col = 0; col < CONFIG_MAX_COL_SIZE; col++) {
                /* If the cell has already been reached, then continue to the next cell */
                if (getDis(row, col) != CELL_DISTANCE_UNREACHED) {
                    continue;
                }
                /* If there is a neighboring cell which has been */
                if (getHighestNeighbouringDistance(row, col)
                        == (currentPathDistance - 1)) {
                    /* you have reached the current cell */
                    setDis(row, col, currentPathDistance);
                }
            }
        }
        if (anyDestinationCellSearched()) {
            break; //If the destination cell has a value after a sweep, the algorithm ends
        }
        /* Increment the distance because we are scanning again. */
        currentPathDistance++;
    }
    /**
     * The highestNeighbouringCell(x,y) function returns the value of the highest,
     * accessible (ie there are no separating walls) neighboring cell. Initially,
     * all the cells are given a value of UNREACHED(which is -1), except the
     * micromouse's current cell, which is given value 0.
     * Then the grid of cell values is scanned. On the first scan, only the cells
     * next to, and accessible to the cell where the micromouse is, will be given
     * a (non-UNREACHED) value. That value is 1. This is repeated until the
     * destination cell has been given a (non-UNREACHED) value.
     */
}

void MouseController::getShortestPath()
{
	/* init all variables */
	PositionController position;
	bool isFound;
	int currentDistance = 0;
	int i = 0;

	availablePositionStack.init();
	pathStack.init();

	/* set first stack = the current position */
	pathStack.pushToBack(PositionController(getCurrentPos(),getCurrentDir()));

	while (1) {
        isFound = false;
        //copy the next position
        position = pathStack.peekFromBack();
        currentDistance = getDis(position);
        //if current position is destination, break
        if (positionIsDestination(position.getCurrentPos())) {
            isFound = true;
            //pathStack.pushToBack(availablePositionStack.popFromBack());
            break;
        }
        /* Now look for next available cells, meaning neighboring cells that has
         distance of 1 more */
        /* Look around in counter-clockwise */
        for (i = (int) row_plus; i <= (int) col_minus; i++) {
        	Direction dir = (Direction) i;
            if (getNextDis(position, dir) == (currentDistance + 1)){
                // Check if that cell is reachable. In other words, check if the
                // cell is not blocked by a wall.
                if (wall == getWall(position.getCurrentPos(), dir)) {
                    continue;
                }
                if (!isFound) {
                    isFound = true;
                }
                availablePositionStack.pushToBack(
                		PositionController(position.getNextPos(dir), dir));
            }
        }
		if (!isFound) {
			/* When not found available next cell?
			 * pop(pathStack) until the peek(pathStack) is adjacent to peek(availablePathStack)
			 * Should also check if they are adjacent distance.
			 */
			bool isAdjacent;
			bool isNextDistance;
			PositionController posFromPath;
			PositionController posFromAvailable;
			do {
				pathStack.popFromBack();
				posFromPath = pathStack.peekFromBack();
				posFromAvailable = availablePositionStack.peekFromBack();
				isAdjacent =
						(  (posFromPath.getNextPos(row_plus)  == posFromAvailable.getCurrentPos())
						|| (posFromPath.getNextPos(col_plus)  == posFromAvailable.getCurrentPos())
						|| (posFromPath.getNextPos(row_minus) == posFromAvailable.getCurrentPos())
						|| (posFromPath.getNextPos(col_minus) == posFromAvailable.getCurrentPos())
						);
				isNextDistance = (getDis(posFromPath) + 1) == getDis(posFromAvailable);
			} while (!(isAdjacent && isNextDistance));
		}
        pathStack.pushToBack(availablePositionStack.popFromBack());
	}
	/* Delete the top element - it is the current position! */
	// FIXME: Do not delete it?
	// FIXME: When not popping, the Front is always (0,0)
	pathStack.popFromFront();
}

void MouseController::moveNextCell()
{
    /* 1. turn first */
    // Actually rotate first
    mover->rotateTo(getDirectionToGo(), *this);
    setDirectionToGo();
    /* 2. scan side wall */
    scanWalls();		// TODO: Try using this outside
    /* 3. move */
    Position tmp_p = getNextPos();
    /* move command */
    mover->moveTo(tmp_p, getCurrentDir(), *this);
    setPos(tmp_p);
    /* 4. scan the front wall */
    // Doesn't need actually
    /* 5. update */
    updateCell();
    /* check if the mouse is in a destination */
	if (isInDestinationCell()) {
		destinations.erase(std::remove(destinations.begin(),
				destinations.end(), getCurrentPos()), destinations.end());
	}
	// finally pop the position the mouse moved into
	if (!pathStack.isEmpty()) {
	    pathStack.popFromFront();
	}
}


void MouseController::setUnsearchDes(int n)
{
	srand(101);
	int count = 0;
	//count non searched cells
	for (int i = 0; i < CONFIG_MAX_ROW_SIZE; i++) {
		for (int j = 0; j < CONFIG_MAX_COL_SIZE; j++) {
			if (getCell(Position{i,j}).status == unsearched) {
				count++;
			}
		}
	}
	//find destinations
	while (destinations.size() < n && count > 0) {
		//choose random row
		int temp = (int) (rand()%16);
	    int i = temp;
	    //look for non searched cells in row
		for (int j = 0; j < CONFIG_MAX_COL_SIZE; j++) {
			if (getCell(Position{i, j}).status == unsearched) {
				if (positionIsDestination(Position{i,j})) {
					continue;
				}
				destinations.push_back(Position{i,j});
				count--;
				break;
			}
	    }
	}
}


void MouseController::setStartAsDes()
{
	if (positionIsDestination(CONFIG_DEFAULT_MAZE_START)) {
		return;
	}
	destinations.push_back(CONFIG_DEFAULT_MAZE_START);
}


void MouseController::setGoalAsDes()
{
    for (int i = 0; i < CONFIG_MAX_ROW_SIZE; i++) {
        for (int j = 0; j < CONFIG_MAX_COL_SIZE; j++) {
            if (getCell(Position{i,j}).attribute == goal) {
                destinations.push_back(Position{i,j});
            }
        }
    }
}


bool MouseController::anyDestinationCellSearched()
{
	for (int i = 0; i < destinations.size(); i++) {
		if (getDis(destinations[i].row, destinations[i].col) != CELL_DISTANCE_UNREACHED) {
			return true; /* return true if any of the destinations has been searched */
		}
	}
	return false;
}


bool MouseController::positionIsDestination(Position pos)
{
	for (int i = 0; i < destinations.size(); i++) {
		if ((pos == destinations[i]) ) {
			return true; /* return true if position found in destination vector*/
		}
	}
	return false;
}


bool MouseController::isInDestinationCell()
{
	/* return true if current position found in destination vector*/
	return positionIsDestination(getCurrentPos());
}


bool MouseController::allDestinationsReached()
{
	return destinations.empty();
}


bool MouseController::isInGoal()
{
    return (getCell(getCurrentPos()).attribute == goal) ? true : false;
}


bool MouseController::isInStart()
{
    return (getCell(getCurrentPos()).attribute == start) ? true : false;
}


void MouseController::printMaze()
{
    Maze::updateCell();
    mazeIO.setMousePosition(*this);
    mazeIO.setDestinations(destinations);
    Maze::printMaze();
}


void MouseController::printPathStack()
{
    void (PositionController::*pvFunc)(
            PositionController) = &PositionController::print;
    //printf("pathStack: ");
    pathStack.print(pvFunc);
    //printf("\n");
}


void MouseController::printAvailablePositionStack()
{
    //printf("availableStack: ");
    availablePositionStack.print(&PositionController::print);
    //printf("\n");
}


void MouseController::turnRight()
{
	/* Use MovingInterface */

	/* Call parent method */
	PositionController::turnRight();
}


void MouseController::turnLeft()
{
	/* Use MovingInterface */

	/* Call parent method */
	PositionController::turnLeft();
}


int MouseController::goForward()
{
	/* Call parent method */
	int ret = PositionController::goForward();
	/* Check if it is really OK to move */
	if (ret != COMMON_MAZE_SUCCESS) {
		return ret;
	}
	/* Use MovingInterface */
	// TODO: What if the mouse actually failed to move??
	return COMMON_MAZE_SUCCESS;
}
/*******************************************************************************
 * Private Methods
 ******************************************************************************/
Cell MouseController::getCell(Position pos)
{
    return Maze::getCell(pos.row, pos.col);
}


void MouseController::initDistance()
{
    int row;
    int col;
    //Fill the last
    for (row = 0; row < CONFIG_MAX_ROW_SIZE; row++) {
        for (col = 0; col < CONFIG_MAX_COL_SIZE; col++) {
            setDis(row, col, CELL_DISTANCE_UNREACHED);
        }
    }
}

/* TODO: Could be a bottleneck */
int MouseController::getHighestNeighbouringDistance(int row, int col)
{
    int tmp = CELL_DISTANCE_UNREACHED;
    int cmp;
    /* Check out of bounds first */
    if (MAZE_IS_POS_OUT_BOUNDS(row, col)) {
        return COMMON_MAZE_ERROR;
    }

    if (getWall(row, col, row_plus) != wall) {
        cmp = Maze::getDistance(row + 1, col);
        if (cmp > tmp) {
            tmp = cmp;
        }
    }
    if (getWall(row, col, col_plus) != wall) {
        cmp = getDis(row, col + 1);
        if (cmp > tmp) {
            tmp = cmp;
        }
    }
    if (getWall(row, col, row_minus) != wall) {
        cmp = getDis(row - 1, col);
        if (cmp > tmp) {
            tmp = cmp;
        }
    }
    if (getWall(row, col, col_minus) != wall) {
        cmp = getDis(row, col - 1);
        if (cmp > tmp) {
            tmp = cmp;
        }
    }
    return tmp;
}

Direction MouseController::getDirectionToGo()
{
    /* get the next position */
    PositionController nextPosition = pathStack.peekFromFront();
    return getNextDir(nextPosition);
}


void MouseController::setDirectionToGo ()
{
    // Then set
	setDir(getDirectionToGo());
}

/*******************************************************************************
 * Inline function definition
 ******************************************************************************/
int MouseController::getDis(int row, int col)
{
    return Maze::getDistance(row, col);
}

int MouseController::getDis(Position pos)
{
    return Maze::getDistance(pos.row, pos.col);
}

int MouseController::getDis(PositionController pos)
{
    Position position = pos.getCurrentPos();
    return Maze::getDistance(position.row, position.col);
}

int MouseController::getNextDis(PositionController pos, Direction dirTo)
{
    PositionController tmp = PositionController(pos.getCurrentPos(), dirTo);
    return getDis(tmp.getNextPos());
}

int MouseController::getNextDis(PositionController pos)
{
    return getDis(pos.getNextPos());
}

int MouseController::setDis(int row, int col, int dis)
{
    return Maze::setDistance(row, col, dis);
}

void MouseController::setDis(Position pos, int dis)
{
    setDis(pos.row, pos.col, dis);
}
