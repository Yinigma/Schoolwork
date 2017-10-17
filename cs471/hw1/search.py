# search.py
# ---------
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
from copy import deepcopy
from matplotlib.cbook import Null
from cgi import valid_boundary


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

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


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    "*** YOUR CODE HERE ***"
    """
    
    This is old stuff just in case the recursive solution doesn't pan out for whatever reason
    
    s = Directions.SOUTH
    w = Directions.WEST
    start = problem.getStartState()
    dfsStack = util.Stack()
    directionStack = util.Stack()
    dfsStack.push(start)
    visitList = []
    pathFound = False
    while not dfsStack.isEmpty():
        nextState = dfsStack.pop()
        visited = False
        #check to see if the next state has already been through
        for state in visitList:
            #compare coordinates of the next node to the ones in the visited list
            if state[0] == nextState[0] and state[1] == nextState[1]:
                visited = True
                break
        if not visited:
            visitList.append(nextState)
            for successor in problem.getSuccessors(nextState):
                dfsStack.push(successor[0])
                directionStack.push(successor[0])
                if problem.isGoalState(successor[0]):
                    pathFound = True
                    break
        if pathFound:
            print dfsStack
            break
    while not directionStack.isEmpty():
        print directionStack.pop()
    """
    dirStack = util.Stack()
    visitedList = []
    start = problem.getStartState()
    dfsRecursive(problem, start, visitedList, dirStack)
    dirList = []
    while not dirStack.isEmpty():
        dirList.insert(0, dirStack.pop())
    return  dirList
    

def dfsRecursive(problem, nextState, visitedList, dirStack):
    if problem.isGoalState(nextState):
        return True
    visitedList.append(nextState)
    for successor in problem.getSuccessors(nextState):
        visited = False
        for state in visitedList:
            #compare coordinates of the next node to the ones in the visited list
            if state == successor[0]:
                visited = True
                break
        if not visited:
            dirStack.push(successor[1])
            if not dfsRecursive(problem, successor[0], visitedList, dirStack):
                dirStack.pop()
            else:
                return True
    return False
            
def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    dirQ = util.Queue()
    root = (problem.getStartState(), [])
    dirQ.push(root)
    visitedList = [root[0]]
    while not dirQ.isEmpty():
        nextState = dirQ.pop()
        if problem.isGoalState(nextState[0]):
            return nextState[1]
        for successor in problem.getSuccessors(nextState[0]):
            visited = False
            for state in visitedList:
            #compare coordinates of the next node to the ones in the visited list
                if state == successor[0]:
                    visited = True
                    break
            if not visited:
                visitedList.append(successor[0])
                #Copy path to parent
                path = deepcopy(nextState[1])
                #Append direction
                path.append(successor[1])
                dirQ.push((successor[0], path))
                
    return []

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    fringe = util.PriorityQueue()
    root = (problem.getStartState(), [], 0)
    fringe.push(root, root[2])
    visitedList = [(root[0],0)]
    while not fringe.isEmpty():
        nextState = fringe.pop()
        if problem.isGoalState(nextState[0]):
            return nextState[1]
        for successor in problem.getSuccessors(nextState[0]):
            visited = False
            cost = nextState[2] + successor[2]
            for state in visitedList:
            #compare coordinates of the next node to the ones in the visited list
                if state[0] == successor[0] and state[1] < cost:
                    visited = True
                    break
            if not visited:
                visitedList.append((successor[0], cost))
                #Copy path to parent
                path = deepcopy(nextState[1])
                #Append direction
                path.append(successor[1])
                toPush = (successor[0], path, cost)
                fringe.push(toPush, toPush[2])
                
    return []

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
# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
