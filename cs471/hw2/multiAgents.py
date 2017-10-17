from cgi import valid_boundary
from matplotlib.cbook import Null
from cmath import sqrt
from numpy.matlib import rand
from numpy.random.mtrand import randint
2147483648# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions, AgentState
import random, util
from game import Actions
from copy import deepcopy

from game import Agent
from _sqlite3 import Row

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        
        "*** YOUR CODE HERE ***"
        numRows = 0
        for foodRow in newFood:
            numRows = numRows+1
        maxScore = numRows+len(newFood[0])+1
        mazeSize = numRows*len(newFood[0])
        
        row = 0
        col = 0
        minDist = maxScore
        minPoint = (-1,-1)
        for foodRow in newFood:
            for food in foodRow:
                if food:
                    point = (row, col)
                    dist = manhattanDistance(point, newPos)
                    if minDist>dist:
                        minPoint = point
                        minDist = dist
                col = col+1
            row = row+1
            col = 0
        
        distScore = maxScore-(manhattanDistance(minPoint, newPos))
        
        i = 0
        score = 0
        curPos = currentGameState.getPacmanPosition()
        for ghost in newGhostStates:
            if isAdjacent(newPos, ghost.getPosition()) or newPos==ghost.getPosition():
                if newScaredTimes[i]>1:
                    score = score+100
                return min(successorGameState.getScore()-10,-2)
            i = i + 1
        
        if newFood[newPos[0]][newPos[1]]==True:
            score = score + maxScore*2
        
        #if foodOnNextStep(successorGameState) and not action==Directions.STOP:
            #score = score + 10
        
        if not foodAdjacent(currentGameState):
            if action==Directions.RIGHT:
                    score = score + 1
            if curPos[1]%2==0:
                #print "even row:", curPos
                if action==Directions.RIGHT:
                    score = score + 1
                if action==Directions.LEFT:
                    score = score -1
                    
            if curPos[1]%2==1:
                #print "odd row:", curPos
                if action==Directions.LEFT:
                    score = score + 1
                if action==Directions.RIGHT:
                    score = score - 1
            if action==Directions.STOP:
                return -1
        
        capsules = currentGameState.getCapsules()
        for cap in capsules:
            if cap==newPos:
                score = score+80
        
        return score+maxScore*(mazeSize-successorGameState.getNumFood())+successorGameState.getScore()+distScore
    
def isAdjacent(pos0, pos1):
    if pos1[1]==pos0[1]:
        if pos1[0]==(pos0[0]+1):
            return True
        if pos1[0]==(pos0[0]-1):
            return True
    if pos1[0]==pos0[0]:
        if pos1[1]==(pos0[1]+1):
            return True
        if pos1[1]==(pos0[1]-1):
            return True
    return False
def foodOnNextStep(state):
    point = state.getPacmanPosition()
    newFood = state.getFood()
    if newFood[point[0]+1][point[1]]==True:
        return True
    if newFood[point[0]-1][point[1]]==True:
        return True
    if newFood[point[0]][point[1]+1]==True:
        return True
    if newFood[point[0]][point[1]-1]==True:
        return True
    return False

def foodAdjacent(state):
    if(foodOnNextStep(state)):
        return True
    point = state.getPacmanPosition()
    newFood = state.getFood()
    if newFood[point[0]+1][point[1]+1]==True:
        return True
    if newFood[point[0]-1][point[1]-1]==True:
        return True
    if newFood[point[0]-1][point[1]+1]==True:
        return True
    if newFood[point[0]+1][point[1]-1]==True:
        return True
    return False
    

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        maxVal = -100000000
        maxAction = Null
        successorActions = gameState.getLegalActions(0)
        for action in successorActions:
            val = self.recValue(gameState.generateSuccessor(0, action), self.depth, 1)
            if val > maxVal:
                maxVal = val
                maxAction = action
        return maxAction
            
        
    def recValue(self, gameState, depth, agentIndex):
        
        if agentIndex>gameState.getNumAgents()-1:
            depth = depth - 1
            agentIndex = 0
        successorActions = gameState.getLegalActions(agentIndex)
        if depth == 0 or not successorActions:
            return self.evaluationFunction(gameState)
        else:
            if self.isMaxAgent(agentIndex):
                maxVal = -100000000
                for action in successorActions:
                    val = self.recValue(gameState.generateSuccessor(agentIndex, action), depth, agentIndex + 1)
                    if val > maxVal:
                        maxVal = val
                return maxVal
            else:
                minVal = 100000000
                for action in successorActions:
                    val = self.recValue(gameState.generateSuccessor(agentIndex, action), depth, agentIndex + 1)
                    if val < minVal:
                        minVal = val
                return minVal
    def isMaxAgent(self, agentIndex):
        if agentIndex == 0:
            return True
        return False

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        
        alpha = -100000000
        beta = 100000000
        maxVal = -100000000
        maxAction = Null
        successorActions = gameState.getLegalActions(0)
        for action in successorActions:
            val = self.recValue(gameState.generateSuccessor(0, action), self.depth, 1, alpha, beta)
            if val > beta:
                return action
            if val > maxVal:
                maxVal = val
                maxAction = action
            alpha = max(val, alpha)
        return maxAction
            
        
        util.raiseNotDefined()
        
    def recValue(self, gameState, depth, agentIndex, alpha, beta):
        
        if agentIndex>gameState.getNumAgents()-1:
            depth = depth - 1
            agentIndex = 0
        successorActions = gameState.getLegalActions(agentIndex)
        if depth == 0 or not successorActions:
            return self.evaluationFunction(gameState)
        else:
            if self.isMaxAgent(agentIndex):
                maxVal = -100000000
                for action in successorActions:
                    val = self.recValue(gameState.generateSuccessor(agentIndex, action), depth, agentIndex + 1, alpha, beta)
                    if val > beta:
                        return val
                    maxVal = max(val, maxVal)
                    alpha = max(val, alpha)
                return maxVal
            else:
                minVal = 100000000
                for action in successorActions:
                    val = self.recValue(gameState.generateSuccessor(agentIndex, action), depth, agentIndex + 1, alpha, beta)
                    if val < alpha:
                        return val
                    minVal = min(val, minVal)
                    beta = min(val, beta)
                return minVal
    
    def isMaxAgent(self, agentIndex):
        if agentIndex == 0:
            return True
        return False

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        maxVal = -100000000
        maxAction = Null
        successorActions = gameState.getLegalActions(0)
        for action in successorActions:
            val = self.recValue(gameState.generateSuccessor(0, action), self.depth, 1)
            if val > maxVal:
                maxVal = val
                maxAction = action
        return maxAction
            
        
    def recValue(self, gameState, depth, agentIndex):
        
        if agentIndex>gameState.getNumAgents()-1:
            depth = depth - 1
            agentIndex = 0
        successorActions = gameState.getLegalActions(agentIndex)
        if depth == 0 or not successorActions:
            return self.evaluationFunction(gameState)
        else:
            if self.isMaxAgent(agentIndex):
                maxVal = -100000000
                for action in successorActions:
                    val = self.recValue(gameState.generateSuccessor(agentIndex, action), depth, agentIndex + 1)
                    if val > maxVal:
                        maxVal = val
                return maxVal
            else:
                space = float(len(successorActions))
                expected = 0.0
                for action in successorActions:
                    val = float(self.recValue(gameState.generateSuccessor(agentIndex, action), depth, agentIndex + 1))
                    expected = expected + val/space
                return expected
    def isMaxAgent(self, agentIndex):
        if agentIndex == 0:
            return True
        return False
    
def euclidDist(p0, p1):
    xDist = p0[0]-p1[0]
    yDist = p0[1]-p1[1]
    square = float(xDist*xDist+yDist*yDist)
    return sqrt(square)

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
      finds the closest food pellet and uses A* to get the cost to get to it
    """
    "*** YOUR CODE HERE ***"
    # Useful information you can extract from a GameState (pacman.py)
    newPos = currentGameState.getPacmanPosition()
    newFood = currentGameState.getFood()
    newGhostStates = currentGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
    capsules = currentGameState.getCapsules()
    numRows = 0
    for foodRow in newFood:
        numRows = numRows+1
    maxScore = numRows+len(newFood[0])+1
    mazeSize = numRows*len(newFood[0])
    
    i = 0
    for ghost in newGhostStates:
        if isAdjacent(newPos, ghost.getPosition()) or newPos==ghost.getPosition():
            if newScaredTimes[i]>1:
                "At ghost"
                return 10*(maxScore+1)*(mazeSize-remainingGubs(currentGameState))+(maxScore)+currentGameState.getScore()
            else:
                return -1
            i = i + 1

    ghostGoal = False
    i = 0
    minGDist = maxScore
    minGhost = (-1,-1)
    for time in newScaredTimes:
        if time>1:
            ghostGoal = True
            ghostPoint = newGhostStates[i].getPosition()
            dist = manhattanDistance(ghostPoint, newPos)
            if dist < minGDist:
                minGhost = ghostPoint
                minGDist = dist
    if ghostGoal:
        return (maxScore+1)*(mazeSize-remainingGubs(currentGameState))+(maxScore-manhattanDistance(minGhost, newPos))+currentGameState.getScore()

    row = 0
    col = 0
    minDist = maxScore
    minPoint = (-1,-1)
    for foodRow in newFood:
        for food in foodRow:
            point = (row, col)
            isCapsule = False
            for capsule in capsules:
                if point == capsule:
                    isCapsule=True
                    break
            if food or isCapsule:
                
                dist = manhattanDistance(point, newPos)
                if minDist>dist:
                    minPoint = point
                    minDist = dist
            col = col+1
        row = row+1
        col = 0
    
    
    psp = PositionSearchProblem(currentGameState, costFn = lambda x: 1, goal=minPoint, start=newPos, warn=False, visualize=False)
    path = aStarSearch(psp)
    cost = psp.getCostOfActions(path)
    score =  (maxScore+1)*(mazeSize-remainingGubs(currentGameState))+(maxScore-cost)+currentGameState.getScore()
    return score

def remainingGubs(gameState):
    
    caps = len(gameState.getCapsules())
    foods = gameState.getNumFood()
    return caps+foods

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    fringe = util.PriorityQueue()
    root = (problem.getStartState(), [], 0, heuristic(problem.getStartState(),problem))
    fringe.push(root, root[2]+root[3])
    visitedList = [(root[0],0,heuristic(problem.getStartState(),problem))]
    while not fringe.isEmpty():
        nextState = fringe.pop()
        if problem.isGoalState(nextState[0]):
            return nextState[1]
        for successor in problem.getSuccessors(nextState[0]):
            visited = False
            gcost = nextState[2] + successor[2]
            hcost = heuristic(successor[0], problem)
            for state in visitedList:
            #compare coordinates of the next node to the ones in the visited list
                if state[0] == successor[0] and state[1] + state[2] < hcost + gcost:
                    visited = True
                    break
            if not visited:
                visitedList.append((successor[0], gcost, hcost))
                #Copy path to parent
                path = deepcopy(nextState[1])
                #Append direction
                path.append(successor[1])
                toPush = (successor[0], path, gcost, hcost)
                fringe.push(toPush, toPush[2]+toPush[3])
    return []

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()

class PositionSearchProblem(SearchProblem):
    """
    A search problem defines the state space, start state, goal test, successor
    function and cost function.  This search problem can be used to find paths
    to a particular point on the pacman board.

    The state space consists of (x,y) positions in a pacman game.

    Note: this search problem is fully specified; you should NOT change it.
    """

    def __init__(self, gameState, costFn = lambda x: 1, goal=(1,1), start=None, warn=True, visualize=True):
        """
        Stores the start and goal.

        gameState: A GameState object (pacman.py)
        costFn: A function from a search state (tuple) to a non-negative number
        goal: A position in the gameState
        """
        self.walls = gameState.getWalls()
        self.startState = gameState.getPacmanPosition()
        if start != None: self.startState = start
        self.goal = goal
        self.costFn = costFn
        self.visualize = visualize
        if warn and (gameState.getNumFood() != 1 or not gameState.hasFood(*goal)):
            print 'Warning: this does not look like a regular search maze'

        # For display purposes
        self._visited, self._visitedlist, self._expanded = {}, [], 0 # DO NOT CHANGE

    def getStartState(self):
        return self.startState

    def isGoalState(self, state):
        isGoal = state == self.goal

        # For display purposes only
        if isGoal and self.visualize:
            self._visitedlist.append(state)
            import __main__
            if '_display' in dir(__main__):
                if 'drawExpandedCells' in dir(__main__._display): #@UndefinedVariable
                    __main__._display.drawExpandedCells(self._visitedlist) #@UndefinedVariable

        return isGoal

    def getSuccessors(self, state):
        """
        Returns successor states, the actions they require, and a cost of 1.

         As noted in search.py:
             For a given state, this should return a list of triples,
         (successor, action, stepCost), where 'successor' is a
         successor to the current state, 'action' is the action
         required to get there, and 'stepCost' is the incremental
         cost of expanding to that successor
        """

        successors = []
        for action in [Directions.NORTH, Directions.SOUTH, Directions.EAST, Directions.WEST]:
            x,y = state
            dx, dy = Actions.directionToVector(action)
            nextx, nexty = int(x + dx), int(y + dy)
            if not self.walls[nextx][nexty]:
                nextState = (nextx, nexty)
                cost = self.costFn(nextState)
                successors.append( ( nextState, action, cost) )

        # Bookkeeping for display purposes
        self._expanded += 1 # DO NOT CHANGE
        if state not in self._visited:
            self._visited[state] = True
            self._visitedlist.append(state)

        return successors

    def getCostOfActions(self, actions):
        """
        Returns the cost of a particular sequence of actions. If those actions
        include an illegal move, return 999999.
        """
        if actions == None: return 999999
        x,y= self.getStartState()
        cost = 0
        for action in actions:
            # Check figure out the next state and see whether its' legal
            dx, dy = Actions.directionToVector(action)
            x, y = int(x + dx), int(y + dy)
            if self.walls[x][y]: return 999999
            cost += self.costFn((x,y))
        return cost

# Abbreviation
better = betterEvaluationFunction

