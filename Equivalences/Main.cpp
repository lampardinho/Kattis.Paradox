#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

template<typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    out << "{";
    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last) 
            out << ", ";
    }
    out << "}";
    return out;
}

std::vector<bool> isVisited;
std::vector<size_t> components;
std::stack<size_t> visitedNodes;
std::vector< std::vector<size_t> > adjacencyList;
std::vector< std::vector<size_t> > reversedAdjacencyList;
std::vector<size_t> incomingComponentEdges;
std::vector<size_t> outgoingComponentEdges;

const size_t INVALID_COMPONENT = ~0;

void dfs(size_t node) 
{
	if (isVisited[node])
	{
		return;
	}

	isVisited[node] = true;

	for (size_t adjNode : adjacencyList[node])
	{
		dfs(adjNode);
	}

	visitedNodes.push(node);
}

void dfsReversed(size_t node, size_t stronglyConnectedComponent) 
{
	if (components[node] == INVALID_COMPONENT)
	{
		return;
	}

	components[node] = stronglyConnectedComponent;

	for (size_t adjNode : reversedAdjacencyList[node])
	{
		dfsReversed(adjNode, stronglyConnectedComponent);
	}
}

void countInOutEdges(size_t node)
{
	const size_t sourceComponent = components[node];

	for (size_t adjNode : adjacencyList[node])
	{		
		const size_t impliedComponent = components[adjNode];

		if (sourceComponent != impliedComponent)
		{
			outgoingComponentEdges[sourceComponent]++;
			incomingComponentEdges[impliedComponent]++;
		}
	}	
}

size_t runTest()
{
	size_t statementsCount = 0;
	size_t provedImplicationsCount = 0;
	std::cin >> statementsCount >> provedImplicationsCount;

	adjacencyList = std::vector< std::vector<size_t> >(statementsCount);
	reversedAdjacencyList = std::vector< std::vector<size_t> >(statementsCount);

	for (size_t i = 0; i < provedImplicationsCount; i++) 
	{
		size_t sourceStatement = 0;
		size_t impliedStatement = 0;
		std::cin >> sourceStatement >> impliedStatement;
		sourceStatement--; 
		impliedStatement--;
		adjacencyList[sourceStatement].push_back(impliedStatement);
		reversedAdjacencyList[impliedStatement].push_back(sourceStatement);
	}
				
	isVisited = std::vector<bool>(statementsCount, false);
	for (size_t i = 0; i < statementsCount; i++)
	{
		dfs(i);
	}

	components = std::vector<size_t>(statementsCount, INVALID_COMPONENT);
	size_t stronglyConnectedComponentsCount = 0;
	while (!visitedNodes.empty())
	{
		const size_t node = visitedNodes.top();			
		visitedNodes.pop();
		
		dfsReversed(node, stronglyConnectedComponentsCount++);
	}

	if (stronglyConnectedComponentsCount == 1) 
	{
		return 0;
	}

	incomingComponentEdges = std::vector<size_t>(stronglyConnectedComponentsCount, 0);
	outgoingComponentEdges = std::vector<size_t>(stronglyConnectedComponentsCount, 0);

	for (size_t i = 0; i < statementsCount; i++)
	{
		countInOutEdges(i);
	}

	size_t componentsWithoutIncomingEdgesCount = 0;
	size_t componentsWithoutOutgoingEdgesCount = 0;
	for (size_t i = 0; i < stronglyConnectedComponentsCount; i++) 
	{
		if (incomingComponentEdges[i] == 0)
		{
			componentsWithoutIncomingEdgesCount++;
		}

		if (outgoingComponentEdges[i] == 0) 
		{
			componentsWithoutOutgoingEdgesCount++; 
		}
	}
	
	return std::max(componentsWithoutIncomingEdgesCount, componentsWithoutOutgoingEdgesCount);
}

int main() 
{
	size_t testsCount = 0;
	std::cin >> testsCount;

	for (size_t test = 0; test < testsCount; test++)
	{
		std::cout << runTest() << std::endl;
	}

	return 0;
}